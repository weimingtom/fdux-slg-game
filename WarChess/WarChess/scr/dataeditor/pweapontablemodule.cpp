#include "pweapontablemodule.h"
#include "DataManager.h"
#include "pweaponmanager.h"

//#define PWEAPONMANAGER() DataManager::getSingleton().mPWeaponManager

const int PWeaponTableColumnCount = 15; 

PWeaponTableModule::PWeaponTableModule(QObject *parent)
: QAbstractTableModel(parent)
{

}

PWeaponTableModule::~PWeaponTableModule()
{

}

int PWeaponTableModule::columnCount(const QModelIndex &parent /* = QModelIndex */) const
{
	return PWeaponTableColumnCount;
}

int PWeaponTableModule::rowCount(const QModelIndex &parent /* = QModelIndex */) const
{
	return DATAMANAGER().GetCount(PWEAPON_TAG);
}

QVariant PWeaponTableModule::data(const QModelIndex &index, int role /* = Qt::DisplayRole */) const
{
	if(!index.isValid() || role != Qt::DisplayRole)
		return QVariant();

	std::wstring id = DATAMANAGER().GetID(PWEAPON_TAG, index.row());
	switch(index.column())
	{
	case 0:
		return QString::fromStdWString(id);
	case 1:
		return QString::fromStdWString(DATAMANAGER().GetLangStr(PWEAPON_TAG, id, NAME_TAG));
	case 2:
		return QString::fromStdWString(DATAMANAGER().GetLangStr(PWEAPON_TAG, id, DESCRIPTION_TAG));
	case 3:
		return  QString::number(DATAMANAGER().GetInt(PWEAPON_TAG, id, VALUE_TAG));
	case 4:
		return  QString::number(DATAMANAGER().GetInt(PWEAPON_TAG, id, TYPE_TAG));
	case 5:
		return QString::number(DATAMANAGER().GetAttribute(PWEAPON_TAG, id, ATTR_ATTACK));
	case 6:
		return QString::number(DATAMANAGER().GetAttribute(PWEAPON_TAG, id, ATTR_DEFENSE));
	case 7:
		return QString::number(DATAMANAGER().GetAttribute(PWEAPON_TAG, id, ATTR_FORMATION));
	case 8:
		return QString::number(DATAMANAGER().GetAttribute(PWEAPON_TAG, id, ATTR_INITIATIVE));
	case 9:
		return QString::number(DATAMANAGER().GetAttribute(PWEAPON_TAG, id, ATTR_ACTIONPOINT));
	case 10:
		return QString::number(DATAMANAGER().GetAttribute(PWEAPON_TAG, id, ATTR_COVERT));
	case 11:
		return QString::fromStdWString(DATAMANAGER().GetDataStr(PWEAPON_TAG, id, MESH_TAG));
	case 12:
		return QString::fromStdWString(DATAMANAGER().GetDataStr(PWEAPON_TAG, id, MAT_TAG));
	case 13:
		return QString::fromStdWString(DATAMANAGER().GetDataStr(PWEAPON_TAG, id, ANIGROUP_TAG));
	case 14:
		return QString::fromStdWString(DATAMANAGER().GetDataStr(PWEAPON_TAG, id, SCRIPT_TAG));
	default:
		return QVariant();
	}
}

QVariant PWeaponTableModule::headerData(int section, Qt::Orientation orientation, int role /* = Qt::DisplayRole */) const
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
			return QString("攻击值");
		case 6:
			return QString("防御值");
		case 7:
			return QString("阵列值");
		case 8:
			return QString("先攻值");
		case 9:
			return QString("行动值");
		case 10:
			return QString("隐蔽值");
		case 11:
			return QString("模型名称");
		case 12:
			return QString("材质名称");
		case 13:
			return QString("动画组名称");
		case 14:
			return QString("脚本名称");
		default:
			return QVariant();
		}
	}
	else
		return QString("%1").arg(section);
}

bool PWeaponTableModule::insertRow(int row, const QModelIndex & parent /* = QModelIndex */)
{
	beginInsertRows(parent, DATAMANAGER().GetCount(PWEAPON_TAG),DATAMANAGER().GetCount(PWEAPON_TAG));
	DATAMANAGER().AddPrimaryWeapon();
	endInsertRows();
	return true;
}

bool PWeaponTableModule::removeRow(int row, const QModelIndex & parent /* = QModelIndex */)
{
	beginRemoveRows(parent, row, row);
	std::wstring id = DATAMANAGER().GetID(PWEAPON_TAG, row);
	DATAMANAGER().RemoveData(PWEAPON_TAG, id);
	endRemoveRows();
	return true;
}

Qt::ItemFlags PWeaponTableModule::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return Qt::ItemIsEnabled;

	return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
}

bool PWeaponTableModule::setData(const QModelIndex &index, const QVariant &qvalue,int role /* = Qt::EditRole */)
{
	if (index.isValid() && role == Qt::EditRole) 
	{
		std::wstring id = DATAMANAGER().GetID(PWEAPON_TAG, index.row());
		switch(index.column())
		{
		case 0:
			return DATAMANAGER().SetID(PWEAPON_TAG, id, qvalue.toString().toStdWString());
		case 1:
			return DATAMANAGER().SetLangStr(PWEAPON_TAG, id, NAME_TAG, qvalue.toString().toStdWString());
		case 2:
			return DATAMANAGER().SetLangStr(PWEAPON_TAG, id, DESCRIPTION_TAG, qvalue.toString().toStdWString());
		case 3:
			return DATAMANAGER().SetInt(PWEAPON_TAG, id, VALUE_TAG, qvalue.toInt());
		case 4:
			return DATAMANAGER().SetInt(PWEAPON_TAG, id, TYPE_TAG, qvalue.toInt());
		case 5:
			return DATAMANAGER().SetAttribute(PWEAPON_TAG, id, ATTR_ATTACK, qvalue.toInt());
		case 6:
			return DATAMANAGER().SetAttribute(PWEAPON_TAG, id, ATTR_DEFENSE, qvalue.toInt());
		case 7:
			return DATAMANAGER().SetAttribute(PWEAPON_TAG, id, ATTR_FORMATION, qvalue.toInt());
		case 8:
			return DATAMANAGER().SetAttribute(PWEAPON_TAG, id, ATTR_INITIATIVE, qvalue.toInt());
		case 9:
			return DATAMANAGER().SetAttribute(PWEAPON_TAG, id, ATTR_ACTIONPOINT,qvalue.toInt());
		case 10:
			return DATAMANAGER().SetAttribute(PWEAPON_TAG, id, ATTR_COVERT, qvalue.toInt());
		case 11:
			return DATAMANAGER().SetDataStr(PWEAPON_TAG, id, MESH_TAG, qvalue.toString().toStdWString());
		case 12:
			return DATAMANAGER().SetDataStr(PWEAPON_TAG, id, MAT_TAG, qvalue.toString().toStdWString());
		case 13:
			return DATAMANAGER().SetDataStr(PWEAPON_TAG, id, ANIGROUP_TAG, qvalue.toString().toStdWString());
		case 14:
			return DATAMANAGER().SetDataStr(PWEAPON_TAG, id, SCRIPT_TAG, qvalue.toString().toStdWString());
		default:
			return false;
		}
	}
	return false;
}