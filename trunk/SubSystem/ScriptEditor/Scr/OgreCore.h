#pragma once

#include <Ogre.h>

#include <OIS.h>

#include "iisingleton.hpp"

using namespace izayoi;

class GUISystem;

class LuaSystem;

class AudioSystem;

class OgreCore:public IISingleton<OgreCore>
{
public:
	OgreCore(void);
	~OgreCore(void);

	Ogre::LogManager* logMgr;
	Ogre::Log* log;
	Ogre::Root *mRoot;
	Ogre::Camera* mCamera;
	Ogre::SceneManager* mSceneMgr;
	Ogre::RenderWindow* mWindow;

	OIS::InputManager*	mInputManager;
	OIS::Keyboard* mKeyboard;
	OIS::Mouse*	mMouse;

	GUISystem* mGUISystem;

	LuaSystem* mLuaSystem;

	AudioSystem* mAudioSystem;

	bool setup();

	void RenderingFrame();
private:
	void initializeOIS();

	void initializeResource();

};
