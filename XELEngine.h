#ifndef XELENGINE_H
#define XELENGINE_H

#include "xel_global.h"
#include <XELContext.h>
#include <Variant.h>
#include <Preprocessor.h>
#include <Tokenizer.h>
#include <Parser.h>

class XEL_EXPORT XELEngine
{

public:
	XELEngine();

	template<typename Func>
	void setUnaryOperator(const QString& name,Func func){
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
						return mEvalFunc(operand()->evaluate());
					}
					Func mEvalFunc;
				};
				return new Operator(mEvalFunc);
			}
			Func mEvalFunc;
		};
		mContext->unaryOperatorTable().insert(name,new Creator(func));
	}

	template<typename Func>
	void setBinaryOperator(const QString& name,Func func,int priority){
		class Creator:public BinaryOperatorCreator{
		public:
			Creator(Func func,int priority):mEvalFunc(func){setPriority(priority);}
			BinaryOperatorNode* create() const{
				class Operator:public BinaryOperatorNode{
				public:
					Operator(Func func):
						BinaryOperatorNode(),
						mEvalFunc(func){}
					Variant evaluate() const{
						return mEvalFunc(leftOperand()->evaluate(),rightOperand()->evaluate());
					}
					Func mEvalFunc;
				};
				return new Operator(mEvalFunc);
			}
			Func mEvalFunc;
		};
		mContext->binaryOperatorTable().insert(name,new Creator(func,priority));
	}

	template<typename EvalFunc>
	void setFunction(const QString& name,EvalFunc evalFunc){
		class Creator:public FunctionCreator{
		public:
			Creator(EvalFunc func):mEvalFunc(func){}
			FunctionNode* create() const{
				class Function:public FunctionNode{
				public:
					Function(EvalFunc func):
						FunctionNode(),
						mEvalFunc(func){}
					Variant evaluate() const{
						QList<Variant> variants;
						for(EvaluateNode* node:parameters()){
							variants.append(node->evaluate());
						}
						return mEvalFunc(variants);
					}
					EvalFunc mEvalFunc;
				};
				return new Function(mEvalFunc);
			}
			EvalFunc mEvalFunc;
		};
		mContext->functionTable().insert(name,new Creator(evalFunc));
	}

	Variant evaluate() const;

	QString expression() const;
	void setExpression(QString expression);

	Variant& variable(const QString& name);
	void setVariable(const QString& name, const Variant& value);
	void removeVariable(QString name);

	std::shared_ptr<XELContext> context() const;
	void setContext(const std::shared_ptr<XELContext>& context);

	std::shared_ptr<Preprocessor> preprocessor() const;
	void setPreprocessor(const std::shared_ptr<Preprocessor>& preprocessor);

	std::shared_ptr<Tokenizer> tokenizer() const;
	void setTokenizer(const std::shared_ptr<Tokenizer>& tokenizer);

	std::shared_ptr<Parser> parser() const;
	void setParser(const std::shared_ptr<Parser>& parser);

	EvaluateNode* rootNode() const;
private:
	QString mExpression;
	EvaluateNode* mRootNode;

	std::shared_ptr<XELContext> mContext;
	std::shared_ptr<Preprocessor> mPreprocessor;
	std::shared_ptr<Tokenizer> mTokenizer;
	std::shared_ptr<Parser> mParser;
};

#endif // FORMULAENGINE_H
