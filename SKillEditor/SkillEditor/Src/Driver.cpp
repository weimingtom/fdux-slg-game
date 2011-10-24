#include "Driver.h"

#include "Skill.h"

Driver::Driver(Skill* skill,unsigned int startTime,unsigned int endTime):
mStartTime(startTime),
mEndTime(endTime),
mIsStart(false),
mSkill(skill)
{
}

Driver::~Driver(void)
{
}

bool Driver::checkTime( unsigned int currTime )
{
	if (currTime>=mStartTime && (!mIsStart))
	{
		mIsStart=true;
		onStart();
		return true;
	}
	else if(currTime>=mEndTime && mIsStart)
	{
		mIsStart=false;
		onEnd();
		return false;
	}

	return false;
}
