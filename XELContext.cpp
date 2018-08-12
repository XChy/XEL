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

std::unordered_map<XString, UnaryOperatorCreator*, XStringHasher>& XELContext::unaryOperatorTable()
{
	return mUnaryOperatorTable;
}

void XELContext::setUnaryOperatorTable(const std::unordered_map<XString, UnaryOperatorCreator*, XStringHasher>& unaryOperatorTable)
{
	mUnaryOperatorTable = unaryOperatorTable;
}

std::unordered_map<XString, BinaryOperatorCreator*, XStringHasher>& XELContext::binaryOperatorTable()
{
	return mBinaryOperatorTable;
}

void XELContext::setBinaryOperatorTable(const std::unordered_map<XString, BinaryOperatorCreator*, XStringHasher>& binaryOperatorTable)
{
	mBinaryOperatorTable = binaryOperatorTable;
}

std::unordered_map<XString, FunctionCreator*, XStringHasher>& XELContext::functionTable()
{
	return mFunctionTable;
}

void XELContext::setFunctionTable(const std::unordered_map<XString, FunctionCreator*, XStringHasher>& functionTable)
{
	mFunctionTable = functionTable;
}

std::unordered_map<XString, Variant, XStringHasher>& XELContext::variableTable()
{
    return mVariableTable;
}

void XELContext::setVariableTable(const std::unordered_map<XString, Variant, XStringHasher>& variableTable)
{
    mVariableTable = variableTable;
}
