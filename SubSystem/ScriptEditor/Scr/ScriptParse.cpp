#include "ScriptParse.h"
#include <QFile>
#include <QMap>

ScriptParse::ScriptParse(void)
{
	QFile file("role.txt");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return;
	
	Role r;
	int state=0;
	while (!file.atEnd()) 
	{
		QByteArray line = file.readLine();
		QString s(line);
		s=s.trimmed();

		if (s=="#")
		{
			state=1;
		}
		else if(state==1)
		{
			r.name=s;
			state=2;
		}
		else if (state==2 && s=="%%")
		{
			state=3;
		}
		else if(state==3)
		{
			if (s!="%%")
			{
				r.param.append(s);
			}
			else
			{
				state=4;
			}
		}
		else if(state==4)
		{
			r.lua=s;

			mRoles.append(r);

			r.param.clear();
		}
	}

	file.close();
}

ScriptParse::~ScriptParse(void)
{
}

QString ScriptParse::parse( QString text )
{
	mResult.clear();
	mError="";
	QString::Iterator it;
	bool isOrderBegin=false;
	bool isTextBegin=true;
	QString s;
	int line=0;

	for (it=text.begin();it!=text.end();it++)
	{
		if (QString((*it))=="[")
		{
			
			if (isOrderBegin)//说明有[没闭合
			{
				mError=QString(line)+":有括号未闭合";
				return mError;
			}

			if (isTextBegin && !s.isEmpty())
			{
				mTextBuffer=s;//将文本放入缓冲中,根据下一个指令的内容,决定如何处理
				s="";
			}
			isOrderBegin=true;
			isTextBegin=false;
		}
		else if (QString((*it))=="]")
		{
			
			if (!isOrderBegin)//说明有]提前闭合
			{
				mError=QString(line)+":有括号未闭合";
				return mError;
			}
			
			if (s.isEmpty())
			{
				mError=QString(line)+":空括号";
				return mError;
			}

			mResult.append(orderParse(s));

			if(!mError.isEmpty())
			{
				return QString().setNum(line)+":"+mError;
			}
			
			isOrderBegin=false;
			isTextBegin=true;
			s="";
		}
		else if (QString((*it))=="\n")
		{
			line++;
		}
		else
		{
			s+=(*it);
		}
	}

	return mResult.join("\n");
}

QString ScriptParse::orderParse( QString text )
{
	QStringList sl=text.trimmed().split(" ");

	if (sl.size()!=0)
	{
		QMap<QString,QString> valueMap;//获取参数
		for (int i=1;i<sl.size();i++)
		{
			QStringList param=sl.at(i).split("=");
			if (param.size()==2)
			{
				valueMap[param.at(0)]=param.at(1);
			}
			else
			{
				mError="参数格式不正确";
				return "";
			}
		}

		if (!mTextBuffer.isEmpty())//如果文本缓冲里面有东西,就加入参数列表中去
		{
			valueMap["TextBuffer"]=mTextBuffer;
		}
		
		bool flag=false;
		QString result;
		QVector<Role>::Iterator it;
		for (it=mRoles.begin();it!=mRoles.end();it++)
		{
			if ((*it).name==sl.at(0))//如果名字匹配
			{
				flag=true;
				result=(*it).lua;
				QStringList::Iterator sIt;
				for (sIt=(*it).param.begin();sIt!=(*it).param.end();sIt++)//遍历参数名称表
				{
					QString value=valueMap.value((*sIt));//从参数表里面找数据;
					if (!value.isEmpty())
					{
						
						if ((*sIt)=="TextBuffer")
						{
							mTextBuffer.clear();//表示使用过了mTextBuffer
						}

						result.replace((*sIt),value);//替换掉lua中的参数名为具体数据
					}
					else
					{
						mError="参数";
						mError+=(*sIt)+"未找到";
						return "";
					}
				}
				break;
			}
		}

		if (!flag)
		{
			mError="指令未定义";
			return "";
		}
		else
		{
			
			if (!mTextBuffer.isEmpty())//这里判定mTextBuffer是否已经被处理了,没处理的话就使用默认处理
			{
				mTextBuffer.insert(0,"GUI.ShowText(\"");
				mTextBuffer.append("\",1);\n");
				result.insert(0,mTextBuffer);
				mTextBuffer.clear();
			}

			return result;
		}
	}
	return "";
}

bool ScriptParse::hasError()
{
	if (!mError.isEmpty())
	{
		return true;
	}
	else
	{
		return false;
	}
}
