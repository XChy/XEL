#ifndef XELERROR_H
#define XELERROR_H

#include <xel_global.h>
#include <XString.h>

class XEL_EXPORT XELError
{
public:
	XELError(XString errorString);
	XString errorString() const;

	void setErrorString(const XString& errorString);
private:
	XString mErrorString;
};

#endif // FORMULAERROR_H
