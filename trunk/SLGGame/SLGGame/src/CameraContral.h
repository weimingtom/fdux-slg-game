#pragma once

#include "Core.h"

#include "iisingleton.hpp"

using namespace izayoi;

class Terrain;

class CameraContral:public IISingleton<CameraContral>
{
public:
	CameraContral();
	~CameraContral();

	void moveCamera(float dx,float dy);
	void moveCameraTo(float x,float y);
	void riseCamera(float dh);
	void riseCameraTo(float h);
	void resetCamera();

	void setMoveRect(float minx, float miny);

	Ogre::Camera* getShadowMapCamera() {return mShadowMapCamera;}
private:

	void setCamera();

	Ogre::Camera *mCamera;
	Ogre::Camera *mShadowMapCamera;
	Terrain *mTerrain;

	float mHeight;
	float mX;
	float mY;

	float mMinX;
	float mMinY;
};