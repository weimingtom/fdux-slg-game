#pragma once

#include "Core.h"

class Terrain;

class CameraContral
{
public:
	CameraContral();
	~CameraContral();

	void moveCamera(float dx,float dy);
	void moveCameraTo(float x,float y);
	void riseCamera(float dh);
	void riseCameraTo(float h);
	void resetCamera();
	Ogre::Camera*  getCamera() {return mCamera;}
	void cameraQuery(int dx,int dy);
private:

	void setCamera();

	Ogre::Camera *mCamera;
	Terrain *mTerrain;

	float mHeight;
	float mX;
	float mY;

	Ogre::SceneNode *mTrancNode;
};