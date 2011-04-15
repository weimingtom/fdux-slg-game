#include "Core.h"

#include "GUISystem.h"
#include "GUIMenu.h"
#include "GUIPUDebug.h"
#include "GUIStage.h"
#include "LoadScene.h"
#include "GUIBattle.h"

#include "LuaSystem.h"
#include "AudioSystem.h"
#include "InputControl.h"

#include "StateManager.h"
#include "DataLibrary.h"
#include "StringTable.h"
#include "LuaAVG.h"
#include "AVGSquadManager.h"
#include "BattleSquadManager.h"
#include "SquadGrapManager.h"
#include "timer.hpp"

#include <ParticleUniverseSystemManager.h> 

Core::Core(void):isRun(false)
{
}

Core::~Core(void)
{
}

bool Core::initialize()
{
	bool rtn=false;
	mRoot = new Ogre::Root("Plugins.cfg","ogre.cfg","log.txt");
	if(!mRoot->restoreConfig())
	{
		rtn=mRoot->showConfigDialog();
	}
	else
	{
		rtn=true;
	}
	if (rtn)
	{
		mWindow=mRoot->initialise(true, "忘却的战场");
		Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);

		mSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC);

		mCamera = mSceneMgr->createCamera("PlayerCam");
		mCamera->setPosition(Ogre::Vector3(0,50,382));
		mCamera->lookAt(Ogre::Vector3(0,0,0));
		mCamera->setNearClipDistance(0.5f);
		mCamera->setFarClipDistance(500.0f);

		Ogre::Viewport* vp = mWindow->addViewport(mCamera);
		mCamera->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));

		initializeResource();

		Ogre::ResourceGroupManager::getSingletonPtr()->initialiseAllResourceGroups();

		mDebugOverlay = Ogre::OverlayManager::getSingleton().getByName("Core/DebugOverlay");
		mDebugOverlay->show();

		mGUISystem=new GUISystem(mWindow,mSceneMgr);
		mGUISystem->registerSceneFactory(StageScene,new GUIStageFactory());
		mGUISystem->registerSceneFactory(MenuScene,new GUIMenuFactory());
		mGUISystem->registerSceneFactory(PUDebugScene,new GUIPUDebugFactory());
		mGUISystem->registerSceneFactory(BattleScene,new GUIBattleFactory());
		mGUISystem->registerSceneFactory(LoadingScene, new LoadSceneFactory());

		mLuaSystem=new LuaSystem();
		mLuaSystem->registerCLib("AVGLib",AVGLib);

		mAudioSystem=new AudioSystem();

		mAudioSystem->init();

		mInputControl=new InputControl();
		mInputControl->setGUISystem(mGUISystem);

		initializeOIS();

		//初始化数据文件
		mDataLibrary=new DataLibrary();
		mDataLibrary->loadXmlData(DataLibrary::StaticData,"../media/data/datafile.xml",true);
		mDataLibrary->loadXmlData(DataLibrary::StaticData,"../media/lang/chinese/datafile.xml",true);
		mDataLibrary->loadXmlData(DataLibrary::StaticData,"../media/lang/chinese/stringtable.xml",true);
		new StringTable;
		new AVGSquadManager;

		//初始化战斗部分
		new BattleSquadManager;
		new SquadGrapManager(mSceneMgr);


		mStateManager=new StateManager();
		mStateManager->changeState("logo",StateManager::Menu);



		isRun=true;

		return true;
	}
	else
	{
		return false;
	}

}

void Core::initializeResource()
{
	Ogre::ConfigFile cf;

	cf.load("resources.cfg");

	// Go through all sections & settings in the file

	Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();

	Ogre::String secName, typeName, archName;

	while (seci.hasMoreElements())

	{

		secName = seci.peekNextKey();

		Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();

		Ogre::ConfigFile::SettingsMultiMap::iterator i;

		for (i = settings->begin(); i != settings->end(); ++i)

		{

			typeName = i->first;

			archName = i->second;

			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(

				archName, typeName, secName);

		}

	}

}

void Core::initializeOIS()
{
	OIS::ParamList pl;	
	size_t windowHnd = 0;
	std::ostringstream windowHndStr;

	mWindow->getCustomAttribute("WINDOW",&windowHnd);
	windowHndStr << windowHnd;
	pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

	//Default mode is foreground exclusive..but, we want to show mouse - so nonexclusive
	pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_FOREGROUND" )));
	//pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_NONEXCLUSIVE;")));
	pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_EXCLUSIVE")));//无鼠标模式

	mInputManager = OIS::InputManager::createInputSystem( pl );

	//Create all devices
	mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject( OIS::OISKeyboard, true ));
	try
	{
		mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject( OIS::OISMouse, true ));
	}
	catch (OIS::Exception e)
	{
		std::cout<<e.eText<<std::endl;
	}
	

	mKeyboard->setEventCallback(static_cast<OIS::KeyListener*>(mInputControl));
	mMouse->setEventCallback(static_cast<OIS::MouseListener*>(mInputControl));

	//Set initial mouse clipping size
	mMouse->getMouseState().width = mWindow->getWidth();
	mMouse->getMouseState().height = mWindow->getHeight();
}

void Core::RenderingFrame(unsigned int deltaTime)
{
	Ogre::WindowEventUtilities::messagePump();

	mKeyboard->capture();
	mMouse->capture();

	mGUISystem->FrameUpdate();

	mAudioSystem->FrameUpdate();

	mLuaSystem->onFrameUpdate();

	mStateManager->StateUpdate(deltaTime);

	mRoot->renderOneFrame();
}

void Core::run()
{
	Timer timer;
	unsigned long t=0;

	timer.reset();
	while(isRun)
	{
		timer.reset();
		RenderingFrame(t);
		t=timer.getMilliseconds();
		updateStats();
	}

	Uninitialize();
}

void Core::Uninitialize()
{
	delete mGUISystem;
	delete mLuaSystem;
	delete mAudioSystem;

	if (mSceneMgr)
	{
		mSceneMgr->clearScene();
		mSceneMgr->destroyAllCameras();
		mSceneMgr = nullptr;
		mCamera = nullptr;
	}

	if (mWindow)
	{
		mWindow->destroy();
		mWindow = nullptr;
	}

	if (mRoot)
	{
		delete mRoot;
		mRoot = nullptr;
	}
}

void Core::stop()
{
	isRun=false;
}

bool Core::windowClosing( Ogre::RenderWindow* rw )
{
	stop();
	return true;
}

ParticleUniverse::ParticleSystem* Core::createPUSystem( std::string name,std::string script )
{
	ParticleUniverse::ParticleSystem* pSys=ParticleUniverse::ParticleSystemManager::getSingletonPtr()->createParticleSystem(name,script,mSceneMgr);
	mPUSystems.push_back(pSys);
	return pSys;
}

void Core::destroyPUSystem( ParticleUniverse::ParticleSystem* pu )
{
	for (std::vector<ParticleUniverse::ParticleSystem*>::iterator it=mPUSystems.begin();it!=mPUSystems.end();it++)
	{
		if (pu==(*it))
		{
			mPUSystems.erase(it);
			break;
		}
	}

	 ParticleUniverse::ParticleSystemManager::getSingletonPtr()->destroyParticleSystem(pu,mSceneMgr);
}

void Core::updateStats(void)
{
	static Ogre::String currFps = "Current FPS: ";
	static Ogre::String avgFps = "Average FPS: ";
	static Ogre::String bestFps = "Best FPS: ";
	static Ogre::String worstFps = "Worst FPS: ";
	static Ogre::String tris = "Triangle Count: ";
	static Ogre::String batches = "Batch Count: ";

	// update stats when necessary

	Ogre::OverlayElement* guiAvg = Ogre::OverlayManager::getSingleton().getOverlayElement("Core/AverageFps");
	Ogre::OverlayElement* guiCurr = Ogre::OverlayManager::getSingleton().getOverlayElement("Core/CurrFps");
	Ogre::OverlayElement* guiBest = Ogre::OverlayManager::getSingleton().getOverlayElement("Core/BestFps");
	Ogre::OverlayElement* guiWorst = Ogre::OverlayManager::getSingleton().getOverlayElement("Core/WorstFps");

	const Ogre::RenderTarget::FrameStats& stats = mWindow->getStatistics();
	guiAvg->setCaption(avgFps + Ogre::StringConverter::toString(stats.avgFPS));
	guiCurr->setCaption(currFps + Ogre::StringConverter::toString(stats.lastFPS));
	guiBest->setCaption(bestFps + Ogre::StringConverter::toString(stats.bestFPS)
		+" "+Ogre::StringConverter::toString(stats.bestFrameTime)+" ms");
	guiWorst->setCaption(worstFps + Ogre::StringConverter::toString(stats.worstFPS)
		+" "+Ogre::StringConverter::toString(stats.worstFrameTime)+" ms");

	Ogre::OverlayElement* guiTris = Ogre::OverlayManager::getSingleton().getOverlayElement("Core/NumTris");
	guiTris->setCaption(tris + Ogre::StringConverter::toString(stats.triangleCount));

	Ogre::OverlayElement* guiBatches = Ogre::OverlayManager::getSingleton().getOverlayElement("Core/NumBatches");
	guiBatches->setCaption(batches + Ogre::StringConverter::toString(stats.batchCount));

}
