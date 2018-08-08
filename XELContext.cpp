#include "XELContext.h"

XELContext::XELContext()
	:mOperatorChars("+-*/^><=|&%!~")
{

}

QString XELContext::operatorChars() const
{
	return mOperatorChars;
}

void XELContext::setOperatorChars(const QString& operatorChars)
{
	mOperatorChars = operatorChars;
}

QHash<QString, UnaryOperatorCreator*>& XELContext::unaryOperatorTable()
{
	return mUnaryOperatorTable;
}

void XELContext::setUnaryOperatorTable(const QHash<QString, UnaryOperatorCreator*>& unaryOperatorTable)
{
	mUnaryOperatorTable = unaryOperatorTable;
}

QHash<QString, BinaryOperatorCreator*>& XELContext::binaryOperatorTable()
{
	return mBinaryOperatorTable;
}

void XELContext::setBinaryOperatorTable(const QHash<QString, BinaryOperatorCreator*>& binaryOperatorTable)
{
	mBinaryOperatorTable = binaryOperatorTable;
}

QHash<QString, FunctionCreator*>& XELContext::functionTable()
{
	return mFunctionTable;
}

void XELContext::setFunctionTable(const QHash<QString, FunctionCreator*>& functionTable)
{
	mFunctionTable = functionTable;
}

QHash<QString, Variant>& XELContext::variableTable()
{
    return mVariableTable;
}

void XELContext::setVariableTable(const QHash<QString, Variant>& variableTable)
{
    mVariableTable = variableTable;
}
