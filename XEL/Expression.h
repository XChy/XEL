#ifndef EXPRESSION_H_VKZODWSA
#define EXPRESSION_H_VKZODWSA

#include <memory>
#include "XEL/EvaluateNode.h"
#include "XEL/Variant.h"

namespace XEL {

class Expression
{
    friend class XELEngine;

   public:
    Expression(EvaluateNode* node);
    Expression(const Expression& expr);

    Variant evaluate();

   private:
    std::shared_ptr<EvaluateNode> node;
};

}  // namespace XEL

#endif /* end of include guard: EXPRESSION_H_VKZODWSA */
