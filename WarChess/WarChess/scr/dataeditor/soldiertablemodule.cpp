#include "soldiertablemodule.h"
#include "DataManager.h"
#include "soldiermanager.h"

#define SOLDIERMANAGER() DataManager::getSingleton().mSoldierManager

const int SoldierTableColumnCount = 16; 

SoldierTableModule::SoldierTableModule(QObject *parent)
	: QAbstractTableModel(parent)
{

}

SoldierTableModule::~SoldierTableModule()
{

}

int SoldierTableModule::columnCount(const QModelIndex &parent /* = QModelIndex */) const
{
	return SoldierTableColumnCount;
}

int SoldierTableModule::rowCount(const QModelIndex &parent /* = QModelIndex */) const
{
	return SOLDIERMANAGER()->GetNum();
}

QVariant SoldierTableModule::data(const QModelIndex &index, int role /* = Qt::DisplayRole */) const
{
	if(!index.isValid() || role != Qt::DisplayRole)
		return QVariant();

	std::wstring id = SOLDIERMANAGER()->GetID(index.row());
	switch(index.column())
	{
	case 0:
		return QString::fromStdWString(id);
	case 1:
		return QString::fromStdWString(SOLDIERMANAGER()->GetName(id));
	case 2:
		return QString::fromStdWString(SOLDIERMANAGER()->GetDescription(id));
	case 3:
		return QString::number(SOLDIERMANAGER()->GetValue(id));
	case 4:
		return QString::number(SOLDIERMANAGER()->GetAttr(id,ATTR_ATTACK));
	case 5:
		return QString::number(SOLDIERMANAGER()->GetAttr(id,ATTR_RANGEDATTACK));
	case 6:
		return QString::number(SOLDIERMANAGER()->GetAttr(id,ATTR_DEFENSE));
	case 7:
		return QString::number(SOLDIERMANAGER()->GetAttr(id,ATTR_FORMATION));
	case 8:
		return QString::number(SOLDIERMANAGER()->GetAttr(id,ATTR_INITIATIVE));
	case 9:
		return QString::number(SOLDIERMANAGER()->GetAttr(id,ATTR_ACTIONPOINT));
	case 10:
		return QString::number(SOLDIERMANAGER()->GetAttr(id,ATTR_DETECTION));
	case 11:
		return QString::number(SOLDIERMANAGER()->GetAttr(id,ATTR_COVERT));
	case 12:
		return QString::number(SOLDIERMANAGER()->GetAttr(id,ATTR_INJURY));
	case 13:
		return QString::number(SOLDIERMANAGER()->GetAttr(id,ATTR_COUNTER));
	case 14:
		return QString::fromStdWString(SOLDIERMANAGER()->GetScriptName(id));
	case 15:
		return QString::number(SOLDIERMANAGER()->GetInjury(id));
	default:
		return QVariant();
	}
}

QVariant SoldierTableModule::headerData(int section, Qt::Orientation orientation, int role /* = Qt::DisplayRole */) const
{
	if (role != Qt::DisplayRole)
		return QVariant();
	if (orientation == Qt::Horizontal)
	{
		switch(section)
		{
		case 0:
			return QString("ID");
		case 1:
			return QString("名称");
		case 2:
			return QString("描述");
		case 3:
			return QString("价值");
		case 4:
			return QString("攻击值");
		case 5:
			return QString("远程攻击值");
		case 6:
			return QString("防御值");
		case 7:
			return QString("阵列值");
		case 8:
			return QString("先攻值");
		case 9:
			return QString("行动值");
		case 10:
			return QString("侦查值");
		case 11:
			return QString("隐蔽值");
		case 12:
			return QString("伤者能力系数(*0.01)");
		case 13:
			return QString("反击系数(*0.01)");
		case 14:
			return QString("脚本名称");
		case 15:
			return QString("是否会受伤");
		default:
			return QVariant();
		}
	}
	else
		return QString("%1").arg(section);
}

bool SoldierTableModule::insertRow(int row, const QModelIndex & parent /* = QModelIndex */)
{
	beginInsertRows(parent, SOLDIERMANAGER()->GetNum(),SOLDIERMANAGER()->GetNum());
	SOLDIERMANAGER()->AddSoldier();
	endInsertRows();
	return true;
}

bool SoldierTableModule::removeRow(int row, const QModelIndex & parent /* = QModelIndex */)
{
	beginRemoveRows(parent, row, row);
	std::wstring id = SOLDIERMANAGER()->GetID(row);
	SOLDIERMANAGER()->DelSoldier(id);
	endRemoveRows();
	return true;
}

Qt::ItemFlags SoldierTableModule::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return Qt::ItemIsEnabled;

	return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
}

bool SoldierTableModule::setData(const QModelIndex &index, const QVariant &qvalue,int role /* = Qt::EditRole */)
{
	if (index.isValid() && role == Qt::EditRole) 
	{
		std::wstring id = SOLDIERMANAGER()->GetID(index.row());
		switch(index.column())
		{
		case 0:
			return SOLDIERMANAGER()->SetID(id, qvalue.toString().toStdWString());
		case 1:
			return SOLDIERMANAGER()->SetName(id, qvalue.toString().toStdWString());
		case 2:
			return SOLDIERMANAGER()->SetDescription(id, qvalue.toString().toStdWString());
		case 3:
			return SOLDIERMANAGER()->SetValue(id,qvalue.toInt());
		case 4:
			return SOLDIERMANAGER()->SetAttr(id,ATTR_ATTACK,qvalue.toInt());
		case 5:
			return SOLDIERMANAGER()->SetAttr(id,ATTR_RANGEDATTACK,qvalue.toInt());
		case 6:
			return SOLDIERMANAGER()->SetAttr(id,ATTR_DEFENSE,qvalue.toInt());
		case 7:
			return SOLDIERMANAGER()->SetAttr(id,ATTR_FORMATION,qvalue.toInt());
		case 8:
			return SOLDIERMANAGER()->SetAttr(id,ATTR_INITIATIVE,qvalue.toInt());
		case 9:
			return SOLDIERMANAGER()->SetAttr(id,ATTR_ACTIONPOINT,qvalue.toInt());
		case 10:
			return SOLDIERMANAGER()->SetAttr(id,ATTR_DETECTION,qvalue.toInt());
		case 11:
			return SOLDIERMANAGER()->SetAttr(id,ATTR_COVERT,qvalue.toInt());
		case 12:
			return SOLDIERMANAGER()->SetAttr(id,ATTR_INJURY,qvalue.toInt());
		case 13:
			return SOLDIERMANAGER()->SetAttr(id,ATTR_COUNTER,qvalue.toInt());
		case 14:
			return SOLDIERMANAGER()->SetScriptName(id,qvalue.toString().toStdWString());
		case 15:
			return SOLDIERMANAGER()->SetInjury(id,qvalue.toInt());
		default:
			return false;
		}
	}
	return false;
}