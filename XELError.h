#ifndef XELERROR_H
#define XELERROR_H

#include <xel_global.h>

class XEL_EXPORT XELError
{
public:
	XELError(QString errorString);
	QString errorString() const;

	void setErrorString(const QString& errorString);
private:
	QString mErrorString;
};

#endif // FORMULAERROR_H
