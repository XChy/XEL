#ifndef PARSER_H
#define PARSER_H

#include <formulaengine_global.h>
#include <FormulaContext.h>
#include <EvaluateNode.h>
#include <Token.h>

class FORMULAENGINESHARED_EXPORT Parser
{
public:
	Parser();
	EvaluateNode* parse(const QList<Token>& tokenList);
	FormulaContext* context() const;

	void setContext(FormulaContext* context);
//private:
	FormulaContext* mContext;
	EvaluateNode* parseNoParenthesesMiddle(QList<Token>::iterator begin, QList<Token>::iterator end);
	EvaluateNode* parseValue(QList<Token>::iterator it);
	UnaryOperatorNode* parseUnaryOperator(QList<Token>::iterator it);
	std::tuple<BinaryOperatorNode*,int> parseBinaryOperator(QList<Token>::iterator it);
};

#endif // PARSER_H
