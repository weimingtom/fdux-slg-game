#include "DataLibrary.h"

#include "LuaSystem.h"
#include "conversion.h"

#include <OgreLogManager.h> 

#include <fstream>

DataLibrary::DataLibrary(void)
{
	LuaSystem::getSingletonPtr()->registerCLib("DataLib",DataLib);

	rapidxml::xml_node<>* gameData_decl = mGameData.allocate_node(rapidxml::node_declaration);  
	rapidxml::xml_attribute<>* gameData_decl_ver =  
		mGameData.allocate_attribute("version", "1.0");
	rapidxml::xml_attribute<>* gameDate_decl_encoding =  
		mGameData.allocate_attribute("encoding", "UTF-8");  
	gameData_decl->append_attribute(gameData_decl_ver);  
	gameData_decl->append_attribute(gameDate_decl_encoding);  
	mGameData.append_node(gameData_decl);
	rapidxml::xml_node<>* gameData_element = mGameData.allocate_node(rapidxml::node_element,"GameData");
	mGameData.append_node(gameData_element);

	rapidxml::xml_node<>* staticData_decl = mStaticData.allocate_node(rapidxml::node_declaration);  
	rapidxml::xml_attribute<>* staticData_decl_ver =  
		mStaticData.allocate_attribute("version", "1.0");
	rapidxml::xml_attribute<>* staticData_decl_encoding =  
		mStaticData.allocate_attribute("encoding", "UTF-8");  
	staticData_decl->append_attribute(staticData_decl_ver);  
	staticData_decl->append_attribute(staticData_decl_encoding);  
	mStaticData.append_node(staticData_decl);
	rapidxml::xml_node<>* staticData_element = mStaticData.allocate_node(rapidxml::node_element,"StaticData");
	mStaticData.append_node(staticData_element);

	rapidxml::xml_node<>* systemConfig_decl = mSystemConfig.allocate_node(rapidxml::node_declaration);  
	rapidxml::xml_attribute<>* systemConfig_decl_ver =  
		mSystemConfig.allocate_attribute("version", "1.0");
	rapidxml::xml_attribute<>* systemConfig_decl_encoding =  
		mSystemConfig.allocate_attribute("encoding", "UTF-8");  
	systemConfig_decl->append_attribute(systemConfig_decl_ver);  
	systemConfig_decl->append_attribute(systemConfig_decl_encoding);  
	mSystemConfig.append_node(systemConfig_decl);
	rapidxml::xml_node<>* systemConfig_element = mSystemConfig.allocate_node(rapidxml::node_element,"SystemConfig");
	mSystemConfig.append_node(systemConfig_element);
}

DataLibrary::~DataLibrary(void)
{

}

void DataLibrary::loadXmlData( DataBlock type,std::string fileName,bool append, std::string resGroup)
{
	rapidxml::xml_document<>* currentDoc;
	switch(type)
	{
	case SystemConfig:
		currentDoc=&mSystemConfig;
		break;
	case GameData:
		currentDoc=&mGameData;
		break;
	case StaticData:
		currentDoc=&mStaticData;
		break;
	}

	try
	{
		if (append)
		{
			appendXmlDate(currentDoc,fileName,resGroup);
		}
		else
		{
			currentDoc->clear();
			Ogre::DataStreamPtr stream = Ogre::ResourceGroupManager::getSingleton().openResource(fileName, resGroup.c_str(), true);
			char* s=new char[stream->size()];
			stream->read(s,stream->size());
			currentDoc->parse<0>(s);
			delete []s;
		}
	}
	catch (rapidxml::parse_error& e)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage(e.what(),Ogre::LML_CRITICAL);
	}
}

void DataLibrary::appendXmlDate( rapidxml::xml_document<>* currentDoc,std::string fileName, std::string resGroup )
{
	try
	{
		rapidxml::xml_document<>* doc;
		Ogre::DataStreamPtr stream = Ogre::ResourceGroupManager::getSingleton().openResource(fileName, resGroup.c_str(), true);
		char* s=new char[stream->size()];
		stream->read(s,stream->size());
		doc->parse<0>(s);
		delete []s;

		rapidxml::xml_node<>* srcElement=doc->first_node();
		rapidxml::xml_node<>* destElement=doc->first_node();

		copyElement(srcElement,destElement);
	}
	catch (rapidxml::parse_error& e)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage(e.what(),Ogre::LML_CRITICAL);
	}
}

void DataLibrary::copyElement(rapidxml::xml_node<>* srcElement,rapidxml::xml_node<>* destElement )
{
	for (rapidxml::xml_attribute<> *attr = srcElement->first_attribute();
		attr; attr = attr->next_attribute())
	{
		rapidxml::xml_attribute<> *oldAttr=destElement->first_attribute(attr->name());
		if(oldAttr!=0)
		{
			char* value=destElement->document()->allocate_string(attr->value());
			oldAttr->value(value);
		}
		else
		{
			char* name=destElement->document()->allocate_string(attr->name());
			char* value=destElement->document()->allocate_string(attr->value());
			rapidxml::xml_attribute<> *newAttr=destElement->document()->allocate_attribute(name,value);
			destElement->append_attribute(newAttr);
		}
	}

	for (rapidxml::xml_node<> *child = srcElement->first_node();
		child; child = srcElement->next_sibling())
	{
		rapidxml::xml_node<> * findElement=destElement->first_node(child->name());
		if(findElement!=NULL)//如果有,就继续递归
		{
			copyElement(&(*child),findElement);
		}
		else//如果没找到,说明目标节点下面没有该源节点
		{
			char* name=destElement->document()->allocate_string(child->name());
			rapidxml::xml_node<> *newNode=destElement->document()->allocate_node(rapidxml::node_element,name);
			destElement->append_node(newNode);

			copyElement(&(*child),newNode);
		}
	}

	
}

void DataLibrary::saveXmlData( DataBlock type,std::string fileName )
{
		std::string text;
		switch(type)
		{
		case SystemConfig:
			rapidxml::print(std::back_inserter(text),mSystemConfig,0); 
			break;
		case GameData:
			rapidxml::print(std::back_inserter(text),mGameData,0);
			break;
		case StaticData:
			rapidxml::print(std::back_inserter(text),mStaticData,0);
			break;
		}   
		  
		std::ofstream fout(fileName.c_str());

		fout<<text;

		fout.close();
}

bool DataLibrary::setData( std::string path,const int& value,bool createpath)
{
	rapidxml::xml_node<>* node=getNode(path,createpath);
	if (node!=NULL)
	{
		rapidxml::xml_attribute<> *typeAttr=node->first_attribute("type");
		if(typeAttr!=0)
		{
			typeAttr->value("Int");
		}
		else
		{
			node->append_attribute(node->document()->allocate_attribute("type","Int"));
		}

		rapidxml::xml_attribute<> *valueAttr=node->first_attribute("value");
		std::string sValue=Ogre::StringConverter::toString(value);
		char* value=node->document()->allocate_string(sValue.c_str());
		if(valueAttr!=0)
		{
			valueAttr->value(value);
		}
		else
		{
			node->append_attribute(node->document()->allocate_attribute("value",value));
		}
		

		return true;
	}
	else
	{
		return false;
	}
}

bool DataLibrary::setData( std::string path,const unsigned int& value,bool createpath)
{
	rapidxml::xml_node<>* node=getNode(path,createpath);
	if (node!=NULL)
	{
		rapidxml::xml_attribute<> *typeAttr=node->first_attribute("type");
		if(typeAttr!=0)
		{
			typeAttr->value("UInt");
		}
		else
		{
			node->append_attribute(node->document()->allocate_attribute("type","UInt"));
		}

		rapidxml::xml_attribute<> *valueAttr=node->first_attribute("value");
		std::string sValue=Ogre::StringConverter::toString(value);
		char* value=node->document()->allocate_string(sValue.c_str());
		if(valueAttr!=0)
		{
			valueAttr->value(value);
		}
		else
		{
			node->append_attribute(node->document()->allocate_attribute("value",value));
		}

		return true;
	}
	else
	{
		return false;
	}
}

bool DataLibrary::setData( std::string path,const float& value,bool createpath)
{
	rapidxml::xml_node<>* node=getNode(path,createpath);
	if (node!=NULL)
	{
		rapidxml::xml_attribute<> *typeAttr=node->first_attribute("type");
		if(typeAttr!=0)
		{
			typeAttr->value("Float");
		}
		else
		{
			node->append_attribute(node->document()->allocate_attribute("type","Float"));
		}

		rapidxml::xml_attribute<> *valueAttr=node->first_attribute("value");
		std::string sValue=Ogre::StringConverter::toString(value);
		char* value=node->document()->allocate_string(sValue.c_str());
		if(valueAttr!=0)
		{
			valueAttr->value(value);
		}
		else
		{
			node->append_attribute(node->document()->allocate_attribute("value",value));
		}

		return true;
	}
	else
	{
		return false;
	}
}

bool DataLibrary::setData( std::string path,const double& value,bool createpath )
{
	rapidxml::xml_node<>* node=getNode(path,createpath);
	if (node!=NULL)
	{
		rapidxml::xml_attribute<> *typeAttr=node->first_attribute("type");
		if(typeAttr!=0)
		{
			typeAttr->value("Double");
		}
		else
		{
			node->append_attribute(node->document()->allocate_attribute("type","Double"));
		}

		rapidxml::xml_attribute<> *valueAttr=node->first_attribute("value");
		std::string sValue=Ogre::StringConverter::toString((float)value);
		char* value=node->document()->allocate_string(sValue.c_str());
		if(valueAttr!=0)
		{
			valueAttr->value(value);
		}
		else
		{
			node->append_attribute(node->document()->allocate_attribute("value",value));
		}

		return true;
	}
	else
	{
		return false;
	}
}

bool DataLibrary::setData( std::string path,const std::string& value,bool createpath )
{
	rapidxml::xml_node<>* node=getNode(path,createpath);
	if (node!=NULL)
	{
		rapidxml::xml_attribute<> *typeAttr=node->first_attribute("type");
		if(typeAttr!=0)
		{
			typeAttr->value("String");
		}
		else
		{
			node->append_attribute(node->document()->allocate_attribute("type","String"));
		}

		rapidxml::xml_attribute<> *valueAttr=node->first_attribute("value");
		char* v=node->document()->allocate_string(value.c_str());
		if(valueAttr!=0)
		{
			valueAttr->value(v);
		}
		else
		{
			node->append_attribute(node->document()->allocate_attribute("value",v));
		}

		return true;
	}
	else
	{
		return false;
	}
}

bool DataLibrary::setData( std::string path,const Ogre::Vector3& value,bool createpath )
{
	rapidxml::xml_node<>* node=getNode(path,createpath);
	if (node!=NULL)
	{
		rapidxml::xml_attribute<> *typeAttr=node->first_attribute("type");
		if(typeAttr!=0)
		{
			typeAttr->value("Vector3");
		}
		else
		{
			node->append_attribute(node->document()->allocate_attribute("type","Vector3"));
		}

		rapidxml::xml_attribute<> *valueAttr=node->first_attribute("value");
		std::string sValue=Ogre::StringConverter::toString(value.x)+","+Ogre::StringConverter::toString(value.y)+","+Ogre::StringConverter::toString(value.z);
		char* value=node->document()->allocate_string(sValue.c_str());
		if(valueAttr!=0)
		{
			valueAttr->value(value);
		}
		else
		{
			node->append_attribute(node->document()->allocate_attribute("value",value));
		}

		return true;
	}
	else
	{
		return false;
	}
}

bool DataLibrary::getData( std::string path,int& value,bool testExist )
{
	rapidxml::xml_node<>* node=getNode(path,false);
	if (node!=NULL)
	{
		rapidxml::xml_attribute<> *valueAttr=node->first_attribute("value");
		if(valueAttr!=0)
		{
			char* v=valueAttr->value();
			value=Ogre::StringConverter::parseInt(v);
			return 	true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		if (!testExist)
		{
			Ogre::LogManager::getSingletonPtr()->logMessage(path+" is not exist",Ogre::LML_CRITICAL);
		}
		return false;
	}
}

bool DataLibrary::getData( std::string path,unsigned int& value,bool testExist )
{
	rapidxml::xml_node<>* node=getNode(path,false);
	if (node!=NULL)
	{
		rapidxml::xml_attribute<> *valueAttr=node->first_attribute("value");
		if(valueAttr!=0)
		{
			char* v=valueAttr->value();
			value=Ogre::StringConverter::parseUnsignedInt(v);
			return 	true;
		}
		else
		{
			return false;
		}	
	}
	else
	{
		if (!testExist)
		{
			Ogre::LogManager::getSingletonPtr()->logMessage(path+" is not exist",Ogre::LML_CRITICAL);
		}
		return false;
	}
}

bool DataLibrary::getData( std::string path,float& value,bool testExist )
{
	rapidxml::xml_node<>* node=getNode(path,false);
	if (node!=NULL)
	{
		rapidxml::xml_attribute<> *valueAttr=node->first_attribute("value");
		if(valueAttr!=0)
		{
			char* v=valueAttr->value();
			value=Ogre::StringConverter::parseReal(v);
			return 	true;
		}
		else
		{
			return false;
		}	
	}
	else
	{
		if (!testExist)
		{
			Ogre::LogManager::getSingletonPtr()->logMessage(path+" is not exist",Ogre::LML_CRITICAL);
		}
		return false;
	}
}

bool DataLibrary::getData( std::string path,double& value,bool testExist )
{
	rapidxml::xml_node<>* node=getNode(path,false);
	if (node!=NULL)
	{
		rapidxml::xml_attribute<> *valueAttr=node->first_attribute("value");
		if(valueAttr!=0)
		{
			char* v=valueAttr->value();
			value=Ogre::StringConverter::parseReal(v);
			return 	true;
		}
		else
		{
			return false;
		}	
	}
	else
	{
		if (!testExist)
		{
			Ogre::LogManager::getSingletonPtr()->logMessage(path+" is not exist",Ogre::LML_CRITICAL);
		}
		return false;
	}
}

bool DataLibrary::getData( std::string path,std::string& value,bool testExist )
{
	rapidxml::xml_node<>* node=getNode(path,false);
	if (node!=NULL)
	{
		rapidxml::xml_attribute<> *valueAttr=node->first_attribute("value");
		if(valueAttr!=0)
		{
			char* v=valueAttr->value();
			value=v;
			return 	true;
		}
		else
		{
			return false;
		}	
	}
	else
	{
		if (!testExist)
		{
			Ogre::LogManager::getSingletonPtr()->logMessage(path+" is not exist",Ogre::LML_CRITICAL);
		}
		return false;
	}
}

bool DataLibrary::getData( std::string path,Ogre::Vector3& value,bool testExist )
{
	rapidxml::xml_node<>* node=getNode(path,false);
	if (node!=NULL)
	{
		rapidxml::xml_attribute<> *valueAttr=node->first_attribute("value");
		if(valueAttr!=0)
		{
			char* v=valueAttr->value();
			std::queue<std::string> vl;
			split(v,',',vl);
			if (vl.size()!=3)
			{
				Ogre::LogManager::getSingletonPtr()->logMessage(path+" has a bad format",Ogre::LML_CRITICAL);
				return false;
			}
			else
			{
				value.x=Ogre::StringConverter::parseReal(vl.front());
				vl.pop();
				value.y=Ogre::StringConverter::parseReal(vl.front());
				vl.pop();
				value.z=Ogre::StringConverter::parseReal(vl.front());
				return true;
			}
		}
		else
		{
			return false;
		}	
	}
	else
	{
		if (!testExist)
		{
			Ogre::LogManager::getSingletonPtr()->logMessage(path+" is not exist",Ogre::LML_CRITICAL);
		}
		return false;
	}
}

bool DataLibrary::delNode(std::string path)
{
	rapidxml::xml_node<>* node=getNode(path,false);
	if(node == NULL)
	{
		return false;
	}

	rapidxml::xml_node<>* parent = node->parent();
	if(parent == NULL)
	{
		return false;
	}

	parent->remove_node(node);
	delete parent;

	return true;
}

void DataLibrary::createPath(std::string path)
{
	getNode(path,true);
}

bool DataLibrary::copyNode(std::string srcpath, std::string distpath, bool createpath)
{
	rapidxml::xml_node<>* srcnode=getNode(srcpath,false);
	if(!srcnode)
	{
		return false;
	}

	rapidxml::xml_node<>* distnode=getNode(distpath,createpath);
	if(!distnode)
	{
		return false;
	}

	copyElement(srcnode,distnode );

	return true;
}

std::vector<std::string> DataLibrary::getChildList(std::string path)
{
	std::vector<std::string> chlidlist;
	rapidxml::xml_node<>* node=getNode(path,false);
	if(node)
	{
		for (rapidxml::xml_attribute<> *attr = node->first_attribute();
			attr; attr = attr->next_attribute())
		{
			chlidlist.push_back(attr->name());
		}
	}

	return chlidlist;
}

rapidxml::xml_node<>* DataLibrary::findNode(rapidxml::xml_node<>* parent,std::queue<std::string>* path,bool createpath)
{
	std::string nodeName=path->front();
	path->pop();
	
	if (parent->first_node())
	{
		rapidxml::xml_node<>* child=parent->first_node(nodeName.c_str());
		if (child!=NULL)
		{
			if (!path->empty())
			{
				rapidxml::xml_node<>* rtn=findNode(child,path,createpath);
				return rtn;
			}
			else
			{
				return child;
			}
		}
	}
	
	if(createpath)
	{
		rapidxml::xml_node<>* newNode=parent->document()->allocate_node(rapidxml::node_element,parent->document()->allocate_string(nodeName.c_str()));
		parent->append_node(newNode);

		if (!path->empty())
		{
			return findNode(newNode,path,createpath);
		}
		else
		{
			return newNode;
		}
	}
	else
	{
		return NULL;
	}

}

void DataLibrary::split(const std::string& s, char c,std::queue<std::string>& v) 
{
	std::string::size_type i = 0;
	std::string::size_type j = s.find(c);

	while (j != std::string::npos) 
	{
		v.push(s.substr(i, j-i));
		i = ++j;
		j = s.find(c, j);

		if (j == std::string::npos)
			v.push(s.substr(i, s.length( )));
	}
}

rapidxml::xml_node<>* DataLibrary::getNode( std::string path,bool createpath)
{
	mCreateState=CreateState_None;
	std::queue<std::string> pathQueue;
	split(path,'/',pathQueue);
	if (pathQueue.size()>=2)
	{
		rapidxml::xml_node<>* parent=NULL;
		if (pathQueue.front()=="GameData")
		{
			parent=mGameData.first_node();
		}
		else if(pathQueue.front()=="StaticData")
		{
			parent=mStaticData.first_node();
		}
		else
		{
			parent=mSystemConfig.first_node();
		}

		pathQueue.pop();
		rapidxml::xml_node<>* e=findNode(parent,&pathQueue,createpath);
		return e;
	}
	else
	{
		return NULL;
	}
}

DataLibrary::DataType DataLibrary::getDataType( std::string path )
{
	rapidxml::xml_node<>* node=getNode(path,false);
	if (node!=NULL)
	{
		std::string value=0;
		rapidxml::xml_attribute<>* attri=node->first_attribute("type");
		DataType type=NoneType;
		if(attri!=0)
		{
			if (value=="Int")
			{
				type=IntType;
			}
			else if (value=="UInt")
			{
				type=UIntType;
			} 
			else if (value=="Float")
			{
				type=FloatType;
			} 
			else if (value=="Double")
			{
				type=DubleType;
			} 
			else if (value=="String")
			{
				type=StringType;
			}
		}

		return 	type;		
	}
	else
	{
		Ogre::LogManager::getSingletonPtr()->logMessage(path+" is not exist",Ogre::LML_CRITICAL);
		return NoneType;
	}
}
