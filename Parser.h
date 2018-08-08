#ifndef PARSER_H
#define PARSER_H

#include <xel_global.h>
#include <XELContext.h>
#include <EvaluateNode.h>
#include <Token.h>

class XELSHARED_EXPORT Parser
{
public:
	Parser();
	virtual EvaluateNode* parse(const QList<Token>& tokenList);

	XELContext* context() const;
	void setContext(XELContext* context);
private:
	XELContext* mContext;
	EvaluateNode* parseNoParenthesesMiddle(QList<Token>::const_iterator begin, QList<Token>::const_iterator end);
	EvaluateNode* parseValue(QList<Token>::const_iterator it);
	UnaryOperatorNode* parseUnaryOperator(QList<Token>::const_iterator it);
	std::tuple<BinaryOperatorNode*,int> parseBinaryOperator(QList<Token>::const_iterator it);
};

#endif // PARSER_H
