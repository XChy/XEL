#ifndef EVALUATENODE_H
#define EVALUATENODE_H

#include <XEL/xel_global.h>
#include <XEL/XHashMap.h>
#include <XEL/Variant.h>

class XEL_EXPORT EvaluateNode
{
public:
	EvaluateNode();
	virtual Variant evaluate() const=0;
	virtual ~EvaluateNode();
};

class XEL_EXPORT ValueNode:public EvaluateNode{
public:
	ValueNode();
	virtual Variant evaluate() const;

	Variant value() const;

	void setValue(const Variant& value);
private:
	Variant mValue;
};

class XEL_EXPORT VariableNode:public EvaluateNode{
public:
	VariableNode();
	virtual Variant evaluate() const;

	XString variableName() const;
	XHashMap<XString, Variant>* variableTable() const;

	void setVariableName(const XString& variableName);
	void setVariableTable(XHashMap<XString, Variant>* variableTable);
private:
	XString mVariableName;
	XHashMap<XString, Variant>* mVariableTable;
};

class XEL_EXPORT UnaryOperatorNode:public EvaluateNode{
public:
	UnaryOperatorNode();
	virtual Variant evaluate() const=0;

	EvaluateNode* operand() const;
	void setOperand(EvaluateNode* operand);

	virtual ~UnaryOperatorNode();
private:
	EvaluateNode* mOperand;
};

class XEL_EXPORT BinaryOperatorNode:public EvaluateNode{
public:
	BinaryOperatorNode();
	virtual Variant evaluate() const=0;

	EvaluateNode* leftOperand() const;
	void setLeftOperand(EvaluateNode* leftOperand);

	EvaluateNode* rightOperand() const;
	void setRightOperand(EvaluateNode* rightOperand);

	virtual ~BinaryOperatorNode();
private:
	EvaluateNode* mLeftOperand;
	EvaluateNode* mRightOperand;
};

class XEL_EXPORT FunctionNode:public EvaluateNode{
public:
	FunctionNode();
	virtual Variant evaluate() const=0;

	std::vector<EvaluateNode*> parameters() const;
	void setParameters(const std::vector<EvaluateNode*>& parameters);

	virtual ~FunctionNode();
private:
	std::vector<EvaluateNode*> mParameters;
};


#endif // EVALUATENODE_H
