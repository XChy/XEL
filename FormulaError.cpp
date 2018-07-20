#include "FormulaError.h"

FormulaError::FormulaError(QString errorString)
{
	mErrorString=errorString;
}

QString FormulaError::errorString() const
{
	return mErrorString;
}

void FormulaError::setErrorString(const QString& error)
{
	mErrorString = error;
}
