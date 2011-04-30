#include "BattleControlState.h"

#include "DataLibrary.h"
#include "LuaSystem.h"
#include "GUIBattle.h"
#include "GUISystem.h"
#include "BattleState.h"
#include "BattlePlayerState.h"
#include "GUIGameStateWindows.h"


BattleControlState::BattleControlState(bool newgame)
{
	if(newgame)
	{
		DataLibrary::getSingletonPtr()->setData("GameData/BattleData/BattleState/Ture",0);
		DataLibrary::getSingletonPtr()->setData("GameData/BattleData/BattleState/CurTeam",4);

		//运行地图初始化脚本
		std::string mapscript;
		bool re = DataLibrary::getSingletonPtr()->getData("GameData/BattleData/MapData/MapScript",mapscript);
		LuaSystem::getSingleton().ExecuteFunction(mapscript, "initmap", "GameData/BattleData/MapData/MapScript/ScriptContext");
	}
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
	bool re = DataLibrary::getSingletonPtr()->getData("GameData/BattleData/BattleState/Ture",turn);
	re = DataLibrary::getSingletonPtr()->getData("GameData/BattleData/BattleState/CurTeam",team);
	//执行回合结束触发器

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
				mMainState->PushState(playerstate);
				turn = turn + 1;
				nextteam = true;
			}
			break;
		case 2:
			nextteam = false;
			break;
		case 3:
			nextteam = false;
			break;
		case 4:
			nextteam = false;
			break;
		}
	}
	DataLibrary::getSingletonPtr()->setData("GameData/BattleData/BattleState/Ture",turn);
	DataLibrary::getSingletonPtr()->setData("GameData/BattleData/BattleState/CurTeam",team);
	mGUIState->update();
}