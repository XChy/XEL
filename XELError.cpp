#include "XELError.h"

XELError::XELError(QString errorString)
{
	mErrorString=errorString;
}

QString XELError::errorString() const
{
	return mErrorString;
}

void XELError::setErrorString(const QString& error)
{
	mErrorString = error;
}
