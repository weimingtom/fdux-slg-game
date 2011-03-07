#pragma once

#include <vector>

#include "GamePlayer.h"

//回合控制器,管理回合控制以及玩家交替
class TurnControl
{
public:
	TurnControl(void);
	~TurnControl(void);
	
	//初始化回合
	void initTurn();

	//切换到下一个玩家
	void nextTurn();

	//保存当前回合状态
	void saveTurn();

	//读取回合状态
	void loadTurn();
	
	//获取当前玩家
	GamePlayer* getCurrencyPlayer();

private:

	int mTurnNum;

	std::vector<GamePlayer*> mPlayerList;

	std::vector<GamePlayer*>::iterator mPlayerIt;

};
