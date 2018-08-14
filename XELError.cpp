#include "XELError.h"

XELError::XELError(XString errorString)
{
	mErrorString=errorString;
}

XString XELError::errorString() const
{
	return mErrorString;
}

void XELError::setErrorString(const XString& error)
{
	mErrorString = error;
}
