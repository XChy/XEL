#ifndef FORMULACONTEXT_H
#define FORMULACONTEXT_H

#include <xel_global.h>
#include <unordered_map>
#include <NodeCreator.h>
#include <Variant.h>

class XEL_EXPORT XELContext
{
public:
	XELContext();
	XString operatorChars() const;
	void setOperatorChars(const XString& operatorChars);

	std::unordered_map<XString, UnaryOperatorCreator*>& unaryOperatorTable();
	void setUnaryOperatorTable(const std::unordered_map<XString, UnaryOperatorCreator*>& unaryOperatorTable);

	std::unordered_map<XString, BinaryOperatorCreator*>& binaryOperatorTable();
	void setBinaryOperatorTable(const std::unordered_map<XString, BinaryOperatorCreator*>& binaryOperatorTable);

	std::unordered_map<XString, FunctionCreator*>& functionTable();
	void setFunctionTable(const std::unordered_map<XString, FunctionCreator*>& functionTable);

	std::unordered_map<XString, Variant>& variableTable();
	void setVariableTable(const std::unordered_map<XString, Variant>& variableTable);

private:
	std::unordered_map<XString,Variant> mVariableTable;
	std::unordered_map<XString,UnaryOperatorCreator*> mUnaryOperatorTable;
	std::unordered_map<XString,BinaryOperatorCreator*> mBinaryOperatorTable;
	std::unordered_map<XString,FunctionCreator*> mFunctionTable;
	XString mOperatorChars;
};

#endif // FORMULACONTEXT_H
