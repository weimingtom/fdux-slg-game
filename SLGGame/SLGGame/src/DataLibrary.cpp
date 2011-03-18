#include "DataLibrary.h"

#include "LuaSystem.h"

#include <OgreLogManager.h> 

DataLibrary::DataLibrary(void)
{
	LuaSystem::getSingletonPtr()->registerCLib("DataLib",DataLib);
	ticpp::Declaration* decl = new ticpp::Declaration( "1.0", "UTF-8", "" );  
	mGameData.LinkEndChild( decl );  
	mGameData.LinkEndChild(new ticpp::Element("GameData"));
	
	decl = new ticpp::Declaration( "1.0", "UTF-8", "" );  
	mSystemConfig.LinkEndChild( decl );  
	mSystemConfig.LinkEndChild(new ticpp::Element("SystemConfig"));
}

DataLibrary::~DataLibrary(void)
{
}

void DataLibrary::loadXmlData( DataBlock type,std::string fileName )
{
	try
	{
		if (type==SystemConfig)
		{
			mSystemConfig.Clear();
			mSystemConfig.LoadFile(fileName,TIXML_ENCODING_UTF8);
		}
		else
		{
			mGameData.Clear();
			mGameData.LoadFile(fileName,TIXML_ENCODING_UTF8);
		}
	}
	catch (ticpp::Exception& e)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage(e.m_details,Ogre::LML_CRITICAL);
	}
}

void DataLibrary::saveXmlData( DataBlock type,std::string fileName )
{
	try
	{
		if (type==SystemConfig)
		{
			mSystemConfig.SaveFile(fileName);
		}
		else
		{
			mGameData.SaveFile(fileName);
		}
	}
	catch (ticpp::Exception& e)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage(e.m_details,Ogre::LML_CRITICAL);
	}
}

bool DataLibrary::setData( std::string path,const int& value,bool createpath)
{
	ticpp::Element* node=getNode(path,createpath);
	if (node!=NULL)
	{
		node->SetAttribute("value",value);
		node->SetAttribute("type","Int");
		return true;
	}
	else
	{
		return false;
	}
}

bool DataLibrary::setData( std::string path,const unsigned int& value,bool createpath)
{
	ticpp::Element* node=getNode(path,createpath);
	if (node!=NULL)
	{
		node->SetAttribute("value",value);
		node->SetAttribute("type","UInt");
		return true;
	}
	else
	{
		return false;
	}
}

bool DataLibrary::setData( std::string path,const float& value,bool createpath)
{
	ticpp::Element* node=getNode(path,createpath);
	if (node!=NULL)
	{
		node->SetAttribute("value",value);	
		node->SetAttribute("type","Float");
		return true;
	}
	else
	{
		return false;
	}
}

bool DataLibrary::setData( std::string path,const double& value,bool createpath )
{
	ticpp::Element* node=getNode(path,createpath);
	if (node!=NULL)
	{
		node->SetAttribute("value",value);
		node->SetAttribute("type","Double");
		return true;
	}
	else
	{
		return false;
	}
}

bool DataLibrary::setData( std::string path,const std::string& value,bool createpath )
{
	ticpp::Element* node=getNode(path,createpath);
	if (node!=NULL)
	{
		node->SetAttribute("value",value);
		node->SetAttribute("type","String");
		return true;
	}
	else
	{
		return false;
	}
}

bool DataLibrary::setData( std::string path,const Ogre::Vector3& value,bool createpath )
{
	ticpp::Element* node=getNode(path,createpath);
	if (node!=NULL)
	{
		std::string v=Ogre::StringConverter::toString(value.x)+","+Ogre::StringConverter::toString(value.y)+","+Ogre::StringConverter::toString(value.z);
		node->SetAttribute("value",v);
		node->SetAttribute("type","Vector3");
		return true;
	}
	else
	{
		return false;
	}
}

bool DataLibrary::getData( std::string path,int& value )
{
	ticpp::Element* node=getNode(path,false);
	if (node!=NULL)
	{
		try
		{
			node->GetAttribute("value",&value);
		}
		catch (ticpp::Exception& e)
		{
			Ogre::LogManager::getSingletonPtr()->logMessage(e.m_details,Ogre::LML_CRITICAL);
			return false;
		}
		
		return 	true;
	}
	else
	{
		Ogre::LogManager::getSingletonPtr()->logMessage(path+" is not exist",Ogre::LML_CRITICAL);
		return false;
	}
}

bool DataLibrary::getData( std::string path,unsigned int& value )
{
	ticpp::Element* node=getNode(path,false);
	if (node!=NULL)
	{
		try
		{
			node->GetAttribute("value",&value);
		}
		catch (ticpp::Exception& e)
		{
			Ogre::LogManager::getSingletonPtr()->logMessage(e.m_details,Ogre::LML_CRITICAL);
			return false;
		}

		return 	true;	
	}
	else
	{
		Ogre::LogManager::getSingletonPtr()->logMessage(path+" is not exist",Ogre::LML_CRITICAL);
		return false;
	}
}

bool DataLibrary::getData( std::string path,float& value )
{
	ticpp::Element* node=getNode(path,false);
	if (node!=NULL)
	{
		try
		{
			node->GetAttribute("value",&value);
		}
		catch (ticpp::Exception& e)
		{
			Ogre::LogManager::getSingletonPtr()->logMessage(e.m_details,Ogre::LML_CRITICAL);
			return false;
		}

		return 	true;		
	}
	else
	{
		Ogre::LogManager::getSingletonPtr()->logMessage(path+" is not exist",Ogre::LML_CRITICAL);
		return false;
	}
}

bool DataLibrary::getData( std::string path,double& value )
{
	ticpp::Element* node=getNode(path,false);
	if (node!=NULL)
	{
		try
		{
			node->GetAttribute("value",&value);
		}
		catch (ticpp::Exception& e)
		{
			Ogre::LogManager::getSingletonPtr()->logMessage(e.m_details,Ogre::LML_CRITICAL);
			return false;
		}

		return 	true;		
	}
	else
	{
		Ogre::LogManager::getSingletonPtr()->logMessage(path+" is not exist",Ogre::LML_CRITICAL);
		return false;
	}
}

bool DataLibrary::getData( std::string path,std::string& value )
{
	ticpp::Element* node=getNode(path,false);
	if (node!=NULL)
	{
		try
		{
			node->GetAttribute("value",&value);
		}
		catch (ticpp::Exception& e)
		{
			Ogre::LogManager::getSingletonPtr()->logMessage(e.m_details,Ogre::LML_CRITICAL);
			return false;
		}

		return 	true;			
	}
	else
	{
		Ogre::LogManager::getSingletonPtr()->logMessage(path+" is not exist",Ogre::LML_CRITICAL);
		return false;
	}
}

bool DataLibrary::getData( std::string path,Ogre::Vector3& value )
{
	ticpp::Element* node=getNode(path,false);
	if (node!=NULL)
	{
		try
		{
			std::string v;
			std::queue<std::string> vl;
			node->GetAttribute("value",&v);
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
			}
		}
		catch (ticpp::Exception& e)
		{
			Ogre::LogManager::getSingletonPtr()->logMessage(e.m_details,Ogre::LML_CRITICAL);
			return false;
		}

		return 	true;			
	}
	else
	{
		Ogre::LogManager::getSingletonPtr()->logMessage(path+" is not exist",Ogre::LML_CRITICAL);
		return false;
	}
}

ticpp::Element* DataLibrary::findNode( ticpp::Element* parent,std::queue<std::string>* path,bool createpath)
{
	std::string nodeName=path->front();
	path->pop();
	
	if (!parent->NoChildren())
	{
		ticpp::Element* chila=parent->FirstChildElement(nodeName,false);
		if (chila!=NULL)
		{
			if (!path->empty())
			{
				return findNode(chila,path,createpath);
			}
			else
			{
				return chila;
			}
		}
	}
	
	if(createpath)
	{
		ticpp::Element* newNode=new ticpp::Element(nodeName);
		parent->LinkEndChild(newNode);
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

ticpp::Element* DataLibrary::getNode( std::string path,bool createpath)
{
	std::queue<std::string> pathQueue;
	split(path,'/',pathQueue);
	if (pathQueue.size()>=2)
	{
		ticpp::Element* parent=NULL;
		if (pathQueue.front()=="GameData")
		{
			parent=mGameData.FirstChildElement();
		}
		else
		{
			parent=mSystemConfig.FirstChildElement();
		}

		pathQueue.pop();
		return findNode(parent,&pathQueue,createpath);
	}
	else
	{
		return NULL;
	}
}

DataLibrary::DataType DataLibrary::getDataType( std::string path )
{
	ticpp::Element* node=getNode(path,false);
	if (node!=NULL)
	{
		std::string value=0;
		try
		{
			value=node->GetAttribute("type");
		}
		catch (ticpp::Exception& e)
		{
			Ogre::LogManager::getSingletonPtr()->logMessage(e.m_details,Ogre::LML_CRITICAL);
			return NoneType;
		}
		
		DataType type=NoneType;
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

		return 	type;		
	}
	else
	{
		Ogre::LogManager::getSingletonPtr()->logMessage(path+" is not exist",Ogre::LML_CRITICAL);
		return NoneType;
	}
}
