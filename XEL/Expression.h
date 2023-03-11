#ifndef EXPRESSION_H_VKZODWSA
#define EXPRESSION_H_VKZODWSA

#include "XEL/EvaluateNode.h"
#include "XEL/Variant.h"

namespace XEL {

class Expression
{
    friend class XELEngine;

   public:
    Expression(EvaluateNode* node);
    Expression(Expression&& other);
    ~Expression();

    Variant evaluate();

   private:
    EvaluateNode* node;
};

}  // namespace XEL

#endif /* end of include guard: EXPRESSION_H_VKZODWSA */
