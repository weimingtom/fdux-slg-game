#include "effecttablemodule.h"
#include "DataManager.h"

const int EffectTableColumnCount = 6; 

EffectTableModule::EffectTableModule(QObject *parent)
: QAbstractTableModel(parent)
{

}

EffectTableModule::~EffectTableModule()
{

}

int EffectTableModule::columnCount(const QModelIndex &parent /* = QModelIndex */) const
{
	return EffectTableColumnCount;
}

int EffectTableModule::rowCount(const QModelIndex &parent /* = QModelIndex */) const
{
	return DATAMANAGER().GetCount(EFFECT_TAG);
}

QVariant EffectTableModule::data(const QModelIndex &index, int role /* = Qt::DisplayRole */) const
{
	if(!index.isValid() || role != Qt::DisplayRole)
		return QVariant();

	std::wstring id = DATAMANAGER().GetID(EFFECT_TAG, index.row());
	switch(index.column())
	{
	case 0:
		return QString::fromStdWString(id);
	case 1:
		return QString::fromStdWString(DATAMANAGER().GetLangStr(EFFECT_TAG, id, NAME_TAG));
	case 2:
		return QString::fromStdWString(DATAMANAGER().GetLangStr(EFFECT_TAG, id, DESCRIPTION_TAG));
	case 3:
		return  QString::number(DATAMANAGER().GetInt(EFFECT_TAG, id, TYPE_TAG));
	case 4:
		return QString::fromStdWString(DATAMANAGER().GetDataStr(EFFECT_TAG, id, ICON_TAG));
	case 5:
		return QString::fromStdWString(DATAMANAGER().GetDataStr(EFFECT_TAG, id, SCRIPT_TAG));
	default:
		return QVariant();
	}
}

QVariant EffectTableModule::headerData(int section, Qt::Orientation orientation, int role /* = Qt::DisplayRole */) const
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
			return QString("图标");
		case 5:
			return QString("脚本名称");
		default:
			return QVariant();
		}
	}
	else
		return QString("%1").arg(section);
}

bool EffectTableModule::insertRow(int row, const QModelIndex & parent /* = QModelIndex */)
{
	beginInsertRows(parent, DATAMANAGER().GetCount(EFFECT_TAG), DATAMANAGER().GetCount(EFFECT_TAG));
	DATAMANAGER().AddEffect();
	endInsertRows();
	return true;
}

bool EffectTableModule::removeRow(int row, const QModelIndex & parent /* = QModelIndex */)
{
	beginRemoveRows(parent, row, row);
	std::wstring id = DATAMANAGER().GetID(EFFECT_TAG, row);
	DATAMANAGER().RemoveData(EFFECT_TAG, id);
	endRemoveRows();
	return true;
}

Qt::ItemFlags EffectTableModule::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return Qt::ItemIsEnabled;

	return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
}

bool EffectTableModule::setData(const QModelIndex &index, const QVariant &qvalue,int role /* = Qt::EditRole */)
{
	if (index.isValid() && role == Qt::EditRole) 
	{
		std::wstring id = DATAMANAGER().GetID(EFFECT_TAG, index.row());
		switch(index.column())
		{
		case 0:
			return DATAMANAGER().SetID(EFFECT_TAG, id, qvalue.toString().toStdWString());
		case 1:
			return DATAMANAGER().SetLangStr(EFFECT_TAG, id, NAME_TAG, qvalue.toString().toStdWString());
		case 2:
			return DATAMANAGER().SetLangStr(EFFECT_TAG, id, DESCRIPTION_TAG, qvalue.toString().toStdWString());
		case 3:
			return DATAMANAGER().SetInt(EFFECT_TAG, id, TYPE_TAG, qvalue.toInt());
		case 4:
			return DATAMANAGER().SetDataStr(EFFECT_TAG, id, ICON_TAG, qvalue.toString().toStdWString());
		case 5:
			return DATAMANAGER().SetDataStr(EFFECT_TAG, id, SCRIPT_TAG, qvalue.toString().toStdWString());
		default:
			return false;
		}
	}
	return false;
}