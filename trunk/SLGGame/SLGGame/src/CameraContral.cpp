#include "CameraContral.h"

#include "Terrain.h"

CameraContral::CameraContral()
{
	mTerrain = Terrain::getSingletonPtr();
	mCamera = Core::getSingleton().mCamera;
	mMinX -= 0.0f;
	mMinY -= 0.0f;
}

CameraContral::~CameraContral()
{

}

void CameraContral::setMoveRect(float minx, float miny)
{
	mMinX = minx;
	mMinY = miny;
}

void CameraContral::moveCamera(float dx,float dy)
{
	mX +=  dx * 0.5f + dy * 0.5f;
	mY +=  -dx * 0.5f + dy * 0.5f;
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
	mHeight = 50.0f;
	setCamera();
}

void CameraContral::setCamera()
{
	float height =mTerrain->getHeight(mX,mY);
	float d = mHeight;//������ʽ
	mCamera->setPosition(mX + d, height +mHeight, mY +d);
	mCamera->lookAt(mX,height, mY );
}

