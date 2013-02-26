#include "Core.h"

#include "GUISystem.h"
#include "GUIMenu.h"
//#include "GUIPUDebug.h"
#include "GUIStage.h"
#include "LoadScene.h"
#include "GUIBattle.h"
#include "GUIMenuWindow.h"
#include "GUIMessageBox.h"
#include "GUIOptionWindow.h"
#include "GUISupply.h"
#include "GUIDebugWindow.h"

#include "LuaSystem.h"
#include "AudioSystem.h"
#include "InputControl.h"

#include "StateManager.h"
#include "DataLibrary.h"
#include "StringTable.h"
#include "LuaAVG.h"
#include "AVGSquadManager.h"
#include "CutSceneBuilder.h"
#include "BattleSquadManager.h"
#include "SquadGrapManager.h"
#include "timer.hpp"
#include "MapDataManager.h"
#include "Terrain.h"
#include "CameraContral.h"
#include "LuaSkill.h"
#include "LuaScriptCommon.h"
#include "LuaMap.h"
#include "LuaSquad.h"
#include "LuaBattle.h"
#include "GUISLWindow.h"
#include "Framerate.h"
#include "UtilsOgreDshow.h"

#include <ParticleUniverseSystemManager.h> 

#include "resource.h"
#include <windows.h>
#include <Shiny.h>

#define VER "V0.1a "

Core::Core(void):isRun(false)
{
}

Core::~Core(void)
{
}

bool Core::initialize(bool isFullScene)
{
	mRoot = new Ogre::Root("Plugins.cfg","","log.txt");
// 	if(!mRoot->restoreConfig())
// 	{
// 		rtn=mRoot->showConfigDialog();
// 	}
// 	else
// 	{
// 		rtn=true;
// 	}
	Ogre::RenderSystem *rSys = mRoot->getRenderSystemByName("Direct3D9 Rendering Subsystem");
	if(!rSys)
		return false;
	
	mRoot->setRenderSystem(rSys);

	mRoot->initialise(false);

	std::string title = "忘却的战场";//StringTable::getSingleton().getAnsiString("gamename");
	title+=" ";
	title+=VER;

	Ogre::NameValuePairList list;

	list["outerDimensions"]="true";
	list["border"]="fixed"; 

	mWindow = mRoot->createRenderWindow(title,1280,720,isFullScene,&list);

	if(!testHardwareSupport())
	{
		return false;
	}

	HWND   hwnd;
	mWindow->getCustomAttribute("WINDOW", &hwnd);   
	SendMessage(hwnd,WM_SETICON,ICON_SMALL,(LPARAM)LoadIcon(GetModuleHandle(NULL),MAKEINTRESOURCE(IDI_ICON1)));   

	Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);

	mSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC);

	Ogre::MovableObject::setDefaultQueryFlags(QUERYMASK_OTHER);
	Ogre::MovableObject::setDefaultVisibilityFlags(VISMASK_OPAQUE);

	mCamera = mSceneMgr->createCamera("PlayerCam");
	mCamera->setPosition(Ogre::Vector3(50.0f,0.0f,50.0f));
	mCamera->lookAt(Ogre::Vector3(0.0f,0.0f,0.0f));
	mCamera->setNearClipDistance(5.0f);
	mCamera->setFarClipDistance(500.0f);

	Ogre::Viewport* vp = mWindow->addViewport(mCamera);
	vp->setMaterialScheme("Default");
	//vp->setMaterialScheme("WriteDepthMap");
	mCamera->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
	//mCamera->setProjectionType(Ogre::PT_ORTHOGRAPHIC);
	//mCamera->setOrthoWindowWidth(Ogre::Real(vp->getActualWidth())/5);
	initializeResource();

	Ogre::ResourceGroupManager::getSingletonPtr()->initialiseAllResourceGroups();

	mRoot->addFrameListener(new OgreUtils::DirectShowManager(vp));

	//初始化数据文件
	mLuaSystem=new LuaSystem();
	mDataLibrary=new DataLibrary();
	mDataLibrary->loadXmlData(DataLibrary::StaticData,"datafile.xml",true, "Data");
	mDataLibrary->loadXmlData(DataLibrary::StaticData,"datafile.xml",true, "Lang");
	mDataLibrary->loadXmlData(DataLibrary::StaticData,"stringtable.xml",true, "Lang");
	mDataLibrary->loadXmlData(DataLibrary::SystemConfig,"Config.xml",true, "Save");

	mDebugOverlay = Ogre::OverlayManager::getSingleton().getByName("Core/DebugOverlay");

	mGUISystem=new GUISystem(mWindow,mSceneMgr);
	mGUISystem->registerSceneFactory(StageScene,new GUIStageFactory());
	mGUISystem->registerSceneFactory(MenuScene,new GUIMenuFactory());
	//mGUISystem->registerSceneFactory(PUDebugScene,new GUIPUDebugFactory());
	mGUISystem->registerSceneFactory(BattleScene,new GUIBattleFactory());
	mGUISystem->registerSceneFactory(LoadingScene, new LoadSceneFactory());
	mGUISystem->registerSceneFactory(SLScene, new GUISLWindowFactory());
	mGUISystem->registerSceneFactory(MenuWindowsScene, new GUIMenuWindowFactory());
	mGUISystem->registerSceneFactory(MessageBoxScene, new GUIMessageBoxFactory());
	mGUISystem->registerSceneFactory(OptionWindowScene, new GUIOptionWindowFactory());
	mGUISystem->registerSceneFactory(SupplyScene, new GUISupplywFactory());
	mGUISystem->registerSceneFactory(DebugWindowsScene, new GUIDebugWindowFactory());
	
	mAudioSystem=new AudioSystem();

	mAudioSystem->init();

	mInputControl=new InputControl();
	mInputControl->setGUISystem(mGUISystem);

	initializeOIS();

	//初始化阴影
	mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_NONE);

	new StringTable;
	//初始化文字部分
	mLuaSystem->registerCLib("AVGLib",AVGLib);
	new AVGSquadManager;

	//初始化战斗部分
	new BattleSquadManager;
	new CutSceneBuilder;
	new MapDataManager;
	new SquadGrapManager(mSceneMgr);
	new Terrain;
	new CameraContral;
	mLuaSystem->registerCLib("ScriptCommonLib",ScriptCommonLib);
	mLuaSystem->registerCLib("SkillLib",SkillLib);
	mLuaSystem->registerCLib("MapLib",MapLib);
	mLuaSystem->registerCLib("SquadLib",SquadLib);
	mLuaSystem->registerCLib("BattleLib",BattleLib);


	mStateManager=new StateManager();
	mStateManager->changeState("logo",StateManager::Menu);

	mFramerate=new Framerate();
	mFramerate->Init(60);

	isRun=true;

	return true;

}

bool Core::testHardwareSupport()
{
	const Ogre::RenderSystemCapabilities* caps=mRoot->getRenderSystem()->getCapabilities();
	if (!caps->hasCapability(Ogre::RSC_VERTEX_PROGRAM) || !caps->hasCapability(Ogre::RSC_FRAGMENT_PROGRAM))
	{
		MessageBoxA(NULL, StringTable::getSingleton().getAnsiString("NotSupportGPUPrograms").c_str(),StringTable::getSingleton().getAnsiString("gamename").c_str(), MB_OK | MB_ICONERROR | MB_TASKMODAL);
		return false;
	}

	if (!Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("arbfp1") &&
		!Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("ps_2_x") &&
		!Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("vs_2_0"))
	{
		MessageBoxA(NULL, StringTable::getSingleton().getAnsiString("NotSupportSM2_0").c_str(),StringTable::getSingleton().getAnsiString("gamename").c_str(), MB_OK | MB_ICONERROR | MB_TASKMODAL);
		return false;
	}

	Ogre::TexturePtr ptrTexture = Ogre::TextureManager::getSingleton().createManual("TestBigSize", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, Ogre::TEX_TYPE_2D, 4096,4096, 0, Ogre::PF_R8G8B8, Ogre::TU_RENDERTARGET);

	if (ptrTexture->getWidth()!=4096)//如果不支持至少4096的贴图,那么将报错
	{
		MessageBoxA(NULL, StringTable::getSingleton().getAnsiString("NotSupportBigTexture").c_str(),StringTable::getSingleton().getAnsiString("gamename").c_str(), MB_OK | MB_ICONERROR | MB_TASKMODAL);
		return false;
	}

	Ogre::TextureManager::getSingleton().remove("TestBigSize");

	return true;
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
	ShowCursor(0);
	OIS::ParamList pl;	
	size_t windowHnd = 0;
	std::ostringstream windowHndStr;

	mWindow->getCustomAttribute("WINDOW",&windowHnd);
	windowHndStr << windowHnd;
	pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

	//Default mode is foreground exclusive..but, we want to show mouse - so nonexclusive
	pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_FOREGROUND")));
	pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_NONEXCLUSIVE")));
	//pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_EXCLUSIVE")));//无鼠标模式

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
		mFramerate->SetSpeedFactor();
		timer.reset();
		RenderingFrame(t);
		t=timer.getMilliseconds();

		if(t<15)//限制到60帧
		{
			Sleep(15-t);
			t=15;
		}

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
		//mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_NONE);
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
	pSys->setVisibilityFlags(VISMASK_TRANSPARENT);
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

void Core::destroyAllPUSystem()
{
	for (std::vector<ParticleUniverse::ParticleSystem*>::iterator it=mPUSystems.begin();it!=mPUSystems.end();it++)
	{
		ParticleUniverse::ParticleSystemManager::getSingletonPtr()->destroyParticleSystem((*it),mSceneMgr);
	}

	mPUSystems.clear();
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
