#ifndef FORMULAERROR_H
#define FORMULAERROR_H

#include <formulaengine_global.h>

class FORMULAENGINESHARED_EXPORT FormulaError
{
public:
	FormulaError(QString errorString);
	QString errorString() const;

	void setErrorString(const QString& errorString);
private:
	QString mErrorString;
};

#endif // FORMULAERROR_H
