#pragma once

#include "GameState.h"

class SupplyState
	:public GameState
{
public:
	SupplyState();
	~SupplyState();

	void initialize(std::string arg);

	void uninitialize();

	void update(unsigned int deltaTime);

	
};