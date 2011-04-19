#pragma once

#include <string>

#include "squaddefine.h"

class BattleSquad
{
public:
	BattleSquad(std::string id, int grapid,int x, int y);
	~BattleSquad();

	void setCrood(int x, int y);
	void getCrood(int* x, int* y);

	void setDirection(Direction d);
	Direction getDirection();

	std::string getSquadName();
	int getGrapId() { return mGrapId; }

private:
	int mX;
	int mY;
	int mGrapId;
	int mTeam;
	std::string mId;
};