#include "XELEngine.h"

XELEngine::XELEngine()
	:mContext(new XELContext),
	  mParser(new Parser),
	  mTokenizer(new Tokenizer),
	  mPreprocessor(new Preprocessor),
	  mRootNode(nullptr)
{
	mParser->setContext(mContext.get());
	mTokenizer->setContext(mContext.get());
	mPreprocessor->setContext(mContext.get());
}

QString XELEngine::expression() const
{
	return mExpression;
}

void XELEngine::setExpression(QString expression)
{
	mRootNode=mParser->parse(mTokenizer->analyze(mPreprocessor->process(expression)));
	mExpression=expression;
}

Variant& XELEngine::variable(const QString& name)
{
	return mContext->variableTable()[name];
}

void XELEngine::setVariable(const QString& name, const Variant& value)
{
	mContext->variableTable().insert(name,value);
}

void XELEngine::removeVariable(QString name)
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
	mPreprocessor->setContext(context.get());
	mContext = context;
}

std::shared_ptr<Preprocessor> XELEngine::preprocessor() const
{
	return mPreprocessor;
}

void XELEngine::setPreprocessor(const std::shared_ptr<Preprocessor>& preprocessor)
{
	mPreprocessor = preprocessor;
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
