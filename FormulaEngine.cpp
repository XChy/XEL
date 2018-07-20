#include "FormulaEngine.h"

FormulaEngine::FormulaEngine()
	:mContext(new FormulaContext),
	  rootNode(nullptr)
{
}

QString FormulaEngine::expression() const
{
	return mExpression;
}

FormulaContext* FormulaEngine::context() const
{
	return mContext;
}

Variant& FormulaEngine::variable(const QString& name)
{
	return mContext->variableTable()[name];
}

void FormulaEngine::setExpression(QString expression)
{
	mExpression=expression;
}

void FormulaEngine::setContext(FormulaContext* context)
{
	mContext = context;
}

void FormulaEngine::setVariable(const QString& name, const Variant& value)
{
	mContext->variableTable().insert(name,value);
}

void FormulaEngine::removeVariable(QString name)
{
	mContext->variableTable().remove(name);
}

Variant FormulaEngine::evaluate() const
{

}
