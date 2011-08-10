#include "ScriptContext.h"

ScriptContext::ScriptContext()
{

}

ScriptContext::~ScriptContext()
{

}

bool ScriptContext::GetInt(unsigned int index, int &outint)
{
	if(index > mIntVector.size())
		return false;
	outint = mIntVector[index];
	return true;
}

void ScriptContext::SetInt(unsigned int index, int inint)
{
	if(index > mIntVector.size())
		mIntVector.resize(index, 0);
	mIntVector[index] = inint;
}

bool ScriptContext::GetFloat(unsigned int index, float &outfloat)
{
	if(index > mFloatVector.size())
		return false;
	outfloat = mFloatVector[index];
	return true;
}
void ScriptContext::SetFloat(unsigned int index, float infloat)
{
	if(index > mFloatVector.size())
		mFloatVector.resize(index, 0.0f);
	mIntVector[index] = infloat;
}