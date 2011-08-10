#include "QTCodeSet.h"

#include <QTextCodec>

QTCodeSet::QTCodeSet(void)
{
	QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
	QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());
	QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
}

QTCodeSet::~QTCodeSet(void)
{
}
