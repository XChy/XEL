#include "XELContext.h"

XELContext::XELContext() : _operatorChars("+-*/^><=|&%!~$#@?") {}

XELContext::~XELContext()
{
    for (auto element : unaryOperatorTable()) {
        delete element.second;
    }
    for (auto element : binaryOperatorTable()) {
        delete element.second;
    }
for (auto element : functionTable()) {
        delete element.second;
    }
}

XString XELContext::operatorChars() const { return _operatorChars; }

void XELContext::setOperatorChars(const XString& operatorChars)
{
    _operatorChars = operatorChars;
}

XHashMap<XString, UnaryOperatorCreator*>& XELContext::unaryOperatorTable()
{
    return _unaryOperatorTable;
}

void XELContext::setUnaryOperatorTable(
    const XHashMap<XString, UnaryOperatorCreator*>& unaryOperatorTable)
{
    _unaryOperatorTable = unaryOperatorTable;
}

XHashMap<XString, BinaryOperatorCreator*>& XELContext::binaryOperatorTable()
{
    return _binaryOperatorTable;
}

void XELContext::setBinaryOperatorTable(
    const XHashMap<XString, BinaryOperatorCreator*>& binaryOperatorTable)
{
    _binaryOperatorTable = binaryOperatorTable;
}

XHashMap<XString, FunctionCreator*>& XELContext::functionTable()
{
    return _functionTable;
}

void XELContext::setFunctionTable(
    const XHashMap<XString, FunctionCreator*>& functionTable)
{
    _functionTable = functionTable;
}

XHashMap<XString, Variant>& XELContext::variableTable()
{
    return _variableTable;
}

void XELContext::setVariableTable(
    const XHashMap<XString, Variant>& variableTable)
{
    _variableTable = variableTable;
}
