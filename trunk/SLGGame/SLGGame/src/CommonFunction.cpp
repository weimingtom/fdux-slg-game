#include "CommonFunction.h"

#include <math.h>

int GetSide(Direction d1, Direction d2)
{
	if(d2 != d1)
	{
		switch(d2)
		{
		case North:
			if(d1 != South)
				return 1;
			else
				return 2;
			break;
		case South:
			if(d1 != North)
				return 1;
			else
				return 2;
			break;
		case West:
			if(d1 != East)
				return 1;
			else
				return 2;
			break;
		case East:
			if(d1 != West)
				return 1;
			else
				return 2;
			break;
		}
	}
	return 0;
}

Direction GetDirection(int sx, int sy, int x, int y)
{
	Direction d = North;
	if(!(sx == x && sy == y))
	{
		float k;
		if(y-sy == 0)
			k = 2.0f;
		else
			k = abs(x -sx)/ abs(y - sy);
		if( y > sy && k <= 1.0f)
			d = South;
		else if( y < sy && k <= 1.0f)
			d = North;
		else if( x > sx )
			d = East;
		else
			d = West;
	}
	return d;
}

int GetDistance(int x1, int y1, int x2, int y2)
{
	return abs(x1 - x2) + abs(y1 - y2);
}

int DeathToMorale(int dead)
{
	if(dead >=  30)
		return 60;
	return floor(0.025f * dead * dead + 1.25f * dead + 0.5f);
}

float AtkDefToPerc(int atk, int def)
{
	float perc = 0.2f + 0.025f * (atk - def);
	perc = (perc > 1.0f)? 1.0f:perc;
	perc = (perc < 0.0f)? 0.0f:perc;
	return perc;
}