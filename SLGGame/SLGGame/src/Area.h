#pragma once

#include <vector>
#include <string>

#include "squaddefine.h"

class Crood
{
public:
	Crood();
	Crood(int x, int y);
	Crood(std::string path);

	void writeCrood(std::string path);

	bool operator==(const Crood& ocrood) const;

	int mX;
	int mY;
};

class Area
{
public:
	Area(std::string path);
	Area(std::vector<Crood> croodVec);
	Area();

	enum LineType
	{
		LINETYPE_SEGMENT, //线段
		LINETYPE_RAY, //射线
		LINETYPE_LINE	//直线
	};

	void setCroodVec(std::vector<Crood> croodVec);
	void calcConvexHull(std::vector<Crood> croodVec);//求填！！！！
	void calcLine(Crood start, Crood end, LineType linetype, Crood min, Crood max);
	std::vector<Crood> getCroodVec();

	void readArea(std::string path);
	void writeArea(std::string path);

	bool crossed(Area& area);
	bool inArea(Crood& crood);

	Crood getCenter() {return mCenter;}
	int getMinX() {return mMin.mX;}
	int getMinY() {return mMin.mY;}
	int getMaxX() {return mMax.mX;}
	int getMaxY() {return mMax.mY;}
	int getRadius() {return mRadius;}
private:
	std::vector<Crood> mCroodVec;
	std::string mPath;

	void calcAreaInfo();

	Crood mCenter;
	Crood mMin;
	Crood mMax;
	int mRadius;
};