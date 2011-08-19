#include "soldiertablemodule.h"
#include "DataManager.h"
#include "soldiermanager.h"

//#define SOLDIERMANAGER() DataManager::getSingleton().mSoldierManager

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
	return DATAMANAGER().GetCount(SOLDIER_TAG);
}

QVariant SoldierTableModule::data(const QModelIndex &index, int role /* = Qt::DisplayRole */) const
{
	if(!index.isValid() || role != Qt::DisplayRole)
		return QVariant();

	std::wstring id = DATAMANAGER().GetID(SOLDIER_TAG, index.row());
	switch(index.column())
	{
	case 0:
		return QString::fromStdWString(id);
	case 1:
		return QString::fromStdWString(DATAMANAGER().GetLangStr(SOLDIER_TAG, id, NAME_TAG));
	case 2:
		return QString::fromStdWString(DATAMANAGER().GetLangStr(SOLDIER_TAG, id, DESCRIPTION_TAG));
	case 3:
		return QString::number(DATAMANAGER().GetInt(SOLDIER_TAG, id, VALUE_TAG));
	case 4:
		return QString::number(DATAMANAGER().GetAttribute(SOLDIER_TAG, id, ATTR_ATTACK));
	case 5:
		return QString::number(DATAMANAGER().GetAttribute(SOLDIER_TAG, id, ATTR_RANGEDATTACK));
	case 6:
		return QString::number(DATAMANAGER().GetAttribute(SOLDIER_TAG, id, ATTR_DEFENSE));
	case 7:
		return QString::number(DATAMANAGER().GetAttribute(SOLDIER_TAG, id, ATTR_FORMATION));
	case 8:
		return QString::number(DATAMANAGER().GetAttribute(SOLDIER_TAG, id, ATTR_INITIATIVE));
	case 9:
		return QString::number(DATAMANAGER().GetAttribute(SOLDIER_TAG, id, ATTR_ACTIONPOINT));
	case 10:
		return QString::number(DATAMANAGER().GetAttribute(SOLDIER_TAG, id, ATTR_DETECTION));
	case 11:
		return QString::number(DATAMANAGER().GetAttribute(SOLDIER_TAG, id, ATTR_COVERT));
	case 12:
		return QString::number(DATAMANAGER().GetAttribute(SOLDIER_TAG, id, ATTR_INJURY));
	case 13:
		return QString::number(DATAMANAGER().GetAttribute(SOLDIER_TAG, id, ATTR_COUNTER));
	case 14:
		return QString::fromStdWString(DATAMANAGER().GetDataStr(SOLDIER_TAG, id, SCRIPT_TAG));
	case 15:
		return QString::number(DATAMANAGER().GetInt(SOLDIER_TAG, id, INJURY_TAG));
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
	beginInsertRows(parent, DATAMANAGER().GetCount(SOLDIER_TAG), DATAMANAGER().GetCount(SOLDIER_TAG));
	DATAMANAGER().AddSoldier();
	endInsertRows();
	return true;
}

bool SoldierTableModule::removeRow(int row, const QModelIndex & parent /* = QModelIndex */)
{
	beginRemoveRows(parent, row, row);
	std::wstring id = DATAMANAGER().GetID(SOLDIER_TAG, row);
	DATAMANAGER().RemoveData(SOLDIER_TAG, id);
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
		std::wstring id = DATAMANAGER().GetID(SOLDIER_TAG, index.row());
		switch(index.column())
		{
		case 0:
			return DATAMANAGER().SetID(SOLDIER_TAG, id, qvalue.toString().toStdWString());
		case 1:
			return DATAMANAGER().SetLangStr(SOLDIER_TAG, id, NAME_TAG, qvalue.toString().toStdWString());
		case 2:
			return DATAMANAGER().SetLangStr(SOLDIER_TAG, id, DESCRIPTION_TAG, qvalue.toString().toStdWString());
		case 3:
			return DATAMANAGER().SetInt(SOLDIER_TAG, id, VALUE_TAG, qvalue.toInt());
		case 4:
			return DATAMANAGER().SetAttribute(SOLDIER_TAG, id, ATTR_ATTACK, qvalue.toInt());
		case 5:
			return DATAMANAGER().SetAttribute(SOLDIER_TAG, id, ATTR_RANGEDATTACK, qvalue.toInt());
		case 6:
			return DATAMANAGER().SetAttribute(SOLDIER_TAG, id, ATTR_DEFENSE, qvalue.toInt());
		case 7:
			return DATAMANAGER().SetAttribute(SOLDIER_TAG, id, ATTR_FORMATION, qvalue.toInt());
		case 8:
			return DATAMANAGER().SetAttribute(SOLDIER_TAG, id, ATTR_INITIATIVE, qvalue.toInt());
		case 9:
			return DATAMANAGER().SetAttribute(SOLDIER_TAG, id, ATTR_ACTIONPOINT, qvalue.toInt());
		case 10:
			return DATAMANAGER().SetAttribute(SOLDIER_TAG, id, ATTR_DETECTION, qvalue.toInt());
		case 11:
			return DATAMANAGER().SetAttribute(SOLDIER_TAG, id, ATTR_COVERT, qvalue.toInt());
		case 12:
			return DATAMANAGER().SetAttribute(SOLDIER_TAG, id, ATTR_INJURY, qvalue.toInt());
		case 13:
			return DATAMANAGER().SetAttribute(SOLDIER_TAG, id, ATTR_COUNTER, qvalue.toInt());
		case 14:
			return DATAMANAGER().SetDataStr(SOLDIER_TAG, id, SCRIPT_TAG, qvalue.toString().toStdWString());
		case 15:
			return DATAMANAGER().SetInt(SOLDIER_TAG, id, INJURY_TAG, qvalue.toInt());
		default:
			return false;
		}
	}
	return false;
}