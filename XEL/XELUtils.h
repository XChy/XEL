#ifndef XELUTILS_H
#define XELUTILS_H

#include <XEL/xel_global.h>
#include <XEL/XELContext.h>

template<typename Sig>
struct getFunctionArgs_;

template<typename R, typename... Args>
struct getFunctionArgs_<R(*)(Args...)> {
    static size_t const value = sizeof...(Args);
};

template<int params>
class funcAndParams;

template<>
class funcAndParams<0>{
public:
    template<typename Func>
    static Variant eval(Func func,std::vector<EvaluateNode*> params){
        return func();
    }
};

template<>
class funcAndParams<1>{
public:
    template<typename Func>
    static Variant eval(Func func,std::vector<EvaluateNode*> params){
        return func(params[0]->evaluate());
    }
};

template<>
class funcAndParams<2>{
public:
    template<typename Func>
    static Variant eval(Func func,std::vector<EvaluateNode*>& params){
        return func(params[0]->evaluate(),params[1]->evaluate());
    }
};

template<>
class funcAndParams<3>{
public:
    template<typename Func>
    static Variant eval(Func func,std::vector<EvaluateNode*>& params){
        return func(params[0]->evaluate(),params[1]->evaluate(),params[2]->evaluate());
    }
};


template<>
class funcAndParams<4>{
public:
    template<typename Func>
    static Variant eval(Func func,std::vector<EvaluateNode*>& params){
        return func(params[0]->evaluate(),params[1]->evaluate(),params[2]->evaluate(),params[3]->evaluate());
    }
};


class XEL_EXPORT XELUtils
{
public:

    template<typename Func>
    static void registerFuntion(std::shared_ptr<XELContext> context,Func func,XString funcName){
        context->functionTable()[funcName]=new FunctionCreator<Func>(func);//BUG Memory leak
    }

    template<typename Object>
    static void registerObject(std::shared_ptr<XELContext> context,XString constructorName){
        registerFuntion(context,&Object::construct,constructorName);
    };
protected:
    template<typename Sig>
    class FuncNode;

    template<typename Sig>
    class FunctionCreator;

    template<typename R, typename... args>
    class FuncNode<R(*)(args...)>:public FunctionNode{
        using Func=R(*)(args...);
    private:
        Func _func;
    public:
        FuncNode(Func func):_func(func){}



        Variant evaluate() const
        {
            return funcAndParams<getFunctionArgs_<Func>::value>::eval(_func,parameters());
        }
    };

    template<typename R, typename... args>
    class FunctionCreator<R(*)(args...)>:public XELFunction{
        using Func=R(*)(args...);
    private:
        Func _func;
    public:
        FunctionCreator(Func func):_func(func){};
        virtual FunctionNode* create() const{
            return new FuncNode<Func>(_func);
        }
        virtual FunctionNode* create(int paramSize) const{return new FuncNode<Func>(_func);};
        virtual bool isVariableParam() const{return false;};
        virtual bool isSupportParamSize(int paramSize) const{return paramSize==getFunctionArgs_<Func>::value;};

    };
};

#endif // XELUTILS_H
