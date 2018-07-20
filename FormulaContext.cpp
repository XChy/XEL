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

QHash<QString, UnaryOperatorCreator*>& FormulaContext::unaryOperatorTable()
{
	return mUnaryOperatorTable;
}

void FormulaContext::setUnaryOperatorTable(const QHash<QString, UnaryOperatorCreator*>& unaryOperatorTable)
{
	mUnaryOperatorTable = unaryOperatorTable;
}

QHash<QString, BinaryOperatorCreator*>& FormulaContext::binaryOperatorTable()
{
	return mBinaryOperatorTable;
}

void FormulaContext::setBinaryOperatorTable(const QHash<QString, BinaryOperatorCreator*>& binaryOperatorTable)
{
	mBinaryOperatorTable = binaryOperatorTable;
}

QHash<QString, FunctionCreator*>& FormulaContext::functionTable()
{
	return mFunctionTable;
}

void FormulaContext::setFunctionTable(const QHash<QString, FunctionCreator*>& functionTable)
{
	mFunctionTable = functionTable;
}

QHash<QString, Variant>& FormulaContext::variableTable()
{
    return mVariableTable;
}

void FormulaContext::setVariableTable(const QHash<QString, Variant>& variableTable)
{
    mVariableTable = variableTable;
}
