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
class funcAndParams<0> {
public:
	template<typename Func>
	static Variant eval(Func func, std::vector<EvaluateNode*> params) {
		return func();
	}
};

template<>
class funcAndParams<1> {
public:
	template<typename Func>
	static Variant eval(Func func, std::vector<EvaluateNode*> params) {
		return func(params[0]->evaluate());
	}
};

template<>
class funcAndParams<2> {
public:
	template<typename Func>
	static Variant eval(Func func, std::vector<EvaluateNode*>& params) {
		return func(params[0]->evaluate(), params[1]->evaluate());
	}
};

template<>
class funcAndParams<3> {
public:
	template<typename Func>
	static Variant eval(Func func, std::vector<EvaluateNode*>& params) {
		return func(params[0]->evaluate(), params[1]->evaluate(), params[2]->evaluate());
	}
};


template<>
class funcAndParams<4> {
public:
	template<typename Func>
	static Variant eval(Func func, std::vector<EvaluateNode*>& params) {
		return func(params[0]->evaluate(), params[1]->evaluate(), params[2]->evaluate(), params[3]->evaluate());
	}
};


namespace XELUtils
{
	template<typename Sig>
	class FuncNode;

	template<typename Sig>
	class CreatorForFunction;

	template<typename R, typename... args>
	class FuncNode<R(*)(args...)> :public FunctionNode {
		using Func = R(*)(args...);
	private:
		Func _func;
	public:
		FuncNode(Func func) :_func(func) {}



		Variant evaluate() const
		{
			return funcAndParams<getFunctionArgs_<Func>::value>::eval(_func, parameters());
		}
	};

	template<typename R, typename... args>
	class CreatorForFunction<R(*)(args...)> :public FunctionCreator {
		using Func = R(*)(args...);
	private:
		Func _func;
	public:
		CreatorForFunction(Func func) :_func(func) {};
		virtual FunctionNode* create() const {
			return new FuncNode<Func>(_func);
		}
		virtual FunctionNode* create(int paramSize) const { return new FuncNode<Func>(_func); };
		virtual bool isVariableParam() const { return false; };
		virtual bool isSupportParamSize(int paramSize) const { return paramSize == getFunctionArgs_<Func>::value; };

	};

	template<typename Func>
	class CreatorForBinaryOperator :public BinaryOperatorCreator {
	public:
		CreatorForBinaryOperator(Func func, int priority, Assoc assoc) :
			mEvalFunc(func)
		{
			setPriority(priority);
			setAssoc(assoc);
		}
		BinaryOperatorNode* create() const {
			class Operator :public BinaryOperatorNode {
			public:
				Operator(Func func) :
					BinaryOperatorNode(),
					mEvalFunc(func) {}
				Variant evaluate() const {
					return mEvalFunc(leftOperand()->evaluate(), rightOperand()->evaluate());
				}
				Func mEvalFunc;
			};
			return new Operator(mEvalFunc);
		}
		Func mEvalFunc;
	};

	template<typename Func>
	class CreatorForUnaryOperator :public UnaryOperatorCreator {
	public:
		CreatorForUnaryOperator(Func func) :mEvalFunc(func) {}
		UnaryOperatorNode* create() const {
			class Operator :public UnaryOperatorNode {
			public:
				Operator(Func func) :
					UnaryOperatorNode(),
					mEvalFunc(func) {}
				Variant evaluate() const {
					return mEvalFunc(operand());
				}
				Func mEvalFunc;
			};
			return new Operator(mEvalFunc);
		}
		Func mEvalFunc;
	};

	template<typename Func>
	static BinaryOperatorCreator* creatorForBinaryOperator(Func func, int priority, Assoc assoc = LeftToRight) {

		return new CreatorForBinaryOperator<Func>(func, priority, assoc);//BUG Memory leak
	}
	template<typename Func>
	static UnaryOperatorCreator* creatorForUnaryOperator(Func func) {

		return new CreatorForUnaryOperator<Func>(func);//BUG Memory leak
	}
	template<typename Func>
	static FunctionCreator* creatorForFunction(Func func) {
		return new CreatorForFunction<Func>(func);;//BUG Memory leak
	}
};

#endif // XELUTILS_H
