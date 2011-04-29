#pragma once

class BattleState;

class SubBattleState
{
public:
	SubBattleState();

	void setMainState(BattleState* mainstate);

	virtual ~SubBattleState();

	virtual void update(unsigned int deltaTime) = 0;

protected:
	BattleState* mMainState;
};