#pragma once
#include "gamestate.h"

class MenuState :
	public GameState
{
public:
	MenuState(void);
	~MenuState(void);

	void initialize(std::string arg);

	void uninitialize();

	void update(unsigned int deltaTime);

private:

};
