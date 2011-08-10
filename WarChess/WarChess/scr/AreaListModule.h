#pragma once
#include <QAbstractListModel>

class AreaManager;
class Area;

class AreaListModule : public QAbstractListModel
{
	Q_OBJECT
public:
	AreaListModule(QObject *parent = 0);
	~AreaListModule();
	virtual int	rowCount ( const QModelIndex & parent = QModelIndex() ) const;
	virtual bool insertRows ( int row, int count, const QModelIndex & parent = QModelIndex() );
	virtual bool setData ( const QModelIndex & index, const QVariant & value, int role = Qt::EditRole );
	virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
	virtual Qt::ItemFlags flags(const QModelIndex &index) const;
	virtual bool removeRows ( int row, int count, const QModelIndex & parent = QModelIndex() );
private:
	AreaManager *mAreaManager;
	Area *mArea;
};