#pragma once
#include "guibillboard.h"

class Framerate;

class GUISquadValueBillBoard :
	public GUIBillBoard
{
public:
	GUISquadValueBillBoard(Ogre::SceneNode* node);
	~GUISquadValueBillBoard(void);

	Ogre::Vector3 getPosition();

	void update(Ogre::Vector2 screen,unsigned int deltaTime);

	void setMarginalValue(float marginalTop,float marginalBottom,float marginalLeft,float marginalRight);

	void setValue(std::string value,MyGUI::Colour c);

	void stopShow();

	void showScene(std::string arg);//ÏÔÊ¾³¡¾°

	void hideScene();//Òþ²Ø³¡¾°
private:
	Ogre::SceneNode* mNode;
	MyGUI::TextBox* mBText;
	float mMoveY;
	bool mStart;
	unsigned int mDeltaTime;
	Framerate* mFramerate;
};
