#include "XELError.h"

XELError::XELError(XString errorString)
{
	_errorString = errorString;
}

XString XELError::errorString() const
{
	return _errorString;
}

void XELError::setErrorString(const XString& error)
{
	_errorString = error;
}
