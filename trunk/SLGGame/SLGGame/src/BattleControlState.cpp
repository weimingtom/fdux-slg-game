#include "BattleControlState.h"

#include "DataLibrary.h"
#include "LuaSystem.h"

#include "MapDataManager.h"

#include "BattleAIState.h"
#include "BattlePlayerState.h"

#include "BattleSquadManager.h"
#include "BattleSquad.h"
#include "CutSceneBuilder.h"

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
			if(CutSceneBuilder::getSingleton().hasCutScenes())
			{

			}
			mCurState = ControlState_Normal;
			DataLibrary::getSingleton().saveXmlData(DataLibrary::GameData,"test.xml");
		}
		break;
	case ControlState_LoadGame:
		{
			BattlePlayerState* playerstate = new BattlePlayerState();
			mMainState->PushState(playerstate);
			mGUIState->showScene("");
			mGUIState->update();
			mCurState = ControlState_Normal;
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
						LuaTempContext* luatempcontext = new LuaTempContext();
						luatempcontext->intMap["turn"] = turn;
						luatempcontext->intMap["team"] = team;
						MapDataManager::getSingleton().Trigger("TurnStart", luatempcontext);
						delete luatempcontext;
						BattleSquadManager* battlesquadmanager = BattleSquadManager::getSingletonPtr();
						BattleSquadManager::BattleSquadIte ite = battlesquadmanager->mSquadList.begin();
						for(; ite != battlesquadmanager->mSquadList.end(); ite++)
						{
							if(ite->second->getTeam() == team)
								ite->second->turnStart();
						}
						if(CutSceneBuilder::getSingleton().hasCutScenes())
						{
							mCurState = ControlState_TurnStart;
						}
						BattlePlayerState* playerstate = new BattlePlayerState();
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
							LuaTempContext* luatempcontext = new LuaTempContext();
							luatempcontext->intMap["turn"] = turn;
							luatempcontext->intMap["team"] = team;
							MapDataManager::getSingleton().Trigger("TurnStart", luatempcontext);
							delete luatempcontext;
							BattleSquadManager* battlesquadmanager = BattleSquadManager::getSingletonPtr();
							BattleSquadManager::BattleSquadIte ite = battlesquadmanager->mSquadList.begin();
							for(; ite != battlesquadmanager->mSquadList.end(); ite++)
							{
								if(ite->second->getTeam() == team)
									ite->second->turnStart();
							}
							if(CutSceneBuilder::getSingleton().hasCutScenes())
							{
								mCurState = ControlState_TurnStart;
							}
							BattleAIState* aistate = new BattleAIState(team);
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
	case ControlState_TurnEnd:
	case ControlState_TurnStart:
		mCurState = ControlState_Normal;
		break;
	}
}

void BattleControlState::reactiveState()
{
	switch(mCurState)
	{
	case ControlState_TurnStart:
		{
			int team;
			DataLibrary::getSingletonPtr()->getData("GameData/BattleData/BattleState/CurTeam",team);
			if(team == 1)
			{
				BattlePlayerState* playerstate = new BattlePlayerState();
				mMainState->PushState(playerstate);
			}
			else
			{
				BattleAIState* aistate = new BattleAIState(team);
				mMainState->PushState(aistate);
			}
			mCurState = ControlState_Normal;
		}
		break;
	case ControlState_Normal:
		{
			int turn,team;
			DataLibrary::getSingletonPtr()->getData("GameData/BattleData/BattleState/Ture",turn);
			DataLibrary::getSingletonPtr()->getData("GameData/BattleData/BattleState/CurTeam",team);
			LuaTempContext* luatempcontext = new LuaTempContext();
			luatempcontext->intMap["turn"] = turn;
			luatempcontext->intMap["team"] = team;
			MapDataManager::getSingleton().Trigger("TurnEnd", luatempcontext);
			delete luatempcontext;
			BattleSquadManager* battlesquadmanager = BattleSquadManager::getSingletonPtr();
			BattleSquadManager::BattleSquadIte ite = battlesquadmanager->mSquadList.begin();
			for(; ite != battlesquadmanager->mSquadList.end(); ite++)
			{
				if(ite->second->getTeam() == team)
					ite->second->turnEnd();
			}
			mCurState = ControlState_Normal;
		}
		break;
	case ControlState_TurnEnd:
	case ControlState_NewGame:
	case ControlState_LoadGame:
		mCurState = ControlState_Normal;
		break;
	}
}