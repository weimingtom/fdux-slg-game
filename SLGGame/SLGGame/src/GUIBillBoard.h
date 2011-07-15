#pragma once

#include "GUIScene.h"

#include <Ogre.h>

class GUIBillBoard:public GUIScene
{
public:
	GUIBillBoard(std::string layoutFile,int Width,int Height):GUIScene(layoutFile,Width,Height){};
	virtual ~GUIBillBoard(void){};

	virtual Ogre::Vector3 getPosition()=0;

	virtual void update(Ogre::Vector2 screen)=0;

	virtual void setMarginalValue(float marginalTop,float marginalBottom,float marginalLeft,float marginalRight)=0;


	//GUIScene中非必要函数
	void FrameEvent(){}

	GUISceneType getType(){return NoneScene;}
};
