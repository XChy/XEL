#include "XEL/EvaluateNode.h"
#include "XEL/Variant.h"

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
