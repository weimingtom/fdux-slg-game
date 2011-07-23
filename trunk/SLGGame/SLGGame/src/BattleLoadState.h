#pragma once

#include "SubBattleState.h"
#include "InputListener.h"

#include <string>
class LoadScene;
class MapLoader;

const int LOADSCENE = 0;
const int LOADTERRAIN = 1;
const int LOADOBJECT = 2;
const int LOADUNIT = 3;
const int LOADGRID = 4;
const int LOADFINISH = 5;

class BattleLoadState: public SubBattleState, public InputListener
{
public:
	BattleLoadState(std::string arg);
	~BattleLoadState();

	virtual void update(unsigned int deltaTime);

	bool keyPressed(const OIS::KeyEvent &arg);
	bool keyReleased(const OIS::KeyEvent &arg){return false;}

	bool mouseMoved(const OIS::MouseEvent &arg){return false;}
	bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id){return false;}
	bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id){return false;}
private:
	MapLoader *mMapLoader;
	LoadScene* mLoadScene;
	bool mLoadFromMap;
	std::string mMapFile;
	int mState;
	bool mIsPressKey;
};