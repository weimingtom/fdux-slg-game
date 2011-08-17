#pragma once

#include <Ogre.h>
#include <ParticleUniverseSystem.h> 

#include <OIS.h>

#include "iisingleton.hpp"

using namespace izayoi;

class GUISystem;

class LuaSystem;

class AudioSystem;

class StateManager;

class DataLibrary;

class InputControl;

class Framerate;

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
	Ogre::Overlay* mDebugOverlay;

	//粒子系统
	ParticleUniverse::ParticleSystem* createPUSystem(std::string name,std::string script);
	void destroyPUSystem(ParticleUniverse::ParticleSystem* pu);
	std::vector<ParticleUniverse::ParticleSystem*> mPUSystems;

	//OIS系统指针
	OIS::InputManager*	mInputManager;
	OIS::Keyboard* mKeyboard;
	OIS::Mouse*	mMouse;

	//游戏子系统指针
	InputControl* mInputControl;
	GUISystem* mGUISystem;
	LuaSystem* mLuaSystem;
	AudioSystem* mAudioSystem;

	//游戏管理器
	StateManager* mStateManager;
	DataLibrary* mDataLibrary;
	Framerate* mFramerate;
	
	//系统初始化
	bool initialize(bool isFullScene);
	//系统启动
	void run();
	//系统停止
	void stop();
	//处理渲染窗口关闭
	bool windowClosing(Ogre::RenderWindow* rw);

private:
	void Uninitialize();

	void RenderingFrame(unsigned int deltaTime);
	
	void initializeOIS();

	void initializeResource();

	void updateStats(void);

	bool testHardwareSupport();

	bool isRun;

	
};
