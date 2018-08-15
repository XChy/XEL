#ifndef XELVALORVAR_H
#define XELVAlORVAR_H

#include <XEL/xel_global.h>
#include <XEL/EvaluateNode.h>

class XEL_EXPORT XELValOrVar{
public:
    XELValOrVar():node(nullptr){}
    XELValOrVar(EvaluateNode* node):node(node){}
    bool isVariable() const;
    void setVariable(const Variant& var) const;

    Variant value() const;
    operator Variant() const;
    operator double() const;
    operator int() const;
    operator bool() const;
    operator XString() const;
private:
    EvaluateNode* node;
};

#endif
