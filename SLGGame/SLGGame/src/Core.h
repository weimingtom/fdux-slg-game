#pragma once

#include <Ogre.h>

#include <OIS.h>

#include "iisingleton.hpp"

using namespace izayoi;

class GUISystem;

class LuaSystem;

class AudioSystem;

class StateManager;

//游戏核心类,处理游戏初始化以及结束,存放了各个系统的指针
class Core:public IISingleton<Core>,public Ogre::WindowEventListener
{
public:
	Core(void);
	~Core(void);

	//Oger系统指针
	Ogre::LogManager* logMgr;
	Ogre::Log* log;
	Ogre::Root *mRoot;
	Ogre::Camera* mCamera;
	Ogre::SceneManager* mSceneMgr;
	Ogre::RenderWindow* mWindow;

	//OIS系统指针
	OIS::InputManager*	mInputManager;
	OIS::Keyboard* mKeyboard;
	OIS::Mouse*	mMouse;

	//游戏子系统指针
	GUISystem* mGUISystem;
	LuaSystem* mLuaSystem;
	AudioSystem* mAudioSystem;

	//游戏管理器
	StateManager* mStateManager;
	
	//系统初始化
	bool initialize();
	//系统启动
	void run();
	//系统停止
	void stop();
	//处理渲染窗口关闭
	bool windowClosing(Ogre::RenderWindow* rw);

private:
	void Uninitialize();

	void RenderingFrame();
	
	void initializeOIS();

	void initializeResource();

	bool isRun;
};
