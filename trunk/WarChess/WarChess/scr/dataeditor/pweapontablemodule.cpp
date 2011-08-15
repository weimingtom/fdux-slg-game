#include "pweapontablemodule.h"
#include "DataManager.h"
#include "pweaponmanager.h"

#define PWEAPONMANAGER() DataManager::getSingleton().mPWeaponManager

const int PWeaponTableColumnCount = 15; 

PWeaponTableModule::PWeaponTableModule(QObject *parent)
: QAbstractTableModel(parent)
{

}

PWeaponTableModule::~PWeaponTableModule()
{

}

int PWeaponTableModule::columnCount(const QModelIndex &parent /* = QModelIndex */) const
{
	return PWeaponTableColumnCount;
}

int PWeaponTableModule::rowCount(const QModelIndex &parent /* = QModelIndex */) const
{
	return PWEAPONMANAGER()->GetNum();
}

QVariant PWeaponTableModule::data(const QModelIndex &index, int role /* = Qt::DisplayRole */) const
{
	if(!index.isValid() || role != Qt::DisplayRole)
		return QVariant();

	std::wstring id = PWEAPONMANAGER()->GetID(index.row());
	switch(index.column())
	{
	case 0:
		return QString::fromStdWString(id);
	case 1:
		return QString::fromStdWString(PWEAPONMANAGER()->GetName(id));
	case 2:
		return QString::fromStdWString(PWEAPONMANAGER()->GetDescription(id));
	case 3:
		return  QString::number(PWEAPONMANAGER()->GetValue(id));
	case 4:
		return  QString::number(PWEAPONMANAGER()->GetPWeaponType(id));
	case 5:
		return QString::number(PWEAPONMANAGER()->GetAttr(id,ATTR_ATTACK));
	case 6:
		return QString::number(PWEAPONMANAGER()->GetAttr(id,ATTR_DEFENSE));
	case 7:
		return QString::number(PWEAPONMANAGER()->GetAttr(id,ATTR_FORMATION));
	case 8:
		return QString::number(PWEAPONMANAGER()->GetAttr(id,ATTR_INITIATIVE));
	case 9:
		return QString::number(PWEAPONMANAGER()->GetAttr(id,ATTR_ACTIONPOINT));
	case 10:
		return QString::number(PWEAPONMANAGER()->GetAttr(id,ATTR_COVERT));
	case 11:
		return QString::fromStdWString(PWEAPONMANAGER()->GetMeshName(id));
	case 12:
		return QString::fromStdWString(PWEAPONMANAGER()->GetMatName(id));
	case 13:
		return QString::fromStdWString(PWEAPONMANAGER()->GetAniGroup(id));
	case 14:
		return QString::fromStdWString(PWEAPONMANAGER()->GetScriptName(id));
	default:
		return QVariant();
	}
}

QVariant PWeaponTableModule::headerData(int section, Qt::Orientation orientation, int role /* = Qt::DisplayRole */) const
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
			return QString("武器类型");
		case 5:
			return QString("攻击值");
		case 6:
			return QString("防御值");
		case 7:
			return QString("阵列值");
		case 8:
			return QString("先攻值");
		case 9:
			return QString("行动值");
		case 10:
			return QString("隐蔽值");
		case 11:
			return QString("模型名称");
		case 12:
			return QString("材质名称");
		case 13:
			return QString("动画组名称");
		case 14:
			return QString("脚本名称");
		default:
			return QVariant();
		}
	}
	else
		return QString("%1").arg(section);
}

bool PWeaponTableModule::insertRow(int row, const QModelIndex & parent /* = QModelIndex */)
{
	beginInsertRows(parent, PWEAPONMANAGER()->GetNum(),PWEAPONMANAGER()->GetNum());
	PWEAPONMANAGER()->AddPWeapon();
	endInsertRows();
	return true;
}

bool PWeaponTableModule::removeRow(int row, const QModelIndex & parent /* = QModelIndex */)
{
	beginRemoveRows(parent, row, row);
	std::wstring id = PWEAPONMANAGER()->GetID(row);
	PWEAPONMANAGER()->DelPWeapon(id);
	endRemoveRows();
	return true;
}

Qt::ItemFlags PWeaponTableModule::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return Qt::ItemIsEnabled;

	return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
}

bool PWeaponTableModule::setData(const QModelIndex &index, const QVariant &qvalue,int role /* = Qt::EditRole */)
{
	if (index.isValid() && role == Qt::EditRole) 
	{
		std::wstring id = PWEAPONMANAGER()->GetID(index.row());
		switch(index.column())
		{
		case 0:
			return PWEAPONMANAGER()->SetID(id, qvalue.toString().toStdWString());
		case 1:
			return PWEAPONMANAGER()->SetName(id, qvalue.toString().toStdWString());
		case 2:
			return PWEAPONMANAGER()->SetDescription(id, qvalue.toString().toStdWString());
		case 3:
			return PWEAPONMANAGER()->SetValue(id,qvalue.toInt());
		case 4:
			return PWEAPONMANAGER()->SetPWeaponType(id,qvalue.toInt());
		case 5:
			return PWEAPONMANAGER()->SetAttr(id,ATTR_ATTACK,qvalue.toInt());
		case 6:
			return PWEAPONMANAGER()->SetAttr(id,ATTR_DEFENSE,qvalue.toInt());
		case 7:
			return PWEAPONMANAGER()->SetAttr(id,ATTR_FORMATION,qvalue.toInt());
		case 8:
			return PWEAPONMANAGER()->SetAttr(id,ATTR_INITIATIVE,qvalue.toInt());
		case 9:
			return PWEAPONMANAGER()->SetAttr(id,ATTR_ACTIONPOINT,qvalue.toInt());
		case 10:
			return PWEAPONMANAGER()->SetAttr(id,ATTR_COVERT,qvalue.toInt());
		case 11:
			return PWEAPONMANAGER()->SetMeshName(id,qvalue.toString().toStdWString());
		case 12:
			return PWEAPONMANAGER()->SetMatName(id,qvalue.toString().toStdWString());
		case 13:
			return PWEAPONMANAGER()->SetAniGroup(id,qvalue.toString().toStdWString());
		case 14:
			return PWEAPONMANAGER()->SetScriptName(id,qvalue.toString().toStdWString());
		default:
			return false;
		}
	}
	return false;
}