#include "GUISupply.h"

#include "DataLibrary.h"
#include "StringTable.h"

#include "ItemData.h"

#include "boost/format.hpp"
#include <string>
#include <map>

GUISupply::GUISupply(int width,int height):GUIScene("supply.layout",width,height)
{
	setSceneLanguage();

	assignWidget(mSupplyBG,"SupplyBG");
	assignWidget(mArmyList,"ArmyList");

	MyGUI::ItemBox* baseItemBox;
	assignWidget(baseItemBox,"PWeaponItemBox");
	mPWeaponItemBox=new demo::ItemBox(baseItemBox);

	assignWidget(mSquadImage,"SquadImage");
	assignWidget(mTextSquadLeadName,"SquadLeadName");
	assignWidget(mTextSquadType,"SquadType");
	assignWidget(mTextSquadLv,"SquadLv");
	assignWidget(mTextSquadExp,"SquadExp");
	assignWidget(mTextSquadPWeapon,"SquadPWeapon");
	assignWidget(mTextSquadSWeapon,"SquadSWeapon");
	assignWidget(mTextSquadShield,"SquadShield");
	assignWidget(mTextSquadArmor,"SquadArmor");
	assignWidget(mTextSqureHorse,"SqureHorse");
	assignWidget(mTextSquadAttack,"SquadAttack");
	assignWidget(mTextSquadRangeAttack,"SquadRangeAttack");
	assignWidget(mTextSquadDefense,"SquadDefense");
	assignWidget(mTextSquadArray,"SquadArray");
	assignWidget(mTextSquadAgility,"SquadAgility");
	assignWidget(mTextSquadDetect,"SquadDetect");
	assignWidget(mTextSquadConcealment,"SquadConcealment");
	assignWidget(mTextSquadTenacity,"SquadTenacity");
	assignWidget(mTextSquadCounterattack,"SquadCounterattack");
	assignWidget(mTextSquadPeople,"SquadPeople");
	assignWidget(mTextSquadAP,"SquadAP");

	int i=0;
	for(i=0;i<SQUAD_SKILL_NUM;i++)
	{
		assignWidget(mSquadSkillIcon[i],str(boost::format("SquadSkillIcon%1%")%(i+1)));
	}

	for(i=0;i<SQUAD_PASSIVE_SKILL_NUM;i++)
	{
		assignWidget(mSquadPassiveSkillIcon[i],str(boost::format("SquadPassiveSkillIcon%1%")%(i+1)));
	}

	for(i=0;i<SQUAD_USE_EQUIP_NUM;i++)
	{
		assignWidget(mSquadUseEquipIcon[i],str(boost::format("SquadUseEquipIcon%1%")%(i+1)));
	}

	for(i=0;i<SQUAD_EFFECT_NUM;i++)
	{
		assignWidget(mSquadEffectIcon[i],str(boost::format("SquadEffectIcon%1%")%(i+1)));
	}

	createBattleSquad();
	refreshArmyList();

	mArmyList->eventListMouseItemActivate+= MyGUI::newDelegate(this, &GUISupply::onSelect);
}

GUISupply::~GUISupply(void)
{
	clearBattleSquad();
}

void GUISupply::clearBattleSquad()
{
	//Ïú»ÙBattleDate
	for(std::vector<BattleSquad*>::iterator it=mBattleSquad.begin();it!=mBattleSquad.end();it++)
	{
		delete (*it);
	}

	mBattleSquad.clear();
}

void GUISupply::createBattleSquad()
{
	//¶ÁÈ¡BattleData
	clearBattleSquad();

	std::vector<std::string> child=DataLibrary::getSingletonPtr()->getChildList("GameData/BattleData/SquadList");
	for(std::vector<std::string>::iterator it=child.begin();it!=child.end();it++)
	{
		mBattleSquad.push_back(new BattleSquad(std::string("GameData/BattleData/SquadList/")+(*it)));
	}
}

void GUISupply::refreshArmyList()
{
	mArmyList->removeAllItems();
	for(std::vector<BattleSquad*>::iterator it=mBattleSquad.begin();it!=mBattleSquad.end();it++)
	{
		mArmyList->addItem((*it)->getName());
	}
}

void GUISupply::showArmy( int index )
{
	BattleSquad* army=mBattleSquad.at(index);
	
	std::string tempstr,temppath;
	tempstr = army->getLeaderId();
	temppath = str(boost::format("StaticData/LeaderDate/%1%/Picture")%tempstr);
	bool re = DataLibrary::getSingletonPtr()->getData(temppath, tempstr);
	mSquadImage->setImageTexture(tempstr);

	mTextSquadLeadName->setCaption(army->getName());
	mTextSquadType->setCaption(getItemNameFormLanguage("LeaderDate",army->getLeaderId()));
	mTextSquadLv->setCaption(Ogre::StringConverter::toString(army->getLevel()));
	mTextSquadExp->setCaption(Ogre::StringConverter::toString(army->getExp()));
	mTextSquadPWeapon->setCaption(getItemNameFormLanguage("PweaponData",army->getPweaponId()));
	mTextSquadSWeapon->setCaption(getItemNameFormLanguage("SweaponData",army->getSweaponId()));
	mTextSquadShield->setCaption(getItemNameFormLanguage("ShieldData",army->getShieldId()));
	mTextSquadArmor->setCaption(getItemNameFormLanguage("ArmorData",army->getArmorId()));
	mTextSqureHorse->setCaption(getItemNameFormLanguage("HorseData",army->getHorseId()));

	showAttribute(index,0,"");
}

std::string GUISupply::itemCompare(BattleSquad* newSquad,BattleSquad* oldSquad,AttrType type)
{
	int oldAttr=oldSquad->getAttr(type,ATTRCALC_FULL);
	int newAttr=newSquad->getAttr(type,ATTRCALC_FULL);

	int difference=newAttr-oldAttr;
	if(difference>0)
	{
		return Ogre::StringConverter::toString(newAttr) +" (+"+Ogre::StringConverter::toString(difference)+")";
	}
	else if(difference==0)
	{
		return Ogre::StringConverter::toString(oldAttr);
	}
	else if(difference<0)
	{
		return Ogre::StringConverter::toString(newAttr) +" (-"+Ogre::StringConverter::toString(difference)+")";
	}
}

void GUISupply::showAttribute(int index,int itemType,std::string itemID)
{
	BattleSquad* army=mBattleSquad.at(index);

	mTextSquadAttack->setCaption(Ogre::StringConverter::toString(army->getAttr(ATTR_ATTACK,ATTRCALC_FULL)));
	mTextSquadRangeAttack->setCaption(Ogre::StringConverter::toString(army->getAttr(ATTR_RANGEDATTACK,ATTRCALC_FULL)));
	mTextSquadDefense->setCaption(Ogre::StringConverter::toString(army->getAttr(ATTR_DEFENCE,ATTRCALC_FULL)));
	mTextSquadArray->setCaption(Ogre::StringConverter::toString(army->getAttr(ATTR_FORM,ATTRCALC_FULL)));
	mTextSquadAgility->setCaption(Ogre::StringConverter::toString(army->getAttr(ATTR_INITIATIVE,ATTRCALC_FULL)));
	mTextSquadDetect->setCaption(Ogre::StringConverter::toString(army->getAttr(ATTR_DETECTION,ATTRCALC_FULL)));
	mTextSquadConcealment->setCaption(Ogre::StringConverter::toString(army->getAttr(ATTR_COVERT,ATTRCALC_FULL)));
	mTextSquadTenacity->setCaption(Ogre::StringConverter::toString(army->getAttr(ATTR_TOUGHNESS,ATTRCALC_FULL)));
	mTextSquadAP->setCaption(Ogre::StringConverter::toString(army->getAttr(ATTR_ACTIONPOINT,ATTRCALC_FULL)));
	mTextSquadCounterattack->setCaption(Ogre::StringConverter::toString(army->getAttr(ATTR_CONTER,ATTRCALC_FULL)));
	mTextSquadPeople->setCaption(Ogre::StringConverter::toString(army->getUnitNum()));
	
	m_SquadSkillNum=0;
	m_SquadPassiveSkillNum=0;
	m_SquadUseEquipNum=0;
	m_SquadEffectNum=0;
	std::map<std::string,enumtype> skillmap=army->getSkillTable();

	for(std::map<std::string,enumtype>::iterator it=skillmap.begin();it!=skillmap.end();it++)
	{
		if(it->second==SKILLTYPE_ACTIVE)
		{
			mSquadSkillIcon[m_SquadSkillNum]->setItemResource(it->first);
			m_SquadSkillNum++;
		}
		else if(it->second==SKILLTYPE_PASSIVE)
		{
			mSquadPassiveSkillIcon[m_SquadPassiveSkillNum]->setItemResource(it->first);
			m_SquadPassiveSkillNum++;
		}
		else if (it->second==SKILLTYPE_EQUIP)
		{
			mSquadUseEquipIcon[m_SquadUseEquipNum]->setItemResource(it->first);
			m_SquadUseEquipNum++;
		}
	}
}

void GUISupply::showItem(ItemType type)
{
	std::string path;
	demo::ItemBox* itemBox;
	switch(type)
	{
	case ePWeapon:
		path="StaticData/PweaponData";
		itemBox=mPWeaponItemBox;
		break;
	case eSWeapon:
		break;
	}

	itemBox->removeAllItems();
	std::vector<std::string> child=DataLibrary::getSingletonPtr()->getChildList(path);
	for(std::vector<std::string>::iterator it=child.begin();it!=child.end();it++)
	{
		itemBox->addItem(new demo::ItemData((*it)));
	}
}

std::string GUISupply::getItemNameFormLanguage(std::string type,std::string name)
{

	if(name == "none")
		return StringTable::getSingleton().getString(name);
	else
	{
		std::string tempstr;
		std::string temppath = std::string("StaticData/")+type+"/"+ name + std::string("/Name");
		DataLibrary::getSingletonPtr()->getData(temppath,tempstr);
		return tempstr;
	}
}

void GUISupply::onSelect( MyGUI::ListBox* _sender, size_t _index )
{
	if(_index!=-1)
	{
		showArmy(_index);
		showItem(ePWeapon);
		m_CurrIndex=_index;
	}
}

void GUISupply::showScene( std::string arg )
{

}

void GUISupply::hideScene()
{

}

void GUISupply::FrameEvent()
{

}
