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
	mPWeaponItemBox=new WeaponItemBox(baseItemBox);
	mPWeaponItemBox->getItemBox()->eventMouseItemActivate+= MyGUI::newDelegate(this, &GUISupply::eventMouseItemActivate);
	mPWeaponItemBox->getItemBox()->eventSelectItemAccept+= MyGUI::newDelegate(this, &GUISupply::eventSelectItemAccept);

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

	m_CurrSelectType=EQUIP_PWEAPON;
	DataLibrary::getSingletonPtr()->setData("GameData/StoryData/Money",1000);
	m_Money=0;
	DataLibrary::getSingletonPtr()->getData("GameData/StoryData/Money",m_Money);
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

std::string GUISupply::itemCompare(BattleSquad* compareSquad,BattleSquad* squad,AttrType type)
{
	float oldAttr=squad->getAttr(type,ATTRCALC_FULL);

	if(compareSquad!=NULL)
	{
		float newAttr=compareSquad->getAttr(type,ATTRCALC_FULL);

		float difference=newAttr-oldAttr;
		if(difference>0)
		{
			return "#00FF00" + Ogre::StringConverter::toString(newAttr) +" (+"+Ogre::StringConverter::toString(difference)+")";
		}
		else if(difference==0)
		{
			return Ogre::StringConverter::toString(oldAttr);
		}
		else
		{
			return "#FF0000"+Ogre::StringConverter::toString(newAttr) +" (-"+Ogre::StringConverter::toString(abs(difference))+")";
		}
	}
	else
	{
		return Ogre::StringConverter::toString(oldAttr);
	}
}

void GUISupply::eventMouseItemActivate(MyGUI::ItemBox* _sender, size_t _index)
{
	if(_index!=-1)
	{
		WeaponItemData* item=*(_sender->getItemDataAt<WeaponItemData*>(_index));
		showAttribute(m_CurrSquadIndex,m_CurrSelectType,item->getID());
	}
	else
	{
		showAttribute(m_CurrSquadIndex,0,"");
	}
}

void GUISupply::eventSelectItemAccept(MyGUI::ItemBox* _sender, size_t _index)
{
	if(_index!=-1)
	{
		WeaponItemData* item=*(_sender->getItemDataAt<WeaponItemData*>(_index));
		buyItem(m_CurrSquadIndex,item);
	}
}

void GUISupply::showAttribute(int index,int itemType,std::string itemID)
{
	BattleSquad* army=mBattleSquad.at(index);
	BattleSquad* copySquad=NULL;
	if(itemID!="")
	{
		DataLibrary::getSingletonPtr()->copyNode(army->getPath(),"GameData/BattleData/SquadList/TempSquad");
		copySquad=new BattleSquad("GameData/BattleData/SquadList/TempSquad");
		copySquad->equipEquipment(itemType,itemID);

	}

	mTextSquadAttack->setCaption(itemCompare(copySquad,army,ATTR_ATTACK));
	mTextSquadRangeAttack->setCaption(itemCompare(copySquad,army,ATTR_RANGEDATTACK));
	mTextSquadDefense->setCaption(itemCompare(copySquad,army,ATTR_DEFENCE));
	mTextSquadArray->setCaption(itemCompare(copySquad,army,ATTR_FORM));
	mTextSquadAgility->setCaption(itemCompare(copySquad,army,ATTR_INITIATIVE));
	mTextSquadDetect->setCaption(itemCompare(copySquad,army,ATTR_DETECTION));
	mTextSquadConcealment->setCaption(itemCompare(copySquad,army,ATTR_COVERT));
	mTextSquadTenacity->setCaption(itemCompare(copySquad,army,ATTR_TOUGHNESS));
	mTextSquadAP->setCaption(itemCompare(copySquad,army,ATTR_ACTIONPOINT));
	mTextSquadCounterattack->setCaption(itemCompare(copySquad,army,ATTR_CONTER));
	mTextSquadPeople->setCaption(Ogre::StringConverter::toString(army->getUnitNum()));
	
	m_SquadSkillNum=0;
	m_SquadPassiveSkillNum=0;
	m_SquadUseEquipNum=0;
	m_SquadEffectNum=0;
	std::map<std::string,enumtype> skillmap;
	if(itemID!="")
		skillmap=copySquad->getSkillTable();
	else
		skillmap=army->getSkillTable();

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

	if(itemID!="")
	{
		delete copySquad;
		DataLibrary::getSingletonPtr()->delNode("GameData/BattleData/SquadList/TempSquad");
	}

}

void GUISupply::showItem(int type)
{
	std::string path;
	WeaponItemBox* itemBox;
	std::string equipID;
	int equipType=type;
	BattleSquad* army=mBattleSquad.at(m_CurrSquadIndex);

	switch(type)
	{
	case EQUIP_PWEAPON:
		path="StaticData/PweaponData";
		itemBox=mPWeaponItemBox;
		equipID=army->getPweaponId();
		break;
	}

	itemBox->removeAllItems();
	std::vector<std::string> child=DataLibrary::getSingletonPtr()->getChildList(path);
	for(std::vector<std::string>::iterator it=child.begin();it!=child.end();it++)
	{
		WeaponItemData* data=new WeaponItemData(equipType,(*it));
		if((*it)==equipID)
		{
			data->setEquip(true);
		}
		itemBox->addItem(data);
	}
}

void GUISupply::buyItem(int index,WeaponItemData* item)
{
	BattleSquad* army=mBattleSquad.at(index);

	if(!item->getEquip() && item->getCanBuy())
	{
		army->equipEquipment(item->getType(),item->getID());

		showArmy(m_CurrSquadIndex);
		showItem(item->getType());

		m_Money-=item->getPriceValue();
		DataLibrary::getSingletonPtr()->setData("GameData/StoryData/Money",m_Money);
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
		m_CurrSquadIndex=_index;
		showArmy(_index);
		showItem(EQUIP_PWEAPON);
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
