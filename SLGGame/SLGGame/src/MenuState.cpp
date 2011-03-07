#include "MenuState.h"

#include "GUISystem.h"
#include "GUIScene.h"

MenuState::MenuState(void)
{
}

MenuState::~MenuState(void)
{
}

void MenuState::initialize( std::string arg )
{
	GUIScene* menuScene=GUISystem::getSingletonPtr()->createScene(MenuScene);

	if(arg=="logo")
	{
		menuScene->showScene("logo");
	}
	else
	{
		menuScene->showScene("");
	}
}

void MenuState::uninitialize()
{
	GUISystem::getSingletonPtr()->destoryScene(MenuScene);
}

void MenuState::update(unsigned int deltaTime)
{
	
}
