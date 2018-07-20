#ifndef PARSER_H
#define PARSER_H

#include <formulaengine_global.h>
#include <FormulaContext.h>
#include <Token.h>

class FORMULAENGINESHARED_EXPORT Parser
{
public:
	Parser();
	void parse(const QList<Token>& tokenList);
	FormulaContext* context() const;

	void setContext(FormulaContext* context);
private:
	FormulaContext* mContext;
};

#endif // PARSER_H
