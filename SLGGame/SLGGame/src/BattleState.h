#pragma once
#include "gamestate.h"

#include <vector>
class SubBattleState;

class Terrain;
class CameraContral;
class MapDataManager;
class CutSceneDirector;

class SquadGrapManager;


class BattleState :
	public GameState
{
public:

	BattleState(void);
	~BattleState(void);

	void initialize(std::string arg);

	void uninitialize();

	void update(unsigned int deltaTime);

	void ChangeState(SubBattleState* substate); //ÇÐ»»×´Ì¬
	void PushState(SubBattleState* substate); //Ñ¹Èë×´Ì¬
	void PopState(); //Ñ¹³ö×´Ì¬

private:

	Terrain *mTerrain; //µØÐÎÊÔÍ¼

	std::vector<SubBattleState*> mSubStateStack; //Õ½¶·×´Ì¬¶ÑÕ»
	typedef std::vector<SubBattleState*>::iterator SubStateIte;
};