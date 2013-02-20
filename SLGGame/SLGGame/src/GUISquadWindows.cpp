#include "GUISquadWindows.h"

#include "DataLibrary.h"
#include "StringTable.h"
#include "boost/format.hpp"
#include <math.h>

#include "BattleSquad.h"

#include "GUITipsWindow.h"
#include "GUIBattle.h"
#include "GUIEffectWindow.h"

GUISquadWindows::GUISquadWindows(MyGUI::Window* window,int Width,int Height):GUISubWindows(window,Width,Height),mWindow(window)
{
	assignWidget(mSquadLeadName,"SquadLeadName");
	assignWidget(mSquadTypeName,"SquadType");
	assignWidget(mSquadGridX,"SquadGridX");
	assignWidget(mSquadGridY,"SquadGridY");
	assignWidget(mSquadPWeapon,"SquadPWeapon");
	assignWidget(mSquadSWeapon,"SquadSWeapon");
	assignWidget(mSquadShield,"SquadShield");
	assignWidget(mSquadArmor,"SquadArmor");
	assignWidget(mSquadUnitNum,"SquadUnitNum");
	assignWidget(mSquadLevel,"SquadLevel");
	assignWidget(mSquadExp,"SquadExp");
	assignWidget(mSquadAttackFront,"SquadAttackFront");
	assignWidget(mSquadDefenceFront,"SquadDefenceFront");
	assignWidget(mSquadAttackFlank,"SquadAttackFlank");
	assignWidget(mSquadDefenceFlank,"SquadDefenceFlank");
	assignWidget(mSquadAttackBack,"SquadAttackBack");
	assignWidget(mSquadDefenceBack,"SquadDefenceBack");
	assignWidget(mSquadAttackRA,"SquadAttackRA");
	assignWidget(mSquadDefenceRA,"SquadDefenceRA");

	//MyGUI::TextBox* textBox;
	//assignWidget(textBox,"FormationLabel");
	//textBox->setCaption(StringTable::getSingleton().getString("Formation"));
	//assignWidget(textBox,"DirectionLabel");
	//textBox->setCaption(StringTable::getSingleton().getString("Direction"));

	//assignWidget(mSquadDirection,"SquadDirection");
	assignWidget(mSquadFormation,"SquadFormation");

	assignWidget(mSquadImage,"SquadImage");
	assignWidget(mSquadFactionImage,"SquadFactionImage");

	mSquadLeadName->eventToolTip += MyGUI::newDelegate(GUITipsWindow::getSingletonPtr(), &GUITipsWindow::eventToolTip);


	window->setPosition(0,Height-window->getHeight());

	mEffectWindow=NULL;

	setSquad(NULL);
}

GUISquadWindows::~GUISquadWindows(void)
{
}

void GUISquadWindows::showScene( std::string arg )
{
	mWindow->setVisible(true);

	if(mEffectWindow==NULL)
	{
		GUIBattle* battle=(GUIBattle*)GUISystem::getSingletonPtr()->getScene(BattleScene);
		mEffectWindow=(GUIEffectWindow*)battle->getSubWindow("EffectWindow1");
	}

	mEffectWindow->showScene("");

}

void GUISquadWindows::hideScene()
{
	mWindow->setVisible(false);
	if (mEffectWindow!=NULL)
	{
		mEffectWindow->hideScene();
	}
}

void GUISquadWindows::FrameEvent()
{
	//updateSquad();
}

bool GUISquadWindows::GridInputEvent( int x,int y )
{
	/*
	std::vector<std::string> squadList=DataLibrary::getSingletonPtr()->getChildList("GameData/BattleData/SquadList");
	
	std::string squadId="";
	bool flag=false;
	for (std::vector<std::string>::iterator it=squadList.begin();it!=squadList.end();it++)
	{
		squadId=str(boost::format("GameData/BattleData/SquadList/%1%/GridX")%(*it));
		int value=0;
		DataLibrary::getSingletonPtr()->getData(squadId,value);
		if (value==x)
		{
			squadId=str(boost::format("GameData/BattleData/SquadList/%1%/GridY")%(*it));
			DataLibrary::getSingletonPtr()->getData(squadId,value);
			if (value==y)
			{
				squadId=str(boost::format("GameData/BattleData/SquadList/%1%/")%(*it));
				flag=true;
				break;
			}
		}
	}
	
	if(flag)
	{
		std::string value="";
		DataLibrary::getSingletonPtr()->getData(squadId+"Name",value);
		mSquadNameLabel->setCaption(value);
		DataLibrary::getSingletonPtr()->getData(squadId+"Type",value);
		mSquadTypeLabel->setCaption(value);
		DataLibrary::getSingletonPtr()->getData(squadId+"Describe",value);
		mSquadDescribeLabel->setCaption(value);
		DataLibrary::getSingletonPtr()->getData(squadId+"LeaderPicture",value);
		mSquadImage->setImageTexture(value);
	}
	else
	{
		mSquadNameLabel->setCaption(StringTable::getSingletonPtr()->getString("GUINoSquadName"));
		mSquadTypeLabel->setCaption(StringTable::getSingletonPtr()->getString("GUINoSquadType"));
		mSquadDescribeLabel->setCaption(StringTable::getSingletonPtr()->getString("GUINoSquadDescribe"));
		mSquadImage->setImageTexture("");
	}
	*/
	return false;
}

void GUISquadWindows::setSquad(BattleSquad* squad)
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

void GUISquadWindows::updateSquad()
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

	/*x = mSelectSquad->getDirection();
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
	}*/

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