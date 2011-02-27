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
		Ogre::LogManager::getSingletonPtr()->logMessage(e.m_details,Ogre::LogMessageLevel::LML_CRITICAL);
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
		Ogre::LogManager::getSingletonPtr()->logMessage(e.m_details,Ogre::LogMessageLevel::LML_CRITICAL);
	}
}

void DataLibrary::setData( std::string path,int value )
{
	ticpp::Element* node=getNode(path);
	if (node!=NULL)
	{
		node->SetAttribute("value",value);
		node->SetAttribute("type","Int");
	}
}

void DataLibrary::setData( std::string path,unsigned int value )
{
	ticpp::Element* node=getNode(path);
	if (node!=NULL)
	{
		node->SetAttribute("value",value);
		node->SetAttribute("type","UInt");
	}
}

void DataLibrary::setData( std::string path,float value )
{
	ticpp::Element* node=getNode(path);
	if (node!=NULL)
	{
		node->SetAttribute("value",value);	
		node->SetAttribute("type","Float");
	}
}

void DataLibrary::setData( std::string path,double value )
{
	ticpp::Element* node=getNode(path);
	if (node!=NULL)
	{
		node->SetAttribute("value",value);
		node->SetAttribute("type","Double");
	}
}

void DataLibrary::setData( std::string path,std::string value )
{
	ticpp::Element* node=getNode(path);
	if (node!=NULL)
	{
		node->SetAttribute("value",value);
		node->SetAttribute("type","String");
	}
}

int DataLibrary::getDataI( std::string path)
{
	ticpp::Element* node=getNode(path);
	if (node!=NULL)
	{
		int value=0;
		try
		{
			node->GetAttribute("value",&value);
		}
		catch (ticpp::Exception& e)
		{
			Ogre::LogManager::getSingletonPtr()->logMessage(e.m_details,Ogre::LogMessageLevel::LML_CRITICAL);
			return -1;
		}

		return 	value;
	}
	else
	{
		Ogre::LogManager::getSingletonPtr()->logMessage(path+" is not exist",Ogre::LogMessageLevel::LML_CRITICAL);
		return -1;
	}
}

unsigned int DataLibrary::getDataUI( std::string path )
{
	ticpp::Element* node=getNode(path);
	if (node!=NULL)
	{
		unsigned int value=0;
		try
		{
			node->GetAttribute("value",&value);
		}
		catch (ticpp::Exception& e)
		{
			Ogre::LogManager::getSingletonPtr()->logMessage(e.m_details,Ogre::LogMessageLevel::LML_CRITICAL);
			return 0;
		}

		return 	value;	
	}
	else
	{
		Ogre::LogManager::getSingletonPtr()->logMessage(path+" is not exist",Ogre::LogMessageLevel::LML_CRITICAL);
		return 0;
	}
}

float DataLibrary::getDataF( std::string path )
{
	ticpp::Element* node=getNode(path);
	if (node!=NULL)
	{
		float value=0;
		try
		{
			node->GetAttribute("value",&value);
		}
		catch (ticpp::Exception& e)
		{
			Ogre::LogManager::getSingletonPtr()->logMessage(e.m_details,Ogre::LogMessageLevel::LML_CRITICAL);
			return 0;
		}

		return 	value;		
	}
	else
	{
		Ogre::LogManager::getSingletonPtr()->logMessage(path+" is not exist",Ogre::LogMessageLevel::LML_CRITICAL);
		return 0;
	}
}

double DataLibrary::getDataD( std::string path )
{
	ticpp::Element* node=getNode(path);
	if (node!=NULL)
	{
		double value=0;
		try
		{
			node->GetAttribute("value",&value);
		}
		catch (ticpp::Exception& e)
		{
			Ogre::LogManager::getSingletonPtr()->logMessage(e.m_details,Ogre::LogMessageLevel::LML_CRITICAL);
			return 0;
		}

		return 	value;		
	}
	else
	{
		Ogre::LogManager::getSingletonPtr()->logMessage(path+" is not exist",Ogre::LogMessageLevel::LML_CRITICAL);
		return 0;
	}
}

std::string DataLibrary::getDataS( std::string path )
{
	ticpp::Element* node=getNode(path);
	if (node!=NULL)
	{
		std::string value="";
		try
		{
			node->GetAttribute("value",&value);
		}
		catch (ticpp::Exception& e)
		{
			Ogre::LogManager::getSingletonPtr()->logMessage(e.m_details,Ogre::LogMessageLevel::LML_CRITICAL);
			return "";
		}

		return 	value;			
	}
	else
	{
		Ogre::LogManager::getSingletonPtr()->logMessage(path+" is not exist",Ogre::LogMessageLevel::LML_CRITICAL);
		return "";
	}
}

ticpp::Element* DataLibrary::findNode( ticpp::Element* parent,std::queue<std::string>* path )
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
				return findNode(chila,path);
			}
			else
			{
				return chila;
			}
		}
	}
	
	ticpp::Element* newNode=new ticpp::Element(nodeName);
	parent->LinkEndChild(newNode);
	if (!path->empty())
	{
		return findNode(newNode,path);
	}
	else
	{
		return newNode;
	}
}

void DataLibrary::split(const std::string& s, char c,std::queue<std::string>& v) 
{
			   std::string::size_type i = 0;
			   std::string::size_type j = s.find(c);

			   while (j != std::string::npos) {
				   v.push(s.substr(i, j-i));
				   i = ++j;
				   j = s.find(c, j);

				   if (j == std::string::npos)
					   v.push(s.substr(i, s.length( )));
			   }
}

ticpp::Element* DataLibrary::getNode( std::string path )
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
		return findNode(parent,&pathQueue);
	}
	else
	{
		return NULL;
	}
}

DataLibrary::DataType DataLibrary::getDataType( std::string path )
{
	ticpp::Element* node=getNode(path);
	if (node!=NULL)
	{
		std::string value=0;
		try
		{
			value=node->GetAttribute("type");
		}
		catch (ticpp::Exception& e)
		{
			Ogre::LogManager::getSingletonPtr()->logMessage(e.m_details,Ogre::LogMessageLevel::LML_CRITICAL);
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
		Ogre::LogManager::getSingletonPtr()->logMessage(path+" is not exist",Ogre::LogMessageLevel::LML_CRITICAL);
		return NoneType;
	}
}
