#include "Area.h"

#include <boost/format.hpp>

#include "DataLibrary.h"

Crood::Crood()
:mX(0),mY(0)
{
}

Crood::Crood(int x, int y)
:mX(x),mY(y)
{

}

Crood::Crood(std::string path)
:mX(0),mY(0)
{
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	datalib->getData(str(boost::format("%1%/X")%path), mX);
	datalib->getData(str(boost::format("%1%/Y")%path), mY);
}


void Crood::writeCrood(std::string path)
{
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	datalib->setData(str(boost::format("%1%/X")%path), mX);
	datalib->setData(str(boost::format("%1%/Y")%path), mY);
}

bool Crood::operator==(const Crood& ocrood) const
{
	if(mX == ocrood.mX && mY == ocrood.mY)
		return true;
	return false;
}

Area::Area(std::string path)
:mPath(path)
{
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	std::vector<std::string> croodlist = datalib->getChildList(path);
	std::vector<std::string>::iterator croodite = croodlist.begin();
	for(;croodite != croodlist.end(); croodite++)
	{
		Crood crood(str(boost::format("%1%/%2%")%path%(*croodite)));
		mCroodVec.push_back(crood);
	}
	calcAreaInfo();
}

Area::Area(std::vector<Crood> croodVec)
:mCroodVec(croodVec)
{
	calcAreaInfo();
}

Area::Area()
{
	mCenter.mX = 0;
	mCenter.mY = 0;
	mMin.mX = 0;
	mMin.mY = 0;
	mMax.mX = 0;
	mMax.mY = 0;
}

void Area::setCroodVec(std::vector<Crood> croodVec)
{
	mCroodVec = croodVec;
	calcAreaInfo();
	if(mPath.size() > 0)
	{
		writeArea(mPath);
	}
}

void Area::calcConvexHull(std::vector<Crood> croodVec)
{
	mCroodVec = croodVec;
	calcAreaInfo();
	if(mPath.size() > 0)
	{
		writeArea(mPath);
	}
}

void Area::calcLine(Crood start, Crood end, LineType linetype, Crood min, Crood max)
{
	mCroodVec.clear();
	mCroodVec.push_back(start);
	calcAreaInfo();
	if(mPath.size() > 0)
	{
		writeArea(mPath);
	}
}

std::vector<Crood> Area::getCroodVec()
{
	return mCroodVec;
}

void Area::readArea(std::string path)
{
	mCroodVec.clear();
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	std::vector<std::string> croodlist = datalib->getChildList(path);
	std::vector<std::string>::iterator croodite = croodlist.begin();
	for(;croodite != croodlist.end(); croodite++)
	{
		Crood crood(str(boost::format("%1%/%2%")%path%(*croodite)));
		mCroodVec.push_back(crood);
	}
	calcAreaInfo();
	if(mPath.size() > 0)
	{
		writeArea(mPath);
	}
}

void Area::writeArea(std::string path)
{
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	datalib->delNode(path);
	for(unsigned int n = 0; n < mCroodVec.size(); n++)
	{
		mCroodVec[n].writeCrood(str(boost::format("%1%/c%2%")%path%n));
	}
}

bool Area::crossed(Area& area)
{
	std::vector<Crood>::iterator croodite1 = mCroodVec.begin();
	for(; croodite1 != mCroodVec.end(); croodite1++)
	{
		std::vector<Crood>::iterator croodite2 = area.mCroodVec.begin();
		for(; croodite2 != area.mCroodVec.end(); croodite2++)
		{
			if((abs((*croodite1).mX - (*croodite2).mX) <= 1 && abs((*croodite1).mY - (*croodite2).mY) == 0) ||
				(abs((*croodite1).mY - (*croodite2).mY) <= 1 && abs((*croodite1).mX - (*croodite2).mX) == 0) )
			{
				return true;
			}
		}
	}
	return false;
}

bool Area::inArea(Crood& crood)
{
	std::vector<Crood>::iterator croodite1 = mCroodVec.begin();
	for(; croodite1 != mCroodVec.end(); croodite1++)
	{
		if(crood == (*croodite1))
			return true;
	}
	return false;
}

void Area::calcAreaInfo()
{
	std::vector<Crood>::iterator croodite = mCroodVec.begin();
	if(croodite != mCroodVec.end())
	{
		mCenter = (*croodite);
		mMin = mCenter;
		mMax = mCenter;
		croodite++;
		for(; croodite != mCroodVec.end(); croodite++)
		{
			mCenter.mX += (*croodite).mX;
			mCenter.mY += (*croodite).mY;
			if((*croodite).mX > mMax.mX)
				mMax.mX = (*croodite).mX;
			if((*croodite).mY > mMax.mY)
				mMax.mY = (*croodite).mY;
			if((*croodite).mX < mMin.mX)
				mMin.mX = (*croodite).mX;
			if((*croodite).mY < mMin.mY)
				mMin.mY = (*croodite).mY;
		}
		mCenter.mX /= mCroodVec.size();
		mCenter.mY /= mCroodVec.size();
		mRadius = sqrt(pow(float(mCenter.mX - mMin.mX), 2) + pow(float(mCenter.mY - mMin.mY), 2)) + 0.5f;
		int tempradius = sqrt(pow(float(mCenter.mX - mMin.mX), 2) + pow(float(mCenter.mY - mMax.mY), 2)) + 0.5f;
		mRadius = (tempradius > mRadius)?tempradius:mRadius;
		tempradius = sqrt(pow(float(mCenter.mX - mMax.mX), 2) + pow(float(mCenter.mY - mMin.mY), 2)) + 0.5f;
		mRadius = (tempradius > mRadius)?tempradius:mRadius;
		tempradius = sqrt(pow(float(mCenter.mX - mMax.mX), 2) + pow(float(mCenter.mY - mMax.mY), 2)) + 0.5f;
		mRadius = (tempradius > mRadius)?tempradius:mRadius;
	}
	else
	{
		mCenter.mX = 0;
		mCenter.mY = 0;
		mMin.mX = 0;
		mMin.mY = 0;
		mMax.mX = 0;
		mMax.mY = 0;
		mRadius = 0;
	}
}