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
	return mVariableTable->operator [](mVariableName);
}

QString VariableNode::variableName() const
{
	return mVariableName;
}

void VariableNode::setVariableName(const QString& variableName)
{
	mVariableName = variableName;
}

QHash<QString, Variant>* VariableNode::variableTable() const
{
	return mVariableTable;
}

void VariableNode::setVariableTable(QHash<QString, Variant>* variableTable)
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

QList<EvaluateNode*> FunctionNode::parameters() const
{
	return mParameters;
}

void FunctionNode::setParameters(const QList<EvaluateNode*>& parameters)
{
	mParameters = parameters;
}

FunctionNode::~FunctionNode()
{
	qDeleteAll(mParameters);
}
