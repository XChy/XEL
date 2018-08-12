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

	std::unordered_map<XString, UnaryOperatorCreator*, XStringHasher>& unaryOperatorTable();
	void setUnaryOperatorTable(const std::unordered_map<XString, UnaryOperatorCreator*, XStringHasher>& unaryOperatorTable);

	std::unordered_map<XString, BinaryOperatorCreator*, XStringHasher>& binaryOperatorTable();
	void setBinaryOperatorTable(const std::unordered_map<XString, BinaryOperatorCreator*, XStringHasher>& binaryOperatorTable);

	std::unordered_map<XString, FunctionCreator*, XStringHasher>& functionTable();
	void setFunctionTable(const std::unordered_map<XString, FunctionCreator*, XStringHasher>& functionTable);

	std::unordered_map<XString, Variant, XStringHasher>& variableTable();
	void setVariableTable(const std::unordered_map<XString, Variant, XStringHasher>& variableTable);

private:
	std::unordered_map<XString,Variant, XStringHasher> mVariableTable;
	std::unordered_map<XString,UnaryOperatorCreator*, XStringHasher> mUnaryOperatorTable;
	std::unordered_map<XString,BinaryOperatorCreator*, XStringHasher> mBinaryOperatorTable;
	std::unordered_map<XString,FunctionCreator*, XStringHasher> mFunctionTable;
	XString mOperatorChars;
};

#endif // FORMULACONTEXT_H
