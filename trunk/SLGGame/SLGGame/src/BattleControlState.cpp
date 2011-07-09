#include "BattleControlState.h"

#include "DataLibrary.h"
#include "LuaSystem.h"
#include "GUIBattle.h"
#include "GUISystem.h"
#include "BattleState.h"
#include "BattlePlayerState.h"
#include "GUIGameStateWindows.h"
#include "TriggerManager.h"


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
		mNewGame = true;
		return;
	}
	//执行回合结束触发器
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
			team += 1;
			nextteam = false;
			break;
		case 3:
			team += 1;
			nextteam = false;
			break;
		case 4:
			team += 1;
			nextteam = false;
			break;
		}
	}
	DataLibrary::getSingletonPtr()->setData("GameData/BattleData/BattleState/Ture",turn);
	DataLibrary::getSingletonPtr()->setData("GameData/BattleData/BattleState/CurTeam",team);
	mGUIState->update();
	DataLibrary::getSingleton().saveXmlData(DataLibrary::GameData,"test.xml");
}