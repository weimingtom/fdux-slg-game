#pragma once

#include "Core.h"

class Terrain;

class CameraContral
{
public:
	CameraContral(Terrain *terrain);
	~CameraContral();

	void moveCamera(float dx,float dy);
	void riseCamera(float dh);
	void resetCamera();
private:

	void setCamera();

	Ogre::Camera *mCamera;
	Terrain *mTerrain;

	float mHeight;
	float mX;
	float mY;

	Ogre::SceneNode *mTrancNode;
};