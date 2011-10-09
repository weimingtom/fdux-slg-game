#include "renderwindow.h"

#include "IIRoot.h"

#include <QKeyEvent>
#include <QMouseEvent>
#include <QResizeEvent>

IIRenderWindow::IIRenderWindow(QWidget* mWindow):mFpsLable(NULL),mCameraLable(NULL)
{
    mTranslateVector.x=0;
    mTranslateVector.y=0;
    mTranslateVector.z=0;
	this->setMouseTracking(true);
	isPushButton=false;
}

void IIRenderWindow::setMainWindow(QMainWindow* mWindow)
{
	this->mWindow=(MainWindow*)mWindow;
}

void IIRenderWindow::timerEvent(QTimerEvent * event)
{
    mCamera->setPosition(mCamera->getPosition()+(mCamera->getOrientation()*mTranslateVector));
	mFpsLable->setText(QString("FPS:%1").arg(IIRoot::getSingletonPtr()->mWindow->getStatistics().lastFPS));
}

void IIRenderWindow::keyPressEvent(QKeyEvent * event)
{
    switch(event->key())
    {
                case Qt::Key_W:
        {
            mTranslateVector.z=-1;
            break;
        }
                case Qt::Key_S:
        {
            mTranslateVector.z=1;
            break;
        }
                case Qt::Key_A:
        {
            mTranslateVector.x=-1;
            break;
        }
                case Qt::Key_D:
        {
            mTranslateVector.x=1;
            break;
        }
                case Qt::Key_Q:
        {
            mTranslateVector.y=1;
            break;
        }
                case Qt::Key_E:
        {
            mTranslateVector.y=-1;
            break;
        }
                case Qt::Key_H:
        {
            mCamera->setPosition( 40, 300, 580 );
            break;
        }
    }
    QString x;
    x.setNum(mCamera->getPosition().x);
    QString y;
    y.setNum(mCamera->getPosition().y);
    QString z;
    z.setNum(mCamera->getPosition().z);
    mCameraLable->setText("Camera:"+x+","+y+","+z);

	emit cameraMove(mCamera->getPosition().x,mCamera->getPosition().y,mCamera->getPosition().z);
}

void IIRenderWindow::keyReleaseEvent ( QKeyEvent * event )
{
    switch(event->key())
    {
                case Qt::Key_W:
        {
            mTranslateVector.z=0;
            break;
        }
                case Qt::Key_S:
        {
            mTranslateVector.z=0;
            break;
        }
                case Qt::Key_A:
        {
            mTranslateVector.x=0;
            break;
        }
                case Qt::Key_D:
        {
            mTranslateVector.x=0;
            break;
        }
                case Qt::Key_Q:
        {
            mTranslateVector.y=0;
            break;
        }
                case Qt::Key_E:
        {
            mTranslateVector.y=0;
            break;
        }
                case Qt::Key_H:
        {

            break;
        }
    }
}

void IIRenderWindow::mousePressEvent ( QMouseEvent * event )
{
	emit mousePress(event);
	mouseButton=event->button();
	isPushButton=true;
}
void IIRenderWindow::mouseReleaseEvent ( QMouseEvent * event )
{
	emit mouseRelease(event);
	mouseButton=event->button();
	isPushButton=false;
}

void IIRenderWindow::mouseMoveEvent ( QMouseEvent * event )
{
	if(mouseButton==Qt::RightButton && isPushButton)
    {
        QPoint currentPos = event->pos();
        float angleX=0;
        float angleY=0;

        if(mousePos.x() < currentPos.x())
            angleX = -0.01;
        else if(mousePos.x() > currentPos.x())
            angleX = 0.01;
        else
            angleX = 0.00;

        if(mousePos.y() < currentPos.y())
            angleY = -0.01;
        else if(mousePos.y() > currentPos.y())
            angleY = 0.01;
        else
            angleY = 0.00;

        mousePos = currentPos;

        mCamera->yaw(Ogre::Radian(angleX));
        mCamera->pitch(Ogre::Radian(angleY));
    }

	emit mouseMove(event);
}

void IIRenderWindow::resizeEvent( QResizeEvent * event )
{
	IIRoot::getSingletonPtr()->mWindow->resize(event->size().width(),event->size().height());
	IIRoot::getSingletonPtr()->mWindow->windowMovedOrResized();
	
	Ogre::Viewport *vp = IIRoot::getSingletonPtr()->mCamera->getViewport();
	mCamera->setAspectRatio((Ogre::Real)(vp->getActualWidth()) / (Ogre::Real)(vp->getActualHeight()));
}

void IIRenderWindow::setInfoLable( QLabel* FPSLable,QLabel* CameraLable )
{
	mFpsLable=FPSLable;
	mCameraLable=CameraLable;
}

void IIRenderWindow::setCamera( Ogre::Camera* camera )
{
	mCamera=camera;
}
