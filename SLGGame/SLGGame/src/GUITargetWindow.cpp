#include "GUITargetWindow.h"

#include "DataLibrary.h"
#include "StringTable.h"
#include "boost/format.hpp"

#include "BattleSquad.h"
#include "BattleSquadManager.h"

GUITargetWindows::GUITargetWindows(MyGUI::Window* window,int Width,int Height):GUISubWindows(window,Width,Height),mWindow(window)
{
	assignWidget(mSquadLeadName,"TargetLeadName");
	assignWidget(mSquadTypeName,"TargetType");
	assignWidget(mSquadGridX,"TargetGridX");
	assignWidget(mSquadGridY,"TargetGridY");
	assignWidget(mSquadPWeapon,"TargetPWeapon");
	assignWidget(mSquadSWeapon,"TargetSWeapon");
	assignWidget(mSquadShield,"TargetShield");
	assignWidget(mSquadArmor,"TargetArmor");
	assignWidget(mSquadUnitNum,"TargetUnitNum");
	assignWidget(mSquadAp,"TargetAp");
	assignWidget(mSquadAttack,"TargetAttack");
	assignWidget(mSquadDefence,"TargetDefence");
	assignWidget(mSquadDirection,"TargetDirection");
	assignWidget(mSquadFormation,"TargetFormation");

	MyGUI::TextBox* textBox;
	assignWidget(textBox,"FormationLabel");
	textBox->setCaption(StringTable::getSingleton().getString("Formation"));
	assignWidget(textBox,"DirectionLabel");
	textBox->setCaption(StringTable::getSingleton().getString("Direction"));

	assignWidget(mSquadImage,"TargetImage");
	assignWidget(mSquadFactionImage,"TargetFactionImage");


	window->setPosition(Width-window->getWidth(),Height-window->getHeight());

	mCurX = -1;
	mCurY = -1;

	setSquad(NULL);
}

GUITargetWindows::~GUITargetWindows(void)
{
}

void GUITargetWindows::showScene( std::string arg )
{
	mWindow->setVisible(true);
}

void GUITargetWindows::hideScene()
{
	mWindow->setVisible(false);
}

void GUITargetWindows::FrameEvent()
{
	//updateSquad();
}

bool GUITargetWindows::GridInputEvent( int x,int y )
{
	if(mCurY == y && mCurX == x)
		return false;
	mCurX = x;
	mCurY = y;
	
	BattleSquadManager* battlemanager = BattleSquadManager::getSingletonPtr();
	BattleSquad* battesquade = battlemanager->getBattleSquadAt(mCurX,mCurY,1,true);
	setSquad(battesquade);
	/*
	for(int n = 0; n < battlemanager->mSquadList.size(); n++)
	{
		battlemanager->mSquadList[n]->getCrood(&x,&y);
		if(x == mCurX && y == mCurY)
		{
			if(battlemanager->mSquadList[n]->viewbyTeam(0))
				setSquad(battlemanager->mSquadList[n]);
			else
				setSquad(NULL);
			return false;
		}
	}
	setSquad(NULL);
	*/
	return false;
}

void GUITargetWindows::setSquad(BattleSquad* squad)
{
	mSelectSquad = squad;
	if(mSelectSquad == NULL)
		hideScene();
	else
	{
		showScene("");
		updateSquad();
	}
}

void GUITargetWindows::updateSquad()
{
	if(mSelectSquad ==NULL)
		return;
	std::string tempstr,temppath;
	std::string datapath = mSelectSquad->getPath();
	bool re = DataLibrary::getSingletonPtr()->getData(datapath+"/LeaderPicture",tempstr);
	mSquadImage->setImageTexture(tempstr);
	tempstr = mSelectSquad->getFactionId();
	temppath = std::string("StaticData/FactionData/") + tempstr + std::string("/LittlePicture");
	re = DataLibrary::getSingletonPtr()->getData(temppath,tempstr);
	mSquadFactionImage->setImageTexture(tempstr);

	re = DataLibrary::getSingletonPtr()->getData(datapath+"/LeaderName",tempstr);
	mSquadLeadName->setCaption(tempstr);
	re = DataLibrary::getSingletonPtr()->getData(datapath+"/Name",tempstr);
	mSquadTypeName->setCaption(tempstr);
	int x,y;
	mSelectSquad->getCrood(&x,&y);
	mSquadGridX->setCaption(Ogre::StringConverter::toString(x));
	mSquadGridY->setCaption(Ogre::StringConverter::toString(y));

	x = mSelectSquad->getDirection();
	switch(x)
	{
	case North:
		mSquadDirection->setCaption(StringTable::getSingleton().getString("DirectionNorth"));
		break;
	case South:
		mSquadDirection->setCaption(StringTable::getSingleton().getString("DirectionSouth"));
		break;
	case West:
		mSquadDirection->setCaption(StringTable::getSingleton().getString("DirectionWest"));
		break;
	case East:
		mSquadDirection->setCaption(StringTable::getSingleton().getString("DirectionEast"));
		break;
	}

	y = mSelectSquad->getFormation();
	switch(y)
	{
	case Line:
		mSquadFormation->setCaption(StringTable::getSingleton().getString("FormationLine"));
		break;
	case Circular:
		mSquadFormation->setCaption(StringTable::getSingleton().getString("FormationCirc"));
		break;
	case Loose:
		mSquadFormation->setCaption(StringTable::getSingleton().getString("FormationLoos"));
		break;
	}

	float tempfloat;
	tempfloat = mSelectSquad->getAttr(ATTR_ATTACK,ATTRCALC_FULL,x);
	mSquadAttack->setCaption(Ogre::StringConverter::toString(tempfloat));
	tempfloat = mSelectSquad->getAttr(ATTR_DEFENCE,ATTRCALC_FULL,x);
	mSquadDefence->setCaption(Ogre::StringConverter::toString(tempfloat));

	re = DataLibrary::getSingletonPtr()->getData(datapath+"/UnitMaxNumber",x);
	re = DataLibrary::getSingletonPtr()->getData(datapath+"/UnitNumber",y);
	int inj;
	re = DataLibrary::getSingletonPtr()->getData(datapath+"/SoilderId",tempstr);
	re = DataLibrary::getSingletonPtr()->getData(std::string("StaticData/SoilderData/") + tempstr + std::string("/Injury"),inj);
	if(inj == 1)
	{
		re = DataLibrary::getSingletonPtr()->getData(datapath+"/WoundNum",inj);
		mSquadUnitNum->setCaption(str(boost::format(StringTable::getSingletonPtr()->getString("SquadUnitNumSimple"))%y%inj%x));
	}
	else
		mSquadUnitNum->setCaption(str(boost::format(StringTable::getSingletonPtr()->getString("SquadUnitNumNoInjSimple"))%y%x));
	
	re = DataLibrary::getSingletonPtr()->getData(datapath+"/ActionPoint",x);
	mSquadAp->setCaption(Ogre::StringConverter::toString(x));

	re = DataLibrary::getSingletonPtr()->getData(datapath+"/PweaponId",tempstr);
	if(tempstr == "none")
		mSquadPWeapon->setCaption(StringTable::getSingleton().getString(tempstr));
	else
	{
		temppath = std::string("StaticData/PweaponData/") + tempstr + std::string("/Name");
		re = DataLibrary::getSingletonPtr()->getData(temppath,tempstr);
		mSquadPWeapon->setCaption(tempstr);
	}
	re = DataLibrary::getSingletonPtr()->getData(datapath+"/SweaponId",tempstr);
	if(tempstr == "none")
		mSquadSWeapon->setCaption(StringTable::getSingleton().getString(tempstr));
	else
	{
		temppath = std::string("StaticData/SweaponData/") + tempstr + std::string("/Name");
		re = DataLibrary::getSingletonPtr()->getData(temppath,tempstr);
		mSquadSWeapon->setCaption(tempstr);
	}
	re = DataLibrary::getSingletonPtr()->getData(datapath+"/ShieldId",tempstr);
	if(tempstr == "none")
		mSquadShield->setCaption(StringTable::getSingleton().getString(tempstr));
	else
	{
		temppath = std::string("StaticData/ShieldData/") + tempstr + std::string("/Name");
		re = DataLibrary::getSingletonPtr()->getData(temppath,tempstr);
		mSquadShield->setCaption(tempstr);
	}
	re = DataLibrary::getSingletonPtr()->getData(datapath+"/ArmorId",tempstr);
	if(tempstr == "none")
		mSquadArmor->setCaption(StringTable::getSingleton().getString(tempstr));
	else
	{
		temppath = std::string("StaticData/ArmorData/") + tempstr + std::string("/Name");
		re = DataLibrary::getSingletonPtr()->getData(temppath,tempstr);
		mSquadArmor->setCaption(tempstr);
	}
}