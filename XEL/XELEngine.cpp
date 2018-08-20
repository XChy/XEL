#include "XELEngine.h"
#include <XEL/XELContainerObject.h>
#include <XEL/XELFunctions.h>

XELEngine::XELEngine()
	:mContext(new XELContext),
	  mParser(new Parser),
	  mTokenizer(new Tokenizer),
	  mRootNode(nullptr)
{
	mParser->setContext(mContext.get());
	mTokenizer->setContext(mContext.get());
	setUnaryOperator("-",[](const Variant& v)->Variant{
		if(v.type()==VariantType::Int){
			return -v.intValue();
		}else if(v.type()==VariantType::Double){
			return -v.doubleValue();
		}else{
			throw XELError("Unary operator '-' cannot eval value as "+Variant::convertString(v.type()));
		}
	});
	setUnaryOperator("!",[](bool o){
		return !o;
	});
	setBinaryOperator("=",[](XELValOrVar left,XELValOrVar right){
		left.setVariable(right.value());
		return left;
	},0,RightToLeft);
	setBinaryOperator("+=",[](XELValOrVar left,XELValOrVar right){
		Variant leftValue=left.value();
		if(leftValue.type()==VariantType::Double){
			left.setVariable(leftValue.doubleValue()+double(right));
		}else if(leftValue.type()==VariantType::Int){
			left.setVariable(leftValue.intValue()+int(right));
		}
		return left;
	},0,RightToLeft);
	setBinaryOperator("-=",[](XELValOrVar left,XELValOrVar right){
		Variant leftValue=left.value();
		if(leftValue.type()==VariantType::Double){
			left.setVariable(leftValue.doubleValue()-double(right));
		}else if(leftValue.type()==VariantType::Int){
			left.setVariable(leftValue.intValue()-int(right));
		}
		return left;
	},0,RightToLeft);
	setBinaryOperator(">",[](const Variant& left,const Variant& right){
		switch (left.type()) {
			case VariantType::Double:
				return left.doubleValue()>double(right);
			case VariantType::Int:
				if(right.type()==VariantType::Int)
					return left.intValue()>right.intValue();
				else if(right.type()==VariantType::Double)
					return double(left.intValue())>right.doubleValue();
			default:
				return false;
		}
	},1);
	setBinaryOperator(">=",[](const Variant& left,const Variant& right){
		switch (left.type()) {
			case VariantType::Double:
				return left.doubleValue()>=double(right);
			case VariantType::Int:
				if(right.type()==VariantType::Int)
					return left.intValue()>=right.intValue();
				else if(right.type()==VariantType::Double)
					return double(left.intValue())>=right.doubleValue();
			default:
				return false;
		}
	},1);
	setBinaryOperator("<",[](const Variant& left,const Variant& right){
		switch (left.type()) {
			case VariantType::Double:
				return left.doubleValue()<double(right);
			case VariantType::Int:
				if(right.type()==VariantType::Int)
					return left.intValue()<right.intValue();
				else if(right.type()==VariantType::Double)
					return double(left.intValue())<right.doubleValue();
			default:
				return false;
		}
	},1);
	setBinaryOperator("<=",[](const Variant& left,const Variant& right){
		switch (left.type()) {
			case VariantType::Double:
				return left.doubleValue()<=double(right);
			case VariantType::Int:
				if(right.type()==VariantType::Int)
					return left.intValue()<=right.intValue();
				else if(right.type()==VariantType::Double)
					return double(left.intValue())<=right.doubleValue();
			default:
				return false;
		}
	},1);
	setBinaryOperator("==",[](const Variant& left,const Variant& right){
		return left==right;
	},0);
	setBinaryOperator("||",[](bool left,bool right){
		return left||right;
	},1);
	setBinaryOperator("&&",[](bool left,bool right){
		return left&&right;
	},1);
	setBinaryOperator("+",[](double left,double right){
		return left+right;
	},1);
	setBinaryOperator("-",[](double left,double right){
		return left-right;
	},1);
	setBinaryOperator("*",[](double left,double right){
		return left*right;
	},2);
	setBinaryOperator("/",[](double left,double right){
		return left/right;
	},2);
	setBinaryOperator("|",[](int left,int right){
		return left|right;
	},3,RightToLeft);
	setBinaryOperator("&",[](int left,int right){
		return left&right;
	},3,RightToLeft);
	setBinaryOperator("^",[](int left,int right){
		return left^right;
	},3,RightToLeft);
	mContext->functionTable()["sin"]=new SinFunction;
	mContext->functionTable()["cos"]=new CosFunction;
	mContext->functionTable()["tan"]=new TanFunction;
	mContext->functionTable()["cot"]=new CotFunction;
//	setFunction("Vector",[](const std::vector<XELValOrVar>& params){
//		XVectorObject* vec=new XVectorObject;
//		for(auto v:params)
//			vec->vector().push_back(v.value());
//		return XELObjectWrapper((XELObject*)vec);
//	});
//	setFunction("Map",[](const std::vector<XELValOrVar>& params){
//		XMapObject* map=new XMapObject;
//		return XELObjectWrapper((XELObject*)map);
//	});
//	setFunction("sin",[](const std::vector<XELValOrVar>& params){
//		return sin(params.at(0));
//	});
//	setFunction("cos",[](const std::vector<XELValOrVar>& params){
//		return cos(params.at(0));
//	});
//	setFunction("tan",[](const std::vector<XELValOrVar>& params){
//		return tan(params.at(0));
//	});
}

XString XELEngine::expression() const
{
	return mExpression;
}

void XELEngine::setExpression(XString expression)
{
	mRootNode=mParser->parse(mTokenizer->analyze(expression));
	mExpression=expression;
}

Variant& XELEngine::variable(const XString& name)
{
	return mContext->variableTable()[name];
}

void XELEngine::setVariable(const XString& name, const Variant& value)
{
	mContext->variableTable()[name]=value;
}

void XELEngine::removeVariable(XString name)
{
	mContext->variableTable().remove(name);
}

Variant XELEngine::evaluate() const
{
	if(mRootNode){
		return mRootNode->evaluate();
	}
	return Variant();
}

std::shared_ptr<XELContext> XELEngine::context() const
{
	return mContext;
}

void XELEngine::setContext(const std::shared_ptr<XELContext>& context)
{
	mParser->setContext(context.get());
	mTokenizer->setContext(context.get());
	mContext = context;
}

std::shared_ptr<Tokenizer> XELEngine::tokenizer() const
{
	return mTokenizer;
}

void XELEngine::setTokenizer(const std::shared_ptr<Tokenizer>& tokenizer)
{
	mTokenizer = tokenizer;
}

std::shared_ptr<Parser> XELEngine::parser() const
{
	return mParser;
}

void XELEngine::setParser(const std::shared_ptr<Parser>& parser)
{
	mParser = parser;
}

EvaluateNode* XELEngine::rootNode() const
{
	return mRootNode;
}
