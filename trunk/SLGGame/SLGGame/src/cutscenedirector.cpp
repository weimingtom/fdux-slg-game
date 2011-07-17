#include "cutscenediretor.h"
#include "cutscene.h"

#include "BattleState.h"
#include "CameraContral.h"

CutSceneDirector::CutSceneDirector()
{
	mId = 0;
	mMouseX = 640;
	mMouseY = 360;
	mCameraContral = CameraContral::getSingletonPtr();
}
CutSceneDirector::~CutSceneDirector()
{
	CutSceneIte ite;
	for(ite = mCutScene.begin(); ite != mCutScene.end();ite++)
	{
		delete ite->second;
	}
}

int CutSceneDirector::addCutScene(CutScene* cutscene)
{
	if(cutscene!= NULL)
	{
		int id = mId++;
		mCutScene.insert(CutScenePair(id, cutscene));
		cutscene->start();
		return id;
	}
	return -1;
}

void CutSceneDirector::skipCutScene(int id)
{
	CutSceneIte ite;
	ite = mCutScene.find(id);
	if(ite != mCutScene.end())
	{
		ite->second->skipall();
	}
}

void CutSceneDirector::update(unsigned int deltaTime)
{
	float dx = 0.0f,dy = 0.0f;
	float dt = (float)deltaTime / 5.0f;
	if(mMouseX < 20)
		dx = -dt;
	if(mMouseX > 1260)
		dx = dt;
	if(mMouseY < 20)
		dy = -dt;
	if(mMouseY > 680)
		dy = dt;
	mCameraContral->moveCamera(dx,dy);

	CutSceneIte ite;
	for(ite = mCutScene.begin(); ite != mCutScene.end();)
	{
		if(ite->second->end())
		{
			delete ite->second;
			ite = mCutScene.erase(ite);
		}
		else
		{
			ite->second->update(deltaTime);
			ite++;
		}
	}
	if(mCutScene.size() == 0)
		mMainState->PopState();
}

bool CutSceneDirector::keyPressed(const OIS::KeyEvent &arg)
{
	return false;
}
bool CutSceneDirector::keyReleased(const OIS::KeyEvent &arg)
{
	return false;
}

bool CutSceneDirector::mouseMoved(const OIS::MouseEvent &arg)
{
	mMouseX = arg.state.X.abs;
	mMouseY = arg.state.Y.abs;
	return false;
}
bool CutSceneDirector::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
	return false;
}
bool CutSceneDirector::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
	return false;
}