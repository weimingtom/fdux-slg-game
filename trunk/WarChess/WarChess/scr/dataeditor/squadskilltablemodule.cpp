#include "squadskilltablemodule.h"
#include "DataManager.h"

const int SquadSkillTableColumnCount = 4; 

SquadSkillTableModule::SquadSkillTableModule(QObject *parent)
: QAbstractTableModel(parent)
{
	rowIndex_ = -1;
}

SquadSkillTableModule::~SquadSkillTableModule()
{

}

int SquadSkillTableModule::columnCount(const QModelIndex &parent /* = QModelIndex */) const
{
	return SquadSkillTableColumnCount;
}

int SquadSkillTableModule::rowCount(const QModelIndex &parent /* = QModelIndex */) const
{
	return DATAMANAGER().GetCount(SKILL_TAG);
}

QVariant SquadSkillTableModule::data(const QModelIndex &index, int role /* = Qt::DisplayRole */) const
{
	if(!index.isValid() || role != Qt::DisplayRole || rowIndex_ == -1)
		return QVariant();

	std::wstring squadid = DATAMANAGER().GetID(SQUAD_TAG, rowIndex_);
	std::wstring skillid = DATAMANAGER().GetID(SKILL_TAG, index.row());
	switch(index.column())
	{
	case 0:
		return QString::fromStdWString(skillid);
	case 1:
		return QString::fromStdWString(DATAMANAGER().GetLangStr(SKILL_TAG, skillid, NAME_TAG));
	case 2:
		return QString::fromStdWString(DATAMANAGER().GetLangStr(SKILL_TAG, skillid, DESCRIPTION_TAG));
	case 3:
		return  QString::number(DATAMANAGER().GetIsSquadSkill(squadid, skillid));
	default:
		return QVariant();
	}
}

QVariant SquadSkillTableModule::headerData(int section, Qt::Orientation orientation, int role /* = Qt::DisplayRole */) const
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
			return QString("是否属于小队");
		default:
			return QVariant();
		}
	}
	else
		return QString("%1").arg(section);
}

bool SquadSkillTableModule::markRow(int row, const QModelIndex & parent /* = QModelIndex */)
{
	//beginInsertRows(parent, DATAMANAGER().GetCount(SKILL_TAG), DATAMANAGER().GetCount(SKILL_TAG));
	//DATAMANAGER().AddSquad();
	//endInsertRows();
	std::wstring squadid = DATAMANAGER().GetID(SQUAD_TAG, rowIndex_);
	std::wstring skillid = DATAMANAGER().GetID(SKILL_TAG, row);
	DATAMANAGER().AddSquadSkill(squadid, skillid);
	reset();
	return true;
}

bool SquadSkillTableModule::unmarkRow(int row, const QModelIndex & parent /* = QModelIndex */)
{
	//beginRemoveRows(parent, row, row);
	//std::wstring id = DATAMANAGER().GetID(SKILL_TAG, row);
	//DATAMANAGER().RemoveData(SKILL_TAG, id);
	//endRemoveRows();
	std::wstring squadid = DATAMANAGER().GetID(SQUAD_TAG, rowIndex_);
	std::wstring skillid = DATAMANAGER().GetID(SKILL_TAG, row);
	DATAMANAGER().RemoveSquadSkill(squadid, skillid);
	reset();
	return true;
}

Qt::ItemFlags SquadSkillTableModule::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return Qt::ItemIsEnabled;

	return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
}

bool SquadSkillTableModule::setData(const QModelIndex &index, const QVariant &qvalue,int role /* = Qt::EditRole */)
{
	if (index.isValid() && role == Qt::EditRole) 
	{
		std::wstring squadid = DATAMANAGER().GetID(SQUAD_TAG, rowIndex_);
		std::wstring skillid = DATAMANAGER().GetID(SKILL_TAG, index.row());
		switch(index.column())
		{
		case 0:
			return DATAMANAGER().SetID(SKILL_TAG, skillid, qvalue.toString().toStdWString());
		case 1:
			return DATAMANAGER().SetLangStr(SKILL_TAG, skillid, NAME_TAG, qvalue.toString().toStdWString());
		case 2:
			return DATAMANAGER().SetLangStr(SKILL_TAG, skillid, DESCRIPTION_TAG, qvalue.toString().toStdWString());
		case 3:
			return DATAMANAGER().SetIsSquadSkill(squadid, skillid, qvalue.toInt());
		default:
			return false;
		}
	}
	return false;
}