#include "sweapontablemodule.h"
#include "DataManager.h"
#include "sweaponmanager.h"

//#define SWEAPONMANAGER() DataManager::getSingleton().mSWeaponManager

const int SWeaponTableColumnCount = 15; 

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
	return DATAMANAGER().GetCount(SWEAPON_TAG);
}

QVariant SWeaponTableModule::data(const QModelIndex &index, int role /* = Qt::DisplayRole */) const
{
	if(!index.isValid() || role != Qt::DisplayRole)
		return QVariant();

	std::wstring id = DATAMANAGER().GetID(SWEAPON_TAG, index.row());
	switch(index.column())
	{
	case 0:
		return QString::fromStdWString(id);
	case 1:
		return QString::fromStdWString(DATAMANAGER().GetLangStr(SWEAPON_TAG, id, NAME_TAG));
	case 2:
		return QString::fromStdWString(DATAMANAGER().GetLangStr(SWEAPON_TAG, id, DESCRIPTION_TAG));
	case 3:
		return  QString::number(DATAMANAGER().GetInt(SWEAPON_TAG, id, VALUE_TAG));
	case 4:
		return  QString::number(DATAMANAGER().GetInt(SWEAPON_TAG, id, TYPE_TAG));
	case 5:
		return QString::number(DATAMANAGER().GetAttribute(SWEAPON_TAG, id, ATTR_RANGEDATTACK));
	case 6:
		return QString::number(DATAMANAGER().GetInt(SWEAPON_TAG, id, MAXRANGE_TAG));
	case 7:
		return QString::number(DATAMANAGER().GetInt(SWEAPON_TAG, id, MINRANGE_TAG));
	case 8:
		return QString::number(DATAMANAGER().GetAttribute(SWEAPON_TAG, id, ATTR_DEFENSE));
	case 9:
		return QString::number(DATAMANAGER().GetAttribute(SWEAPON_TAG, id, ATTR_ACTIONPOINT));
	case 10:
		return QString::number(DATAMANAGER().GetAttribute(SWEAPON_TAG, id, ATTR_COVERT));
	case 11:
		return QString::fromStdWString(DATAMANAGER().GetDataStr(SWEAPON_TAG, id, MESH_TAG));
	case 12:
		return QString::fromStdWString(DATAMANAGER().GetDataStr(SWEAPON_TAG, id, MAT_TAG));
	case 13:
		return QString::fromStdWString(DATAMANAGER().GetDataStr(SWEAPON_TAG, id, ANIGROUP_TAG));
	case 14:
		return QString::fromStdWString(DATAMANAGER().GetDataStr(SWEAPON_TAG, id, SCRIPT_TAG));
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
			return QString("最大射程");
		case 7:
			return QString("最小射程");
		case 8:
			return QString("防御值");
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

bool SWeaponTableModule::insertRow(int row, const QModelIndex & parent /* = QModelIndex */)
{
	beginInsertRows(parent, DATAMANAGER().GetCount(SWEAPON_TAG), DATAMANAGER().GetCount(SWEAPON_TAG));
	DATAMANAGER().AddSecondaryWeapon();
	endInsertRows();
	return true;
}

bool SWeaponTableModule::removeRow(int row, const QModelIndex & parent /* = QModelIndex */)
{
	beginRemoveRows(parent, row, row);
	std::wstring id = DATAMANAGER().GetID(SWEAPON_TAG, row);
	DATAMANAGER().RemoveData(SWEAPON_TAG, id);
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
		std::wstring id = DATAMANAGER().GetID(SWEAPON_TAG, index.row());
		switch(index.column())
		{
		case 0:
			return DATAMANAGER().SetID(SWEAPON_TAG, id, qvalue.toString().toStdWString());
		case 1:
			return DATAMANAGER().SetLangStr(SWEAPON_TAG, id, NAME_TAG, qvalue.toString().toStdWString());
		case 2:
			return DATAMANAGER().SetLangStr(SWEAPON_TAG, id, DESCRIPTION_TAG, qvalue.toString().toStdWString());
		case 3:
			return DATAMANAGER().SetInt(SWEAPON_TAG, id, VALUE_TAG, qvalue.toInt());
		case 4:
			return DATAMANAGER().SetInt(SWEAPON_TAG, id, TYPE_TAG, qvalue.toInt());
		case 5:
			return DATAMANAGER().SetAttribute(SWEAPON_TAG, id, ATTR_RANGEDATTACK, qvalue.toInt());
		case 6:
			return DATAMANAGER().SetInt(SWEAPON_TAG, id, MAXRANGE_TAG, qvalue.toInt());
		case 7:
			return DATAMANAGER().SetInt(SWEAPON_TAG, id, MINRANGE_TAG, qvalue.toInt());
		case 8:
			return DATAMANAGER().SetAttribute(SWEAPON_TAG, id, ATTR_DEFENSE, qvalue.toInt());
		case 9:
			return DATAMANAGER().SetAttribute(SWEAPON_TAG, id, ATTR_ACTIONPOINT, qvalue.toInt());
		case 10:
			return DATAMANAGER().SetAttribute(SWEAPON_TAG, id, ATTR_COVERT, qvalue.toInt());
		case 11:
			return DATAMANAGER().SetDataStr(SWEAPON_TAG, id, MESH_TAG, qvalue.toString().toStdWString());
		case 12:
			return DATAMANAGER().SetDataStr(SWEAPON_TAG, id, MAT_TAG, qvalue.toString().toStdWString());
		case 13:
			return DATAMANAGER().SetDataStr(SWEAPON_TAG, id, ANIGROUP_TAG, qvalue.toString().toStdWString());
		case 14:
			return DATAMANAGER().SetDataStr(SWEAPON_TAG, id, SCRIPT_TAG, qvalue.toString().toStdWString());
		default:
			return false;
		}
	}
	return false;
}