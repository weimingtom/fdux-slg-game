#include "InputControl.h"

#include "GUISystem.h"
#include "GUIDebugWindow.h"
#include "CameraContral.h"
#include "InputListener.h"
#include "Terrain.h"
#include "Core.h"

#include <iostream>
//#include <Shiny.h>

InputControl::InputControl(void)
{

}

InputControl::~InputControl(void)
{
}

bool InputControl::keyPressed( const OIS::KeyEvent &arg )
{

	if (arg.key==OIS::KC_F12)
	{
		if (Core::getSingletonPtr()->mDebugOverlay->isVisible())
		{
			Core::getSingletonPtr()->mDebugOverlay->hide();
		//	GUIDebugWindow* debug=(GUIDebugWindow*)GUISystem::getSingletonPtr()->getScene(DebugWindowsScene);
		//	debug->hideScene();
		//	GUISystem::getSingletonPtr()->destoryScene(DebugWindowsScene);
		}
		else
		{
			Core::getSingletonPtr()->mDebugOverlay->show();
		//	GUIDebugWindow* debug=(GUIDebugWindow*)GUISystem::getSingletonPtr()->createScene(DebugWindowsScene);
		//	debug->showScene("");
		}

		//PROFILER_OUTPUT();
	}

	if (!mGUISystem->keyPressed(arg))
	{
		if(mLisenerStack.size() > 0)
		{
			mLisenerStack.back()->keyPressed(arg);
		}
	}
	return true;
}

bool InputControl::keyReleased( const OIS::KeyEvent &arg )
{
	return mGUISystem->keyReleased(arg);
}

bool InputControl::mouseMoved( const OIS::MouseEvent &arg )
{
	mGUISystem->mouseMoved(arg);
	if(mLisenerStack.size() > 0)
	{
		mLisenerStack.back()->mouseMoved(arg);
	}
	return true;
}

bool InputControl::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
	if (!mGUISystem->mousePressed(arg,id))
	{
		if(mLisenerStack.size() > 0)
		{
			mLisenerStack.back()->mousePressed(arg,id);
		}
	}
	return true;
}

bool InputControl::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
	if (!mGUISystem->mouseReleased(arg,id))
	{
		if(mLisenerStack.size() > 0)
		{
			mLisenerStack.back()->mouseReleased(arg,id);
		}
	}
	return true;
}

void InputControl::setGUISystem( GUISystem* system )
{
	mGUISystem=system;
}

void InputControl::pushListener(InputListener* listener)
{
	mLisenerStack.push_back(listener);
}
void InputControl::popListener()
{
	mLisenerStack.pop_back();
}