#ifndef CAMERACONTROL_H
#define CAMERACONTROL_H

#include <QObject>

class CameraControl : public QObject
{
	Q_OBJECT

public:
	CameraControl();
	~CameraControl();

public slots:
	void PM_POINTS_action();
	void PM_WIREFRAME_action();
	void PM_SOLID_action();

private:
	
};

#endif // CAMERACONTROL_H
