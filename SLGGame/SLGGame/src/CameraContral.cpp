#include "CameraContral.h"

#include "Terrain.h"

#include <iostream>

CameraContral::CameraContral()
{
	mTerrain = Terrain::getSingletonPtr();
	mCamera = Core::getSingleton().mCamera;
	mTerrain->getWorldCoords(0,0,mMinX,mMinY);
	mMinX -= TILESIZE / 2.0f;
	mMinY -= TILESIZE / 2.0f;
}

CameraContral::~CameraContral()
{

}

void CameraContral::moveCamera(float dx,float dy)
{
	mX +=  dx * 0.5 + dy * 0.5;
	mY +=  -dx * 0.5 + dy * 0.5;
	mX = (mX > -mMinX)? -mMinX: mX;
	mX = (mX < mMinX)? mMinX: mX;
	mY = (mY > -mMinY)? -mMinY: mY;
	mY = (mY < mMinY)? mMinY: mY;
	setCamera();
}

void ::CameraContral::riseCamera(float dh)
{
	mHeight += dh;
	mHeight = (mHeight > 100.0f)? 100.0f: mHeight;
	mHeight = (mHeight < 10.0f)? 10.0f: mHeight;
	setCamera();
}


void CameraContral::moveCameraTo(float x,float y)
{
	mX = x;
	mY = y;
	mX = (mX > -mMinX)? -mMinX: mX;
	mX = (mX < mMinX)? mMinX: mX;
	mY = (mY > -mMinY)? -mMinY: mY;
	mY = (mY < mMinY)? mMinY: mY;
	setCamera();
}

void ::CameraContral::riseCameraTo(float h)
{
	mHeight = h;
	mHeight = (mHeight > 100.0f)? 100.0f: mHeight;
	mHeight = (mHeight < 10.0f)? 10.0f: mHeight;
	setCamera();
}

void CameraContral::resetCamera()
{
	mX = 0.0f;
	mY = 0.0f;
	mHeight = 20.0f;
	setCamera();
}

void CameraContral::setCamera()
{
	float height = mTerrain->getHeight(mX,mY);
	float d = mHeight;//´ý¶¨¹«Ê½
	mCamera->setPosition(mX + d, height +mHeight, mY +d);
	mCamera->lookAt(mX,height, mY );
}

