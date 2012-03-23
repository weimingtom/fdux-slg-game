#include "BattleControlState.h"

#include "DataLibrary.h"
#include "LuaSystem.h"

#include "MapDataManager.h"

#include "BattleAIState.h"
#include "BattlePlayerState.h"

#include "GUISystem.h"
#include "GUIBattle.h"
#include "GUIGameStateWindows.h"


BattleControlState::BattleControlState(bool newgame)
{
	mGUIBattle = static_cast<GUIBattle *>(GUISystem::getSingleton().getScene(BattleScene));
	mGUIState = static_cast<GUIGameStateWindows *>(mGUIBattle->getSubWindow("GameState"));
	mGUIState->setBattleState(mMainState);
	mCurState = (newgame)?ControlState_NewGame:ControlState_LoadGame;
}
BattleControlState::~BattleControlState()
{
	mGUIState->setBattleState(NULL);
}

void BattleControlState::update(unsigned int deltaTime)
{
	switch(mCurState)
	{
	case ControlState_NewGame:
		{
			LuaTempContext* luatempcontext = new LuaTempContext();
			MapDataManager::getSingleton().Trigger("FinishDeploy", luatempcontext);
			delete luatempcontext;
			mCurState = ControlState_Normal;
			DataLibrary::getSingleton().saveXmlData(DataLibrary::GameData,"test.xml");
			return;
		}
		break;
	case ControlState_LoadGame:
		{
			BattlePlayerState* playerstate = new BattlePlayerState(false);
			mMainState->PushState(playerstate);
			mGUIState->showScene("");
			mGUIState->update();
		}
		break;
	case ControlState_Normal:
		{
			int turn,team;
			DataLibrary::getSingletonPtr()->getData("GameData/BattleData/BattleState/Ture",turn);
			DataLibrary::getSingletonPtr()->getData("GameData/BattleData/BattleState/CurTeam",team);
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
						BattlePlayerState* playerstate = new BattlePlayerState(true);
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
							//					aistate->newTurn();
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
			mGUIState->showScene("");
			mGUIState->update();
		}
		break;
	}
}