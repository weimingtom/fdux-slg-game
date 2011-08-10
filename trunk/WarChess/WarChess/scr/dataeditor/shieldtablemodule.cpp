#include "shieldtablemodule.h"
#include "DataManager.h"
#include "shieldmanager.h"

#define SHILEDMANAGER() DataManager::getSingleton().mShieldManager

const int ShieldTableColumnCount = 12; 

ShieldTableModule::ShieldTableModule(QObject *parent)
: QAbstractTableModel(parent)
{

}

ShieldTableModule::~ShieldTableModule()
{

}

int ShieldTableModule::columnCount(const QModelIndex &parent /* = QModelIndex */) const
{
	return ShieldTableColumnCount;
}

int ShieldTableModule::rowCount(const QModelIndex &parent /* = QModelIndex */) const
{
	return SHILEDMANAGER()->GetNum();
}

QVariant ShieldTableModule::data(const QModelIndex &index, int role /* = Qt::DisplayRole */) const
{
	if(!index.isValid() || role != Qt::DisplayRole)
		return QVariant();

	std::wstring id = SHILEDMANAGER()->GetID(index.row());
	switch(index.column())
	{
	case 0:
		return QString::fromStdWString(id);
	case 1:
		return QString::fromStdWString(SHILEDMANAGER()->GetName(id));
	case 2:
		return QString::fromStdWString(SHILEDMANAGER()->GetDescription(id));
	case 3:
		return QString::number(SHILEDMANAGER()->GetValue(id));
	case 4:
		return QString::number(SHILEDMANAGER()->GetAttr(id,ATTR_ATTACK));
	case 5:
		return QString::number(SHILEDMANAGER()->GetAttr(id,ATTR_DEFENSE));
	case 6:
		return QString::number(SHILEDMANAGER()->GetAttr(id,ATTR_FORMATION));
	case 7:
		return QString::number(SHILEDMANAGER()->GetAttr(id,ATTR_INITIATIVE));
	case 8:
		return QString::number(SHILEDMANAGER()->GetAttr(id,ATTR_ACTIONPOINT));
	case 9:
		return QString::number(SHILEDMANAGER()->GetAttr(id,ATTR_COVERT));
	case 10:
		return QString::fromStdWString(SHILEDMANAGER()->GetModuleName(id));
	case 11:
		return QString::fromStdWString(SHILEDMANAGER()->GetScriptName(id));
	default:
		return QVariant();
	}
}

QVariant ShieldTableModule::headerData(int section, Qt::Orientation orientation, int role /* = Qt::DisplayRole */) const
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
			return QString("防御值");
		case 6:
			return QString("阵列值");
		case 7:
			return QString("先攻值");
		case 8:
			return QString("行动值");
		case 9:
			return QString("隐蔽值");
		case 10:
			return QString("模型名称");
		case 11:
			return QString("脚本名称");
		default:
			return QVariant();
		}
	}
	else
		return QString("%1").arg(section);
}

bool ShieldTableModule::insertRow(int row, const QModelIndex & parent /* = QModelIndex */)
{
	beginInsertRows(parent, SHILEDMANAGER()->GetNum(),SHILEDMANAGER()->GetNum());
	SHILEDMANAGER()->AddShield();
	endInsertRows();
	return true;
}

bool ShieldTableModule::removeRow(int row, const QModelIndex & parent /* = QModelIndex */)
{
	beginRemoveRows(parent, row, row);
	std::wstring id = SHILEDMANAGER()->GetID(row);
	SHILEDMANAGER()->DelShield(id);
	endRemoveRows();
	return true;
}

Qt::ItemFlags ShieldTableModule::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return Qt::ItemIsEnabled;

	return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
}

bool ShieldTableModule::setData(const QModelIndex &index, const QVariant &qvalue,int role /* = Qt::EditRole */)
{
	if (index.isValid() && role == Qt::EditRole) 
	{
		std::wstring id = SHILEDMANAGER()->GetID(index.row());
		switch(index.column())
		{
		case 0:
			return SHILEDMANAGER()->SetID(id, qvalue.toString().toStdWString());
		case 1:
			return SHILEDMANAGER()->SetName(id, qvalue.toString().toStdWString());
		case 2:
			return SHILEDMANAGER()->SetDescription(id, qvalue.toString().toStdWString());
		case 3:
			return SHILEDMANAGER()->SetValue(id,qvalue.toInt());
		case 4:
			return SHILEDMANAGER()->SetAttr(id,ATTR_ATTACK,qvalue.toInt());
		case 5:
			return SHILEDMANAGER()->SetAttr(id,ATTR_DEFENSE,qvalue.toInt());
		case 6:
			return SHILEDMANAGER()->SetAttr(id,ATTR_FORMATION,qvalue.toInt());
		case 7:
			return SHILEDMANAGER()->SetAttr(id,ATTR_INITIATIVE,qvalue.toInt());
		case 8:
			return SHILEDMANAGER()->SetAttr(id,ATTR_ACTIONPOINT,qvalue.toInt());
		case 9:
			return SHILEDMANAGER()->SetAttr(id,ATTR_COVERT,qvalue.toInt());
		case 10:
			return SHILEDMANAGER()->SetModuleName(id,qvalue.toString().toStdWString());
		case 11:
			return SHILEDMANAGER()->SetScriptName(id,qvalue.toString().toStdWString());
		default:
			return false;
		}
	}
	return false;
}