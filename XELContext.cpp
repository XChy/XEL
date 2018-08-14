#include "XELContext.h"

XELContext::XELContext()
	:mOperatorChars("+-*/^><=|&%!~")
{

}

XString XELContext::operatorChars() const
{
	return mOperatorChars;
}

void XELContext::setOperatorChars(const XString& operatorChars)
{
	mOperatorChars = operatorChars;
}

XHashMap<XString, UnaryOperatorCreator*>& XELContext::unaryOperatorTable()
{
	return mUnaryOperatorTable;
}

void XELContext::setUnaryOperatorTable(const XHashMap<XString, UnaryOperatorCreator*>& unaryOperatorTable)
{
	mUnaryOperatorTable = unaryOperatorTable;
}

XHashMap<XString, BinaryOperatorCreator*>& XELContext::binaryOperatorTable()
{
	return mBinaryOperatorTable;
}

void XELContext::setBinaryOperatorTable(const XHashMap<XString, BinaryOperatorCreator*>& binaryOperatorTable)
{
	mBinaryOperatorTable = binaryOperatorTable;
}

XHashMap<XString, FunctionCreator*>& XELContext::functionTable()
{
	return mFunctionTable;
}

void XELContext::setFunctionTable(const XHashMap<XString, FunctionCreator*>& functionTable)
{
	mFunctionTable = functionTable;
}

XHashMap<XString, Variant>& XELContext::variableTable()
{
    return mVariableTable;
}

void XELContext::setVariableTable(const XHashMap<XString, Variant>& variableTable)
{
    mVariableTable = variableTable;
}
