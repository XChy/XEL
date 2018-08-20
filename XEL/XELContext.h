#ifndef FORMULACONTEXT_H
#define FORMULACONTEXT_H

#include <XEL/xel_global.h>
#include <XEL/XHashMap.h>
#include <XEL/NodeCreator.h>
#include <XEL/Variant.h>

class XEL_EXPORT XELContext
{
public:
	XELContext();
	XString operatorChars() const;
	void setOperatorChars(const XString& operatorChars);

	XHashMap<XString, UnaryOperatorCreator*>& unaryOperatorTable();
	void setUnaryOperatorTable(const XHashMap<XString, UnaryOperatorCreator*>& unaryOperatorTable);

	XHashMap<XString, BinaryOperatorCreator*>& binaryOperatorTable();
	void setBinaryOperatorTable(const XHashMap<XString, BinaryOperatorCreator*>& binaryOperatorTable);

	XHashMap<XString, XELFunction*>& functionTable();
	void setFunctionTable(const XHashMap<XString, XELFunction*>& functionTable);

	XHashMap<XString, Variant>& variableTable();
	void setVariableTable(const XHashMap<XString, Variant>& variableTable);

private:
	XHashMap<XString,Variant> mVariableTable;
	XHashMap<XString,UnaryOperatorCreator*> mUnaryOperatorTable;
	XHashMap<XString,BinaryOperatorCreator*> mBinaryOperatorTable;
	XHashMap<XString,XELFunction*> mFunctionTable;
	XString mOperatorChars;
};

#endif // FORMULACONTEXT_H
