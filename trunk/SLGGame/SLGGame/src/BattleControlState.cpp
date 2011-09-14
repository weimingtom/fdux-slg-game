#include "BattleControlState.h"

#include "DataLibrary.h"
#include "LuaSystem.h"
#include "GUIBattle.h"
#include "GUISystem.h"
#include "BattleState.h"
#include "BattleSquad.h"
#include "BattlePlayerState.h"
#include "BattleAIState.h"
#include "BattleSquadManager.h"
#include "GUIGameStateWindows.h"
#include "TriggerManager.h"
#include "cutscene.h"
#include "cutscenediretor.h"


BattleControlState::BattleControlState(bool newgame)
:mNewGame(newgame)
{
	mGUIBattle = static_cast<GUIBattle *>(GUISystem::getSingleton().getScene(BattleScene));
	mGUIState = static_cast<GUIGameStateWindows *>(mGUIBattle->getSubWindow("GameState"));
	mGUIState->showScene("");
	mGUIState->update();
}
BattleControlState::~BattleControlState()
{

}

void BattleControlState::update(unsigned int deltaTime)
{
	int turn,team;
	DataLibrary::getSingletonPtr()->getData("GameData/BattleData/BattleState/Ture",turn);
	DataLibrary::getSingletonPtr()->getData("GameData/BattleData/BattleState/CurTeam",team);
	if(!mNewGame)
	{
		BattlePlayerState* playerstate = new BattlePlayerState;
		mMainState->PushState(playerstate);
		mGUIState->update();
		mNewGame = true;
		return;
	}
	//执行回合结束触发器
	BattleSquadManager* battlesquadmanager = BattleSquadManager::getSingletonPtr();
	for(int n = 0; n < battlesquadmanager->mSquadList.size(); n++)
	{
		if(battlesquadmanager->mSquadList[n]->getTeam() == team)
			battlesquadmanager->mSquadList[n]->OnTurnEnd();
	}
	TriggerManager::getSingleton().turnEnd(turn,team);
	//切换回合与玩家
	team += 1;
	bool nextteam = false;
	while(!nextteam)
	{
		team = (team> 4)? 1:team;
		switch (team)
		{
		case 1:
			{
				BattlePlayerState* playerstate = new BattlePlayerState;
				playerstate->newTurn();
				mMainState->PushState(playerstate);
				turn = turn + 1;
				nextteam = true;
			}
			break;
		case 2:
		case 3:
		case 4:
			{
				std::string teamstr;
				std::string teampath = std::string("GameData/BattleData/Team/Team") + Ogre::StringConverter::toString(team) + std::string("/FactionId");
				DataLibrary::getSingleton().getData(teampath,teamstr);
				if(teamstr == "none")
				{
					team += 1;
					nextteam = false;
				}
				else
				{
					BattleAIState* aistate = new BattleAIState(team);
					aistate->newTurn();
					mMainState->PushState(aistate);
					nextteam = true;
				}	
			}
			break;
		default:
			{
				team = 1;
				nextteam = false;
			}
		}
	}
	DataLibrary::getSingletonPtr()->setData("GameData/BattleData/BattleState/Ture",turn);
	DataLibrary::getSingletonPtr()->setData("GameData/BattleData/BattleState/CurTeam",team);
	mGUIState->update();
	DataLibrary::getSingleton().saveXmlData(DataLibrary::GameData,"test.xml");
	CutScene* cutscene = battlesquadmanager->getCutScene();
	if(cutscene != NULL)
	{
		CutSceneDirector* csd= new CutSceneDirector();
		csd->addCutScene(cutscene);
		mMainState->PushState(csd);
	}
}