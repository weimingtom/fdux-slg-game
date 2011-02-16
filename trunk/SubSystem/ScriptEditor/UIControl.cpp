#include "UIControl.h"

#include <QDebug>

UIControl::UIControl(void)
{
	//QuickGUI初始化
	mOgreCore=OgreCore::getSingletonPtr();

	QuickGUI::Root* guiRoot = new QuickGUI::Root();
	
	QuickGUI::SkinTypeManager::getSingleton().loadTypes();

	QuickGUI::GUIManagerDesc d;
	mGUIManager = QuickGUI::Root::getSingletonPtr()->createGUIManager(d);

	// Lets assume NumLock is on by default for this app
	mGUIManager->setNumLock(true);

	//创建默认截面
	QuickGUI::Root::getSingleton().setDefaultFontName("fireflysung");

	QuickGUI::SheetDesc* sd = QuickGUI::DescManager::getSingleton().getDefaultSheetDesc();
	sd->widget_dimensions.size =QuickGUI::Size(mOgreCore->mWindow->getWidth(),mOgreCore->mWindow->getHeight());

	mSheet = QuickGUI::SheetManager::getSingleton().createSheet(sd);
	mGUIManager->setActiveSheet(mSheet);

	//创建默认的表现层
	mBackGroundLayer=mSheet->createImage();
	mBackGroundUniversal=mSheet->createImage();
	mBackGroundUniversal->setVisible(false);

	mRightLayer=mSheet->createImage();
	mRightUniversal=mSheet->createImage();
	mRightUniversal->setVisible(false);

	mMidLayer=mSheet->createImage();
	mMidUniversal=mSheet->createImage();
	mMidUniversal->setVisible(false);

	mLeftLayer=mSheet->createImage();
	mLeftUniversal=mSheet->createImage();
	mLeftUniversal->setVisible(false);

	mEffectsLayer=mSheet->createImage();
	mEffectsUniversal=mSheet->createImage();
	mEffectsUniversal->setVisible(false);

	//创建文字对话框
	mDialog=mSheet->createTextArea();
	mDialog->setReadOnly(true);

	//创建人物名称框
	mRoleName=mSheet->createLabel();
	mRoleName->setText("");

	setTextDialogVisible(false);

	//创建定时器,用于打字效果
	QuickGUI::TimerDesc timerDesc;
	timerDesc.repeat = true;
	mTimer=QuickGUI::TimerManager::getSingletonPtr()->createTimer(timerDesc);
	mTimer->setCallback(&UIControl::timerCallback,this);
	mTimer->stop();
	mTimerWork=NoneWork;
}

UIControl::~UIControl(void)
{
}

void UIControl::showImage( std::string imageName,UIImageLayer layer,std::string universalName,int step,int left,int top)
{

	if(imageName==universalName)//防止目标与过渡图片相同
	{
		return;
	}

	//选择图层
	QuickGUI::Image* selectLayer=NULL;

	switch(layer)
	{
	case EffectsLayer:
		{
			selectLayer=mEffectsLayer;
			break;
		}
	case LeftLayer:
		{
			selectLayer=mLeftLayer;
			break;
		}
	case MidLayer:
		{
			selectLayer=mMidLayer;
			break;
		}
	case RightLayer:
		{
			selectLayer=mRightLayer;
			break;
		}
	case BackGroundLayer:
		{
			selectLayer=mBackGroundLayer;
			break;
		}
	}

	//预先加载,获取图片的宽高
	
	int width,height=0;

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

	if (selectLayer!=NULL)
	{
		selectLayer->setPosition(QuickGUI::Point(left,top));
		selectLayer->setSize(QuickGUI::Size(width,height));

		if (universalName!="")//如果要使用渐变进入
		{

			if(selectLayer->getImageName()=="")//如果该图层是空的
			{
				mScrTexture.setNull();
				mIsNoneScr=true;
			}
			else
			{
				mScrTexture=(Ogre::TexturePtr)Ogre::TextureManager::getSingleton().getByName(selectLayer->getImageName());
				mIsNoneScr=false;
			}

			if (Ogre::TextureManager::getSingleton().resourceExists(imageName))
			{
				mDestTexture=(Ogre::TexturePtr)Ogre::TextureManager::getSingleton().getByName(imageName);
			}
			else
			{
				mDestTexture=Ogre::TextureManager::getSingleton().load(imageName,Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
			}

			if (Ogre::TextureManager::getSingleton().resourceExists(universalName))
			{
				mUniversalTexture=(Ogre::TexturePtr)Ogre::TextureManager::getSingleton().getByName(universalName);
			}
			else
			{
				mUniversalTexture=Ogre::TextureManager::getSingleton().load(universalName,Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
			}
			
			mConvertTexture=Ogre::TextureManager::getSingleton().createManual("convertTexture",Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,Ogre::TEX_TYPE_2D,mDestTexture->getWidth(),mDestTexture->getHeight(),mDestTexture->getDepth(),0,mDestTexture->getFormat());
			
			if (!mIsNoneScr)
			{
				Ogre::HardwarePixelBufferSharedPtr scrBuffer=mScrTexture->getBuffer();
				Ogre::HardwarePixelBufferSharedPtr convertBuffer=mConvertTexture->getBuffer();

				convertBuffer->blit(scrBuffer);
			}

			selectLayer->setImage("convertTexture");
			mUniversalLayer=selectLayer;
			mUniversalLayer->setUpdateEveryFrame(true);
			
			h=0;
			mStep=0;
			mTimeSetp=step;
			mTimerWork=UniversalWork;
			mTimer->setTimePeriod(0.01);
			mTimer->start();
		}
		else
		{
			selectLayer->setImage(imageName);
		}

	}
}

void UIControl::universalImage( Ogre::TexturePtr& scrTexture,Ogre::TexturePtr& destTexture,Ogre::TexturePtr& universalTexture,Ogre::TexturePtr& convertTexture,int step)
{
	//获取贴图缓冲
	Ogre::HardwarePixelBufferSharedPtr scrBuffer=scrTexture->getBuffer();
	Ogre::HardwarePixelBufferSharedPtr destBuffer=destTexture->getBuffer();
	Ogre::HardwarePixelBufferSharedPtr universalBuffer=universalTexture->getBuffer();
	Ogre::HardwarePixelBufferSharedPtr convertBuffer=convertTexture->getBuffer();

	//给缓冲上锁
	unsigned int* scrIndex=(unsigned int*)scrBuffer->lock(0,scrBuffer->getSizeInBytes(),Ogre::HardwareBuffer::HBL_READ_ONLY);

	unsigned int* destIndex;//防止源与目标一样时,多次锁定
	if (scrBuffer!=destBuffer)
	{
		destIndex=(unsigned int*)destBuffer->lock(0,destBuffer->getSizeInBytes(),Ogre::HardwareBuffer::HBL_READ_ONLY);
	}
	else
	{
		destIndex=scrIndex;
	}

	unsigned int* universalIndex=(unsigned int*)universalBuffer->lock(0,universalBuffer->getSizeInBytes(),Ogre::HardwareBuffer::HBL_READ_ONLY);
	unsigned int* convertIndex=(unsigned int*)convertBuffer->lock(0,convertBuffer->getSizeInBytes(),Ogre::HardwareBuffer::HBL_DISCARD);
	
	TARGB32 scrPixel;
	TARGB32 destPixel;
	TARGB32 universalPixel;
	TARGB32 convertPixel;

	for (int index=0;index<scrBuffer->getWidth()*scrBuffer->getHeight();index++)
	{
		scrPixel.setValue(*scrIndex);
		destPixel.setValue(*destIndex);
		universalPixel.setValue(*universalIndex);

		int Alpha=universalPixel.r;

		Alpha=((step-Alpha)<<8)>>5;// ((step-Alpha)*255)/32

		Alpha=255-Alpha;


		if (Alpha<=0)
		{
			convertPixel.b=destPixel.b;
			convertPixel.g=destPixel.g;
			convertPixel.r=destPixel.r;
			convertPixel.a=destPixel.a;
		}
		else if (Alpha>=255)
		{
			convertPixel.b=scrPixel.b;
			convertPixel.g=scrPixel.g;
			convertPixel.r=scrPixel.r;
			convertPixel.a=scrPixel.a;
		}
		else
		{
			convertPixel.b=(destPixel.b*(255-Alpha) + scrPixel.b*Alpha)>>8;// /256
			convertPixel.g=(destPixel.g*(255-Alpha) + scrPixel.g*Alpha)>>8;
			convertPixel.r=(destPixel.r*(255-Alpha) + scrPixel.r*Alpha)>>8;
			convertPixel.a=(destPixel.a*(255-Alpha) + scrPixel.a*Alpha)>>8;
		}
		
		(*convertIndex)=convertPixel.getValue();
		

		scrIndex++;
		destIndex++;
		universalIndex++;
		convertIndex++;
	}

	scrBuffer->unlock();

	if (scrBuffer!=destBuffer)//防止源与目标一样时多次解锁
	{
		destBuffer->unlock();
	}

	universalBuffer->unlock();
	convertBuffer->unlock();
}

void UIControl::universalImage( Ogre::TexturePtr& destTexture,Ogre::TexturePtr& universalTexture,Ogre::TexturePtr& convertTexture,int step)
{
	Ogre::HardwarePixelBufferSharedPtr destBuffer=destTexture->getBuffer();
	Ogre::HardwarePixelBufferSharedPtr universalBuffer=universalTexture->getBuffer();
	Ogre::HardwarePixelBufferSharedPtr convertBuffer=convertTexture->getBuffer();

	unsigned int* destIndex=(unsigned int*)destBuffer->lock(0,destBuffer->getSizeInBytes(),Ogre::HardwareBuffer::HBL_READ_ONLY);
	unsigned int* universalIndex=(unsigned int*)universalBuffer->lock(0,universalBuffer->getSizeInBytes(),Ogre::HardwareBuffer::HBL_READ_ONLY);
	unsigned int* convertIndex=(unsigned int*)convertBuffer->lock(0,convertBuffer->getSizeInBytes(),Ogre::HardwareBuffer::HBL_DISCARD);

	TARGB32 destPixel;
	TARGB32 universalPixel;
	TARGB32 convertPixel;

	for (int index=0;index<destBuffer->getWidth()*destBuffer->getHeight();index++)
	{
		destPixel.setValue(*destIndex);
		universalPixel.setValue(*universalIndex);

		int Alpha=universalPixel.r;

		Alpha=(step-Alpha)*255/64;

		if (Alpha>=255)
		{
			Alpha=255;
		}
		else
		{
			if (Alpha<=0)
			{
				Alpha=0;
			}
		}

		Alpha=255-Alpha;

		convertPixel.b=destPixel.b*(255-Alpha)/255;
		convertPixel.g=destPixel.g*(255-Alpha)/255;
		convertPixel.r=destPixel.r*(255-Alpha)/255;
		convertPixel.a=destPixel.a*(255-Alpha)/255;

		(*convertIndex)=convertPixel.getValue();

		destIndex++;
		universalIndex++;
		convertIndex++;
	}

	destBuffer->unlock();
	universalBuffer->unlock();
	convertBuffer->unlock();
}

void UIControl::setTextDialog( const UIDialogAttribute& attribute )
{
	mDialog->setPosition(QuickGUI::Point(attribute.DialogLeft,attribute.DialogTop));
	mDialog->setSize(QuickGUI::Size(attribute.DialogWidth,attribute.DialogHeight));
	mDialog->setDefaultColor(QuickGUI::ColourValue(attribute.TextRed,attribute.TextGreen,attribute.TextBlue));
	mDialog->setDefaultFont(attribute.TextFont);
	mDialog->setTextRect(QuickGUI::Rect(attribute.TextLeft,attribute.TextTop,attribute.TextWidth,attribute.TextHeight));
	mDialog->setSkinType("myTextArea");
	
	mRoleName->setPosition(QuickGUI::Point(attribute.RoleNameLeft,attribute.RoleNameTop));
	mRoleName->setSize(QuickGUI::Size(attribute.RoleNameWidth,attribute.RoleNameHeight));
	mRoleName->setDefaultColor(QuickGUI::ColourValue(attribute.RoleNameRed,attribute.RoleNameGreen,attribute.RoleNameBlue));
	mRoleName->setDefaultFont(attribute.RoleFont);
	mRoleName->setSkinType("myLable");
}

void UIControl::showText( std::wstring text,float delay)
{
	if(delay==0)
	{
		mDialog->addText(text.c_str());
	}
	else
	{
		//如果是打字效果,那么启动打字定时器
		mTextBuffer=text;
		mTimerWork=PrinterWork;
		mTimer->setTimePeriod(delay);
		mTimer->start();
	}
}


void UIControl::timerCallback()
{
	switch(mTimerWork)
	{
	case PrinterWork:
		{
			if (!mTextBuffer.empty())
			{
				mDialog->addText(mTextBuffer.substr(0,1).c_str());
				mTextBuffer.erase(mTextBuffer.begin());
			}
			else
			{
				mTimer->stop();
				mTimerWork=NoneWork;
			}
			break;
		}
	case UniversalWork:
		{
			if (mStep<=255)
			{
				if (!mIsNoneScr)
				{
					//universalImage(mScrTexture,mDestTexture,mUniversalTexture,mConvertTexture,mStep);
				}
				else
				{
					universalImage(mDestTexture,mUniversalTexture,mConvertTexture,mStep);
				}
				mUniversalLayer->setRelativeOpacity(h);
				h+=0.05;
			}
			else
			{
				mTimer->stop();
				mTimerWork=NoneWork;
				mUniversalLayer->setImage(mDestTexture->getName());
				Ogre::TextureManager::getSingletonPtr()->remove(mConvertTexture->getName());//移除渐变图像
			}
			mStep+=mTimeSetp;
			break;
		}
	}

}

void UIControl::clearText()
{
	mDialog->clearText();
}

void UIControl::showRoleName( std::wstring text )
{
	mRoleName->setText(text.c_str());
}

void UIControl::setTextDialogVisible( bool visible )
{
	mDialog->setVisible(visible);
	mRoleName->setVisible(visible);
}

bool UIControl::keyPressed( const OIS::KeyEvent &arg )
{
	//将OIS的消息注入到QuickGUI中
	mGUIManager->injectChar(static_cast<Ogre::UTFString::unicode_char>(arg.text));
	mGUIManager->injectKeyDown(static_cast<QuickGUI::KeyCode>(arg.key));

	return true;
}

bool UIControl::keyReleased( const OIS::KeyEvent &arg )
{
	mGUIManager->injectKeyUp(static_cast<QuickGUI::KeyCode>(arg.key));

	return true;
}

bool UIControl::mouseMoved( const OIS::MouseEvent &arg )
{
	mGUIManager->injectMousePosition(arg.state.X.abs, arg.state.Y.abs);

	float z = arg.state.Z.rel;
	if(z != 0)
		mGUIManager->injectMouseWheelChange(z);

	return true;
}

bool UIControl::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
	mGUIManager->injectMouseButtonDown(static_cast<QuickGUI::MouseButtonID>(id));

	return true;
}

bool UIControl::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
	mGUIManager->injectMouseButtonUp(static_cast<QuickGUI::MouseButtonID>(id));

	return true;
}

