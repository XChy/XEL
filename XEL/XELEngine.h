#ifndef XELENGINE_H
#define XELENGINE_H

#include "XEL/xel_global.h"
#include <XEL/XELContext.h>
#include <XEL/Variant.h>
#include <XEL/Tokenizer.h>
#include <XEL/Parser.h>
#include <XEL/XELValOrVar.h>
#include <XEL/XELUtils.h>

class XEL_EXPORT XELEngine
{

public:
	XELEngine();

	template<typename Func>
	void setUnaryOperator(const XString& name,Func func){
		class Creator:public UnaryOperatorCreator{
		public:
			Creator(Func func):mEvalFunc(func){}
			UnaryOperatorNode* create() const{
				class Operator:public UnaryOperatorNode{
				public:
					Operator(Func func):
						UnaryOperatorNode(),
						mEvalFunc(func){}
					Variant evaluate() const{
						return mEvalFunc(XELValOrVar(operand()));
					}
					Func mEvalFunc;
				};
				return new Operator(mEvalFunc);
			}
			Func mEvalFunc;
		};
		mContext->unaryOperatorTable()[name]=new Creator(func);
	}

	template<typename Func>
	void setBinaryOperator(const XString& name,Func func,int priority,Assoc assoc=LeftToRight){
		class Creator:public BinaryOperatorCreator{
		public:
			Creator(Func func,int priority,Assoc assoc):
				mEvalFunc(func)
			{
				setPriority(priority);
				setAssoc(assoc);
			}
			BinaryOperatorNode* create() const{
				class Operator:public BinaryOperatorNode{
				public:
					Operator(Func func):
						BinaryOperatorNode(),
						mEvalFunc(func){}
					Variant evaluate() const{
						return mEvalFunc(XELValOrVar(leftOperand()),XELValOrVar(rightOperand()));
					}
					Func mEvalFunc;
				};
				return new Operator(mEvalFunc);
			}
			Func mEvalFunc;
		};
		mContext->binaryOperatorTable()[name]=new Creator(func,priority,assoc);
	}

	Variant evaluate() const;

	XString expression() const;
	void setExpression(XString expression);

	Variant& variable(const XString& name);
	void setVariable(const XString& name, const Variant& value);
	void removeVariable(XString name);

	std::shared_ptr<XELContext> context() const;
	void setContext(const std::shared_ptr<XELContext>& context);

	std::shared_ptr<Tokenizer> tokenizer() const;
	void setTokenizer(const std::shared_ptr<Tokenizer>& tokenizer);

	std::shared_ptr<Parser> parser() const;
	void setParser(const std::shared_ptr<Parser>& parser);

	EvaluateNode* rootNode() const;
private:
	XString mExpression;
	EvaluateNode* mRootNode;

	std::shared_ptr<XELContext> mContext;
	std::shared_ptr<Tokenizer> mTokenizer;
	std::shared_ptr<Parser> mParser;
};

#endif // FORMULAENGINE_H
