#include "sweapontablemodule.h"
#include "DataManager.h"
#include "sweaponmanager.h"

#define SWEAPONMANAGER() DataManager::getSingleton().mSWeaponManager

const int SWeaponTableColumnCount = 14; 

SWeaponTableModule::SWeaponTableModule(QObject *parent)
: QAbstractTableModel(parent)
{

}

SWeaponTableModule::~SWeaponTableModule()
{

}

int SWeaponTableModule::columnCount(const QModelIndex &parent /* = QModelIndex */) const
{
	return SWeaponTableColumnCount;
}

int SWeaponTableModule::rowCount(const QModelIndex &parent /* = QModelIndex */) const
{
	return SWEAPONMANAGER()->GetNum();
}

QVariant SWeaponTableModule::data(const QModelIndex &index, int role /* = Qt::DisplayRole */) const
{
	if(!index.isValid() || role != Qt::DisplayRole)
		return QVariant();

	std::wstring id = SWEAPONMANAGER()->GetID(index.row());
	switch(index.column())
	{
	case 0:
		return QString::fromStdWString(id);
	case 1:
		return QString::fromStdWString(SWEAPONMANAGER()->GetName(id));
	case 2:
		return QString::fromStdWString(SWEAPONMANAGER()->GetDescription(id));
	case 3:
		return  QString::number(SWEAPONMANAGER()->GetValue(id));
	case 4:
		return  QString::number(SWEAPONMANAGER()->GetSWeaponType(id));
	case 5:
		return QString::number(SWEAPONMANAGER()->GetAttr(id,ATTR_RANGEDATTACK));
	case 6:
		return QString::number(SWEAPONMANAGER()->GetRange(id));
	case 7:
		return QString::number(SWEAPONMANAGER()->GetAttr(id,ATTR_DEFENSE));
	case 8:
		return QString::number(SWEAPONMANAGER()->GetAttr(id,ATTR_ACTIONPOINT));
	case 9:
		return QString::number(SWEAPONMANAGER()->GetAttr(id,ATTR_COVERT));
	case 10:
		return QString::fromStdWString(SWEAPONMANAGER()->GetModuleName(id));
	case 11:
		return QString::fromStdWString(SWEAPONMANAGER()->GetIdleAnimName(id));
	case 12:
		return QString::fromStdWString(SWEAPONMANAGER()->GetActAnimName(id));
	case 13:
		return QString::fromStdWString(SWEAPONMANAGER()->GetScriptName(id));
	default:
		return QVariant();
	}
}

QVariant SWeaponTableModule::headerData(int section, Qt::Orientation orientation, int role /* = Qt::DisplayRole */) const
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
			return QString("武器类型");
		case 5:
			return QString("远程攻击值");
		case 6:
			return QString("射程");
		case 7:
			return QString("防御值");
		case 8:
			return QString("行动值");
		case 9:
			return QString("隐蔽值");
		case 10:
			return QString("模型名称");
		case 11:
			return QString("持有动作名称");
		case 12:
			return QString("攻击动作名称");
		case 13:
			return QString("脚本名称");
		default:
			return QVariant();
		}
	}
	else
		return QString("%1").arg(section);
}

bool SWeaponTableModule::insertRow(int row, const QModelIndex & parent /* = QModelIndex */)
{
	beginInsertRows(parent, SWEAPONMANAGER()->GetNum(),SWEAPONMANAGER()->GetNum());
	SWEAPONMANAGER()->AddSWeapon();
	endInsertRows();
	return true;
}

bool SWeaponTableModule::removeRow(int row, const QModelIndex & parent /* = QModelIndex */)
{
	beginRemoveRows(parent, row, row);
	std::wstring id = SWEAPONMANAGER()->GetID(row);
	SWEAPONMANAGER()->DelSWeapon(id);
	endRemoveRows();
	return true;
}

Qt::ItemFlags SWeaponTableModule::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return Qt::ItemIsEnabled;

	return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
}

bool SWeaponTableModule::setData(const QModelIndex &index, const QVariant &qvalue,int role /* = Qt::EditRole */)
{
	if (index.isValid() && role == Qt::EditRole) 
	{
		std::wstring id = SWEAPONMANAGER()->GetID(index.row());
		switch(index.column())
		{
		case 0:
			return SWEAPONMANAGER()->SetID(id, qvalue.toString().toStdWString());
		case 1:
			return SWEAPONMANAGER()->SetName(id, qvalue.toString().toStdWString());
		case 2:
			return SWEAPONMANAGER()->SetDescription(id, qvalue.toString().toStdWString());
		case 3:
			return SWEAPONMANAGER()->SetValue(id,qvalue.toInt());
		case 4:
			return SWEAPONMANAGER()->SetSWeaponType(id,qvalue.toInt());
		case 5:
			return SWEAPONMANAGER()->SetAttr(id,ATTR_RANGEDATTACK,qvalue.toInt());
		case 6:
			return SWEAPONMANAGER()->SetRange(id,qvalue.toInt());
		case 7:
			return SWEAPONMANAGER()->SetAttr(id,ATTR_DEFENSE,qvalue.toInt());
		case 8:
			return SWEAPONMANAGER()->SetAttr(id,ATTR_ACTIONPOINT,qvalue.toInt());
		case 9:
			return SWEAPONMANAGER()->SetAttr(id,ATTR_COVERT,qvalue.toInt());
		case 10:
			return SWEAPONMANAGER()->SetModuleName(id,qvalue.toString().toStdWString());
		case 11:
			return SWEAPONMANAGER()->SetIdleAnimName(id,qvalue.toString().toStdWString());
		case 12:
			return SWEAPONMANAGER()->SetActAnimName(id,qvalue.toString().toStdWString());
		case 13:
			return SWEAPONMANAGER()->SetScriptName(id,qvalue.toString().toStdWString());
		default:
			return false;
		}
	}
	return false;
}