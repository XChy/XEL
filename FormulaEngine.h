#ifndef FORMULAENGINE_H
#define FORMULAENGINE_H

#include "formulaengine_global.h"
#include <FormulaContext.h>
#include <Variant.h>
#include <Preprocessor.h>
#include <Tokenizer.h>
#include <Parser.h>

class FORMULAENGINESHARED_EXPORT FormulaEngine
{

public:
	FormulaEngine();
	QString expression() const;
	FormulaContext* context() const;

	Variant& variable(const QString& name);

	void setExpression(QString expression);
	void setContext(FormulaContext* context);

	void setVariable(const QString& name, const Variant& value);
	void removeVariable(QString name);

	template<typename Func>
	void setUnaryOperator(const QString& name,Func func){
		class Creator:public UnaryOperatorCreator{
		public:
			Creator(Func func):mFunc(func){}
			UnaryOperatorNode* create() const{
				class Operator:public UnaryOperatorNode{
				public:
					Operator(Func func):
						UnaryOperatorNode(),
						mFunc(func){}
					Variant evaluate() const{
						return mFunc(operand()->evaluate());
					}
					Func mFunc;
				};
				return new Operator(mFunc);
			}
			Func mFunc;
		};
		mContext->unaryOperatorTable().insert(name,new Creator(func));
	}

	template<typename Func>
	void setBinaryOperator(const QString& name,Func func,int priority){
		class Creator:public BinaryOperatorCreator{
		public:
			Creator(Func func,int priority):mFunc(func){}
			BinaryOperatorNode* create() const{
				class Operator:public BinaryOperatorNode{
				public:
					Operator(Func func):
						BinaryOperatorNode(),
						mFunc(func){}
					Variant evaluate() const{
						return mFunc(leftOperand()->evaluate(),rightOperand()->evaluate());
					}
					Func mFunc;
				};
				return new Operator(mFunc);
			}
			Func mFunc;
		};
		mContext->binaryOperatorTable().insert(name,new Creator(func,priority));
	}

	template<typename Func>
	void setFunction(const QString& name,Func func){
		class Creator:public FunctionCreator{
		public:
			Creator(Func func):mFunc(func){}
			FunctionNode* create() const{
				class Function:public FunctionNode{
				public:
					Function(Func func):
						FunctionNode(),
						mFunc(func){}
					Variant evaluate() const{
						QList<Variant> variants;
						for(EvaluateNode* node:parameters()){
							variants.append(node->evaluate());
						}
						return mFunc(variants);
					}
					Func mFunc;
				};
				return new Function(mFunc);
			}
			Func mFunc;
		};
		mContext->functionTable().insert(name,new Creator(func));
	}

	Variant evaluate() const;
private:
	QString mExpression;
	FormulaContext* mContext;

	Preprocessor preprocessor;
	Tokenizer tokenizer;
	Parser parser;
	EvaluateNode* rootNode;
};

#endif // FORMULAENGINE_H
