#pragma once
#include "iisingleton.hpp"

#include <vector>

class Area;

class AreaManager: public izayoi::IISingleton<AreaManager>
{
public:
	AreaManager();
	~AreaManager();

	std::vector<Area *> mAreaList;
private:	
};