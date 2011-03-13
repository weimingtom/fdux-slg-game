#pragma once

class CutScence
{
public:
	CutScence(unsigned int lasttime = 0);
	~CutScence();
	
	void play() {mPaused = false;}
	void pause() {mPaused = true;} 
	void skip();  //跳过当前片断
	void skipall(); //跳过所有片断
	bool end(); //片断是否结束
	void update(unsigned int deltaTime);

	void setNextScence(CutScence* next);
	CutScence* getNextScence() { return mNextScence;}
protected:
	CutScence *mNextScence;
	unsigned int mLastTime;
	unsigned int mPassedTime;

	bool mPaused;

	virtual bool endCutScence() = 0;
	virtual void skipCutScence() = 0;
	virtual void updateCutScence(unsigned int deltaTime) = 0;
};