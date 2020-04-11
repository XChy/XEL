#ifndef PARSER_H
#define PARSER_H

#include <XEL/xel_global.h>
#include <XEL/XELContext.h>
#include <XEL/EvaluateNode.h>
#include <XEL/Token.h>

typedef std::vector<Token>::const_iterator TokenIt;

class XEL_EXPORT Parser
{
public:
	Parser();
	virtual EvaluateNode* parse(const std::vector<Token>& tokenList);

	XELContext* context() const;
	void setContext(XELContext* context);
private:
	XELContext* _context;
	ValueNode* createValue(TokenIt it);
	VariableNode* createVariable(TokenIt it);
	UnaryOperatorNode* createUnaryOperator(TokenIt it);
	std::tuple<BinaryOperatorNode*, int, Assoc> createBinaryOperator(TokenIt it);
	FunctionNode* createFunction(TokenIt it, int paramSize);
	EvaluateNode* parseAll(TokenIt begin, TokenIt end);
	std::vector<EvaluateNode*> parseFunctionParams(TokenIt& it, TokenIt end);
	EvaluateNode* parseNoUnaryOperatorOperand(TokenIt& it, TokenIt end);
	EvaluateNode* parseOperand(TokenIt& it, TokenIt end);
};

#endif // PARSER_H
