#pragma once

class Skill;

class Driver
{
public:
	Driver(Skill* mSkill,unsigned int startTime,unsigned int endTime);
	virtual ~Driver(void);

	bool checkTime(unsigned int currTime);

	virtual void update(unsigned int time)=0;
	virtual void onStart()=0;
	virtual void onEnd()=0;
protected:
	unsigned int mStartTime;
	unsigned int mEndTime;
	bool mIsStart;

	Skill* mSkill;
};
