#pragma once

#include <OIS.h>
#include <vector>

class CameraContral;
class GUISystem;
class InputListener;

class InputControl:public OIS::KeyListener,public OIS::MouseListener
{
public:
	InputControl(void);
	~InputControl(void);

	//void setCameraContral(CameraContral* camera);
	void setGUISystem(GUISystem* system);

	/* KeyListener Callbacks */
	bool keyPressed(const OIS::KeyEvent &arg);
	bool keyReleased(const OIS::KeyEvent &arg);

	/* MouseListener Callbacks */
	bool mouseMoved(const OIS::MouseEvent &arg);
	bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
	bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);

	void pushListener(InputListener* listener);
	void popListener();

private:
	//CameraContral* mCameraContral;
	GUISystem* mGUISystem;
	std::vector<InputListener*> mLisenerStack;
};
