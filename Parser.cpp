#include "Parser.h"

Parser::Parser()
	:mContext(nullptr)
{

}

void Parser::parse(const QList<Token>& tokenList)
{

}

FormulaContext* Parser::context() const
{
	return mContext;
}

void Parser::setContext(FormulaContext* context)
{
	mContext = context;
}
