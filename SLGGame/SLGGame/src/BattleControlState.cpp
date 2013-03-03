#include "BattleControlState.h"

#include "DataLibrary.h"
#include "LuaSystem.h"

#include "MapDataManager.h"

#include "BattleAIState.h"
#include "BattlePlayerState.h"

#include "BattleSquadManager.h"
#include "BattleSquad.h"
#include "CutSceneBuilder.h"
#include "cutscenediretor.h"

#include "GUISystem.h"
#include "GUIBattle.h"
#include "GUIGameStateWindows.h"

#include "StringTable.h"
#include "StateManager.h"

#include "GUIInfoWindow.h"
#include "GUIBattle.h"

#include <boost/format.hpp>


BattleControlState::BattleControlState(bool newgame)
{
	mGUIBattle = static_cast<GUIBattle *>(GUISystem::getSingleton().getScene(BattleScene));
	mGUIState = static_cast<GUIGameStateWindows *>(mGUIBattle->getSubWindow("GameState"));
	//mGUIState->setBattleState(mMainState);
	mCurState = (newgame)?ControlState_NewGame:ControlState_LoadGame;
}
BattleControlState::~BattleControlState()
{
	//mGUIState->setBattleState(NULL);
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
				CutSceneDirector* cutscenedirector = new CutSceneDirector(CutSceneBuilder::getSingleton().getCutScenes());
				mMainState->PushState(cutscenedirector);
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
						turn += 1;
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
							CutSceneDirector* cutscenedirector = new CutSceneDirector(CutSceneBuilder::getSingleton().getCutScenes());
							mMainState->PushState(cutscenedirector);
							mCurState = ControlState_TurnStart;
							DataLibrary::getSingletonPtr()->setData("GameData/BattleData/BattleState/Ture",turn);
							DataLibrary::getSingletonPtr()->setData("GameData/BattleData/BattleState/CurTeam",team);
							mGUIState->showScene("");
							mGUIState->update();

							std::string temp;
							DataLibrary::getSingletonPtr()->getData("GameData/BattleData/MapData/MapName",temp);
							//int val;
							//DataLibrary::getSingletonPtr()->getData("GameData/BattleData/BattleState/Ture",val);
							DataLibrary::getSingletonPtr()->setData("SystemConfig/Save/Save2",std::string("AutoSave ")+temp+" "+str(boost::format(StringTable::getSingletonPtr()->getString("RoundNum"))%(turn)));
							DataLibrary::getSingletonPtr()->saveXmlData(DataLibrary::SystemConfig,std::string("..\\save")+std::string("\\Config.xml"));
							StateManager::getSingletonPtr()->saveState(std::string("..\\save")+std::string("\\save2.xml"));
							return;
						}
						else
						{
							DataLibrary::getSingletonPtr()->setData("GameData/BattleData/BattleState/Ture",turn);
							DataLibrary::getSingletonPtr()->setData("GameData/BattleData/BattleState/CurTeam",team);
							mGUIState->showScene("");
							mGUIState->update();

							std::string temp;
							DataLibrary::getSingletonPtr()->getData("GameData/BattleData/MapData/MapName",temp);
							//int val;
							//DataLibrary::getSingletonPtr()->getData("GameData/BattleData/BattleState/Ture",val);
							DataLibrary::getSingletonPtr()->setData("SystemConfig/Save/Save2",std::string("AutoSave ")+temp+" "+str(boost::format(StringTable::getSingletonPtr()->getString("RoundNum"))%(turn)));
							DataLibrary::getSingletonPtr()->saveXmlData(DataLibrary::SystemConfig,std::string("..\\save")+std::string("\\Config.xml"));
							StateManager::getSingletonPtr()->saveState(std::string("..\\save")+std::string("\\save2.xml"));
						}
						BattlePlayerState* playerstate = new BattlePlayerState();
						mMainState->PushState(playerstate);
						nextteam = true;
					}
					break;
				case 2:
				case 3:
				case 4:
					{
						std::string tempid;
						std::string tempInfo;
						DataLibrary::getSingletonPtr()->getData(str(boost::format("GameData/BattleData/Team/Team%1%/Relation")%team), tempid);
						if (tempid=="enemy1" || tempid=="enemy2" ||tempid=="enemy3")
						{
							tempInfo="EnemyTurn.png";
						}
						else if (tempid=="alliance")
						{
							tempInfo="FriendlyTurn.png";
						}

						std::string teamstr;
						std::string teampath =str(boost::format("GameData/BattleData/Team/Team%1%/FactionId")%team);
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
								CutSceneDirector* cutscenedirector = new CutSceneDirector(CutSceneBuilder::getSingleton().getCutScenes());
								mMainState->PushState(cutscenedirector);
								mCurState = ControlState_TurnStart;
								DataLibrary::getSingletonPtr()->setData("GameData/BattleData/BattleState/Ture",turn);
								DataLibrary::getSingletonPtr()->setData("GameData/BattleData/BattleState/CurTeam",team);
								mGUIState->showScene("");
								mGUIState->update();
								return;
							}
							else
							{
								GUIBattle* mGUIBattle = static_cast<GUIBattle *>(GUISystem::getSingleton().getScene(BattleScene));
								GUIInfoWindow* infoWindow=(GUIInfoWindow*)mGUIBattle->getSubWindow("InfoWindow");
								infoWindow->setCaption(tempInfo,MyGUI::Colour::White);
								infoWindow->showScene("");
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
			if(team == 1)
			{
				std::string temp;
				DataLibrary::getSingletonPtr()->getData("GameData/BattleData/MapData/MapName",temp);
				//int val;
				//DataLibrary::getSingletonPtr()->getData("GameData/BattleData/BattleState/Ture",val);
				DataLibrary::getSingletonPtr()->setData("SystemConfig/Save/Save2",std::string("AutoSave ")+temp+" "+str(boost::format(StringTable::getSingletonPtr()->getString("RoundNum"))%(turn)));
				DataLibrary::getSingletonPtr()->saveXmlData(DataLibrary::SystemConfig,std::string("..\\save")+std::string("\\Config.xml"));
				StateManager::getSingletonPtr()->saveState(std::string("..\\save")+std::string("\\save2.xml"));
			}
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
			battlesquadmanager->turnEnd(team);
			DataLibrary::getSingleton().saveXmlData(DataLibrary::GameData,"test.xml");
			if(CutSceneBuilder::getSingleton().hasCutScenes())
			{
				CutSceneDirector* cutscenedirector = new CutSceneDirector(CutSceneBuilder::getSingleton().getCutScenes());
				mMainState->PushState(cutscenedirector);
			}
			mCurState = ControlState_TurnEnd;
		}
		break;
	case ControlState_TurnEnd:
	case ControlState_NewGame:
	case ControlState_LoadGame:
		mCurState = ControlState_Normal;
		break;
	}
}