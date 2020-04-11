#ifndef EVALUATENODE_H
#define EVALUATENODE_H

#include <XEL/xel_global.h>
#include <XEL/XHashMap.h>
#include <XEL/Variant.h>

class XEL_EXPORT EvaluateNode
{
public:
	EvaluateNode();
	virtual Variant evaluate() const = 0;
	virtual bool isVariable() const = 0;
	virtual ~EvaluateNode();
};

class XEL_EXPORT ValueNode :public EvaluateNode {
public:
	ValueNode();
	virtual Variant evaluate() const;
	virtual bool isVariable() const { return false; }

	Variant value() const;

	void setValue(const Variant& value);
private:
	Variant _value;
};

class XEL_EXPORT VariableNode :public EvaluateNode {
public:
	VariableNode();
	virtual Variant evaluate() const;
	virtual bool isVariable() const { return true; }

	XString variableName() const;
	XHashMap<XString, Variant>* variableTable() const;

	void setVariableName(const XString& variableName);
	void setVariableTable(XHashMap<XString, Variant>* variableTable);
private:
	XString mVariableName;
	XHashMap<XString, Variant>* _variableTable;
};

class XEL_EXPORT UnaryOperatorNode :public EvaluateNode {
public:
	UnaryOperatorNode();
	virtual Variant evaluate() const = 0;
	virtual bool isVariable() const { return false; }

	EvaluateNode* operand() const;
	void setOperand(EvaluateNode* operand);

	virtual ~UnaryOperatorNode();
private:
	EvaluateNode* _operand;
};

class XEL_EXPORT BinaryOperatorNode :public EvaluateNode {
public:
	BinaryOperatorNode();
	virtual Variant evaluate() const = 0;
	virtual bool isVariable() const { return false; }

	EvaluateNode* leftOperand() const;
	void setLeftOperand(EvaluateNode* leftOperand);

	EvaluateNode* rightOperand() const;
	void setRightOperand(EvaluateNode* rightOperand);

	virtual ~BinaryOperatorNode();
private:
	EvaluateNode* _leftOperand;
	EvaluateNode* _rightOperand;
};

class XEL_EXPORT FunctionNode :public EvaluateNode {
public:
	FunctionNode();
	virtual Variant evaluate() const = 0;
	virtual bool isVariable() const { return false; }

	std::vector<EvaluateNode*> parameters() const;
	void setParameters(const std::vector<EvaluateNode*>& parameters);

	virtual ~FunctionNode();
private:
	std::vector<EvaluateNode*> _parameters;
};

class XEL_EXPORT MemberNode :public EvaluateNode {
public:
	MemberNode();
	virtual Variant evaluate() const;
	virtual bool isVariable() const { return true; }

	EvaluateNode* owner() const;
	void setOwner(EvaluateNode* owner);

	XString memberName() const;
	void setMemberName(const XString& memberName);

	virtual ~MemberNode();
private:
	EvaluateNode* _owner;
	XString _memberName;
};

class XEL_EXPORT MemberFunctionNode :public EvaluateNode {
public:
	MemberFunctionNode();
	virtual Variant evaluate() const;
	virtual bool isVariable() const { return false; }

	EvaluateNode* owner() const;
	void setOwner(EvaluateNode* owner);

	XString MemberFunctionName() const;
	void setMemberFunctionName(const XString& MemberFunctionName);

	std::vector<EvaluateNode*> parameters() const;
	void setParameters(const std::vector<EvaluateNode*>& parameters);

	virtual ~MemberFunctionNode();
private:
	EvaluateNode* _owner;
	XString _memberFunctionName;
	std::vector<EvaluateNode*> _parameters;
};

#endif // EVALUATENODE_H
