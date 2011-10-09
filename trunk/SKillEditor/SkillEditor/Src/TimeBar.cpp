#include "TimeBar.h"

#include <QPaintEvent>
#include <QWheelEvent>
#include <QPainter>
#include <QPointF>
#include <QRectF>
#include <QFontMetrics>

#include <QtDebug>

const int MIN_SCALE_SIZE=5;

TimeBar::TimeBar(QWidget *parent)
	: QWidget(parent),mZoom(250),mSelectedTimeLine(NULL),mToolTipX(0),mToolTipY(0)
{
	setCurrTime(1000);
}

TimeBar::~TimeBar()
{

}

void TimeBar::paintEvent( QPaintEvent * event )
{
	QPen pen(QColor(0,0,0));
	QPen GrayPen(QColor(0,0,0,50));
	QBrush bush(QColor(0,0,0,70));
	QPainter painter(this);
	pen.setWidth(1);
	painter.setPen(pen);
	painter.setBrush(bush);

	for(int i=0;i<100;i++)
	{
		if (mZoom*i<=event->rect().right())
		{
			//绘制大刻度
			painter.drawLine(QPointF(mZoom*i,15),QPointF(mZoom*i,25));
			painter.drawText(QPointF(mZoom*i,10),QString("%1.0S").arg(i));
			
			//绘制小刻度
			for (int j=1;j<mZoom/MIN_SCALE_SIZE;j++)
			{
				painter.drawLine(QPointF(MIN_SCALE_SIZE*j+mZoom*i,20),QPointF(MIN_SCALE_SIZE*j+mZoom*i,25));
			}

			//绘制TimeLine
			QMapIterator<int,QVector<TimeLine*>*> mapIt(mTimeLine);
			while (mapIt.hasNext()) 
			{
				mapIt.next();
				
				for (QVector<TimeLine*>::const_iterator it=mapIt.value()->begin();it!=mapIt.value()->end();it++)
				{
					if ((*it)->startTime>=i*1000 && (*it)->startTime<=(i+1)*1000)
					{
						//计算TimeLine起始位置
						
						float startX=mZoom*((*it)->startTime/1000.0);
						painter.drawRoundedRect (QRectF(startX,28+mapIt.key()*15+mapIt.key()*3,mZoom*((*it)->len()/1000.0),15),5,3);
					}
				}
				
			}

			//绘制对齐线
			painter.setPen(GrayPen);
			painter.drawLine(QPointF(mZoom*i,15),QPointF(mZoom*i,event->rect().bottom()));
			painter.setPen(pen);
		}
		else
		{
			break;
		}
	}
	
	//绘制当前位置
	QPen redPen(QColor(255,0,0,125));
	painter.setPen(redPen);
	painter.setBrush(QBrush(QColor(255,0,0,125)));
	float startX=mZoom*(mCurrTime/1000.0);
	
	painter.drawLine(QPointF(startX,25),QPointF(startX,event->rect().bottom()));
	painter.drawRect(QRect(startX-3,10,6,15));

	//绘制工具提示
	
	if(!mToopTip.isEmpty())
	{
		redPen.setColor(QColor(255,0,0));
		painter.setBrush(QBrush(QColor(255,255,255)));
		painter.setPen(redPen);
		QFontMetrics fm(painter.font());
		painter.drawRect(QRect(mToolTipX-3,mToolTipY-fm.height(),fm.width(mToopTip)+3,fm.height()+6));
		painter.drawText(mToolTipX,mToolTipY,mToopTip);
	}

		
}

void TimeBar::wheelEvent(QWheelEvent* event)
{
	int numDegrees = event->delta() / 8;
	int numSteps = numDegrees / 15;
		
	if (mZoom+numSteps*10>=50 && mZoom+numSteps*10<=500)
	{
		setZoom(mZoom+numSteps*10);

		repaint();
	}

}

void TimeBar::mousePressEvent( QMouseEvent * event )
{
	if (event->y()<=25)
	{
		//如果小于25,那么就是移动当前位置
		mMoveCurrTime=true;
		float x=event->x();
		x=x/mZoom*1000;
		setCurrTime(x);
		mToopTip=QString("CurrTime:%1").arg(x);
		mToolTipX=event->x()+10;
		mToolTipY=event->y()+5;
		repaint();
	}
	else
	{
		if (mSelectedTimeLine!=NULL)
		{
			return;
		}

		//检查是否选中某个TimeLine
		QMapIterator<int,QVector<TimeLine*>*> mapIt(mTimeLine);
		while (mapIt.hasNext()) 
		{
			mapIt.next();

			for (QVector<TimeLine*>::const_iterator it=mapIt.value()->begin();it!=mapIt.value()->end();it++)
			{
					//计算TimeLine起始位置
					float startX=mZoom*((*it)->startTime/1000.0);
					QRectF rect(startX,28+mapIt.key()*15+mapIt.key()*3,mZoom*((*it)->len()/1000.0),15);
					if (rect.contains(event->posF()))
					{
						mSelectedTimeLine=(*it);
						break;
					}
			}

			if (mSelectedTimeLine!=NULL)
			{
				setCursor(QCursor(Qt::ClosedHandCursor));
				mLastX=event->x();
				break;
			}

		}
	}
}

void TimeBar::mouseMoveEvent( QMouseEvent * event )
{
	if (mSelectedTimeLine!=NULL)
	{
		int offect=(event->x()-mLastX)/(float)mZoom*1000;
		mLastX=event->x();
		int startTime=mSelectedTimeLine->startTime;
		if (startTime+offect>=0)
		{
			mSelectedTimeLine->startTime+=offect;
			mSelectedTimeLine->endTime+=offect;
			mToopTip=QString(tr("Start:%1,End:%2")).arg(mSelectedTimeLine->startTime).arg(mSelectedTimeLine->endTime);
			mToolTipX=event->x()+5;
			mToolTipY=event->y()-5;
			repaint();
		}
	}
	else if (mMoveCurrTime)
	{
		float x=event->x();
		x=x/mZoom*1000;
		if (x<0)
		{
			x=0;
		}
		setCurrTime(x);
		mToopTip=QString(tr("CurrTime:%1")).arg(x);
		mToolTipX=event->x()+10;
		if (mToolTipX<0)
		{
			mToolTipX=0;
		}
		mToolTipY=event->y()+5;
		repaint();
	}
}

void TimeBar::mouseReleaseEvent( QMouseEvent * event )
{
	if (mSelectedTimeLine!=NULL)
	{
		mSelectedTimeLine=NULL;
		setCursor(QCursor(Qt::ArrowCursor));
	}
	mMoveCurrTime=false;
	mToopTip.clear();
	repaint();
}

void TimeBar::setZoom( int zoom )
{
	mZoom=zoom;
}

void TimeBar::setCurrTime( unsigned int time )
{
	mCurrTime=time;
	emit CurrTimeChange(mCurrTime);
}

void TimeBar::addTiemLine( int index,TimeLine* timeLine)
{
	if (mTimeLine.contains(index))
	{
		mTimeLine.value(index)->append(timeLine);
	}
	else
	{
		QVector<TimeLine*>* v=new QVector<TimeLine*>();
		v->append(timeLine);
		mTimeLine[index]=v;
	}
}

void TimeBar::removTimeLine( int index,TimeLine* timeLine )
{
	if (mTimeLine.contains(index))
	{
		mTimeLine.value(index)->remove(mTimeLine.value(index)->indexOf(timeLine));

		if (mTimeLine.value(index)->isEmpty())
		{
			delete mTimeLine.value(index);
			mTimeLine.remove(index);
		}
	}
}
