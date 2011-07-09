#pragma once

#include "GUICommon.h"
#include "iisingleton.hpp"

#include <ogre.h>
#include <MyGUI.h>
#include <MyGUI_OgrePlatform.h>

#include <vector>
#include <map>

using namespace izayoi;

#include <OIS.h>

class GUIScene;
class GUISceneFactory;

class GUISystem:public IISingleton<GUISystem>,public OIS::KeyListener,public OIS::MouseListener
{
public:
	GUISystem(Ogre::RenderWindow* window,Ogre::SceneManager* scene);
	~GUISystem(void);

	/* KeyListener Callbacks */
	bool keyPressed(const OIS::KeyEvent &arg);
	bool keyReleased(const OIS::KeyEvent &arg);

	/* MouseListener Callbacks */
	bool mouseMoved(const OIS::MouseEvent &arg);
	bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
	bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
	
	//GUI场景控制
	void registerSceneFactory(GUISceneType type,GUISceneFactory* factory);
	GUIScene* createScene(GUISceneType type);
	void destoryScene(GUISceneType type);
	GUIScene* getScene(GUISceneType type);
	void setFrameUpdateScene(GUISceneType type);

	//帧事件
	void FrameUpdate();

private:
	MyGUI::Gui* mGUI;
	MyGUI::OgrePlatform* mPlatform;

	Ogre::SceneManager* mSceneManager;
	Ogre::RenderWindow* mWindow;

	std::vector<GUIScene*> mSceneList;
	std::map<GUISceneType,GUISceneFactory*> mSceneFactorys;
	//需要帧更新的场景
	GUIScene* mFrameUpdateScene;
};
