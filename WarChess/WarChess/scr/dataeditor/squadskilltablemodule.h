#ifndef SQUADSKILLTABLEMODULE_H
#define SQUADSKILLTABLEMODULE_H

#include <QAbstractTableModel>

class SquadSkillTableModule : public QAbstractTableModel
{
	Q_OBJECT

public:
	SquadSkillTableModule(QObject *parent = 0);
	~SquadSkillTableModule();

	virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
	virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
	virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
	virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
	virtual Qt::ItemFlags flags(const QModelIndex &index) const;
	virtual bool setData(const QModelIndex &index, const QVariant &qvalue,int role = Qt::EditRole);

	bool markRow(int row, const QModelIndex & parent = QModelIndex());
	bool unmarkRow (int row, const QModelIndex & parent = QModelIndex());

	void ModChanged() {reset();}
	void SquadSelected(int _rowIndex) {rowIndex_ = _rowIndex; reset();}
private:
	int rowIndex_;
};

#endif // SQUADSKILLTABLEMODULE_H