#include "EvaluateNode.h"
#include <vector>

using namespace XEL;

EvaluateNode::EvaluateNode() {}

EvaluateNode::~EvaluateNode() {}

ValueNode::ValueNode() : EvaluateNode() {}

Variant ValueNode::evaluate() const { return _value; }

Variant ValueNode::value() const { return _value; }

void ValueNode::setValue(const Variant &value) { _value = value; }

VariableNode::VariableNode() : EvaluateNode(), _variableTable(nullptr) {}

Variant VariableNode::evaluate() const
{
    if (_variableTable->contains(mVariableName)) {
        return _variableTable->value(mVariableName);
    } else {
        throw XELError("No variable called " + mVariableName);
    }
}

XString VariableNode::variableName() const { return mVariableName; }

void VariableNode::setVariableName(const XString &variableName)
{
    mVariableName = variableName;
}

XHashMap<XString, Variant> *VariableNode::variableTable() const
{
    return _variableTable;
}

void VariableNode::setVariableTable(XHashMap<XString, Variant> *variableTable)
{
    _variableTable = variableTable;
}

UnaryOperatorNode::UnaryOperatorNode() : EvaluateNode(), _operand(nullptr) {}

EvaluateNode *UnaryOperatorNode::operand() const { return _operand; }

void UnaryOperatorNode::setOperand(EvaluateNode *operand)
{
    _operand = operand;
}

UnaryOperatorNode::~UnaryOperatorNode() { delete _operand; }

BinaryOperatorNode::BinaryOperatorNode()
    : EvaluateNode(), _leftOperand(nullptr), _rightOperand(nullptr)
{
}

EvaluateNode *BinaryOperatorNode::leftOperand() const { return _leftOperand; }

void BinaryOperatorNode::setLeftOperand(EvaluateNode *leftOperand)
{
    _leftOperand = leftOperand;
}

EvaluateNode *BinaryOperatorNode::rightOperand() const { return _rightOperand; }

void BinaryOperatorNode::setRightOperand(EvaluateNode *rightOperand)
{
    _rightOperand = rightOperand;
}

BinaryOperatorNode::~BinaryOperatorNode()
{
    delete _leftOperand;
    delete _rightOperand;
}

FunctionNode::FunctionNode() : EvaluateNode() {}

std::vector<EvaluateNode *> FunctionNode::parameters() const
{
    return _parameters;
}

void FunctionNode::setParameters(const std::vector<EvaluateNode *> &parameters)
{
    _parameters = parameters;
}

FunctionNode::~FunctionNode()
{
    for (EvaluateNode *child : _parameters) {
        delete child;
    }
}

MemberNode::MemberNode() : _owner(nullptr) {}

Variant MemberNode::evaluate() const
{
    XELObjectWrapper wrapper = _owner->evaluate().convertObject();
    if (wrapper.hasMember(memberName())) {
        return wrapper.member(_memberName);
    } else {
        throw XELError("No member called " + memberName());
    }
}

EvaluateNode *MemberNode::owner() const { return _owner; }

void MemberNode::setOwner(EvaluateNode *owner) { _owner = owner; }

XString MemberNode::memberName() const { return _memberName; }

void MemberNode::setMemberName(const XString &memberName)
{
    _memberName = memberName;
}

MemberNode::~MemberNode() { delete _owner; }

MemberFunctionNode::MemberFunctionNode() : _owner(nullptr) {}

Variant MemberFunctionNode::evaluate() const
{
    XELObjectWrapper wrapper = _owner->evaluate().convertObject();
    if (wrapper.hasMemberFunction(_memberFunctionName, parameters().size())) {
        std::vector<Variant> variants;
        for (EvaluateNode *node : parameters()) {
            variants.push_back(node->evaluate());
        }
        return wrapper.invoke(_memberFunctionName, variants);
    } else {
        throw XELError("No function called " + _memberFunctionName +
                       " or size of params is not right");
    }
}

EvaluateNode *MemberFunctionNode::owner() const { return _owner; }

void MemberFunctionNode::setOwner(EvaluateNode *owner) { _owner = owner; }

XString MemberFunctionNode::MemberFunctionName() const
{
    return _memberFunctionName;
}

void MemberFunctionNode::setMemberFunctionName(
    const XString &MemberFunctionName)
{
    _memberFunctionName = MemberFunctionName;
}

std::vector<EvaluateNode *> MemberFunctionNode::parameters() const
{
    return _parameters;
}

void MemberFunctionNode::setParameters(
    const std::vector<EvaluateNode *> &parameters)
{
    _parameters = parameters;
}

MemberFunctionNode::~MemberFunctionNode()
{
    for (auto it = parameters().begin(); it != parameters().end(); ++it) {
        delete *it;
    }
    delete _owner;
}
