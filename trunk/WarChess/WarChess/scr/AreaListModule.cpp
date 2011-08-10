#include "AreaListModule.h"

#include <Ogre.h>
#include "AreaManager.h"
#include "Area.h"

AreaListModule::AreaListModule(QObject *parent)
:QAbstractListModel(parent)
{
	mAreaManager = AreaManager::getSingletonPtr();
}

AreaListModule::~AreaListModule()
{

}
int	AreaListModule::rowCount ( const QModelIndex & parent ) const
{
	return mAreaManager->mAreaList.size();
}
bool AreaListModule::insertRows ( int row, int count, const QModelIndex & parent )
{
	beginInsertRows(parent, mAreaManager->mAreaList.size(),mAreaManager->mAreaList.size()+count -1);
	for(int n = 0; n < count; n++)
	{
		std::string newname = std::string("Area") + Ogre::StringConverter::toString(mAreaManager->mAreaList.size());
		mAreaManager->mAreaList.push_back(new Area(newname));
	} 
	endInsertRows();
	return true;
}
bool AreaListModule::setData ( const QModelIndex & index, const QVariant & value, int role )
{
	if (index.isValid() && role == Qt::EditRole) 
	{
		if(value.toString().toStdString().size() > 0)
			mAreaManager->mAreaList[index.row()]->mName = value.toString().toStdString();
	}
	return true;
}
QVariant AreaListModule::data(const QModelIndex &index, int role) const
{
	if(!index.isValid() || role != Qt::DisplayRole)
		return QVariant();
	return QString::fromStdString(mAreaManager->mAreaList[index.row()]->mName);

}
Qt::ItemFlags AreaListModule::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return Qt::ItemIsEnabled;

	return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
}

bool AreaListModule::removeRows ( int row, int count, const QModelIndex & parent )
{
	if(row < 0)
		return false;
	beginRemoveRows(parent, row, row + count-1);
	for(int n = 0; n < count ; n ++)
	{
		//delete mAreaManager->mAreaList[row];
		mAreaManager->mAreaList.erase(mAreaManager->mAreaList.begin() + row);
	}
	endRemoveRows();
	return true;
}