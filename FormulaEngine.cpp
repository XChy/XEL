#include "FormulaEngine.h"

FormulaEngine::FormulaEngine()
{
}

void FormulaEngine::setExpression(QString expression)
{
	mExpression=expression;
}

QString FormulaEngine::expression() const
{
	return mExpression;
}

Variant FormulaEngine::evaluate()
{

}
