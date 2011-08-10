#ifndef IIROOT_H
#define IIROOT_H
#include <Ogre.h>
#include <OgreTerrain.h>
#include <OgreTerrainGroup.h>
#include "mainwindow.h"
#include "iisingleton.hpp"
#include <QGraphicsView>
#include <QDir>
#include <QMessagebox>
#include <QMap>
#include <QObject>
#include <QTextStream>
#include <QFileDialog>

#include "Terrain.h"

//using namespace Ogre;
using namespace izayoi;

class IIRoot:public IISingleton<IIRoot>
{
    public:
		Ogre::LogManager* logMgr;
        Ogre::Log* log;
        Ogre::Root *mRoot;
        Ogre::Camera* mCamera;
        Ogre::SceneManager* mSceneMgr;
        Ogre::RenderWindow* mWindow;
        Ogre::ResourceGroupManager* mRgm;
        Ogre::Light* mLight;
        QMap<QString,QString> resPathList;

		TerrainSystem* mTerrain;

    public:
        bool setup(QGraphicsView *graphicsView);
        void setupLog(Ogre::LogListener* w);
        bool setupResourcesPath();
        void setResourcePath(QDir* dir,QString secName);
        void setPathToFile(QString dir,QString secName);
		//void setupTerrain(int TERRAIN_SIZE,int TERRAIN_WORLD_SIZE,int BlendMapWorldSize,QString DefaulTexture,QString DefaulNormalMap,int GridSize,int MapGrids);

};
#endif // IIROOT_H
