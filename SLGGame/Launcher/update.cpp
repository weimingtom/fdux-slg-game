#include "update.h"

#include <QSettings>
#include <QMessageBox>
#include <QDir>
#include <QTextStream>
#include <QPainter>

#include <objbase.h>

//#define GET_VERSIONS_URL QString("http://127.0.0.1:8000/fduxupdate/getVersions/?Versions=")
//#define DOWNLOAD_URL QString("http://127.0.0.1:8000/fduxupdate/download/?Versions=%1&GUID=%2")
#define GET_VERSIONS_URL QString("http://1.fduxupdate.duapp.com/fduxupdate/getVersions/?Versions=")
#define DOWNLOAD_URL QString("http://1.fduxupdate.duapp.com/fduxupdate/download/?Versions=%1&GUID=%2")
#define GET_DOWNLOAD_URL QString("http://bcs.duapp.com/")

#include "ZLibWrapLib\ZLibWrapLib.h"

#include <Windows.h>

void DeleteDirFile(QString sPath)
{

	WIN32_FIND_DATA fd;

	HANDLE hFind = ::FindFirstFile(QString(sPath + "*.*").toStdWString().c_str(),&fd);



	if (hFind != INVALID_HANDLE_VALUE)

	{           

		while (::FindNextFile(hFind,&fd))

		{

				DeleteFile((sPath + QString().fromWCharArray(fd.cFileName)).toStdWString().c_str());

		}

		::FindClose(hFind);

	}

	RemoveDirectory(sPath.toStdWString().c_str());

}

update::update(QWidget *parent,Launcher* l)
	: QWidget(parent),mLauncher(l)
{
	ui.setupUi(this);

	QSettings settings("config.ini", QSettings::IniFormat);
	mCurVer=settings.value("Versions").toString();
	mGUID=settings.value("GUID").toString();
	if(mGUID=="")
	{
		static char buf[64] = {0};
		GUID guid;
		_snprintf(buf, sizeof(buf)
				, "{%08X-%04X-%04x-%02X%02X-%02X%02X%02X%02X%02X%02X}"
				, guid.Data1
				, guid.Data2
				, guid.Data3
				, guid.Data4[0], guid.Data4[1]
			, guid.Data4[2], guid.Data4[3], guid.Data4[4], guid.Data4[5]
			, guid.Data4[6], guid.Data4[7]
			);
		mGUID=buf;

		settings.setValue("GUID",mGUID);
	}

	reply = manager.get(QNetworkRequest(QUrl(GET_VERSIONS_URL+mCurVer)));
	connect(reply, SIGNAL(finished()),
		this, SLOT(httpFinished()));
	connect(reply, SIGNAL(readyRead()),
		this, SLOT(httpReadyRead()));
	connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),
		this, SLOT(httpError(QNetworkReply::NetworkError)));
	connect(reply,SIGNAL(downloadProgress(qint64,qint64 )),
		this, SLOT(downloadProgress(qint64,qint64)));

	mSetp=checkVer;
	mReceive="";
	mTempFile=NULL;
	ui.label->setText("检查更新中....");
}

update::~update()
{

}

void update::paintEvent(QPaintEvent * e)
{

	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void update::closeUpdate()
{
	if(mTempFile!=NULL)
	{
		mTempFile->close();
	}
	this->hide();

	QSettings settings("config.ini", QSettings::IniFormat);
	QString ver=settings.value("Versions").toString();
	mLauncher->setWindowTitle(QString("忘却的战场 版本:")+ver);

	mLauncher->show();
}


void update::httpFinished()
{
	switch(mSetp)
	{
	case checkVer:
		{
			if (mReceive=="0" || mReceive=="")
			{
				closeUpdate();
			}
			else
			{
				QStringList list=mReceive.split("|");
				mNewVer=list.at(0);
				mUpdateLog=list.at(3);
				mUpdateLog.replace(" ","\n");

				QMessageBox msgBox;
				msgBox.setWindowTitle("有新更新可用");
				msgBox.setText(QString("有一个新版本可更新,版本号:%1 大小:%2KB").arg(list.at(0)).arg(list.at(2)));
				msgBox.setInformativeText("你想要更新吗?");
				msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
				msgBox.setDefaultButton(QMessageBox::Yes);
				msgBox.setDetailedText(mUpdateLog);
				msgBox.setIcon(QMessageBox::Question);
				int ret = msgBox.exec();
				

				switch(ret)
				{
				case QMessageBox::Yes:
					{
						ui.label->setText("获取下载信息....");
						reply->deleteLater();

						reply = manager.get(QNetworkRequest(QUrl(DOWNLOAD_URL.arg(list.at(0)).arg(mGUID))));
						connect(reply, SIGNAL(finished()),
							this, SLOT(httpFinished()));
						connect(reply, SIGNAL(readyRead()),
							this, SLOT(httpReadyRead()));
						connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),
							this, SLOT(httpError(QNetworkReply::NetworkError)));
						connect(reply,SIGNAL(downloadProgress(qint64,qint64 )),
							this, SLOT(downloadProgress(qint64,qint64)));

						mReceive="";
						mSetp=getDownloadInfo;
						break;
					}
				case QMessageBox::No:
					{
						closeUpdate();
						break;
					}
				}
			}

			break;
		}
	case getDownloadInfo:
		{
			if (mReceive=="0")
			{
				QMessageBox::warning(this,"错误","更新失败,已达到配额限制,请明天再试",QMessageBox::Yes);
				closeUpdate();
			}
			else
			{
				mDownLoadRequest=mReceive;
				ui.label->setText("下载中....");

				reply->deleteLater();

				QString a=GET_DOWNLOAD_URL+mDownLoadRequest;
				QUrl url;
				url.setEncodedUrl(a.toLocal8Bit());
				reply = manager.get(QNetworkRequest(url));
				connect(reply, SIGNAL(finished()),
					this, SLOT(httpFinished()));
				connect(reply, SIGNAL(readyRead()),
					this, SLOT(httpReadyRead()));
				connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),
					this, SLOT(httpError(QNetworkReply::NetworkError)));
				connect(reply,SIGNAL(downloadProgress(qint64,qint64 )),
					this, SLOT(downloadProgress(qint64,qint64)));

				mReceive="";
				mSetp=Download;
				mTempFile=new QFile("patch.tmp");
				if(!mTempFile->open(QIODevice::WriteOnly | QIODevice::Unbuffered))
					closeUpdate();
			}
			break;
		}
	case Download:
		{
			mTempFile->close();
			ui.label->setText("安装中....");

			QDir dir;
			if (dir.exists("./temp"))
			{
				DeleteDirFile("./temp/");
			}

			dir.mkdir("./temp");
			
			if(ZipExtract((LPCTSTR)QString("patch.tmp").toStdWString().c_str(),(LPCTSTR)QString("./temp").toStdWString().c_str()))
			{
				QFile fileList("./temp/list.txt");
				fileList.open(QIODevice::ReadOnly | QIODevice::Text);

				QTextStream in(&fileList);
				while (!in.atEnd()) 
				{
					QString line = in.readLine();
					QStringList list=line.split(",");
					if (QFile::exists(list.at(1)))
					{
						QFile::remove(list.at(1));

						if(!QFile::copy(QString("./temp/")+list.at(0),list.at(1)))
						{
							QMessageBox::warning(this,"错误","更新失败,请联系开发人员.错误原因:拷贝文件错误",QMessageBox::Yes);
							closeUpdate();
							return;
						}
					}
					else
					{
						if(!QFile::copy(QString("./temp/")+list.at(0),list.at(1)))
						{
							QMessageBox::warning(this,"错误","更新失败,请联系开发人员.错误原因:拷贝文件错误",QMessageBox::Yes);
							closeUpdate();
							return;
						}
					}
				}
				fileList.close();
	
				QSettings settings("config.ini", QSettings::IniFormat);
				settings.setValue("Versions",mNewVer);
				DeleteDirFile("./temp/");
				QMessageBox::information(this,"",QString("更新完成,下面是更新日志:\n")+mUpdateLog,QMessageBox::Yes);
				closeUpdate();
			}
			else
			{
				QMessageBox::warning(this,"错误","更新失败,请联系开发人员.错误原因:解压缩失败",QMessageBox::Yes);
				closeUpdate();
			}
		}
	}
}

void update::httpReadyRead()
{
	if (mSetp==checkVer )
	{
		mReceive+=QString::fromUtf8(reply->readAll());
	}
	else if (mSetp==getDownloadInfo)
	{
		mReceive+=QString(reply->readAll());
	}
	else if (mSetp==Download)
	{
		if(mTempFile!=NULL)
			mTempFile->write(reply->readAll());
	}
}

void update::httpError( QNetworkReply::NetworkError )
{
	if(mSetp==Download)
	{
		QMessageBox::warning(this,"","更新失败,请检查网络情况.",QMessageBox::Yes);
	}

	closeUpdate();
}

void update::downloadProgress( qint64 bytesReceived, qint64 bytesTotal )
{
	if (mSetp==Download)
	{
		double v=(double)bytesReceived/(double)bytesTotal;
		ui.progressBar->setValue((int)v*100);
	}
}
