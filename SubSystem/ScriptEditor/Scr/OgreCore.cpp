#include "OgreCore.h"

#include "GUISystem.h"
#include "GUIStage.h"

#include "LuaSystem.h"

#include "AudioSystem.h"

OgreCore::OgreCore(void)
{
}

OgreCore::~OgreCore(void)
{
}

bool OgreCore::setup()
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
		mWindow=mRoot->initialise(true, "RenderWindow");

		mSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC);

		mCamera = mSceneMgr->createCamera("PlayerCam");
		mCamera->setPosition(Ogre::Vector3(0,10,382));
		mCamera->lookAt(Ogre::Vector3(0,0,0));
		mCamera->setNearClipDistance(5);

		Ogre::Viewport* vp = mWindow->addViewport(mCamera);
		mCamera->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));

		initializeResource();

		Ogre::ResourceGroupManager::getSingletonPtr()->initialiseAllResourceGroups();
		
		mGUISystem=new GUISystem(mWindow,mSceneMgr);
		mGUISystem->registerSceneFactory(StageScene,new GUIStageFactory());
		GUIScene* stage=mGUISystem->createScene(StageScene);
		stage->showScene("");

		mLuaSystem=new LuaSystem();

		mAudioSystem=new AudioSystem();

		mAudioSystem->init();

		initializeOIS();

		return true;
	}
	else
	{
		return false;
	}

}

void OgreCore::initializeResource()
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

void OgreCore::initializeOIS()
{
	OIS::ParamList pl;	
	size_t windowHnd = 0;
	std::ostringstream windowHndStr;

	OgreCore::getSingletonPtr()->mWindow->getCustomAttribute("WINDOW",&windowHnd);
	windowHndStr << windowHnd;
	pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

	//Default mode is foreground exclusive..but, we want to show mouse - so nonexclusive
	pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_FOREGROUND" )));
	pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_NONEXCLUSIVE")));

	mInputManager = OIS::InputManager::createInputSystem( pl );

	//Create all devices
	mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject( OIS::OISKeyboard, true ));
	mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject( OIS::OISMouse, true ));

	mKeyboard->setEventCallback(static_cast<OIS::KeyListener*>(mGUISystem));
	mMouse->setEventCallback(static_cast<OIS::MouseListener*>(mGUISystem));

	//Set initial mouse clipping size
	mMouse->getMouseState().width = mWindow->getWidth();
	mMouse->getMouseState().height = mWindow->getHeight();
}

void OgreCore::RenderingFrame()
{
	mRoot->renderOneFrame();

	mKeyboard->capture();
	mMouse->capture();

	mGUISystem->FrameUpdate();

	mAudioSystem->FrameUpdate();

	mLuaSystem->onFrameUpdate();
}

