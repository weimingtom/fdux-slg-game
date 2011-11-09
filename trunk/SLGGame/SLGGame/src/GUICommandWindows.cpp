#include "GUICommandWindows.h"

#include "DataLibrary.h"
#include "boost\format.hpp"

#include "BattlePlayerState.h"
#include "BattleSquad.h"
#include <algorithm>
#include "StringTable.h"
#include "GUITipsWindow.h"

GUICommandWindows::GUICommandWindows(MyGUI::Window* window,int Width,int Height):GUISubWindows(window,Width,Height),mWindow(window)
{
	assignWidget(mSkill[0],"Skill1");
	assignWidget(mSkill[1],"Skill2");
	assignWidget(mSkill[2],"Skill3");
	assignWidget(mSkill[3],"Skill4");
	assignWidget(mSkill[4],"Skill5");
	assignWidget(mSkill[5],"Skill6");
	assignWidget(mSkill[6],"Skill7");
	assignWidget(mSkill[7],"Skill8");
	assignWidget(mSkill[8],"Skill9");
	assignWidget(mAPLabel,"APLabel");

	mSkill[0]->eventMouseButtonClick+= MyGUI::newDelegate(this, &GUICommandWindows::onSkill1);
	mSkill[1]->eventMouseButtonClick+= MyGUI::newDelegate(this, &GUICommandWindows::onSkill2);
	mSkill[2]->eventMouseButtonClick+= MyGUI::newDelegate(this, &GUICommandWindows::onSkill3);
	mSkill[3]->eventMouseButtonClick+= MyGUI::newDelegate(this, &GUICommandWindows::onSkill4);
	mSkill[4]->eventMouseButtonClick+= MyGUI::newDelegate(this, &GUICommandWindows::onSkill5);
	mSkill[5]->eventMouseButtonClick+= MyGUI::newDelegate(this, &GUICommandWindows::onSkill6);
	mSkill[6]->eventMouseButtonClick+= MyGUI::newDelegate(this, &GUICommandWindows::onSkill7);
	mSkill[7]->eventMouseButtonClick+= MyGUI::newDelegate(this, &GUICommandWindows::onSkill8);
	mSkill[8]->eventMouseButtonClick+= MyGUI::newDelegate(this, &GUICommandWindows::onSkill9);

	setSquad(NULL);
	mPlayerState = NULL;

	window->setPosition(mWindow->getLeft(),Height-window->getHeight()-5);
}

GUICommandWindows::~GUICommandWindows(void)
{
}

void GUICommandWindows::showScene( std::string arg )
{
	mWindow->setVisible(true);
}

void GUICommandWindows::hideScene()
{
	mWindow->setVisible(false);
}

void GUICommandWindows::FrameEvent()
{

}


bool GUICommandWindows::SceneInputEvent( float x,float y )
{
	return false;
}

bool GUICommandWindows::GridInputEvent( int x,int y )
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

	if (flag)
	{
		mWindow->setVisible(true);
		mWindow->setPosition(mSceneX,mSceneY);
	}
	else
	{
		mWindow->setVisible(false);
	}
	*/
	return true;
}

void GUICommandWindows::setSquad(BattleSquad* squad)
{
	mSelectSquad = squad;
	if(mSelectSquad == NULL)
	{
		for(int n =0; n <9; n++)
		{
			mSkill[n]->setVisible(false);
			mSkill[n]->setImageResource("");
			mSkillId[n] = "none";
		}
		hideScene();
		return;
	}
	showScene("");

	for(int n =0; n <9; n++)
	{
		mSkill[n]->setImageResource("");
	}

	//移动技能
	float apleft = mSelectSquad->getActionPoint();
	mAPLabel->setCaption(str(boost::format(StringTable::getSingletonPtr()->getString("APLabel"))%(int)apleft));
	int skillno = 0;
	mSkill[skillno]->setVisible(true);

	mSkill[skillno]->setCaption(StringTable::getSingletonPtr()->getString("Move"));
	mSkill[skillno]->setUserString("Tips",StringTable::getSingletonPtr()->getString("Tips_Move"));
	mSkill[skillno]->eventToolTip += MyGUI::newDelegate(GUITipsWindow::getSingletonPtr(), &GUITipsWindow::eventToolTip);

	mSkill[skillno]->setImageResource("Move");
	mSkillId[skillno] = "move";
	skillno++;
	if(mSelectSquad->getType()==SQUAD_NORMAL)
	{
		//队列切换技能
		float apcost = mSelectSquad->getActionPointCost(SKILLAPTYPE_SETUP) + 2.0f;
		Formation f = mSelectSquad->getFormation();
		if(f != Line)
		{
			mSkill[skillno]->setVisible(true);
			mSkill[skillno]->setImageResource("Defence");
			mSkill[skillno]->setCaption(str(boost::format(StringTable::getSingletonPtr()->getString("FormationLineButton"))%apcost));
			mSkill[skillno]->setUserString("Tips",StringTable::getSingletonPtr()->getString("Tips_FormationLineButton"));
			mSkill[skillno]->eventToolTip += MyGUI::newDelegate(GUITipsWindow::getSingletonPtr(), &GUITipsWindow::eventToolTip);
			if(apleft >= apcost)
				mSkill[skillno]->setEnabled(true);
			else
				mSkill[skillno]->setEnabled(false);
			mSkillId[skillno] = "line";
			skillno++;
		}
		if(f != Circular)
		{
			mSkill[skillno]->setVisible(true);
			mSkill[skillno]->setImageResource("Defence");
			mSkill[skillno]->setCaption(str(boost::format(StringTable::getSingletonPtr()->getString("FormationCircButton"))%apcost));
			mSkill[skillno]->setUserString("Tips",StringTable::getSingletonPtr()->getString("Tips_FormationCircButton"));
			mSkill[skillno]->eventToolTip += MyGUI::newDelegate(GUITipsWindow::getSingletonPtr(), &GUITipsWindow::eventToolTip);
			if(apleft >= apcost)
				mSkill[skillno]->setEnabled(true);
			else
				mSkill[skillno]->setEnabled(false);
			mSkillId[skillno] = "circular";
			skillno++;
		}
		if(f != Loose)
		{
			mSkill[skillno]->setVisible(true);
			mSkill[skillno]->setImageResource("Defence");
			mSkill[skillno]->setCaption(str(boost::format(StringTable::getSingletonPtr()->getString("FormationLoosButton"))%apcost));
			mSkill[skillno]->setUserString("Tips",StringTable::getSingletonPtr()->getString("Tips_FormationLoosButton"));
			mSkill[skillno]->eventToolTip += MyGUI::newDelegate(GUITipsWindow::getSingletonPtr(), &GUITipsWindow::eventToolTip);
			if(apleft >= apcost)
				mSkill[skillno]->setEnabled(true);
			else
				mSkill[skillno]->setEnabled(false);
			mSkillId[skillno] = "loose";
			skillno++;
		}
	}
	//其他技能
	std::string skilltablepath = mSelectSquad->getPath() + std::string("/SkillTable");
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	std::vector<std::string>::iterator ite;
	std::vector<std::string> skilllist = datalib->getChildList(skilltablepath);
	for(ite = skilllist.begin(); ite != skilllist.end(); ite++)
	{
		SkillType skilltype;
		bool re = datalib->getData(std::string("StaticData/SkillData/")+ (*ite)+ std::string("/Type"),skilltype);
		if(skilltype == SKILLTYPE_PASSIVE)
			continue;
		mSkill[skillno]->setVisible(true);
		std::string skillpath = skilltablepath + std::string("/") + (*ite);
		int cooldown;
		std::string skillname;
		std::string skillTips;
		std::string skillIcon;
		datalib->getData(std::string("StaticData/SkillData/")+ (*ite)+ std::string("/Name"),skillname);

		datalib->getData(std::string("StaticData/SkillData/")+ (*ite)+ std::string("/Describe"),skillTips);
		mSkill[skillno]->setUserString("Tips",skillTips);
		mSkill[skillno]->eventToolTip += MyGUI::newDelegate(GUITipsWindow::getSingletonPtr(), &GUITipsWindow::eventToolTip);

		datalib->getData(skillpath + std::string("/CoolDown"),cooldown);
		datalib->getData(std::string("StaticData/SkillData/")+ (*ite) + std::string("/Icon"),skillIcon);
		if (skillIcon!="none")
		{
			mSkill[skillno]->setImageResource(skillIcon);
		}
		else
		{
			mSkill[skillno]->setImageResource("None");
		}
		if(cooldown > 0)
		{
			mSkill[skillno]->setEnabled(false);
			mSkill[skillno]->setCaption(str(boost::format("%1%\n(%2%)")%skillname%cooldown));
		}
		else
		{
			int aptype ;
			datalib->getData(std::string("StaticData/SkillData/")+ (*ite)+ std::string("/APType"),aptype);
			float apcost;
			datalib->getData(std::string("StaticData/SkillData/")+ (*ite)+ std::string("/APCost"),apcost);
			if(aptype != SKILLAPTYPE_DEFENCE)
			{
				apcost += mSelectSquad->getActionPointCost(aptype);
				mSkill[skillno]->setCaption(str(boost::format("%1%\nAP:%2%")%skillname%apcost));
			}
			else
			{
				float ap = apcost;
				apcost = std::max(apcost,apleft);
				mSkill[skillno]->setCaption(str(boost::format("%1%\nAP:%2%(%3%)")%skillname%apcost%ap));
			}

			if(apleft >= apcost)
			{
				mSkill[skillno]->setEnabled(true);
				mSkillId[skillno] = (*ite);
			}
			else
				mSkill[skillno]->setEnabled(false);
		}
		skillno++;
	}
	for(;skillno < 9; skillno++)
	{
		mSkill[skillno]->setVisible(false);
		mSkill[skillno]->setEnabled(false);
	}
}

void GUICommandWindows::setPlayerState(BattlePlayerState* playerstate)
{
	mPlayerState = playerstate;
}

void GUICommandWindows::onSkill1(MyGUI::Widget* _sender)
{
	useSkill(0);
}
void GUICommandWindows::onSkill2(MyGUI::Widget* _sender)
{
	useSkill(1);
}
void GUICommandWindows::onSkill3(MyGUI::Widget* _sender)
{
	useSkill(2);
}
void GUICommandWindows::onSkill4(MyGUI::Widget* _sender)
{
	useSkill(3);
}
void GUICommandWindows::onSkill5(MyGUI::Widget* _sender)
{
	useSkill(4);
}
void GUICommandWindows::onSkill6(MyGUI::Widget* _sender)
{
	useSkill(5);
}
void GUICommandWindows::onSkill7(MyGUI::Widget* _sender)
{
	useSkill(6);
}
void GUICommandWindows::onSkill8(MyGUI::Widget* _sender)
{
	useSkill(7);
}
void GUICommandWindows::onSkill9(MyGUI::Widget* _sender)
{
	useSkill(8);
}

void GUICommandWindows::useSkill(int n)
{
	if(mSkillId[n] == "move")
	{
		mPlayerState->moveSquad();
		return;
	}
	if(mSkillId[n] == "line")
	{
		mPlayerState->changeFormation(Line);
		return;
	}
	if(mSkillId[n] == "circular")
	{
		mPlayerState->changeFormation(Circular);
		return;
	}
	if(mSkillId[n] == "loose")
	{
		mPlayerState->changeFormation(Loose);
		return;
	}
	mPlayerState->useSkill(mSkillId[n]);
}