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
private:

	void setCamera();

	Ogre::Camera *mCamera;
	Terrain *mTerrain;

	static float mHeight;
	static float mX;
	static float mY;

	float mMinX;
	float mMinY;

	Ogre::SceneNode *mTrancNode;
};