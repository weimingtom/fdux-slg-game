#pragma once
#include "GameState.h"
#include <queue>

class AVGState :
	public GameState
{
public:
	AVGState(void);
	~AVGState(void);

	void initialize(std::string arg);
	void uninitialize();
	void update(unsigned int deltaTime);
private:
	void split(const std::string& s, char c,std::queue<std::string>& v);
};
