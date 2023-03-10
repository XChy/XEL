#ifndef FORMULACONTEXT_H
#define FORMULACONTEXT_H

#include <XEL/xel_global.h>
#include <XEL/XHashMap.h>
#include <XEL/NodeCreator.h>
#include <XEL/Variant.h>

class XEL_EXPORT XELContext
{
   public:
    XELContext();
    ~XELContext();
    XString operatorChars() const;
    void setOperatorChars(const XString& operatorChars);

    XHashMap<XString, UnaryOperatorCreator*>& unaryOperatorTable();
    void setUnaryOperatorTable(
        const XHashMap<XString, UnaryOperatorCreator*>& unaryOperatorTable);

    XHashMap<XString, BinaryOperatorCreator*>& binaryOperatorTable();
    void setBinaryOperatorTable(
        const XHashMap<XString, BinaryOperatorCreator*>& binaryOperatorTable);

    XHashMap<XString, FunctionCreator*>& functionTable();
    void setFunctionTable(
        const XHashMap<XString, FunctionCreator*>& functionTable);

    XHashMap<XString, Variant>& variableTable();
    void setVariableTable(const XHashMap<XString, Variant>& variableTable);

   private:
    XHashMap<XString, Variant> _variableTable;
    XHashMap<XString, UnaryOperatorCreator*> _unaryOperatorTable;
    XHashMap<XString, BinaryOperatorCreator*> _binaryOperatorTable;
    XHashMap<XString, FunctionCreator*> _functionTable;
    XString _operatorChars;
};

#endif  // FORMULACONTEXT_H
