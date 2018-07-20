#include "FormulaContext.h"

FormulaContext::FormulaContext()
	:mOperatorChars("+-*/^><=|&%!~")
{

}

QString FormulaContext::operatorChars() const
{
	return mOperatorChars;
}

void FormulaContext::setOperatorChars(const QString& operatorChars)
{
	mOperatorChars = operatorChars;
}
