#pragma once
#include <vector>

class ScriptContext
{
public:
	ScriptContext();
	~ScriptContext();

	bool GetInt(unsigned int index, int &outint);
	void SetInt(unsigned int index, int inint);

	bool GetFloat(unsigned int index, float &outfloat);
	void SetFloat(unsigned int index, float infloat);

private:
	std::vector<int> mIntVector;
	std::vector<float> mFloatVector;
};