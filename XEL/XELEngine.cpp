#include "XELEngine.h"

XELEngine::XELEngine()
	:mContext(new XELContext),
	  mParser(new Parser),
	  mTokenizer(new Tokenizer),
	  mRootNode(nullptr)
{
	mParser->setContext(mContext.get());
	mTokenizer->setContext(mContext.get());
	setUnaryOperator("-",[](double o){
		return -o;
	});
	setUnaryOperator("!",[](bool o){
		return !o;
	});
	setBinaryOperator("=",[](XELValOrVar left,XELValOrVar right){
		left.setVariable(right.value());
		return left;
	},0,RightToLeft);
	setBinaryOperator("==",[](const Variant& left,const Variant& right){
		return left==right;
	},1);
	setBinaryOperator("||",[](bool left,bool right){
		return left||right;
	},1);
	setBinaryOperator("or",[](int left,int right){
		return left|right;
	},1);
	setBinaryOperator("and",[](int left,int right){
		return left&right;
	},1);
	setBinaryOperator("xor",[](int left,int right){
		return left^right;
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
	setBinaryOperator("^",[](double left,double right){
		return pow(left,right);
	},3,RightToLeft);
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
