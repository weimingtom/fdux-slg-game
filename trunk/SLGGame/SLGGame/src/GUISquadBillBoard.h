#pragma once
#include "guibillboard.h"

class GUISquadBillBoard :
	public GUIBillBoard
{
public:
	GUISquadBillBoard(Ogre::SceneNode* node);
	~GUISquadBillBoard(void);

	Ogre::Vector3 getPosition();

	void update(Ogre::Vector2 screen);

	void setMarginalValue(float marginalTop,float marginalBottom,float marginalLeft,float marginalRight);

	void showScene(std::string arg);//ÏÔÊ¾³¡¾°

	void hideScene();//Òþ²Ø³¡¾°

	void setName(std::string name);

	void setVisible(bool v);

private:
	Ogre::SceneNode* mNode;

	MyGUI::TextBox* mBName;
	MyGUI::ImageBox* mBImage;
	MyGUI::ImageBox* mBIcon;
	
	bool mIsVisible;
};
