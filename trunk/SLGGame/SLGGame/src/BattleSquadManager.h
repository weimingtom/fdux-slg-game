#pragma once

#include "iisingleton.hpp"
using namespace izayoi;

#include <string>
#include <map>
#include <vector>

#include <Ogre.h>

#include "squaddefine.h"

class BattleSquad;
class CutScene;

class BattleSquadManager:public IISingleton<BattleSquadManager>
{
public:
	BattleSquadManager();
	~BattleSquadManager();

	void clear();

	typedef std::map<std::string, BattleSquad*>::iterator BattleSquadIte;
	std::map<std::string, BattleSquad*> mSquadList;

	bool allDeployed();

	BattleSquad* getBattleSquad(std::string id);
	BattleSquad* getBattleSquadAt(int x, int y, int faction, bool visibleonly);

	//移动相关
public:
	struct MoveNode
	{
		int x;
		int y;
		int lastx;
		int lasty;
		float apleft;
		unsigned int eventflag;
	};
	std::map<int, MoveNode> getMoveArea(BattleSquad* squad);
	std::vector<MoveNode> getMovePath(BattleSquad* squad, int x, int y);
	void moveSquad(BattleSquad* squad, std::vector<int> pointlist, unsigned int &stopedpoint, unsigned int &eventflag);
	void InterruptMove();

public:
	bool m_moveInterrupt;
	BattleSquad* m_moveSquad;
	std::vector<Ogre::Vector2> m_moveList;
	Ogre::Vector2 m_startPoint;

	//切换阵型
public:
	void changeFormation(BattleSquad* squad, enumtype formation, bool costap);

	//技能相关
public:
// 	bool useSkillOn(BattleSquad* attacksquad, BattleSquad* targetsquad, std::string skillid);
// 	bool useSkillAt(BattleSquad* attacksquad, int x, int y, std::string skillid);

	bool dealMeleeDamage(BattleSquad* attacksquad, BattleSquad* defenesquad);
	
	bool dealMagicDamage(BattleSquad* attacksquad, BattleSquad* defenesquad, int attacktime, float atk, int fluctuate);

	bool dealRangedDamage(BattleSquad* attacksquad, BattleSquad* defenesquad);
};