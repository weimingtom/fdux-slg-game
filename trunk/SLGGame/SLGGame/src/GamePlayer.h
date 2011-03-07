#pragma once

class GamePlayer
{
public:
	enum PlayerType
	{
		Human,
		AI
	};

	GamePlayer();
	virtual ~GamePlayer();

	virtual PlayerType getPlayerType()=0;
	
	virtual void TurnStart()=0;
	virtual void TurnEnd()=0;

};
