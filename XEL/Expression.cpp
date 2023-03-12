#include "XEL/Expression.h"

using namespace XEL;

Expression::Expression(EvaluateNode* node) : node(node) {}

Expression::Expression(const Expression& expr) : node(expr.node) {}

Variant Expression::evaluate()
{
    if (node)
        return node->evaluate();
    else
        return Variant();
}
