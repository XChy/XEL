#include "XEL/Expression.h"

using namespace XEL;

Expression::Expression(EvaluateNode* node) : node(node) {}

Expression::Expression(Expression&& other)
{
    this->node = other.node;
    other.node = nullptr;
}
Expression::~Expression()
{
    if (node) delete node;
}
Variant Expression::evaluate()
{
    if (node)
        return node->evaluate();
    else
        return Variant();
}
