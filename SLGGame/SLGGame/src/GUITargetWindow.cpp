#include "GUITargetWindow.h"

#include "DataLibrary.h"
#include "StringTable.h"
#include "boost/format.hpp"
#include <math.h>

#include "BattleSquad.h"
#include "BattleSquadManager.h"
#include "GUIBattle.h"
#include "GUIEffectWindow.h"

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
	assignWidget(mSquadFormation,"TargetFormation");
	assignWidget(mSquadLevel,"TargetLevel");
	assignWidget(mSquadExp,"TargetExp");
	assignWidget(mSquadAttackFront,"TargetAttackFront");
	assignWidget(mSquadDefenceFront,"TargetDefenceFront");
	assignWidget(mSquadAttackFlank,"TargetAttackFlank");
	assignWidget(mSquadDefenceFlank,"TargetDefenceFlank");
	assignWidget(mSquadAttackBack,"TargetAttackBack");
	assignWidget(mSquadDefenceBack,"TargetDefenceBack");
	assignWidget(mSquadAttackRA,"TargetAttackRA");
	assignWidget(mSquadDefenceRA,"TargetDefenceRA");

	//assignWidget(textBox,"DirectionLabel");
	//textBox->setCaption(StringTable::getSingleton().getString("Direction"));

	assignWidget(mSquadImage,"TargetImage");
	assignWidget(mSquadFactionImage,"TargetFactionImage");


	window->setPosition(Width-window->getWidth(),Height-window->getHeight());

	mCurX = -1;
	mCurY = -1;

	mEffectWindow=NULL;

	setSquad(NULL);
}

GUITargetWindows::~GUITargetWindows(void)
{
}

void GUITargetWindows::showScene( std::string arg )
{
	mWindow->setVisible(true);

	if(mEffectWindow==NULL)
	{
		GUIBattle* battle=(GUIBattle*)GUISystem::getSingletonPtr()->getScene(BattleScene);
		mEffectWindow=(GUIEffectWindow*)battle->getSubWindow("EffectWindow2");
	}

	mEffectWindow->showScene("");
}

void GUITargetWindows::hideScene()
{
	mWindow->setVisible(false);
	if (mEffectWindow!=NULL)
	{
		mEffectWindow->hideScene();
	}
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
	BattleSquad* battesquade = battlemanager->getBattleSquadAt(mCurX,mCurY,0,true);
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
	//x = mSelectSquad->getGridX();
	//y = mSelectSquad->getGridY();
	//mSquadGridX->setCaption(Ogre::StringConverter::toString(x));
	//mSquadGridY->setCaption(Ogre::StringConverter::toString(y));
	x = mSelectSquad->getLevel();
	mSquadGridX->setCaption(Ogre::StringConverter::toString(x));

	//x = mSelectSquad->getDirection();
	//switch(x)
	//{
	//case North:
	//	mSquadDirection->setCaption(StringTable::getSingleton().getString("DirectionNorth"));
	//	break;
	//case South:
	//	mSquadDirection->setCaption(StringTable::getSingleton().getString("DirectionSouth"));
	//	break;
	//case West:
	//	mSquadDirection->setCaption(StringTable::getSingleton().getString("DirectionWest"));
	//	break;
	//case East:
	//	mSquadDirection->setCaption(StringTable::getSingleton().getString("DirectionEast"));
	//	break;
	//}

	y = mSelectSquad->getFormation();
	switch(y)
	{
	case Line:
		mSquadFormation->setCaption(str(boost::format("%1%(%2%)")%StringTable::getSingleton().getString("FormationLine")%mSelectSquad->getAttr(ATTR_FORM,ATTRCALC_FULL)));
		break;
	case Circular:
		mSquadFormation->setCaption(str(boost::format("%1%(%2%)")%StringTable::getSingleton().getString("FormationCirc")%mSelectSquad->getAttr(ATTR_FORM,ATTRCALC_FULL)));
		break;
	case Loose:
		mSquadFormation->setCaption(str(boost::format("%1%(%2%)")%StringTable::getSingleton().getString("FormationLoos")%mSelectSquad->getAttr(ATTR_FORM,ATTRCALC_FULL)));
		break;
	}

	mSquadAttackFront->setCaption(str(boost::format("%1%")%floor(mSelectSquad->getAtk(0)+0.5f)));
	mSquadAttackFlank->setCaption(str(boost::format("%1%")%floor(mSelectSquad->getAtk(1)+0.5f)));
	mSquadAttackBack->setCaption(str(boost::format("%1%")%floor(mSelectSquad->getAtk(2)+0.5f)));
	mSquadAttackRA->setCaption(str(boost::format("%1%")%floor(mSelectSquad->getRangedAtk()+0.5f)));

	mSquadDefenceFront->setCaption(str(boost::format("%1%")%floor(mSelectSquad->getDef(0)+0.5f)));
	mSquadDefenceFlank->setCaption(str(boost::format("%1%")%floor(mSelectSquad->getDef(1)+0.5f)));
	mSquadDefenceBack->setCaption(str(boost::format("%1%")%floor(mSelectSquad->getDef(2)+0.5f)));
	mSquadDefenceRA->setCaption(str(boost::format("%1%")%floor(mSelectSquad->getRangedDef()+0.5f)));

	x = mSelectSquad->getUnitMaxNum();
	y = mSelectSquad->getUnitNum();
	std::string xc,yc;
	if(mSelectSquad->getType()==0)
	{
		if(y<=50 && y>=35)
		{
			yc="#00FF00";
		}
		else if(y<=35 && y>=20)
		{
			yc="#FFFF00";
		}
		else if(y<=20)
		{
			yc="#FF5700";
		}

		if(x<=50 && x>=35)
		{
			xc="#00FF00";
		}
		else if(x<=35 && x>=20)
		{
			xc="#FFFF00";
		}
		else if(x<=20)
		{
			xc="#FF5700";
		}
	}
	else
	{
		if(y<=20 && y>=12)
		{
			yc="#00FF00";
		}
		else if(y<=12 && y>=5)
		{
			yc="#FFFF00";
		}
		else if(y<=5)
		{
			yc="#FF5700";
		}

		if(x<=20 && x>=12)
		{
			xc="#00FF00";
		}
		else if(x<=12 && x>=5)
		{
			xc="#FFFF00";
		}
		else if(x<=5)
		{
			xc="#FF5700";
		}
	}
	mSquadUnitNum->setCaption(str(boost::format(StringTable::getSingletonPtr()->getString("SquadUnitNumNoInjSimple"))%y%x%yc%xc));

	//	mSquadF->setCaption(str(boost::format(StringTable::getSingletonPtr()->getString("SquadF"))%mSelectSquad->getAttr(ATTR_FORM,ATTRCALC_FULL)));

	mSquadLevel->setCaption(str(boost::format(StringTable::getSingletonPtr()->getString("Level"))%mSelectSquad->getLevel()));
	mSquadExp->setCaption(str(boost::format(StringTable::getSingletonPtr()->getString("Exp"))%mSelectSquad->getExp()));


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

	std::string distpath = mSelectSquad->getPath() + std::string("/Effect");
	std::vector<std::string> effectName;
	std::vector<std::string> effectlist = datalib->getChildList(distpath);
	for(std::vector<std::string>::iterator it=effectlist.begin();it!=effectlist.end();it++)
	{
		std::string p=mSelectSquad->getPath() + std::string("/Effect/")+(*it)+std::string("/EffectId");
		std::string data;
		DataLibrary::getSingletonPtr()->getData(p,data);

		effectName.push_back(data);
	}

	mEffectWindow->setEffectList(effectName);
}