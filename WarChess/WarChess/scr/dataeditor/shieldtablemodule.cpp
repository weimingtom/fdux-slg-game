#include "shieldtablemodule.h"
#include "DataManager.h"

const int ShieldTableColumnCount = 13; 

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
	return DATAMANAGER().GetCount(SHIELD_TAG);
}

QVariant ShieldTableModule::data(const QModelIndex &index, int role /* = Qt::DisplayRole */) const
{
	if(!index.isValid() || role != Qt::DisplayRole)
		return QVariant();

	std::wstring id = DATAMANAGER().GetID(SHIELD_TAG, index.row());
	switch(index.column())
	{
	case 0:
		return QString::fromStdWString(id);
	case 1:
		return QString::fromStdWString(DATAMANAGER().GetLangStr(SHIELD_TAG, id, NAME_TAG));
	case 2:
		return QString::fromStdWString(DATAMANAGER().GetLangStr(SHIELD_TAG, id, DESCRIPTION_TAG));
	case 3:
		return QString::number(DATAMANAGER().GetInt(SHIELD_TAG, id, VALUE_TAG));
	case 4:
		return QString::number(DATAMANAGER().GetAttribute(SHIELD_TAG, id, ATTR_ATTACK));
	case 5:
		return QString::number(DATAMANAGER().GetAttribute(SHIELD_TAG, id, ATTR_DEFENSE));
	case 6:
		return QString::number(DATAMANAGER().GetAttribute(SHIELD_TAG, id, ATTR_FORMATION));
	case 7:
		return QString::number(DATAMANAGER().GetAttribute(SHIELD_TAG, id, ATTR_INITIATIVE));
	case 8:
		return QString::number(DATAMANAGER().GetAttribute(SHIELD_TAG, id, ATTR_ACTIONPOINT));
	case 9:
		return QString::number(DATAMANAGER().GetAttribute(SHIELD_TAG, id, ATTR_COVERT));
	case 10:
		return QString::fromStdWString(DATAMANAGER().GetDataStr(SHIELD_TAG, id, MESH_TAG));
	case 11:
		return QString::fromStdWString(DATAMANAGER().GetDataStr(SHIELD_TAG, id, MAT_TAG));
	case 12:
		return QString::fromStdWString(DATAMANAGER().GetDataStr(SHIELD_TAG, id, SCRIPT_TAG));
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
			return QString("材质名称");
		case 12:
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
	beginInsertRows(parent, DATAMANAGER().GetCount(SHIELD_TAG),DATAMANAGER().GetCount(SHIELD_TAG));
	DATAMANAGER().AddShield();
	endInsertRows();
	return true;
}

bool ShieldTableModule::removeRow(int row, const QModelIndex & parent /* = QModelIndex */)
{
	beginRemoveRows(parent, row, row);
	std::wstring id = DATAMANAGER().GetID(SHIELD_TAG, row);
	DATAMANAGER().RemoveData(SHIELD_TAG, id);
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
		std::wstring id = DATAMANAGER().GetID(SHIELD_TAG, index.row());
		switch(index.column())
		{
		case 0:
			return DATAMANAGER().SetID(SHIELD_TAG, id, qvalue.toString().toStdWString());
		case 1:
			return DATAMANAGER().SetLangStr(SHIELD_TAG, id, NAME_TAG, qvalue.toString().toStdWString());
		case 2:
			return DATAMANAGER().SetLangStr(SHIELD_TAG, id, DESCRIPTION_TAG, qvalue.toString().toStdWString());
		case 3:
			return DATAMANAGER().SetInt(SHIELD_TAG, id, VALUE_TAG, qvalue.toInt());
		case 4:
			return DATAMANAGER().SetAttribute(SHIELD_TAG, id, ATTR_ATTACK, qvalue.toFloat());
		case 5:
			return DATAMANAGER().SetAttribute(SHIELD_TAG, id, ATTR_DEFENSE, qvalue.toFloat());
		case 6:
			return DATAMANAGER().SetAttribute(SHIELD_TAG, id, ATTR_FORMATION, qvalue.toFloat());
		case 7:
			return DATAMANAGER().SetAttribute(SHIELD_TAG, id, ATTR_INITIATIVE, qvalue.toFloat());
		case 8:
			return DATAMANAGER().SetAttribute(SHIELD_TAG, id, ATTR_ACTIONPOINT, qvalue.toFloat());
		case 9:
			return DATAMANAGER().SetAttribute(SHIELD_TAG, id, ATTR_COVERT, qvalue.toFloat());
		case 10:
			return DATAMANAGER().SetDataStr(SHIELD_TAG, id, MESH_TAG, qvalue.toString().toStdWString());
		case 11:
			return DATAMANAGER().SetDataStr(SHIELD_TAG, id, MAT_TAG, qvalue.toString().toStdWString());
		case 12:
			return DATAMANAGER().SetDataStr(SHIELD_TAG, id, SCRIPT_TAG, qvalue.toString().toStdWString());
		default:
			return false;
		}
	}
	return false;
}