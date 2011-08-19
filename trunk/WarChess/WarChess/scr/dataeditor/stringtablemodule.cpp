#include "stringtablemodule.h"
#include "DataManager.h"
#include "stringtable.h"

const int StringTableColumnCount = 2; 

StringTableModule::StringTableModule(QObject *parent)
: QAbstractTableModel(parent)
{

}

StringTableModule::~StringTableModule()
{

}

int StringTableModule::columnCount(const QModelIndex &parent /* = QModelIndex */) const
{
	return StringTableColumnCount;
}

int StringTableModule::rowCount(const QModelIndex &parent /* = QModelIndex */) const
{
	return DATAMANAGER().GetStrTableCount();
}

QVariant StringTableModule::data(const QModelIndex &index, int role /* = Qt::DisplayRole */) const
{
	if(!index.isValid() || role != Qt::DisplayRole)
		return QVariant();

	std::wstring key = DATAMANAGER().GetStrTableID(index.row());
	switch(index.column())
	{
	case 0:
		return QString::fromStdWString(key);
	case 1:
		return QString::fromStdWString(DATAMANAGER().GetStrTable(key));
	default:
		return QVariant();
	}
}

QVariant StringTableModule::headerData(int section, Qt::Orientation orientation, int role /* = Qt::DisplayRole */) const
{
	if (role != Qt::DisplayRole)
		return QVariant();
	if (orientation == Qt::Horizontal)
	{
		switch(section)
		{
		case 0:
			return QString("key");
		case 1:
			return QString("×Ö·û´®");
		default:
			return QVariant();
		}
	}
	else
		return QString("%1").arg(section);
}

bool StringTableModule::insertRow(int row, const QModelIndex & parent /* = QModelIndex */)
{
	beginInsertRows(parent, DATAMANAGER().GetStrTableCount(), DATAMANAGER().GetStrTableCount());
	DATAMANAGER().AddString();
	endInsertRows();
	return true;
}

bool StringTableModule::removeRow(int row, const QModelIndex & parent /* = QModelIndex */)
{
	beginRemoveRows(parent, row, row);
	std::wstring key = DATAMANAGER().GetStrTableID(row);
	DATAMANAGER().RemoveStrTable(key);
	endRemoveRows();
	return true;
}

Qt::ItemFlags StringTableModule::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return Qt::ItemIsEnabled;

	return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
}

bool StringTableModule::setData(const QModelIndex &index, const QVariant &qvalue,int role /* = Qt::EditRole */)
{
	if (index.isValid() && role == Qt::EditRole) 
	{
		std::wstring key= DATAMANAGER().GetStrTableID(index.row());
		switch(index.column())
		{
		case 0:
			return DATAMANAGER().SetStrTableID(key, qvalue.toString().toStdWString());
		case 1:
			return DATAMANAGER().SetStrTable(key, qvalue.toString().toStdWString());
		default:
			return false;
		}
	}
	return false;
}