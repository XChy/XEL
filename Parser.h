#ifndef PARSER_H
#define PARSER_H

#include <xel_global.h>
#include <XELContext.h>
#include <EvaluateNode.h>
#include <Token.h>

typedef QList<Token>::const_iterator TokenIt;

class XELSHARED_EXPORT Parser
{
public:
	Parser();
	virtual EvaluateNode* parse(const QList<Token>& tokenList);

	XELContext* context() const;
	void setContext(XELContext* context);
private:
	XELContext* mContext;
	ValueNode* createValue(TokenIt it);
	VariableNode* createVariable(TokenIt it);
	UnaryOperatorNode* createUnaryOperator(TokenIt it);
	std::tuple<BinaryOperatorNode*,int> createBinaryOperator(TokenIt it);
	FunctionNode* createFunction(TokenIt it);
	EvaluateNode* parseAll(TokenIt begin, TokenIt end);
	EvaluateNode* parseNoUnaryOperatorOperand(TokenIt& it, TokenIt end);
	EvaluateNode* parseOperand(TokenIt& it, TokenIt end);
};

#endif // PARSER_H
