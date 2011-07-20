#include "AVGState.h"

#include "LuaSystem.h"
#include "GUIStage.h"
#include "DataLibrary.h"

AVGState::AVGState(void)
{
}

AVGState::~AVGState(void)
{
}

void AVGState::initialize( std::string arg )
{
	std::queue<std::string> q;
	split(arg,'.',q);

	if (q.size()==2)
	{
		q.pop();

		//显示对话框
		GUIStage* stageScene=static_cast<GUIStage*>(GUISystem::getSingletonPtr()->createScene(StageScene));
		stageScene->showScene("");

		if (q.front()=="lua")//该文件重头读取
		{
			//DataLibrary::getSingleton().loadXmlData(DataLibrary::GameData,"newgame.xml",true);
			LuaSystem::getSingletonPtr()->runScriptFromFile(arg,0);
		}
		else if(q.front()=="sav")//从中间读取
		{

		}
	}
}

void AVGState::uninitialize()
{
	GUISystem::getSingletonPtr()->destoryScene(StageScene);
}

void AVGState::update(unsigned int deltaTime)
{

}

void AVGState::split(const std::string& s, char c,std::queue<std::string>& v) 
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