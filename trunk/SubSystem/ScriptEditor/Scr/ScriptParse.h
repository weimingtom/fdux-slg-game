#pragma once

#include <QString>
#include <QVector>
#include <QStringList>

class ScriptParse
{
public:
	ScriptParse(void);
	~ScriptParse(void);

	QString parse(QString text);

	bool hasError();
	
private:

	struct Role
	{
		QString name;
		QStringList param;
		QString lua;
	};

	QString orderParse(QString text);
	
	QVector<Role> mRoles;
	QStringList mResult;
	QString mError;
	QString mTextBuffer;
};
