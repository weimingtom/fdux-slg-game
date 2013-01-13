#include "IIRoot.h"

#include "renderwindow.h"

bool IIRoot::setup(QGraphicsView *graphicsView)
{
    bool rtn=false;
    mRoot = new Ogre::Root("Plugins.cfg","ogre.cfg","log.txt");
    if(!mRoot->restoreConfig())
    {
        rtn=mRoot->showConfigDialog();
    }
    else
    {
        rtn=true;
    }
    if (rtn)
    {
      mRoot->saveConfig();
      mRoot->initialise(false);

      Ogre::NameValuePairList params;
      params["externalWindowHandle"] = Ogre::StringConverter::toString((size_t)(HWND)graphicsView->winId());
      mWindow = mRoot->createRenderWindow("View",graphicsView->width(),graphicsView->height(), false, &params);

      if(!setupResourcesPath())
      {
          return false;
      }

	  Ogre::ResourceGroupManager::getSingletonPtr()->initialiseAllResourceGroups();

	  mSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC);
      mRgm=Ogre::ResourceGroupManager::getSingletonPtr();

      mCamera = mSceneMgr->createCamera("PlayerCam");
      mCamera->setPosition(Ogre::Vector3(0,20,100));
      mCamera->lookAt(Ogre::Vector3(0,0,0));
      mCamera->setNearClipDistance(5);
	  ((IIRenderWindow*)graphicsView)->setCamera(mCamera);

      Ogre::Viewport* vp = mWindow->addViewport(mCamera);
      mCamera->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));

      mSceneMgr->setAmbientLight(Ogre::ColourValue(0.25f, 0.25f, 0.25f));
	  mSceneMgr->setShadowTechnique(Ogre::SHADOWDETAILTYPE_STENCIL);
      mLight=mSceneMgr->createLight("MainLight");
	  mLight->setPosition(-500.0f,500.0f, 500.0f);
	  mLight->setDirection(1.0f, -1.0f, -1.0f);
	  mLight->setCastShadows(true);
	  mLight->setDiffuseColour(Ogre::ColourValue(1.0f, 1.0f,1.0f));

	  mTerrain=new TerrainSystem(mSceneMgr,mWindow,mCamera);

      return true;
    }
    else
    {
        return false;
    }
}

//void IIRoot::setupTerrain(int TERRAIN_SIZE,int TERRAIN_WORLD_SIZE,int BlendMapWorldSize,QString DefaulTexture,QString DefaulNormalMap,int GridSize,int MapGrids)
//{
//
//	MaterialManager::getSingleton().setDefaultTextureFiltering(TFO_ANISOTROPIC);
//	MaterialManager::getSingleton().setDefaultAnisotropy(7);
//
//	//地形全局配置
//	mTerrainGlobals = new TerrainGlobalOptions();
//    mTerrainGlobals->setMaxPixelError(8);
//    mTerrainGlobals->setCompositeMapDistance(3000);
//    mTerrainGlobals->setLightMapDirection(mLight->getDerivedDirection());//设置光线的方向，所有地形块均采用同一个方向的光
//    mTerrainGlobals->setCompositeMapAmbient(mSceneMgr->getAmbientLight());//设置环境光
//    mTerrainGlobals->setCompositeMapDiffuse(mLight->getDiffuseColour());//设置漫反射光
//    mTerrainGlobals->setLightMapSize(TERRAIN_SIZE); //设置光线图的大小，这个数字越小，地图的阴影将越粗糙
//
//	//创建地形分组对象，该对象用于创建以及管理地形块
//	mTerrainGroup = new TerrainGroup(mSceneMgr, Ogre::Terrain::ALIGN_X_Z, TERRAIN_SIZE, TERRAIN_WORLD_SIZE);//场景管理器、地形的平铺方向、地形的大小
//    mTerrainGroup->setOrigin(Ogre::Vector3(0,0,0)); //设置了该地形组的起始位置，在以后创建的地形块中均采用此位置作为相对位置
//
//	/*
//	有了地形分组之后，我们就可以通过地形分组创建地形块了，但是每一个地形块都有很多属性，我们可以在创建地形块的同时设置那些属性，但是这样极为不方便。所以，我们可以先设置默认的地形块属性，那么创建地形块的时候就可以一个方法搞定了*/
//
//    //设置地形默认属性
//    Ogre::Terrain::ImportData& defaultimp = mTerrainGroup->getDefaultImportSettings();
//    defaultimp.terrainSize = TERRAIN_SIZE;
//    defaultimp.worldSize = TERRAIN_WORLD_SIZE;
//    defaultimp.inputScale = 600;//输入缩放
//    defaultimp.minBatchSize = 33;
//    defaultimp.maxBatchSize = 65;
//    //设置纹理 
//    defaultimp.layerList.resize(1);
//    defaultimp.layerList[0].worldSize = BlendMapWorldSize;
//	defaultimp.layerList[0].textureNames.push_back(DefaulTexture.toLatin1().data());//默认贴图
//	defaultimp.layerList[0].textureNames.push_back(DefaulNormalMap.toLatin1().data());//默认法线贴图
//
//	/*下面是网格的创建,主要是创建一个面,然后设置成网格*/
//	grid=new Grid(mSceneMgr,MapGrids,MapGrids,GridSize,Ogre::ColourValue::White);
//	grid->setPosition(Ogre::Vector3(0,0.5,0));
//}

void IIRoot::setupLog(Ogre::LogListener* w)
{
    logMgr = new Ogre::LogManager();
    log=logMgr->createLog("mylog.log", true, false, true);
    log->addListener(w);
    logMgr->setLogDetail(Ogre::LL_NORMAL);
}

void IIRoot::setPathToFile(QString dir,QString secName)
{
        QFile resFile("setting.cfg");
         if (!resFile.open(QFile::ReadOnly | QFile::Text)) {
             QMessageBox::warning(0, "Scene Editor","Cannot open file");
             return;
         }
         QTextStream in(&resFile);

         QFile tempFile("temp.cfg");
         if (!tempFile.open(QFile::WriteOnly | QFile::Text)) {
             QMessageBox::warning(0, "Scene Editor","Cannot open file");
             return;
         }
         QTextStream out(&tempFile);

         while(!in.atEnd())
         {
             QString data=in.readLine();
             if(data=="["+secName+"]")
             {
                 out<<"["+secName+"]"<<endl;
                 out<<"Path="<<dir<<endl;
                 data=in.readLine();
             }
             else
             {
                 out<<data<<endl;
             }
         }
        resFile.close();
        resFile.remove();
		tempFile.close();
        tempFile.rename("temp.cfg","setting.cfg");
}

void IIRoot::setResourcePath(QDir* dir,QString secName)
{
    QFileInfoList fileList=dir->entryInfoList(QDir::Dirs);
    fileList.removeAt(1);//移除 ..
    if(!fileList.isEmpty())
    {
        for(int i=0;i<fileList.count();i++)
        {
                QString path=fileList.at(i).filePath();
                path.replace("/", "\\");
				Ogre::ResourceGroupManager::getSingletonPtr()->addResourceLocation(std::string(path.toLatin1().data()),"FileSystem",std::string(secName.toLatin1().data()));
                if(path.right(1)!=".")//防止产生递归
                {
                    setResourcePath(new QDir(fileList.at(i).filePath()),secName);
                }
        }
    }
//    delete dir;
}

bool IIRoot::setupResourcesPath()
{
	Ogre::ConfigFile cf;

	cf.load("resources.cfg");

	// Go through all sections & settings in the file

	Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();

	Ogre::String secName, typeName, archName;

	while (seci.hasMoreElements())

	{

		secName = seci.peekNextKey();

		Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();

		Ogre::ConfigFile::SettingsMultiMap::iterator i;

		for (i = settings->begin(); i != settings->end(); ++i)

		{

			typeName = i->first;

			archName = i->second;

			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(

				archName, typeName, secName);

		}

	}
    return true;
}