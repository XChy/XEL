#include "EvaluateNode.h"

EvaluateNode::EvaluateNode()
{
}

EvaluateNode::~EvaluateNode()
{
}

ValueNode::ValueNode()
	:EvaluateNode()
{}

Variant ValueNode::evaluate() const
{
	return mValue;
}

Variant ValueNode::value() const
{
	return mValue;
}

void ValueNode::setValue(const Variant& value)
{
	mValue = value;
}

VariableNode::VariableNode()
	:EvaluateNode(),
	  mVariableTable(nullptr)
{

}

Variant VariableNode::evaluate() const
{
	if(mVariableTable->contains(mVariableName)){
		return mVariableTable->value(mVariableName);
	}else{
		throw XELError("No variable called "+mVariableName);
	}
}

XString VariableNode::variableName() const
{
	return mVariableName;
}

void VariableNode::setVariableName(const XString& variableName)
{
	mVariableName = variableName;
}

XHashMap<XString, Variant>* VariableNode::variableTable() const
{
	return mVariableTable;
}

void VariableNode::setVariableTable(XHashMap<XString, Variant>* variableTable)
{
	mVariableTable = variableTable;
}

UnaryOperatorNode::UnaryOperatorNode()
	:EvaluateNode(),
	  mOperand(nullptr)
{

}

EvaluateNode* UnaryOperatorNode::operand() const
{
	return mOperand;
}

void UnaryOperatorNode::setOperand(EvaluateNode* operand)
{
	mOperand = operand;
}


UnaryOperatorNode::~UnaryOperatorNode()
{
	delete mOperand;
}


BinaryOperatorNode::BinaryOperatorNode()
	:EvaluateNode(),
	  mLeftOperand(nullptr),
	  mRightOperand(nullptr)
{

}

EvaluateNode* BinaryOperatorNode::leftOperand() const
{
	return mLeftOperand;
}

void BinaryOperatorNode::setLeftOperand(EvaluateNode* leftOperand)
{
	mLeftOperand = leftOperand;
}

EvaluateNode* BinaryOperatorNode::rightOperand() const
{
	return mRightOperand;
}

void BinaryOperatorNode::setRightOperand(EvaluateNode* rightOperand)
{
	mRightOperand = rightOperand;
}

BinaryOperatorNode::~BinaryOperatorNode()
{
	delete mLeftOperand;
	delete mRightOperand;
}

FunctionNode::FunctionNode()
	:EvaluateNode()
{}

std::vector<EvaluateNode*> FunctionNode::parameters() const
{
	return mParameters;
}

void FunctionNode::setParameters(const std::vector<EvaluateNode*>& parameters)
{
	mParameters = parameters;
}

FunctionNode::~FunctionNode()
{
	for(auto it=parameters().begin();it!=parameters().end();++it){
		delete *it;
	}
}

MemberNode::MemberNode()
	:mOwner(nullptr)
{

}

Variant MemberNode::evaluate() const
{
	return mOwner->evaluate().convertObject().member(mMemberName);
}

EvaluateNode* MemberNode::owner() const
{
	return mOwner;
}

void MemberNode::setOwner(EvaluateNode* owner)
{
	mOwner = owner;
}

XString MemberNode::memberName() const
{
	return mMemberName;
}

void MemberNode::setMemberName(const XString& memberName)
{
	mMemberName = memberName;
}

MemberNode::~MemberNode()
{
	delete mOwner;
}

MemberFunctionNode::MemberFunctionNode()
	:mOwner(nullptr)
{

}

Variant MemberFunctionNode::evaluate() const
{
	std::vector<Variant> variants;
	for(EvaluateNode* node:parameters()){
		variants.push_back(node->evaluate());
	}
	return mOwner->evaluate().convertObject().invoke(mMemberFunctionName,variants);
}

EvaluateNode* MemberFunctionNode::owner() const
{
	return mOwner;
}

void MemberFunctionNode::setOwner(EvaluateNode* owner)
{
	mOwner = owner;
}

XString MemberFunctionNode::MemberFunctionName() const
{
	return mMemberFunctionName;
}

void MemberFunctionNode::setMemberFunctionName(const XString& MemberFunctionName)
{
	mMemberFunctionName = MemberFunctionName;
}

std::vector<EvaluateNode*> MemberFunctionNode::parameters() const
{
	return mParameters;
}

void MemberFunctionNode::setParameters(const std::vector<EvaluateNode*>& parameters)
{
	mParameters = parameters;
}

MemberFunctionNode::~MemberFunctionNode()
{
	for(auto it=parameters().begin();it!=parameters().end();++it){
		delete *it;
	}
	delete mOwner;
}
