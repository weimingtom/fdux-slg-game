#include "squadtablemodule.h"
#include "DataManager.h"

const int SquadTableColumnCount = 19; 

SquadTableModule::SquadTableModule(QObject *parent)
: QAbstractTableModel(parent)
{

}

SquadTableModule::~SquadTableModule()
{

}

int SquadTableModule::columnCount(const QModelIndex &parent /* = QModelIndex */) const
{
	return SquadTableColumnCount;
}

int SquadTableModule::rowCount(const QModelIndex &parent /* = QModelIndex */) const
{
	return DATAMANAGER().GetCount(SQUAD_TAG);
}

QVariant SquadTableModule::data(const QModelIndex &index, int role /* = Qt::DisplayRole */) const
{
	if(!index.isValid() || role != Qt::DisplayRole)
		return QVariant();

	std::wstring id = DATAMANAGER().GetID(SQUAD_TAG, index.row());
	switch(index.column())
	{
	case 0:
		return QString::fromStdWString(id);
	case 1:
		return QString::fromStdWString(DATAMANAGER().GetLangStr(SQUAD_TAG, id, NAME_TAG));
	case 2:
		return QString::fromStdWString(DATAMANAGER().GetLangStr(SQUAD_TAG, id, DESCRIPTION_TAG));
	case 3:
		return  QString::number(DATAMANAGER().GetInt(SQUAD_TAG, id, TYPE_TAG));
	case 4:
		return  QString::number(DATAMANAGER().GetInt(SQUAD_TAG, id, SQUADTYPE_TAG));
	case 5:
		return QString::fromStdWString(DATAMANAGER().GetDataStr(SQUAD_TAG, id, SOLDIERID_TAG));
	case 6:
		return QString::fromStdWString(DATAMANAGER().GetDataStr(SQUAD_TAG, id, HORSEID_TAG));
	case 7:
		return QString::fromStdWString(DATAMANAGER().GetDataStr(SQUAD_TAG, id, PWEAPONID_TAG));
	case 8:
		return QString::fromStdWString(DATAMANAGER().GetDataStr(SQUAD_TAG, id, SWEAPONID_TAG));
	case 9:
		return QString::fromStdWString(DATAMANAGER().GetDataStr(SQUAD_TAG, id, SHIELDID_TAG));
	case 10:
		return QString::fromStdWString(DATAMANAGER().GetDataStr(SQUAD_TAG, id, ARMORID_TAG));
	case 11:
		return QString::fromStdWString(DATAMANAGER().GetDataStr(SQUAD_TAG, id, LEADERNAME_TAG));
	case 12:
		return QString::fromStdWString(DATAMANAGER().GetDataStr(SQUAD_TAG, id, LEADERPIC_TAG));
	case 13:
		return QString::fromStdWString(DATAMANAGER().GetDataStr(SQUAD_TAG, id, LEADERMESH_TAG));
	case 14:
		return QString::fromStdWString(DATAMANAGER().GetDataStr(SQUAD_TAG, id, LEADERMAT_TAG));
	case 15:
		return QString::fromStdWString(DATAMANAGER().GetDataStr(SQUAD_TAG, id, UNITMESH_TAG));
	case 16:
		return QString::fromStdWString(DATAMANAGER().GetDataStr(SQUAD_TAG, id, UNITMAT_TAG));
	case 17:
		return QString::number(DATAMANAGER().GetInt(SQUAD_TAG, id, UNITMAXNUM_TAG));
	case 18:
		return QString::fromStdWString(DATAMANAGER().GetDataStr(SQUAD_TAG, id, MOVESOUND_TAG));
	default:
		return QVariant();
	}
}

QVariant SquadTableModule::headerData(int section, Qt::Orientation orientation, int role /* = Qt::DisplayRole */) const
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
			return QString("类型");
		case 4:
			return QString("小队类型");
		case 5:
			return QString("兵源ID");
		case 6:
			return QString("马匹ID");
		case 7:
			return QString("主武器ID");
		case 8:
			return QString("副武器ID");
		case 9:
			return QString("盾牌ID");
		case 10:
			return QString("盔甲ID");
		case 11:
			return QString("领袖名称");
		case 12:
			return QString("领袖图片");
		case 13:
			return QString("领袖模型名称");
		case 14:
			return QString("领袖材质名称");
		case 15:
			return QString("单位模型名称");
		case 16:
			return QString("单位材质名称");
		case 17:
			return QString("最大单位数量");
		case 18:
			return QString("移动音效");
		default:
			return QVariant();
		}
	}
	else
		return QString("%1").arg(section);
}

bool SquadTableModule::insertRow(int row, const QModelIndex & parent /* = QModelIndex */)
{
	beginInsertRows(parent, DATAMANAGER().GetCount(SQUAD_TAG), DATAMANAGER().GetCount(SQUAD_TAG));
	DATAMANAGER().AddSquad();
	endInsertRows();
	return true;
}

bool SquadTableModule::removeRow(int row, const QModelIndex & parent /* = QModelIndex */)
{
	beginRemoveRows(parent, row, row);
	std::wstring id = DATAMANAGER().GetID(SQUAD_TAG, row);
	DATAMANAGER().RemoveData(SQUAD_TAG, id);
	endRemoveRows();
	return true;
}

Qt::ItemFlags SquadTableModule::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return Qt::ItemIsEnabled;

	return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
}

bool SquadTableModule::setData(const QModelIndex &index, const QVariant &qvalue,int role /* = Qt::EditRole */)
{
	if (index.isValid() && role == Qt::EditRole) 
	{
		std::wstring id = DATAMANAGER().GetID(SQUAD_TAG, index.row());
		switch(index.column())
		{
		case 0:
			return DATAMANAGER().SetID(SQUAD_TAG, id, qvalue.toString().toStdWString());
		case 1:
			return DATAMANAGER().SetLangStr(SQUAD_TAG, id, NAME_TAG, qvalue.toString().toStdWString());
		case 2:
			return DATAMANAGER().SetLangStr(SQUAD_TAG, id, DESCRIPTION_TAG, qvalue.toString().toStdWString());
		case 3:
			return DATAMANAGER().SetInt(SQUAD_TAG, id, TYPE_TAG, qvalue.toInt());
		case 4:
			return DATAMANAGER().SetInt(SQUAD_TAG, id, SQUADTYPE_TAG, qvalue.toInt());
		case 5:
			return DATAMANAGER().SetDataStr(SQUAD_TAG, id, ARMORID_TAG, qvalue.toString().toStdWString());
		case 6:
			return DATAMANAGER().SetDataStr(SQUAD_TAG, id, HORSEID_TAG, qvalue.toString().toStdWString());
		case 7:
			return DATAMANAGER().SetDataStr(SQUAD_TAG, id, PWEAPONID_TAG, qvalue.toString().toStdWString());
		case 8:
			return DATAMANAGER().SetDataStr(SQUAD_TAG, id, SWEAPONID_TAG, qvalue.toString().toStdWString());
		case 9:
			return DATAMANAGER().SetDataStr(SQUAD_TAG, id, SHIELDID_TAG, qvalue.toString().toStdWString());
		case 10:
			return DATAMANAGER().SetDataStr(SQUAD_TAG, id, ARMORID_TAG, qvalue.toString().toStdWString());
		case 11:
			return DATAMANAGER().SetDataStr(SQUAD_TAG, id, LEADERNAME_TAG, qvalue.toString().toStdWString());
		case 12:
			return DATAMANAGER().SetDataStr(SQUAD_TAG, id, LEADERPIC_TAG, qvalue.toString().toStdWString());
		case 13:
			return DATAMANAGER().SetDataStr(SQUAD_TAG, id, LEADERMESH_TAG, qvalue.toString().toStdWString());
		case 14:
			return DATAMANAGER().SetDataStr(SQUAD_TAG, id, LEADERMAT_TAG, qvalue.toString().toStdWString());
		case 15:
			return DATAMANAGER().SetDataStr(SQUAD_TAG, id, UNITMESH_TAG, qvalue.toString().toStdWString());
		case 16:
			return DATAMANAGER().SetDataStr(SQUAD_TAG, id, UNITMAT_TAG, qvalue.toString().toStdWString());
		case 17:
			return DATAMANAGER().SetInt(SQUAD_TAG, id, UNITMAXNUM_TAG, qvalue.toInt());
		case 18:
			return DATAMANAGER().SetDataStr(SQUAD_TAG, id, MOVESOUND_TAG, qvalue.toString().toStdWString());
		default:
			return false;
		}
	}
	return false;
}