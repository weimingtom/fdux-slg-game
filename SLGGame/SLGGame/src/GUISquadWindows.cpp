#include "GUISquadWindows.h"

#include "DataLibrary.h"
#include "StringTable.h"
#include "boost/format.hpp"

#include "BattleSquad.h"

#include "GUITipsWindow.h"

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
	assignWidget(mSquadAp,"SquadAp");
	assignWidget(mSquadAttack,"SquadAttack");
	assignWidget(mSquadDefence,"SquadDefence");

	MyGUI::TextBox* textBox;
	assignWidget(textBox,"FormationLabel");
	textBox->setCaption(StringTable::getSingleton().getString("Formation"));
	assignWidget(textBox,"DirectionLabel");
	textBox->setCaption(StringTable::getSingleton().getString("Direction"));

	assignWidget(mSquadDirection,"SquadDirection");
	assignWidget(mSquadFormation,"SquadFormation");

	assignWidget(mSquadImage,"SquadImage");
	assignWidget(mSquadFactionImage,"SquadFactionImage");

	mSquadLeadName->eventToolTip+= MyGUI::newDelegate(GUITipsWindow::getSingletonPtr(), &GUITipsWindow::eventToolTip);


	window->setPosition(0,Height-window->getHeight());

	setSquad(NULL);
}

GUISquadWindows::~GUISquadWindows(void)
{
}

void GUISquadWindows::showScene( std::string arg )
{
	mWindow->setVisible(true);
}

void GUISquadWindows::hideScene()
{
	mWindow->setVisible(false);
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
	if(mSelectSquad->IsEliminated())
	{
		setSquad(NULL);
		return;
	}
	std::string tempstr,temppath;
	std::string datapath = mSelectSquad->getPath();
	bool re = DataLibrary::getSingletonPtr()->getData(datapath+"/LeaderPicture",tempstr);
	mSquadImage->setImageTexture(tempstr);
	//mSquadImage->setImageTexture("shadowdepthmap");
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
	mSquadAttack->setCaption(str(boost::format("%1$3.1f")%tempfloat));
	tempfloat = mSelectSquad->getAttr(ATTR_DEFENCE,ATTRCALC_FULL,x);
	mSquadDefence->setCaption(str(boost::format("%1$3.1f")%tempfloat));

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