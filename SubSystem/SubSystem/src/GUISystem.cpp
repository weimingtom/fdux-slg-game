#include "GUISystem.h"

#include "GUIScene.h"
#include "GUIStage.h"

#include "MyGUI_RTTLayer.h"

GUISystem::GUISystem(Ogre::RenderWindow* window,Ogre::SceneManager* scene):mWindow(window),mSceneManager(scene),mFrameUpdateScene(NULL)
{
	mPlatform = new MyGUI::OgrePlatform();
	mPlatform->initialise(mWindow, mSceneManager);
	mGUI = new MyGUI::Gui();
	mGUI->initialise("MyGUI_Core.xml");
	MyGUI::FactoryManager::getInstance().registerFactory<MyGUI::RTTLayer>("Layer");
	MyGUI::ResourceManager::getInstance().load("MyGUI_Layers.xml");
	MyGUI::ResourceManager::getInstance().load("MyGUI_Pointers.xml");
	MyGUI::ResourceManager::getInstance().load("MyGUI_Settings.xml");
}

GUISystem::~GUISystem(void)
{
	for (std::vector<GUIScene*>::iterator it=mSceneList.begin();it!=mSceneList.end();it++)
	{
		delete (*it);
	}
	mSceneList.clear();

	std::map<GUISceneType,GUISceneFactory*>::iterator iter;

	for(iter = mSceneFactorys.begin(); iter != mSceneFactorys.end(); iter++)
	{
		delete iter->second;
	}

	if (mGUI)
	{
		mGUI->shutdown();
		delete mGUI;
		mGUI = nullptr;
	}

	if (mPlatform)
	{
		mPlatform->shutdown();
		delete mPlatform;
		mPlatform = nullptr;
	}
}

bool GUISystem::keyPressed( const OIS::KeyEvent &arg )
{
	//将OIS的消息注入到MyGUI中
	return mGUI->injectKeyPress(MyGUI::KeyCode::Enum(arg.key), (MyGUI::Char)arg.text);
	
}

bool GUISystem::keyReleased( const OIS::KeyEvent &arg )
{
	return mGUI->injectKeyRelease(MyGUI::KeyCode::Enum(arg.key));
}

bool GUISystem::mouseMoved( const OIS::MouseEvent &arg )
{
	return mGUI->injectMouseMove(arg.state.X.abs,arg.state.Y.abs,arg.state.Z.abs);
}

bool GUISystem::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
	return mGUI->injectMousePress(arg.state.X.abs,arg.state.Y.abs, MyGUI::MouseButton::Enum(id));
}

bool GUISystem::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
	return mGUI->injectMouseRelease(arg.state.X.abs,arg.state.Y.abs, MyGUI::MouseButton::Enum(id));
}


void GUISystem::registerSceneFactory( GUISceneType type,GUISceneFactory* factory )
{
	mSceneFactorys[type]=factory;
}


GUIScene* GUISystem::createScene(GUISceneType type )
{
	GUIScene* scene=NULL;

	std::map<GUISceneType,GUISceneFactory*>::iterator itr;
	itr = mSceneFactorys.find(type);

	if( itr != mSceneFactorys.end() )
	{
		scene=itr->second->CreateScene(mWindow->getWidth(),mWindow->getHeight());
	}
	else
	{
		return NULL;
	}

	if (scene!=NULL)
	{
		mSceneList.push_back(scene);
	}

	return scene;
}

void GUISystem::destoryScene( GUISceneType type )
{
	GUIScene* scene=NULL;
	scene=getScene(type);
	if (scene!=NULL)
	{
		std::vector<GUIScene*>::iterator itr = mSceneList.begin();
		while (itr != mSceneList.end())
		{
			if (*itr == scene)
			{
				mSceneList.erase(itr);
				break;
			}
			++itr;
		}

	}
	
	if (mFrameUpdateScene==scene)
	{
		mFrameUpdateScene=NULL;
	}

	delete scene;
}

GUIScene* GUISystem::getScene( GUISceneType type )
{
	for (std::vector<GUIScene*>::iterator it=mSceneList.begin();it!=mSceneList.end();it++)
	{
		if ((*it)->getType()==type)
		{
			return (*it);
		}
	}

	return NULL;
}

void GUISystem::FrameUpdate()
{
	if(mFrameUpdateScene!=NULL)
	{
		mFrameUpdateScene->FrameEvent();
	}
}

void GUISystem::setFrameUpdateScene( GUISceneType type )
{
	
	if (type==NoneScene)
	{
		mFrameUpdateScene=NULL;
	}
	else
	{
		for (std::vector<GUIScene*>::iterator it=mSceneList.begin();it!=mSceneList.end();it++)
		{
			if ((*it)->getType()==type)
			{
				mFrameUpdateScene=(*it);
			}
		}
	}
}
