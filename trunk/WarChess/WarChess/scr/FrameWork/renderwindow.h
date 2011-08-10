#ifndef RENDERWINDOW_H
#define RENDERWINDOW_H

#include <UTILITY>

#include <QGraphicsView>
#include <QStatusBar>
#include <QMainWindow>
#include <QLabel>

#include <Ogre.h>

class MainWindow;
class IIRenderWindow : public QGraphicsView
{
	Q_OBJECT

signals:
	void mouseMove(QMouseEvent * event );
	void mousePress( QMouseEvent * event );
	void mouseRelease( QMouseEvent * event );

	void cameraMove(float x,float y,float z);
public:
    IIRenderWindow(QWidget* mWindow);

    void keyReleaseEvent( QKeyEvent * event );
    void keyPressEvent(QKeyEvent * event);
    void timerEvent(QTimerEvent * event);
    void mouseMoveEvent ( QMouseEvent * event );
    void mousePressEvent ( QMouseEvent * event );
    void mouseReleaseEvent ( QMouseEvent * event );
	void resizeEvent( QResizeEvent * event );

	void setMainWindow(QMainWindow* mWindow);
	void setInfoLable(QLabel* FPSLable,QLabel* CameraLable);
	void setCamera(Ogre::Camera* camera);
private:
    Ogre::Vector3 mTranslateVector;
	Ogre::Camera* mCamera;
    MainWindow* mWindow;
    QPoint mousePos;
    Ogre::Vector3 pos;
	Qt::MouseButton mouseButton;
	bool isPushButton;
	QLabel* mFpsLable;
	QLabel* mCameraLable;

};
#endif // RENDERWINDOW_H
