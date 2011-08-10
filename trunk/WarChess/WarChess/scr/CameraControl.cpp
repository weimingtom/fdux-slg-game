#include "CameraControl.h"

#include "IIRoot.h"

CameraControl::CameraControl()
{

}

CameraControl::~CameraControl()
{

}

void CameraControl::PM_POINTS_action()
{
	IIRoot::getSingletonPtr()->mCamera->setPolygonMode(Ogre::PM_POINTS);
}

void CameraControl::PM_WIREFRAME_action()
{
	IIRoot::getSingletonPtr()->mCamera->setPolygonMode(Ogre::PM_WIREFRAME);
}

void CameraControl::PM_SOLID_action()
{
	IIRoot::getSingletonPtr()->mCamera->setPolygonMode(Ogre::PM_SOLID);
}
