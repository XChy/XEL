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
	virtual bool isVariable() const=0;
	virtual void setVariable(const Variant& v)=0;
	virtual ~EvaluateNode();
};

class XEL_EXPORT ValueNode:public EvaluateNode{
public:
	ValueNode();
	virtual Variant evaluate() const;
	virtual bool isVariable() const{return false;}
	virtual void setVariable(const Variant& v){throw XELError("value cannot be a variable");}

	Variant value() const;

	void setValue(const Variant& value);
private:
	Variant mValue;
};

class XEL_EXPORT VariableNode:public EvaluateNode{
public:
	VariableNode();
	virtual Variant evaluate() const;
	virtual bool isVariable() const{return true;}
	virtual void setVariable(const Variant& v){
		mVariableTable->insert(mVariableName,v);
	}

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
	virtual bool isVariable() const{return false;}
	virtual void setVariable(const Variant& v){throw XELError("Operator cannot be a variable");}

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
	virtual bool isVariable() const{return false;}
	virtual void setVariable(const Variant& v){throw XELError("Operator cannot be a variable");}

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
	virtual bool isVariable() const{return false;}
	virtual void setVariable(const Variant& v){throw XELError("Function cannot be a variable");}

	std::vector<EvaluateNode*> parameters() const;
	void setParameters(const std::vector<EvaluateNode*>& parameters);

	virtual ~FunctionNode();
private:
	std::vector<EvaluateNode*> mParameters;
};

class XEL_EXPORT MemberNode:public EvaluateNode{
public:
	MemberNode();
	virtual Variant evaluate() const;
	virtual bool isVariable() const{return true;}
	virtual void setVariable(const Variant& v)
	{
		mOwner->evaluate().convertObject().setMember(memberName(),v);
	}

	EvaluateNode* owner() const;
	void setOwner(EvaluateNode* owner);

	XString memberName() const;
	void setMemberName(const XString& memberName);

	virtual ~MemberNode();
private:
	EvaluateNode* mOwner;
	XString mMemberName;
};

class XEL_EXPORT MemberFunctionNode:public EvaluateNode{
public:
	MemberFunctionNode();
	virtual Variant evaluate() const;
	virtual bool isVariable() const{return false;}
	virtual void setVariable(const Variant& v){throw XELError("member function cannot be a variable");}

	EvaluateNode* owner() const;
	void setOwner(EvaluateNode* owner);

	XString MemberFunctionName() const;
	void setMemberFunctionName(const XString& MemberFunctionName);

	std::vector<EvaluateNode*> parameters() const;
	void setParameters(const std::vector<EvaluateNode*>& parameters);

	virtual ~MemberFunctionNode();
private:
	EvaluateNode* mOwner;
	XString mMemberFunctionName;
	std::vector<EvaluateNode*> mParameters;
};

#endif // EVALUATENODE_H
