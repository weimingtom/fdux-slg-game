#pragma once

class CutScene
{
public:
	CutScene(unsigned int lasttime = 0);
	virtual ~CutScene();
	
	void start();
	void skip();  //跳过当前片断
	void skipall(); //跳过所有片断
	bool end(); //片断是否结束
	bool endthis();
	void update(unsigned int deltaTime);

	void setNextScene(CutScene* next);
	CutScene* getNextScene() { return mNextScene;}
protected:
	CutScene *mNextScene;
	unsigned int mLastTime;
	unsigned int mPassedTime;

	bool mStarted;
	bool mEnded;

	virtual void startCutScence() = 0;
	virtual bool endCutScene() = 0;
	virtual void skipCutScene() = 0;
	virtual void updateCutScene(unsigned int deltaTime) = 0;
};