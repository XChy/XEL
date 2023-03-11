#ifndef XELUTILS_H
#define XELUTILS_H

#include <functional>
#include "XEL/XELObject.h"
#include <XEL/xel_global.h>
#include <XEL/XELContext.h>

namespace XEL {

template <typename... Args>
struct ArgumentAmount {
    static size_t const value = sizeof...(Args);
};

template <int params>
class funcAndParams;

template <>
class funcAndParams<0>
{
   public:
    template <typename Func>
    static Variant eval(Func func, std::vector<EvaluateNode *> params)
    {
        return func();
    }
};
template <>
class funcAndParams<1>
{
   public:
    template <typename Func>
    static Variant eval(Func func, std::vector<EvaluateNode *> params)
    {
        return func(params[0]->evaluate());
    }
};
template <>
class funcAndParams<2>
{
   public:
    template <typename Func>
    static Variant eval(Func func, std::vector<EvaluateNode *> params)
    {
        return func(params[0]->evaluate(), params[1]->evaluate());
    }
};
template <>
class funcAndParams<3>
{
   public:
    template <typename Func>
    static Variant eval(Func func, std::vector<EvaluateNode *> &params)
    {
        return func(params[0]->evaluate(), params[1]->evaluate(),
                    params[2]->evaluate());
    }
};
template <>
class funcAndParams<4>
{
   public:
    template <typename Func>
    static Variant eval(Func func, std::vector<EvaluateNode *> &params)
    {
        return func(params[0]->evaluate(), params[1]->evaluate(),
                    params[2]->evaluate(), params[3]->evaluate());
    }
};
template <>
class funcAndParams<5>
{
   public:
    template <typename Func>
    static Variant eval(Func func, std::vector<EvaluateNode *> &params)
    {
        return func(params[0]->evaluate(), params[1]->evaluate(),
                    params[2]->evaluate(), params[3]->evaluate(),
                    params[4]->evaluate());
    }
};

template <typename Func, int params>
class FuncNode : public FunctionNode
{
   private:
    Func _func;

   public:
    FuncNode(Func func) : _func(func) {}

    Variant evaluate() const
    {
        return funcAndParams<params>::eval(_func, parameters());
    }
};

template <typename Func>
class VariableFuncNode : public FunctionNode
{
   private:
    Func _func;

   public:
    VariableFuncNode(Func func) : _func(func) {}

    Variant evaluate() const
    {
        std::vector<Variant> params;
        for (EvaluateNode *node : parameters())
            params.push_back(node->evaluate());
        return _func(params);
    }
};

template <typename R, typename... args>
class CreatorForFunction : public FunctionCreator
{
    using Func = std::function<R(args...)>;

   private:
    Func _func;

   public:
    CreatorForFunction(Func func) : _func(func){};
    virtual FunctionNode *create() const
    {
        return new FuncNode<Func, ArgumentAmount<args...>::value>(_func);
    }
    virtual FunctionNode *create(int paramSize) const
    {
        return new FuncNode<Func, ArgumentAmount<args...>::value>(_func);
    };
    virtual bool isVariableParam() const { return false; };
    virtual bool isSupportParamSize(int paramSize) const
    {
        return paramSize == ArgumentAmount<args...>::value;
    };
};

template <typename Func>
class CreatorForVariableParamFunction : public FunctionCreator
{
    Func _func;

   public:
    CreatorForVariableParamFunction(Func func) : _func(func){};
    virtual FunctionNode *create() const
    {
        return new VariableFuncNode<Func>(_func);
    }
    virtual FunctionNode *create(int paramSize) const
    {
        return new VariableFuncNode<Func>(_func);
    };
    virtual bool isVariableParam() const { return true; };
    virtual bool isSupportParamSize(int paramSize) const { return true; };
};

template <typename Func>
class CreatorForBinaryOperator : public BinaryOperatorCreator
{
   public:
    CreatorForBinaryOperator(Func func, int priority, Assoc assoc) : _func(func)
    {
        setPriority(priority);
        setAssoc(assoc);
    }
    BinaryOperatorNode *create() const
    {
        class Operator : public BinaryOperatorNode
        {
           public:
            Operator(Func func) : BinaryOperatorNode(), _func(func) {}
            Variant evaluate() const
            {
                return _func(leftOperand()->evaluate(),
                             rightOperand()->evaluate());
            }
            Func _func;
        };
        return new Operator(_func);
    }
    Func _func;
};

template <typename Func>
class CreatorForUnaryOperator : public UnaryOperatorCreator
{
   public:
    CreatorForUnaryOperator(Func func) : _func(func) {}
    UnaryOperatorNode *create() const
    {
        class Operator : public UnaryOperatorNode
        {
           public:
            Operator(Func func) : UnaryOperatorNode(), _func(func) {}
            Variant evaluate() const { return _func(operand()->evaluate()); }
            Func _func;
        };
        return new Operator(_func);
    }
    Func _func;
};

template <typename Func>
static BinaryOperatorCreator *creatorForBinaryOperator(
    Func func, int priority, Assoc assoc = LeftToRight)
{
    return new CreatorForBinaryOperator<Func>(func, priority,
                                              assoc);  // BUG Memory leak
}
template <typename Func>
static UnaryOperatorCreator *creatorForUnaryOperator(Func func)
{
    return new CreatorForUnaryOperator<Func>(func);  // BUG Memory leak
}
template <typename R, typename... args>
static FunctionCreator *creatorForFunction(
    const std::function<R(args...)> &func)
{
    return new CreatorForFunction<R, args...>(func);
    ;  // BUG Memory leak
}
template <typename Func>
static FunctionCreator *creatorForVariableParamFunction(Func func)
{
    return new CreatorForVariableParamFunction<Func>(func);
}

}  // namespace XEL
#endif  // XELUTILS_H
