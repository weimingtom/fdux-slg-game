#pragma once

#include <Ogre.h>
#include <map>
#include <string>

class Driver;

class Skill
{
public:
	Skill(std::string name);
	~Skill(void);

	void addObject(std::string name,Ogre::MovableObject* object,Ogre::SceneNode* node);
	void removeObjcetAndNode(std::string name);
	Ogre::MovableObject* getObject(std::string name);
	Ogre::SceneNode* getNode(std::string name);

	void addDriver(std::string name,std::string datapath);

	std::string getName();
	
	void start();
	void end();
	void update(unsigned int time);

private:
	std::map<std::string,Ogre::MovableObject*> mObjectList;
	std::map<std::string,Ogre::SceneNode*> mNodeList;
	std::map<std::string,Driver*> mDriverList;

	unsigned int mCurrTime;
	std::string mName;
};
