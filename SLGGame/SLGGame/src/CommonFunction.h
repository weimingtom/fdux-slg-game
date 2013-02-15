#pragma once
#include "squaddefine.h"

int GetSide(Direction d1, Direction d2);

float GetFormationBonus(int side, int formtype);

Direction GetDirection(int sx, int sy, int x, int y);

int GetDistance(int x1, int y1, int x2, int y2);

float AtkDefToPerc(int atk, int def);