#include "GUITargetWindow.h"

#include "DataLibrary.h"
#include "StringTable.h"
#include "boost/format.hpp"
#include <math.h>

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
	if(mSelectSquad->getUnitNum() == 0)
	{
		setSquad(NULL);
		return;
	}
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	std::string tempstr,temppath;
	tempstr = mSelectSquad->getLeaderId();
	temppath = str(boost::format("StaticData/LeaderDate/%1%/Picture")%tempstr);
	bool re = datalib->getData(temppath, tempstr);
	mSquadImage->setImageTexture(tempstr);

	tempstr = mSelectSquad->getFactionId();
	temppath = str(boost::format("StaticData/FactionData/%1%/LittlePicture")%tempstr);
	re = datalib->getData(temppath,tempstr);
	mSquadFactionImage->setImageTexture(tempstr);

	tempstr = mSelectSquad->getLeaderId();
	temppath = str(boost::format("StaticData/LeaderDate/%1%/Name")%tempstr);
	re = datalib->getData(temppath, tempstr);
	mSquadLeadName->setCaption(tempstr);

	mSquadTypeName->setCaption(mSelectSquad->getName());

	int x,y;
	x = mSelectSquad->getGridX();
	y = mSelectSquad->getGridY();
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
	tempfloat = mSelectSquad->getAttr(ATTR_ATTACK,ATTRCALC_FULL);
	mSquadAttack->setCaption(str(boost::format("%1%")%floor(tempfloat+0.5f)));
	tempfloat = mSelectSquad->getAttr(ATTR_DEFENCE,ATTRCALC_FULL);
	mSquadDefence->setCaption(str(boost::format("%1%")%floor(tempfloat+0.5f)));

	x = mSelectSquad->getUnitMaxNum();
	y = mSelectSquad->getUnitNum();
	// 	int morale;
	// 	re = DataLibrary::getSingletonPtr()->getData(datapath+"/SoilderId",tempstr);
	// 	re = DataLibrary::getSingletonPtr()->getData(std::string("StaticData/SoilderData/") + tempstr + std::string("/Morale"),morale);
	// 	if(morale == 1)
	// 	{
	// 		re = DataLibrary::getSingletonPtr()->getData(datapath+"/Morale",morale);
	// 	}
	mSquadUnitNum->setCaption(str(boost::format(StringTable::getSingletonPtr()->getString("SquadUnitNumNoInjSimple"))%y%x));

	x = mSelectSquad->getActionPoint();
	mSquadAp->setCaption(Ogre::StringConverter::toString(x));

	tempstr = mSelectSquad->getPweaponId();
	if(tempstr == "none")
		mSquadPWeapon->setCaption(StringTable::getSingleton().getString(tempstr));
	else
	{
		temppath = std::string("StaticData/PweaponData/") + tempstr + std::string("/Name");
		re = datalib->getData(temppath,tempstr);
		mSquadPWeapon->setCaption(tempstr);
	}
	tempstr = mSelectSquad->getSweaponId();
	if(tempstr == "none")
		mSquadSWeapon->setCaption(StringTable::getSingleton().getString(tempstr));
	else
	{
		temppath = std::string("StaticData/SweaponData/") + tempstr + std::string("/Name");
		re = DataLibrary::getSingletonPtr()->getData(temppath,tempstr);
		mSquadSWeapon->setCaption(tempstr);
	}
	tempstr = mSelectSquad->getShieldId();
	if(tempstr == "none")
		mSquadShield->setCaption(StringTable::getSingleton().getString(tempstr));
	else
	{
		temppath = std::string("StaticData/ShieldData/") + tempstr + std::string("/Name");
		re = DataLibrary::getSingletonPtr()->getData(temppath,tempstr);
		mSquadShield->setCaption(tempstr);
	}

	tempstr = mSelectSquad->getArmorId();
	if(tempstr == "none")
		mSquadArmor->setCaption(StringTable::getSingleton().getString(tempstr));
	else
	{
		temppath = std::string("StaticData/ArmorData/") + tempstr + std::string("/Name");
		re = DataLibrary::getSingletonPtr()->getData(temppath,tempstr);
		mSquadArmor->setCaption(tempstr);
	}
}