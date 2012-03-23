#pragma once

#include "SubBattleState.h"
#include "InputListener.h"

//#include <map>


class CutScene;
class CameraContral;

class CutSceneDirector:public SubBattleState, public InputListener
{
public:
	CutSceneDirector(CutScene* cutscene);
	~CutSceneDirector();

//	void addCutScene(CutScene* cutscene);
	void skipCutScene();

	virtual bool keyPressed(const OIS::KeyEvent &arg);
	virtual bool keyReleased(const OIS::KeyEvent &arg);

	virtual bool mouseMoved(const OIS::MouseEvent &arg);
	virtual bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
	virtual bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);

	virtual void update(unsigned int deltaTime);
private:
// 	typedef std::pair<int, CutScene*> CutScenePair;
// 	typedef std::map<int, CutScene*>::iterator CutSceneIte;
// 	std::map<int, CutScene*> mCutScene;
	CutScene* mCutScene;
	int mId;

	int mMouseX;
	int mMouseY;
	CameraContral* mCameraContral;
};