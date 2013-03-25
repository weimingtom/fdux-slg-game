#include "GUICommandWindows.h"

#include "DataLibrary.h"
#include "boost\format.hpp"

#include "BattlePlayerState.h"
#include "BattleSquad.h"
#include <algorithm>
#include "StringTable.h"
#include "GUITipsWindow.h"
#include "SquadGrapManager.h"
#include "SquadGraphics.h"

#include "GUIBattle.h"
#include "GUIMapWindow.h"

void split(const std::string& s, std::string c,std::queue<std::string>& v) 
{
	std::string::size_type i = 0;
	std::string::size_type j = s.find(c);

	while (j != std::string::npos) 
	{
		v.push(s.substr(i, j-i));
		i = ++j;
		j = s.find(c, j);

		if (j == std::string::npos)
			v.push(s.substr(i, s.length( )));
	}
}

GUICommandWindows::GUICommandWindows(MyGUI::Window* window,int Width,int Height):GUISubWindows(window,Width,Height),mWindow(window)
{
	assignWidget(mSkill[0],"Skill_1");
	assignWidget(mSkill[1],"Skill_2");
	assignWidget(mSkill[2],"Skill_3");
	assignWidget(mSkill[3],"Skill_4");
	assignWidget(mSkill[4],"Skill_5");
	assignWidget(mSkill[5],"Skill_6");
	assignWidget(mSkill[6],"Skill_7");
	assignWidget(mSkill[7],"Skill_8");
	assignWidget(mSkill[8],"Skill_9");
	assignWidget(mSkill[9],"Skill_10");
	assignWidget(mSkill[10],"Skill_11");
	assignWidget(mSkill[11],"Skill_12");
	assignWidget(mSkill[12],"Skill_13");
	assignWidget(mSkill[13],"Skill_14");
	assignWidget(mSkill[14],"Skill_15");
	assignWidget(mSkill[15],"Skill_16");
	assignWidget(mSkill[16],"Skill_17");
	assignWidget(mSkill[17],"Skill_18");
	assignWidget(mAPLabel,"APLabel");
	assignWidget(mSkillName,"SkillName");

	for(int i=0;i<18;i++)
	{
		mSkill[i]->eventMouseButtonClick+= MyGUI::newDelegate(this, &GUICommandWindows::onSkillClick);
		mSkill[i]->eventMouseSetFocus+= MyGUI::newDelegate(this, &GUICommandWindows::onSkillHighlighted);
		mSkill[i]->eventMouseLostFocus+= MyGUI::newDelegate(this, &GUICommandWindows::onSkillLostFocus);
	}

	setSquad(NULL);
	//mPlayerState = NULL;

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
	return true;
}

void GUICommandWindows::setSquad(BattleSquad* squad)
{
	GUIBattle* guibattle=static_cast<GUIBattle *>(GUISystem::getSingleton().getScene(BattleScene));
	GUIMapWindow* mapwindow=NULL;
	if(guibattle!=NULL)
		mapwindow=(GUIMapWindow*)guibattle->getSubWindow("MapWindow");

	mSelectSquad = squad;
	if(mSelectSquad == NULL)
	{
		mSkillPage = 1;
		for(int n =0; n <18; n++)
		{
			mSkill[n]->setVisible(false);
			mSkill[n]->setImageResource("");
			mSkillId[n] = "none";
		}
		hideScene();
		if(mapwindow!=NULL)
			mapwindow->clearSelect();
		return;
	}
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	float apleft = mSelectSquad->getActionPoint();
	if(apleft<2)
		SquadGrapManager::getSingletonPtr()->getSquad(mSelectSquad->getSquadId())->setSquadBillBoardState(false);
	else
		SquadGrapManager::getSingletonPtr()->getSquad(mSelectSquad->getSquadId())->setSquadBillBoardState(true);


	mapwindow->updatePointState(mSelectSquad);
	mapwindow->setSelectPoint(mSelectSquad);

	mAPLabel->setCaption(str(boost::format(StringTable::getSingletonPtr()->getString("APLabel"))%(int)apleft%mSelectSquad->getAttr(ATTR_ACTIONPOINT,ATTRCALC_FULL)));
	std::vector<BattleSquad::ActiveSkillInfo> skilllist = mSelectSquad->GetActiveSkillList();
	std::vector<BattleSquad::ActiveSkillInfo>::iterator ite = skilllist.begin();
	int maxn = 18;
	std::vector<BattleSquad::ActiveSkillInfo>::iterator endite = skilllist.end();
	/*if(skilllist.size() > 9)
	{
		maxn = 8;
		mSkill[8]->setVisible(true);
		mSkill[8]->setEnabled(true);
		if(mSkillPage == 1)
		{
			endite = ite + 8;
			mSkill[8]->setCaption("nextpage");
			mSkill[8]->setUserString("Tips",StringTable::getSingletonPtr()->getString("Tips_FormationLoosButton"));
			mSkill[8]->setImageResource("Defence");
			mSkillId[8] = "nextpage";
		}
		else
		{
			ite = ite + 8;
			mSkill[8]->setCaption("prevpage");
			mSkill[8]->setUserString("Tips",StringTable::getSingletonPtr()->getString("Tips_FormationLoosButton"));
			mSkill[8]->setImageResource("Defence");
			mSkillId[8] = "prevpage";
		}
	}
	else
		mSkillPage = 1;*/
	int n = 0;
	std::string skillname;
	std::string skillTips;
	std::string skillIcon;
	for(;ite != endite; ite++)
	{
		if(ite->skillid == "move")
		{
			mSkill[n]->setImageResource("ac");
			mSkill[n]->setImageGroup("ac_move");
			mSkill[n]->setCaption("");
			mSkill[n]->setUserString("Tips",StringTable::getSingleton().getString("Tips_Move"));
			mSkill[n]->setUserString("Discribe",StringTable::getSingleton().getString("Move"));
		}
		else if(ite->skillid == "turn")
		{
			mSkill[n]->setCaption("");
			mSkill[n]->setUserString("Tips",StringTable::getSingleton().getString("Tips_Turn"));
			mSkill[n]->setUserString("Discribe",StringTable::getSingleton().getString("TurnSquad"));
			mSkill[n]->setImageResource("ac");
			mSkill[n]->setImageGroup("ac_turn");
		}
		else if(ite->skillid == "looseformation")
		{
			mSkill[n]->setCaption(Ogre::StringConverter::toString((*ite).apcost)+"   ");
			mSkill[n]->setUserString("Tips",StringTable::getSingletonPtr()->getString("Tips_FormationLoosButton"));
			mSkill[n]->setUserString("Discribe",str(boost::format(StringTable::getSingletonPtr()->getString("FormationLoosButton"))%((*ite).apcost)));
			mSkill[n]->setImageResource("ac");
			mSkill[n]->setImageGroup("form_dispersed");
		}
		else if(ite->skillid == "lineformation")
		{
			mSkill[n]->setCaption(Ogre::StringConverter::toString((*ite).apcost)+"   ");
			mSkill[n]->setUserString("Tips",StringTable::getSingletonPtr()->getString("Tips_FormationLineButton"));
			mSkill[n]->setUserString("Discribe",str(boost::format(StringTable::getSingletonPtr()->getString("FormationLineButton"))%((*ite).apcost)));
			mSkill[n]->setImageResource("ac");
			mSkill[n]->setImageGroup("form_line");
		}
		else if(ite->skillid == "circularformation")
		{
			mSkill[n]->setCaption(Ogre::StringConverter::toString((*ite).apcost)+"   ");
			mSkill[n]->setUserString("Tips",StringTable::getSingletonPtr()->getString("Tips_FormationCircButton"));
			mSkill[n]->setUserString("Discribe",str(boost::format(StringTable::getSingletonPtr()->getString("FormationCircButton"))%((*ite).apcost)));
			mSkill[n]->setImageResource("ac");
			mSkill[n]->setImageGroup("form_round");
		}
		else
		{
			datalib->getData(std::string("StaticData/SkillData/")+ (*ite).skillid + std::string("/Name"),skillname);
			datalib->getData(std::string("StaticData/SkillData/")+ (*ite).skillid + std::string("/Describe"),skillTips);
			datalib->getData(std::string("StaticData/SkillData/")+ (*ite).skillid + std::string("/Icon"),skillIcon);
			mSkill[n]->setImageResource("skill");
			mSkill[n]->setImageGroup(skillIcon);
			mSkill[n]->setCaption(Ogre::StringConverter::toString((*ite).apcost)+"   ");
			mSkill[n]->setUserString("Tips",skillTips);
			mSkill[n]->setUserString("Discribe",str(boost::format("%1%(AP:%2%)")%skillname%((*ite).apcost)));
		}
		mSkill[n]->setVisible(true);
		mSkill[n]->setEnabled((*ite).available);
		mSkill[n]->setNeedToolTip(true);
		GUITipsWindow::getSingletonPtr()->addToolTipEvent(mSkill[n]);
		mSkillId[n] = (*ite).skillid;
		n++;
	}
	for(; n < maxn; n++)
	{
		mSkill[n]->setImageResource("");
		mSkill[n]->setVisible(false);
		mSkill[n]->setNeedToolTip(false);
		mSkillId[n] = "none";
	}
	showScene("");
}

 void GUICommandWindows::setPlayerState(BattlePlayerState* playerstate)
 {
 	mPlayerState = playerstate;
 }

void GUICommandWindows::onSkillClick(MyGUI::Widget* _sender)
{
	std::string name=_sender->getName();

	std::queue<std::string> r;

	split(name,"_",r);

	r.pop();

	int index=atoi(r.front().c_str());

	useSkill(index-1);
}

void GUICommandWindows::onSkillHighlighted(MyGUI::Widget* _sender, MyGUI::Widget* _old)
{
	mSkillName->setCaption(_sender->getUserString("Discribe"));
}

void GUICommandWindows::onSkillLostFocus( MyGUI::Widget* _sender, MyGUI::Widget* _old )
{
	mSkillName->setCaption("");
}

void GUICommandWindows::useSkill(int n)
{
// 	if(mSkillId[n] == "move")
// 	{
// 		mPlayerState->moveSquad();
// 		return;
// 	}
// 	if(mSkillId[n] == "line")
// 	{
// 		mPlayerState->changeFormation(Line);
// 		return;
// 	}
// 	if(mSkillId[n] == "circular")
// 	{
// 		mPlayerState->changeFormation(Circular);
// 		return;
// 	}
// 	if(mSkillId[n] == "loose")
// 	{
// 		mPlayerState->changeFormation(Loose);
// 		return;
// 	}
	if(mSkillId[n] == "nextpage")
	{
		mSkillPage = 2;
		setSquad(mSelectSquad);
	}
	else if(mSkillId[n] == "prevpage")
	{
		mSkillPage = 1;
		setSquad(mSelectSquad);
	}
	else if(mPlayerState)
 		mPlayerState->useSkill(mSkillId[n]);
}