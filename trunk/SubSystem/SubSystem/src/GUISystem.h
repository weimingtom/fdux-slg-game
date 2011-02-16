#pragma once

#include "GUICommon.h"
#include "GUIScene.h"
#include "iisingleton.hpp"

#include <OIS.h>
#include <ogre.h>
#include <MyGUI.h>
#include <MyGUI_OgrePlatform.h>

#include <vector>

using namespace izayoi;

class GUISystem:public OIS::KeyListener,public OIS::MouseListener,public IISingleton<GUISystem>
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
	void createScene(GUISceneType type);
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
	//需要帧更新的场景
	GUIScene* mFrameUpdateScene;
};
