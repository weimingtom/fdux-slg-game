#ifndef TIMEBAR_H
#define TIMEBAR_H

#include <QWidget>
#include <QMap>
#include <QVector>

struct TimeLine
{
	unsigned int startTime;
	unsigned int endTime;

	unsigned int len()
	{
		return endTime-startTime;
	}
};

class TimeBar : public QWidget
{
	Q_OBJECT

public:
	TimeBar(QWidget *parent);
	~TimeBar();

	void paintEvent( QPaintEvent * event );
	void wheelEvent(QWheelEvent * event);
	void mouseMoveEvent( QMouseEvent * event );
	void mousePressEvent( QMouseEvent * event );
	void mouseReleaseEvent( QMouseEvent * event );

	void addTiemLine(int index,TimeLine* timeLine);
	void removTimeLine(int index,TimeLine* timeLine);

	void setZoom(int zoom);
	void setCurrTime(unsigned int time);

signals:
	void CurrTimeChange(int time);
private:
	int mZoom;

	unsigned int mCurrTime;
	
	QMap<int,QVector<TimeLine*>*> mTimeLine;

	TimeLine* mSelectedTimeLine;

	int mLastX;

	int mToolTipX;
	int mToolTipY;
	QString mToopTip;
	bool mMoveCurrTime;

};


#endif // TIMEBAR_H
