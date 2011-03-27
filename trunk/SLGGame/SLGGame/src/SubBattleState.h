#pragma once

class BattleState;

class SubBattleState
{
public:
	SubBattleState(BattleState* mainState);

	~SubBattleState();

	virtual void update(unsigned int deltaTime) = 0;

protected:
	BattleState* mMainState;
};