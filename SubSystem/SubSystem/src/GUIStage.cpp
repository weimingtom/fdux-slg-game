#include "GUIStage.h"

#include "GUISystem.h"

#include <ogre.h>

GUIStage::GUIStage(int width,int height):mCheckMouseDown(false),mIsMouseDown(false),mTextX(0),mTextY(0)
{
	mWidgetVector=MyGUI::LayoutManager::getInstance().loadLayout("Stage.layout");
	mWidgetVector.at(0)->setSize(width,height);//设置背景大小
	mWidgetVector.at(0)->findWidget("BackGround")->setSize(width,height);
	mWidgetVector.at(0)->findWidget("BackGroundUniversal")->setSize(width,height);

	mWidgetVector.at(1)->setSize(width,height);//设置左大小
	mWidgetVector.at(2)->setSize(width,height);//设置中大小
	mWidgetVector.at(3)->setSize(width,height);//设置右大小

	mWidgetVector.at(4)->setSize(width,height);//TextBoxBG
	mWidgetVector.at(5)->setSize(width,height);//EFLayer
	mWidgetVector.at(5)->eventMouseButtonClick+= MyGUI::newDelegate(this, &GUIStage::eventMouseButtonClick);
}

GUIStage::~GUIStage(void)
{
}

void GUIStage::showScene()
{

}

void GUIStage::hideScene()
{

}

void GUIStage::eventMouseButtonClick(MyGUI::Widget* _sender)
{
	if (mCheckMouseDown)
	{
		mIsMouseDown=true;
		mCheckMouseDown=false;
	}
}


void GUIStage::setCheckMouseDown()
{
	mCheckMouseDown=true;
	mIsMouseDown=false;
}

bool GUIStage::CheckMouseState()
{
	return mIsMouseDown;
}


void GUIStage::setTextDialog( const GUIDialogAttribute& attribute )
{
	mWidgetVector.at(4)->findWidget("TextBox")->castType<MyGUI::EditBox>()->setPosition(attribute.TextLeft,attribute.TextTop);
	mTextX=attribute.TextLeft;
	mTextY=attribute.TextTop;

	mWidgetVector.at(4)->findWidget("TextBox")->castType<MyGUI::EditBox>()->setSize(attribute.TextWidth,attribute.TextHeight);
	mWidgetVector.at(4)->findWidget("TextBox")->castType<MyGUI::EditBox>()->setTextColour(MyGUI::Colour(attribute.TextRed,attribute.TextGreen,attribute.TextBlue));
	mWidgetVector.at(4)->findWidget("TextBox")->castType<MyGUI::EditBox>()->setFontName(attribute.TextFont);

	mWidgetVector.at(4)->findWidget("RoleName")->castType<MyGUI::EditBox>()->setPosition(attribute.RoleNameLeft,attribute.RoleNameTop);
	mWidgetVector.at(4)->findWidget("RoleName")->castType<MyGUI::EditBox>()->setSize(attribute.RoleNameWidth,attribute.RoleNameHeight);
	mWidgetVector.at(4)->findWidget("RoleName")->castType<MyGUI::EditBox>()->setTextColour(MyGUI::Colour(attribute.RoleNameRed,attribute.RoleNameGreen,attribute.RoleNameBlue));
	mWidgetVector.at(4)->findWidget("RoleName")->castType<MyGUI::EditBox>()->setFontName(attribute.RoleFont);

	mWidgetVector.at(4)->findWidget("RoleNameUniversal")->castType<MyGUI::EditBox>()->setPosition(attribute.RoleNameLeft,attribute.RoleNameTop);
	mWidgetVector.at(4)->findWidget("RoleNameUniversal")->castType<MyGUI::EditBox>()->setSize(attribute.RoleNameWidth,attribute.RoleNameHeight);
	mWidgetVector.at(4)->findWidget("RoleNameUniversal")->castType<MyGUI::EditBox>()->setTextColour(MyGUI::Colour(attribute.RoleNameRed,attribute.RoleNameGreen,attribute.RoleNameBlue));
	mWidgetVector.at(4)->findWidget("RoleNameUniversal")->castType<MyGUI::EditBox>()->setFontName(attribute.RoleFont);
}


void GUIStage::setTextDialogVisible( bool visible )
{
	if (visible)
	{
		mSetp=0;
		mSetpDirection=true;
	}
	else
	{
		mSetp=1;
		mSetpDirection=false;
	}

	mWidgetVector.at(4)->setVisible(true);

	mWidgetVector.at(4)->setAlpha(mSetp);

	mTimerWork=DialogVisible;
	mTickTime=DefaultDialogVisibleTime*1000;

	//开始帧更新
	mTimer.reset();
	GUISystem::getSingletonPtr()->setFrameUpdateScene(StageScene);
}

void GUIStage::waitTime( float time )
{
	mTimerWork=WaitWork;
	mTickTime=time;

	//开始帧更新
	mTimer.reset();
	GUISystem::getSingletonPtr()->setFrameUpdateScene(StageScene);
}

void GUIStage::showText( std::wstring text,float delay)
{
	if(delay==0)
	{
		mWidgetVector.at(4)->findWidget("TextBox")->castType<MyGUI::EditBox>()->addText(text);
	}
	else
	{
		//如果是打字效果,那么启动打字定时器
		mTextBuffer=text;
		mTimerWork=PrinterWork;
		mTickTime=delay*1000;

		//开始帧更新
		mTimer.reset();
		GUISystem::getSingletonPtr()->setFrameUpdateScene(StageScene);
	}
}

void GUIStage::showImage( std::string imageName,GUIImageLayer layer,float time,int left,int top)
{

	//选择图层

	switch(layer)
	{
	case EffectsLayer:
		{
			mScrLayer=mWidgetVector.at(5)->castType<MyGUI::ImageBox>();
			mUniversalLayer=NULL;
		}
	case LeftLayer:
		{
			mScrLayer=mWidgetVector.at(1)->findWidget("LeftLayer")->castType<MyGUI::ImageBox>();
			mUniversalLayer=mWidgetVector.at(1)->findWidget("LeftLayerUniversal")->castType<MyGUI::ImageBox>();
			break;
		}
	case MidLayer:
		{
			mScrLayer=mWidgetVector.at(2)->findWidget("MidLayer")->castType<MyGUI::ImageBox>();
			mUniversalLayer=mWidgetVector.at(2)->findWidget("MidUniversal")->castType<MyGUI::ImageBox>();
			break;
		}
	case RightLayer:
		{
			mScrLayer=mWidgetVector.at(3)->findWidget("RightLayer")->castType<MyGUI::ImageBox>();
			mUniversalLayer=mWidgetVector.at(3)->findWidget("RightUniversal")->castType<MyGUI::ImageBox>();
			break;
		}
	case BackGroundLayer:
		{
			mScrLayer=mWidgetVector.at(0)->findWidget("BackGround")->castType<MyGUI::ImageBox>();
			mUniversalLayer=mWidgetVector.at(0)->findWidget("BackGroundUniversal")->castType<MyGUI::ImageBox>();
			break;
		}
	}

	//预先加载,获取图片的宽高

	int width,height=0;

	if (!imageName.empty())
	{
		if(!Ogre::TextureManager::getSingleton().resourceExists(imageName))
		{
			Ogre::Image i;
			i.load(imageName,Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
			width=i.getWidth();
			height=i.getHeight();
		}
		else
		{
			width=((Ogre::TexturePtr)Ogre::TextureManager::getSingleton().getByName(imageName))->getWidth();
			height=((Ogre::TexturePtr)Ogre::TextureManager::getSingleton().getByName(imageName))->getHeight();
		}
	}

	if (mScrLayer!=NULL)
	{
		mScrLayer->setPosition(left,top);
		mUniversalLayer->setPosition(left,top);
		if (!imageName.empty())//如果名字为空的话...那么不调整大小
		{
			mScrLayer->setSize(width,height);
			mUniversalLayer->setSize(width,height);
		}


		if (time!=0)//如果要使用渐变进入
		{
			mUniversalLayer->setAlpha(0);
			mUniversalLayer->setImageTexture(imageName);
			mUniversalLayer->setVisible(true);

			mSetp=0;
			mTimerWork=UniversalWork;
			mTickTime=time/100;
			mTextureName=imageName;

			//开始帧更新
			mTimer.reset();
			GUISystem::getSingletonPtr()->setFrameUpdateScene(StageScene);
		}
		else
		{
			mScrLayer->setImageTexture(imageName);
		}

	}
}

void GUIStage::showRoleName( std::wstring text )
{
	mWidgetVector.at(4)->findWidget("RoleNameUniversal")->castType<MyGUI::EditBox>()->setAlpha(0);
	mWidgetVector.at(4)->findWidget("RoleNameUniversal")->castType<MyGUI::EditBox>()->setCaption(text);
	mWidgetVector.at(4)->findWidget("RoleNameUniversal")->castType<MyGUI::EditBox>()->setVisible(true);

	mSetp=0;
	mTimerWork=RoleNameWork;
	mTickTime=DefaultRoleNameVisibleTime*1000/100;

	//开始帧更新
	mTimer.reset();
	GUISystem::getSingletonPtr()->setFrameUpdateScene(StageScene);
}

void GUIStage::showOtherText()
{
	//停止帧更新
	mTickTime=0;
	mTimerWork=NoneWork;
	GUISystem::getSingletonPtr()->setFrameUpdateScene(NoneScene);

	mWidgetVector.at(4)->findWidget("TextBox")->castType<MyGUI::EditBox>()->addText(mTextBuffer);
	mTextBuffer.clear();
}

void GUIStage::clearText()
{
	mWidgetVector.at(4)->findWidget("TextBox")->castType<MyGUI::EditBox>()->setCaption("");
}

void GUIStage::FrameEvent()
{
	if(mTickTime!=0)
	{
		if (mTimer.getMilliseconds()>=mTickTime)
		{
			//复位定时器
			mTimer.reset();

			switch(mTimerWork)
			{
			case PrinterWork:
				{
					if (!mTextBuffer.empty())
					{
						mWidgetVector.at(4)->findWidget("TextBox")->castType<MyGUI::EditBox>()->addText(mTextBuffer.substr(0,1));
						mTextBuffer.erase(mTextBuffer.begin());
					}
					else
					{
						//停止帧更新
						mTickTime=0;
						mTimerWork=NoneWork;
						GUISystem::getSingletonPtr()->setFrameUpdateScene(NoneScene);
					}
					break;
				}
			case UniversalWork:
				{
					if(mSetp<=1.0)
					{
						mScrLayer->setAlpha(1.0-mSetp);
						mUniversalLayer->setAlpha(mSetp);

						mSetp+=0.01;
					}
					else
					{
						mScrLayer->setImageTexture(mTextureName);
						mScrLayer->setAlpha(1.0);
						mUniversalLayer->setVisible(false);

						//停止帧更新
						mTickTime=0;
						mTimerWork=NoneWork;
						GUISystem::getSingletonPtr()->setFrameUpdateScene(NoneScene);
					}

					break;
				}
				case DialogVisible:
					{
						if (mSetpDirection)//判定渐变步方向
						{
							if(mSetp<=1.0)
							{
								mSetp+=0.01;

								mWidgetVector.at(4)->setAlpha(mSetp);
							}
							else
							{
								mWidgetVector.at(4)->setAlpha(1.0);

								//停止帧更新
								mTickTime=0;
								mTimerWork=NoneWork;
								GUISystem::getSingletonPtr()->setFrameUpdateScene(NoneScene);
							}
						}
						else
						{
							if(mSetp>=0)
							{
								mSetp-=0.01;

								mWidgetVector.at(4)->setAlpha(mSetp);
							}
							else
							{
								mWidgetVector.at(4)->setAlpha(0);
								mWidgetVector.at(4)->setVisible(false);


								//停止帧更新
								mTickTime=0;
								mTimerWork=NoneWork;
								GUISystem::getSingletonPtr()->setFrameUpdateScene(NoneScene);
							}

						}

						break;
					}
				case WaitWork:
					{
						//停止帧更新
						mTickTime=0;
						mTimerWork=NoneWork;
						GUISystem::getSingletonPtr()->setFrameUpdateScene(NoneScene);

						break;
					}
				case RoleNameWork:
					{
						if(mSetp<=1.0)
						{
							mWidgetVector.at(4)->findWidget("RoleName")->castType<MyGUI::EditBox>()->setAlpha(1.0-mSetp);
							mWidgetVector.at(4)->findWidget("RoleNameUniversal")->castType<MyGUI::EditBox>()->setAlpha(mSetp);

							mSetp+=0.01;
						}
						else
						{
							std::string s=mWidgetVector.at(4)->findWidget("RoleNameUniversal")->castType<MyGUI::EditBox>()->getCaption();
							mWidgetVector.at(4)->findWidget("RoleNameUniversal")->castType<MyGUI::EditBox>()->setVisible(false);
							mWidgetVector.at(4)->findWidget("RoleName")->castType<MyGUI::EditBox>()->setCaption(s);
							mWidgetVector.at(4)->findWidget("RoleName")->castType<MyGUI::EditBox>()->setAlpha(1);

							//停止帧更新
							mTickTime=0;
							mTimerWork=NoneWork;
							GUISystem::getSingletonPtr()->setFrameUpdateScene(NoneScene);
						}

						break;
					}
			}
		}
	}
}

void GUIStage::showTextCursor( bool isLine )
{
	MyGUI::IntPoint p=mWidgetVector.at(4)->findWidget("TextBox")->castType<MyGUI::EditBox>()->getTextCursorPos();

	mWidgetVector.at(4)->findWidget("TextCursor")->setPosition(p.left,p.top);
	mWidgetVector.at(4)->findWidget("TextCursor")->castType<MyGUI::ImageBox>()->setVisible(true);
	mWidgetVector.at(4)->findWidget("TextCursor")->castType<MyGUI::ImageBox>()->setItemResource ("TextCursorImage");

	if(!isLine)
	{
		mWidgetVector.at(4)->findWidget("TextCursor")->castType<MyGUI::ImageBox>()->setItemGroup("LineBreak");
	}
	else
	{
		mWidgetVector.at(4)->findWidget("TextCursor")->castType<MyGUI::ImageBox>()->setItemGroup("PageBreak");
	}

	mWidgetVector.at(4)->findWidget("TextCursor")->castType<MyGUI::ImageBox>()->setItemName("show");

}

void GUIStage::hideTextCursor()
{
	mWidgetVector.at(4)->findWidget("TextCursor")->castType<MyGUI::ImageBox>()->setVisible(false);
}
