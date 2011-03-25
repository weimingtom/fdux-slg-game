#include "BillboardManager.h"

#include "Core.h"

#define RTT_WIDTH 256.0
#define WIDGET_WIDTH 128.0
#define WIDGET_HEIGHT 64.0
#define RTT_ROWS RTT_WIDTH/WIDGET_WIDTH
#define RTT_COLUMNS RTT_WIDTH/WIDGET_HEIGHT

BillboardManager::BillboardManager(void):
mIndex(0),mRow(0),mColumn(1)
{
	MyGUI::VectorWidgetPtr p=MyGUI::LayoutManager::getInstance().loadLayout("RTT.layout");
	BaseWidget=static_cast<MyGUI::ImageBox*>(p.at(0));
	Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().create("RTTMat", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	Ogre::Technique* technique = material->createTechnique();
	technique->createPass();
	material->getTechnique(0)->getPass(0)->createTextureUnitState("RTTTexture1");
}

BillboardManager::~BillboardManager(void)
{
}

Ogre::BillboardSet* BillboardManager::getBillboardSet()
{
	mIndex++;
	if (mRow<RTT_COLUMNS)
	{
		mRow++;
	}
	else
	{
		if(mColumn<RTT_COLUMNS)
		{
			mColumn++;
			mRow=0;
		}
		else
		{
			Ogre::LogManager::getSingletonPtr()->logMessage("RTTLayer is Full!",Ogre::LML_CRITICAL);
			return NULL;
		}
	}
	
	MyGUI::Button* button=BaseWidget->createWidget<MyGUI::Button>("Button", MyGUI::IntCoord((mRow-1)*WIDGET_WIDTH, (mColumn-1)*WIDGET_HEIGHT,WIDGET_WIDTH,WIDGET_HEIGHT), MyGUI::Align::Left | MyGUI::Align::Top);
	button->setCaption("Test"+Ogre::StringConverter::toString(mIndex));

	Ogre::BillboardSet* BBSet = Core::getSingletonPtr()->mSceneMgr->createBillboardSet("BBSet_"+Ogre::StringConverter::toString(mIndex), 1);
	BBSet->setMaterialName("RTTMat");
	BBSet->setDefaultDimensions(8,4);
	Ogre::Billboard* bb = BBSet->createBillboard(Ogre::Vector3(0,  20,  0));
	
	Ogre::FloatRect coords((mRow-1)*WIDGET_WIDTH/RTT_WIDTH,(mColumn-1)*WIDGET_WIDTH/RTT_WIDTH,mRow*WIDGET_WIDTH/RTT_WIDTH, mColumn*WIDGET_HEIGHT/RTT_WIDTH);
	bb->setTexcoordRect(coords);
	return BBSet;
}
