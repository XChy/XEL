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
	if(mVariableTable->operator [](mVariableName)){
		return mVariableTable->operator [](mVariableName);
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

std::unordered_map<XString, Variant, XStringHasher>* VariableNode::variableTable() const
{
	return mVariableTable;
}

void VariableNode::setVariableTable(std::unordered_map<XString, Variant, XStringHasher>* variableTable)
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
