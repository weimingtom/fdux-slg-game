#include "DataLibrary.h"

#include "LuaSystem.h"
#include "conversion.h"

#include <OgreLogManager.h> 

DataLibrary::DataLibrary(void)
{
	LuaSystem::getSingletonPtr()->registerCLib("DataLib",DataLib);
	ticpp::Declaration* decl = new ticpp::Declaration( "1.0", "UTF-8", "" );  
	mGameData.LinkEndChild( decl );  
	mGameData.LinkEndChild(new ticpp::Element("GameData"));

	decl = new ticpp::Declaration( "1.0", "UTF-8", "" );  
	mStaticData.LinkEndChild( decl );  
	mStaticData.LinkEndChild(new ticpp::Element("StaticData"));
	
	decl = new ticpp::Declaration( "1.0", "UTF-8", "" );  
	mSystemConfig.LinkEndChild( decl );  
	mSystemConfig.LinkEndChild(new ticpp::Element("SystemConfig"));
}

DataLibrary::~DataLibrary(void)
{

}

void DataLibrary::loadXmlData( DataBlock type,std::string fileName,bool append)
{
	ticpp::Document* currentDoc;
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
			appendXmlDate(currentDoc,fileName);
		}
		else
		{
			currentDoc->Clear();
			currentDoc->LoadFile(fileName,TIXML_ENCODING_UTF8);
		}
	}
	catch (ticpp::Exception& e)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage(e.m_details,Ogre::LML_CRITICAL);
	}
}

void DataLibrary::appendXmlDate( ticpp::Document* currentDoc,std::string fileName )
{
	try
	{
		ticpp::Document doc;
		doc.LoadFile(fileName,TIXML_ENCODING_UTF8);

		ticpp::Element* srcElement=doc.FirstChildElement();
		ticpp::Element* destElement=currentDoc->FirstChildElement();

		copyElement(srcElement,destElement);

		delete destElement;
	}
	catch (ticpp::Exception& e)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage(e.m_details,Ogre::LML_CRITICAL);
	}
}

void DataLibrary::copyElement( ticpp::Element* srcElement,ticpp::Element* destElement )
{

	ticpp::Iterator< ticpp::Element > child;
	for ( child = child.begin(srcElement); child != child.end(); child++ )
	{
		ticpp::Element* findElement=destElement->FirstChildElement(child->Value(),false);
		if(findElement!=NULL)//如果有,就继续递归
		{
			copyElement(&(*child),findElement);
		}
		else//如果没找到,说明目标节点下面没有该源节点
		{
			std::auto_ptr< ticpp::Node > clonedNode=child->Clone();
			destElement->LinkEndChild(clonedNode->ToElement());
		}
		delete findElement;
	}

	
}

void DataLibrary::saveXmlData( DataBlock type,std::string fileName )
{
	try
	{
		switch(type)
		{
		case SystemConfig:
			mSystemConfig.SaveFile(fileName);
			break;
		case GameData:
			mGameData.SaveFile(fileName);
			break;
		case StaticData:
			mStaticData.SaveFile(fileName);
			break;
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
		if (mCreateState==CreateState_NoCreate)
		{
			delete node;
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
	ticpp::Element* node=getNode(path,createpath);
	if (node!=NULL)
	{
		node->SetAttribute("value",value);
		node->SetAttribute("type","UInt");
		if (mCreateState==CreateState_NoCreate)
		{
			delete node;
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
	ticpp::Element* node=getNode(path,createpath);
	if (node!=NULL)
	{
		node->SetAttribute("value",value);	
		node->SetAttribute("type","Float");
		if (mCreateState==CreateState_NoCreate)
		{
			delete node;
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
	ticpp::Element* node=getNode(path,createpath);
	if (node!=NULL)
	{
		node->SetAttribute("value",value);
		node->SetAttribute("type","Double");
		if (mCreateState==CreateState_NoCreate)
		{
			delete node;
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
	ticpp::Element* node=getNode(path,createpath);
	if (node!=NULL)
	{
		node->SetAttribute("value",value);
		node->SetAttribute("type","String");
		if (mCreateState==CreateState_NoCreate)
		{
			delete node;
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
	ticpp::Element* node=getNode(path,createpath);
	if (node!=NULL)
	{
		std::string v=Ogre::StringConverter::toString(value.x)+","+Ogre::StringConverter::toString(value.y)+","+Ogre::StringConverter::toString(value.z);
		node->SetAttribute("value",v);
		node->SetAttribute("type","Vector3");
		if (mCreateState==CreateState_NoCreate)
		{
			delete node;
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
	ticpp::Element* node=getNode(path,false);
	if (node!=NULL)
	{
		try
		{
			node->GetAttribute("value",&value);
			delete node;
		}
		catch (ticpp::Exception& e)
		{
			Ogre::LogManager::getSingletonPtr()->logMessage(e.m_details,Ogre::LML_CRITICAL);
			delete node;
			return false;
		}
		
		return 	true;
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
	ticpp::Element* node=getNode(path,false);
	if (node!=NULL)
	{
		try
		{
			node->GetAttribute("value",&value);
			delete node;
		}
		catch (ticpp::Exception& e)
		{
			Ogre::LogManager::getSingletonPtr()->logMessage(e.m_details,Ogre::LML_CRITICAL);
			delete node;
			return false;
		}

		return 	true;	
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
	ticpp::Element* node=getNode(path,false);
	if (node!=NULL)
	{
		try
		{
			node->GetAttribute("value",&value);
			delete node;
		}
		catch (ticpp::Exception& e)
		{
			Ogre::LogManager::getSingletonPtr()->logMessage(e.m_details,Ogre::LML_CRITICAL);
			delete node;
			return false;
		}

		return 	true;		
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
	ticpp::Element* node=getNode(path,false);
	if (node!=NULL)
	{
		try
		{
			node->GetAttribute("value",&value);
			delete node;
		}
		catch (ticpp::Exception& e)
		{
			Ogre::LogManager::getSingletonPtr()->logMessage(e.m_details,Ogre::LML_CRITICAL);
			delete node;
			return false;
		}

		return 	true;		
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
	ticpp::Element* node=getNode(path,false);
	if (node!=NULL)
	{
		try
		{
			node->GetAttribute("value",&value);
			delete node;
		}
		catch (ticpp::Exception& e)
		{
			Ogre::LogManager::getSingletonPtr()->logMessage(e.m_details,Ogre::LML_CRITICAL);
			delete node;
			return false;
		}

		return 	true;			
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
				delete node;
				return false;
			}
			else
			{
				value.x=Ogre::StringConverter::parseReal(vl.front());
				vl.pop();
				value.y=Ogre::StringConverter::parseReal(vl.front());
				vl.pop();
				value.z=Ogre::StringConverter::parseReal(vl.front());
				delete node;
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
		if (!testExist)
		{
			Ogre::LogManager::getSingletonPtr()->logMessage(path+" is not exist",Ogre::LML_CRITICAL);
		}
		return false;
	}
}

bool DataLibrary::delNode(std::string path)
{
	ticpp::Element* node=getNode(path,false);
	if(node == NULL)
	{
		return false;
	}

	ticpp::Node* parent = node->Parent(false);
	if(parent == NULL)
	{
		delete node;
		return false;
	}

	parent->RemoveChild(node);
	delete parent;

	return true;
}

void DataLibrary::createPath(std::string path)
{
	getNode(path,true);
}

bool DataLibrary::copyNode(std::string srcpath, std::string distpath, bool createpath)
{
	ticpp::Element* srcnode=getNode(srcpath,false);
	if(!srcnode)
	{
		return false;
	}

	ticpp::Element* distnode=getNode(distpath,createpath);
	if(!distnode)
	{
		delete srcnode;
		return false;
	}

	copyElement(srcnode,distnode );

	delete srcnode;
	if (mCreateState==CreateState_Create)
	{
		delete distnode;
	}

	return true;
}

std::vector<std::string> DataLibrary::getChildList(std::string path)
{
	std::vector<std::string> chlidlist;
	ticpp::Element* node=getNode(path,false);
	if(node)
	{
		ticpp::Iterator<ticpp::Element> child;
		for(child = child.begin(node); child != child.end(); child++)
		{
			std::string childname;
			child->GetValue(&childname);
			chlidlist.push_back(childname);
		}
	}
	delete node;

	return chlidlist;
}

ticpp::Element* DataLibrary::findNode( ticpp::Element* parent,std::queue<std::string>* path,bool createpath)
{
	std::string nodeName=path->front();
	path->pop();
	
	if (!parent->NoChildren())
	{
		ticpp::Element* child=parent->FirstChildElement(nodeName,false);
		if (child!=NULL)
		{
			if (!path->empty())
			{
				ticpp::Element* rtn=findNode(child,path,createpath);
				delete child;
				return rtn;
			}
			else
			{
				mCreateState=CreateState_NoCreate;
				return child;
			}
		}
		delete child;
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
			mCreateState=CreateState_Create;
			return newNode;
		}
	}
	else
	{
		mCreateState=CreateState_NoCreate;
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
	mCreateState=CreateState_None;
	std::queue<std::string> pathQueue;
	split(path,'/',pathQueue);
	if (pathQueue.size()>=2)
	{
		ticpp::Element* parent=NULL;
		if (pathQueue.front()=="GameData")
		{
			parent=mGameData.FirstChildElement();
		}
		else if(pathQueue.front()=="StaticData")
		{
			parent=mStaticData.FirstChildElement();
		}
		else
		{
			parent=mSystemConfig.FirstChildElement();
		}

		pathQueue.pop();
		ticpp::Element* e=findNode(parent,&pathQueue,createpath);
		delete parent;
		return e;
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
			delete node;
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
		
		delete node;

		return 	type;		
	}
	else
	{
		Ogre::LogManager::getSingletonPtr()->logMessage(path+" is not exist",Ogre::LML_CRITICAL);
		return NoneType;
	}
}
