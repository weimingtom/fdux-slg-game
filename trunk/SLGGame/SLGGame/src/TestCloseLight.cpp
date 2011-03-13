#include "testcloselight.h"

#include "Core.h"

TestCloseLight::TestCloseLight()
:CutScence(5000)
{
	Core::getSingleton().mSceneMgr->setAmbientLight(Ogre::ColourValue(1.0f, 1.0f, 1.0f));

}
TestCloseLight::~TestCloseLight()
{

}

bool TestCloseLight::endCutScence()
{
	Ogre::ColourValue color = Core::getSingleton().mSceneMgr->getAmbientLight();
	if(color.r <= 0.0f)
		return true;
	return false;
}
void TestCloseLight::skipCutScence()
{
	Core::getSingleton().mSceneMgr->setAmbientLight(Ogre::ColourValue(0.0f, 0.0f, 0.0f));
}
void TestCloseLight::updateCutScence(unsigned int deltaTime)
{
	Ogre::ColourValue color = Core::getSingleton().mSceneMgr->getAmbientLight();
	if(color.r > 0.0f)
	{
		Core::getSingleton().mSceneMgr->setAmbientLight(Ogre::ColourValue(color.r -0.01f, color.g -0.01f, color.b -0.01f));
	}	
}