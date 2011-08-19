#include "skilltablemodule.h"
#include "DataManager.h"

const int SkillTableColumnCount = 12;

SkillTableModule::SkillTableModule(QObject *parent)
: QAbstractTableModel(parent)
{

}

SkillTableModule::~SkillTableModule()
{

}

int SkillTableModule::columnCount(const QModelIndex &parent /* = QModelIndex */) const
{
	return SkillTableColumnCount;
}

int SkillTableModule::rowCount(const QModelIndex &parent /* = QModelIndex */) const
{
	return DATAMANAGER().GetCount(SKILL_TAG);
}

QVariant SkillTableModule::data(const QModelIndex &index, int role /* = Qt::DisplayRole */) const
{
	if(!index.isValid() || role != Qt::DisplayRole)
		return QVariant();

	std::wstring id = DATAMANAGER().GetID(SKILL_TAG, index.row());
	switch(index.column())
	{
	case 0:
		return QString::fromStdWString(id);
	case 1:
		return QString::fromStdWString(DATAMANAGER().GetLangStr(SKILL_TAG, id, NAME_TAG));
	case 2:
		return QString::fromStdWString(DATAMANAGER().GetLangStr(SKILL_TAG, id, DESCRIPTION_TAG));
	case 3:
		return QString::number(DATAMANAGER().GetInt(SKILL_TAG, id, VALUE_TAG));
	case 4:
		return QString::number(DATAMANAGER().GetInt(SKILL_TAG, id, MAXRANGE_TAG));
	case 5:
		return QString::number(DATAMANAGER().GetInt(SKILL_TAG, id, MINRANGE_TAG));
	case 6:
		return QString::number(DATAMANAGER().GetInt(SKILL_TAG, id, AREA_TAG));
	case 7:
		return QString::number(DATAMANAGER().GetInt(SKILL_TAG, id, APTYPE_TAG));
	case 8:
		return QString::number(DATAMANAGER().GetFloat(SKILL_TAG, id, APCOST_TAG));
	case 9:
		return QString::number(DATAMANAGER().GetInt(SKILL_TAG, id, COOLDOWN_TAG));
	case 10:
		return QString::fromStdWString(DATAMANAGER().GetDataStr(SKILL_TAG, id, ICON_TAG));
	case 11:
		return QString::fromStdWString(DATAMANAGER().GetDataStr(SKILL_TAG, id, SCRIPT_TAG));
	default:
		return QVariant();
	}
}

QVariant SkillTableModule::headerData(int section, Qt::Orientation orientation, int role /* = Qt::DisplayRole */) const
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
			return QString("最大射程");
		case 5:
			return QString("最小射程");
		case 6:
			return QString("范围");
		case 7:
			return QString("AP类型");
		case 8:
			return QString("AP消耗");
		case 9:
			return QString("冷却");
		case 10:
			return QString("图标");
		case 11:
			return QString("脚本名称");
		default:
			return QVariant();
		}
	}
	else
		return QString("%1").arg(section);
}

bool SkillTableModule::insertRow(int row, const QModelIndex & parent /* = QModelIndex */)
{
	beginInsertRows(parent, DATAMANAGER().GetCount(SKILL_TAG), DATAMANAGER().GetCount(SKILL_TAG));
	DATAMANAGER().AddSkill();
	endInsertRows();
	return true;
}

bool SkillTableModule::removeRow(int row, const QModelIndex & parent /* = QModelIndex */)
{
	beginRemoveRows(parent, row, row);
	std::wstring id = DATAMANAGER().GetID(SKILL_TAG, row);
	DATAMANAGER().RemoveData(SKILL_TAG, id);
	endRemoveRows();
	return true;
}

Qt::ItemFlags SkillTableModule::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return Qt::ItemIsEnabled;

	return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
}

bool SkillTableModule::setData(const QModelIndex &index, const QVariant &qvalue,int role /* = Qt::EditRole */)
{
	if (index.isValid() && role == Qt::EditRole) 
	{
		std::wstring id = DATAMANAGER().GetID(SKILL_TAG, index.row());
		switch(index.column())
		{
		case 0:
			return DATAMANAGER().SetID(SKILL_TAG, id, qvalue.toString().toStdWString());
		case 1:
			return DATAMANAGER().SetLangStr(SKILL_TAG, id, NAME_TAG, qvalue.toString().toStdWString());
		case 2:
			return DATAMANAGER().SetLangStr(SKILL_TAG, id, DESCRIPTION_TAG, qvalue.toString().toStdWString());
		case 3:
			return DATAMANAGER().SetInt(SKILL_TAG, id, VALUE_TAG, qvalue.toInt());
		case 4:
			return DATAMANAGER().SetInt(SKILL_TAG, id, MAXRANGE_TAG, qvalue.toInt());
		case 5:
			return DATAMANAGER().SetInt(SKILL_TAG, id, MINRANGE_TAG, qvalue.toInt());
		case 6:
			return DATAMANAGER().SetInt(SKILL_TAG, id, AREA_TAG, qvalue.toInt());
		case 7:
			return DATAMANAGER().SetInt(SKILL_TAG, id, APTYPE_TAG, qvalue.toInt());
		case 8:
			return DATAMANAGER().SetFloat(SKILL_TAG, id, APCOST_TAG, qvalue.toFloat());
		case 9:
			return DATAMANAGER().SetInt(SKILL_TAG, id, COOLDOWN_TAG, qvalue.toInt());
		case 10:
			return DATAMANAGER().SetDataStr(SKILL_TAG, id, ICON_TAG, qvalue.toString().toStdWString());
		case 11:
			return DATAMANAGER().SetDataStr(SKILL_TAG, id, SCRIPT_TAG, qvalue.toString().toStdWString());
		default:
			return false;
		}
	}
	return false;
}