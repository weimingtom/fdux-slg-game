#include "ui_mainwindow.h"
#include <QInputDialog>
#include <QMessageBox>

#include "DataEditorControl.h"
#include "soldiertablemodule.h"
#include "horsetablemodule.h"
#include "pweapontablemodule.h"
#include "sweapontablemodule.h"
#include "armortablemodule.h"
#include "shieldtablemodule.h"
#include "skilltablemodule.h"
#include "effecttablemodule.h"
#include "squadtablemodule.h"
#include "squadskilltablemodule.h"
#include "stringtablemodule.h"

#include "DataManager.h"

#define SAFEDEL(a) if(!a) { delete a; a = NULL;}

DataEditorControl::DataEditorControl(Ui::MainWindow *ui)
{
	//设置视图模型
	mSoldierTableModule = new SoldierTableModule(this);
	mSoldierTableView = ui->soldierTableView;
	mSoldierTableView->setModel(mSoldierTableModule);

	mHorseTableModule = new HorseTableModule(this);
	mHorseTableView = ui->horseTableView;
	mHorseTableView->setModel(mHorseTableModule);

	mPWeaponTableModule = new PWeaponTableModule(this);
	mPWeaponTableView = ui->pweaponTableView;
	mPWeaponTableView->setModel(mPWeaponTableModule);

	mSWeaponTableModule = new SWeaponTableModule(this);
	mSWeaponTableView = ui->sweaponTableView;
	mSWeaponTableView->setModel(mSWeaponTableModule);

	mArmorTableModule = new ArmorTableModule(this);
	mArmorTableView = ui->armorTableView;
	mArmorTableView->setModel(mArmorTableModule);

	mShieldTableModule = new ShieldTableModule(this);
	mShieldTableView = ui->shieldTableView;
	mShieldTableView->setModel(mShieldTableModule);

	mSkillTableModule = new SkillTableModule(this);
	mSkillTableView = ui->skillTableView;
	mSkillTableView->setModel(mSkillTableModule);

	mEffectTableModule = new EffectTableModule(this);
	mEffectTableView = ui->effectTableView;
	mEffectTableView->setModel(mEffectTableModule);

	mSquadTableModule = new SquadTableModule(this);
	mSquadTableView = ui->squadTableView;
	mSquadTableView->setModel(mSquadTableModule);

	mSquadSkillTableModule = new SquadSkillTableModule(this);
	mSquadSkillTableView = ui->squadSkillTableView;
	mSquadSkillTableView->setModel(mSquadSkillTableModule);

	mStringTableModule = new StringTableModule(this);
	mStringTableView = ui->stringTableView;
	mStringTableView->setModel(mStringTableModule);

	mModBox = ui->modBox;
	mLangBox = ui->langBox;
	RefreshModList();

	//连接消息
	connect(ui->addMod,SIGNAL(clicked()),this,SLOT(AddMod()));
	connect(ui->addLang,SIGNAL(clicked()),this,SLOT(AddLang()));
	connect(ui->addSoldier,SIGNAL(clicked()),this,SLOT(AddSoldier()));
	connect(ui->delSoldier,SIGNAL(clicked()),this,SLOT(DelSoldier()));
	connect(ui->addHorse,SIGNAL(clicked()),this,SLOT(AddHorse()));
	connect(ui->delHorse,SIGNAL(clicked()),this,SLOT(DelHorse()));
	connect(ui->addPWeapon,SIGNAL(clicked()),this,SLOT(AddPWeapon()));
	connect(ui->delPWeapon,SIGNAL(clicked()),this,SLOT(DelPWeapon()));
	connect(ui->addSWeapon,SIGNAL(clicked()),this,SLOT(AddSWeapon()));
	connect(ui->delSWeapon,SIGNAL(clicked()),this,SLOT(DelSWeapon()));
	connect(ui->addArmor,SIGNAL(clicked()),this,SLOT(AddArmor()));
	connect(ui->delArmor,SIGNAL(clicked()),this,SLOT(DelArmor()));
	connect(ui->addShield,SIGNAL(clicked()),this,SLOT(AddShield()));
	connect(ui->delShield,SIGNAL(clicked()),this,SLOT(DelShield()));
	connect(ui->addSkill,SIGNAL(clicked()),this,SLOT(AddSkill()));
	connect(ui->delSkill,SIGNAL(clicked()),this,SLOT(DelSkill()));
	connect(ui->addEffect,SIGNAL(clicked()),this,SLOT(AddEffect()));
	connect(ui->delEffect,SIGNAL(clicked()),this,SLOT(DelEffect()));
	connect(ui->addSquad,SIGNAL(clicked()),this,SLOT(AddSquad()));
	connect(ui->delSquad,SIGNAL(clicked()),this,SLOT(DelSquad()));
	connect(ui->addSquadSkill,SIGNAL(clicked()),this,SLOT(AddSquadSkill()));
	connect(ui->delSquadSkill,SIGNAL(clicked()),this,SLOT(DelSquadSkill()));
	connect(ui->addString,SIGNAL(clicked()),this,SLOT(AddString()));
	connect(ui->delString,SIGNAL(clicked()),this,SLOT(DelString()));

	connect(ui->squadTableView,SIGNAL(clicked(const QModelIndex &)),this,SLOT(SelectSquad(const QModelIndex &)));
}

DataEditorControl::~DataEditorControl()
{

}

void DataEditorControl::RefreshModList()
{
	DataManager* dataManager = DataManager::getSingletonPtr();
	DataManager::DirIter it;
	int index;
	disconnect(mModBox,SIGNAL(currentIndexChanged(QString)),this,SLOT(ModBoxChanged(QString)));
	mModBox->clear ();
	for(it = dataManager->mModList.begin();it != dataManager->mModList.end(); it++)
		mModBox->addItem(QString::fromStdWString(*it));
	connect(mModBox,SIGNAL(currentIndexChanged(QString)),this,SLOT(ModBoxChanged(QString)));
	index = mModBox->findText(QString::fromStdWString(*dataManager->mCurMod));
	mModBox->setCurrentIndex(index);
	RefreshLangList();
}

void DataEditorControl::RefreshLangList()
{
	DataManager* dataManager = DataManager::getSingletonPtr();
	DataManager::DirIter it;
	int index;
	disconnect(mLangBox,SIGNAL(currentIndexChanged(QString)),this,SLOT(LangBoxChanged(QString)));
	mLangBox->clear();
	for(it = dataManager->mLangList.begin();it != dataManager->mLangList.end(); it++)
		mLangBox->addItem(QString::fromStdWString(*it));
	connect(mLangBox,SIGNAL(currentIndexChanged(QString)),this,SLOT(LangBoxChanged(QString)));
	index = mLangBox->findText(QString::fromStdWString(*dataManager->mCurLang));
	mLangBox->setCurrentIndex(index);
}

void DataEditorControl::ModBoxChanged(const QString & text)
{
	DataManager::getSingleton().ChangeMod(text.toStdWString());
	RefreshLangList();
	mStringTableModule->ModChanged();
	mSoldierTableModule->ModChanged();
	mHorseTableModule->ModChanged();
	mPWeaponTableModule->ModChanged();
	mSWeaponTableModule->ModChanged();
	mArmorTableModule->ModChanged();
	mShieldTableModule->ModChanged();
	mEffectTableModule->ModChanged();
	mSkillTableModule->ModChanged();
	mSquadTableModule->ModChanged();
	mSquadSkillTableModule->ModChanged();
}

void DataEditorControl::LangBoxChanged(const QString & text)
{
	DataManager::getSingleton().ChangeLang(text.toStdWString());
	mStringTableModule->ModChanged();
	mSoldierTableModule->ModChanged();
	mHorseTableModule->ModChanged();
	mPWeaponTableModule->ModChanged();
	mSWeaponTableModule->ModChanged();
	mArmorTableModule->ModChanged();
	mShieldTableModule->ModChanged();
	mEffectTableModule->ModChanged();
	mSkillTableModule->ModChanged();
	mSquadTableModule->ModChanged();
	mSquadSkillTableModule->ModChanged();
}

void DataEditorControl::AddSoldier()
{
	mSoldierTableModule->insertRow();
}

void DataEditorControl::DelSoldier()
{
	QModelIndexList indexlist = mSoldierTableView->selectionModel()->selectedIndexes();
	if (indexlist.size() > 0)
		mSoldierTableModule->removeRow(indexlist.begin()->row());
}

void DataEditorControl::AddHorse()
{
	mHorseTableModule->insertRow();
}

void DataEditorControl::DelHorse()
{
	QModelIndexList indexlist = mHorseTableView->selectionModel()->selectedIndexes();
	if (indexlist.size() > 0)
		mHorseTableModule->removeRow(indexlist.begin()->row());
}

void DataEditorControl::AddMod()
{
	bool ok;
	QString text = QInputDialog::getText(mModBox, tr("请输入模组名称"),
		tr("模组名称:"), QLineEdit::Normal,
		QString(), &ok);
	if (ok && !text.isEmpty())
	{
		DataManager::getSingleton().ChangeMod(text.toStdWString ());
		RefreshModList();
	}
}

void DataEditorControl::AddLang()
{
	bool ok;
	QString text = QInputDialog::getText(mLangBox, tr("请输入语言名称"),
		tr("语言名称:"), QLineEdit::Normal,
		QString(), &ok);
	if (ok && !text.isEmpty())
	{
		DataManager::getSingleton().ChangeLang(text.toStdWString ());
		RefreshLangList();
	}
}

void DataEditorControl::AddPWeapon()
{
	mPWeaponTableModule->insertRow();
}

void DataEditorControl::DelPWeapon()
{
	QModelIndexList indexlist = mPWeaponTableView->selectionModel()->selectedIndexes();
	if (indexlist.size() > 0)
		mPWeaponTableModule->removeRow(indexlist.begin()->row());
}

void DataEditorControl::AddSWeapon()
{
	mSWeaponTableModule->insertRow();
}

void DataEditorControl::DelSWeapon()
{
	QModelIndexList indexlist = mSWeaponTableView->selectionModel()->selectedIndexes();
	if (indexlist.size() > 0)
		mSWeaponTableModule->removeRow(indexlist.begin()->row());
}

void DataEditorControl::AddArmor()
{
	mArmorTableModule->insertRow();
}

void DataEditorControl::DelArmor()
{
	QModelIndexList indexlist = mArmorTableView->selectionModel()->selectedIndexes();
	if (indexlist.size() > 0)
		mArmorTableModule->removeRow(indexlist.begin()->row());
}

void DataEditorControl::AddShield()
{
	mShieldTableModule->insertRow();
}

void DataEditorControl::DelShield()
{
	QModelIndexList indexlist = mShieldTableView->selectionModel()->selectedIndexes();
	if (indexlist.size() > 0)
		mShieldTableModule->removeRow(indexlist.begin()->row());
}

void DataEditorControl::AddSkill()
{
	mSkillTableModule->insertRow();
}

void DataEditorControl::DelSkill()
{
	QModelIndexList indexlist = mSkillTableView->selectionModel()->selectedIndexes();
	if (indexlist.size() > 0)
		mSkillTableModule->removeRow(indexlist.begin()->row());
}

void DataEditorControl::AddEffect()
{
	mEffectTableModule->insertRow();
}

void DataEditorControl::DelEffect()
{
	QModelIndexList indexlist = mEffectTableView->selectionModel()->selectedIndexes();
	if (indexlist.size() > 0)
		mEffectTableModule->removeRow(indexlist.begin()->row());
}

void DataEditorControl::AddSquad()
{
	mSquadTableModule->insertRow();
}

void DataEditorControl::DelSquad()
{
	QModelIndexList indexlist = mSquadTableView->selectionModel()->selectedIndexes();
	if (indexlist.size() > 0)
		mSquadTableModule->removeRow(indexlist.begin()->row());
}

void DataEditorControl::AddSquadSkill()
{
	QModelIndexList indexlist = mSquadSkillTableView->selectionModel()->selectedIndexes();
	if (indexlist.size() > 0)
		mSquadSkillTableModule->markRow(indexlist.begin()->row());
}

void DataEditorControl::DelSquadSkill()
{
	QModelIndexList indexlist = mSquadSkillTableView->selectionModel()->selectedIndexes();
	if (indexlist.size() > 0)
		mSquadSkillTableModule->unmarkRow(indexlist.begin()->row());
}

void DataEditorControl::AddString()
{
	mStringTableModule->insertRow();
}

void DataEditorControl::DelString()
{
	QModelIndexList indexlist = mStringTableView->selectionModel()->selectedIndexes();
	if (indexlist.size() > 0)
		mStringTableModule->removeRow(indexlist.begin()->row());
}

void DataEditorControl::SelectSquad(QModelIndex _index)
{
	mSquadSkillTableModule->SquadSelected(_index.row());
}