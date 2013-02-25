#pragma once
#include "cutscene.h"

#include "ogre.h"
#include <string>

class CameraCutScene :
	public CutScene
{
public:
	CameraCutScene(int gridx,int gridy,bool moveto);
	virtual ~CameraCutScene(void);

	void startCutScence();
	bool endCutScene();
	void skipCutScene();
	void updateCutScene(unsigned int deltaTime);

	void clear();

	int mGridX;
	int mGridY;

	bool mMoveTo;
	bool mIsOver;
	
	Ogre::Animation* mNodeAnimation;
	Ogre::AnimationState* mNodeAnimationState;
	Ogre::SceneNode* mNode;

};