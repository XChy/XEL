#include "Parser.h"

Parser::Parser()
	:mContext(nullptr)
{

}

TokenIt findNextCloseParenthese(TokenIt begin, TokenIt end)
{
	int numOpenParentheses = 1;
	for (auto it = begin;it != end;++it) {
		if (it->type() == OpenParentheses) {
			++numOpenParentheses;
		}
		else if (it->type() == CloseParentheses) {
			--numOpenParentheses;
		}
		if (!numOpenParentheses) {
			return it;
		}
	}
	return end;
}

std::vector<TokenIt> findFunctionComma(TokenIt begin, TokenIt end)
{
	std::vector<TokenIt> result;
	int numOpenParentheses = 0;
	for (auto it = begin;it != end;++it) {
		if (it->type() == OpenParentheses) {
			++numOpenParentheses;
		}
		else if (it->type() == CloseParentheses) {
			--numOpenParentheses;
		}
		if (it->type() == Comma) {
			if (!numOpenParentheses) {
				result.push_back(it);
			}
		}
	}
	return result;
}

ValueNode* Parser::createValue(TokenIt it)
{
	ValueNode* value = new ValueNode;
	value->setValue(it->value());
	return value;
}

VariableNode* Parser::createVariable(TokenIt it)
{
	VariableNode* variable = new VariableNode;
	variable->setVariableName(it->value().toString());
	variable->setVariableTable(&mContext->variableTable());
	return variable;
}

UnaryOperatorNode* Parser::createUnaryOperator(TokenIt it)
{
	if (it->type() == Operator) {
		if (!mContext->unaryOperatorTable().contains(it->value().convertString())) {
			throw XELError("No unary Operator called " + it->value().stringValue());
		}
		return mContext->unaryOperatorTable()[it->value().stringValue()]->create();
	}
	else {
		throw XELError("Is not unary operator");
	}
}

std::tuple<BinaryOperatorNode*, int, Assoc> Parser::createBinaryOperator(TokenIt it) {
	if (it->type() == Operator || it->type() == Identifier) {
		if (!mContext->binaryOperatorTable().contains(it->value().convertString())) {
			throw XELError("No binary Operator called " + it->value().stringValue());
		}
		auto creator = mContext->binaryOperatorTable()[it->value().stringValue()];
		return std::make_tuple(creator->create(), creator->priority(), creator->assoc());
	}
	else {
		throw XELError("Is not binary operator");
	}
}

FunctionNode* Parser::createFunction(TokenIt it, int paramSize)
{
	if (!mContext->functionTable().contains(it->value().convertString())) {
		throw XELError("No function called " + it->value().stringValue());
	}
	auto creator = mContext->functionTable()[it->value().stringValue()];
	if (creator->isVariableParam()) {
		return creator->create();
	}
	if (!creator->isSupportParamSize(paramSize)) {
		throw XELError("Size of params is not right");
	}
	return creator->create(paramSize);
}

std::vector<EvaluateNode*> Parser::parseFunctionParams(TokenIt& it, TokenIt end)
{
	if (it->type() == OpenParentheses) {
		auto subFunctionEnd = findNextCloseParenthese(it + 1, end);

		if (subFunctionEnd == end) {
			throw XELError("Cannot find function close parentheses");
		}

		if (subFunctionEnd != it + 1) {
			std::vector<TokenIt> commas = findFunctionComma(it + 1, subFunctionEnd);
			if (commas.empty()) {
				auto OldIt = it;
				it = subFunctionEnd;
				return { parseAll(OldIt + 1,subFunctionEnd) };
			}
			else {
				std::vector<EvaluateNode*> params;
				params.push_back(parseAll(it + 1, commas[0]));
				for (auto itOfIt = commas.begin();itOfIt != commas.end();++itOfIt) {
					if (itOfIt == commas.end() - 1) {
						params.push_back(parseAll((*itOfIt) + 1, subFunctionEnd));
					}
					else {
						params.push_back(parseAll((*itOfIt) + 1, *(itOfIt + 1)));
					}
				}
				it = subFunctionEnd;
				return params;
			}
		}
		it = subFunctionEnd;
		return std::vector<EvaluateNode*>();
	}
}

EvaluateNode* Parser::parseNoUnaryOperatorOperand(TokenIt& it, TokenIt end)
{
	if (it->type() == Literal) {
		return createValue(it);
	}
	else if (it->type() == Identifier) {
		if (it + 1 == end) {
			return createVariable(it);
		}
		else if ((it + 1)->type() == OpenParentheses) {
			FunctionNode* func1;
			TokenIt idIt = it;
			auto params = parseFunctionParams(++it, end);
			func1 = createFunction(idIt, params.size());
			func1->setParameters(params);
			return func1;
		}
		else {
			return createVariable(it);
		}
	}
	else if (it->type() == OpenParentheses) {
		auto subParsingEnd = findNextCloseParenthese(it + 1, end);
		if (subParsingEnd == end) {
			throw XELError("missing close parentheses");
		}
		EvaluateNode* result = parseAll(it + 1, subParsingEnd);
		it = subParsingEnd;
		return result;
	}
	else {
		throw XELError("Unknown operand");
	}
}

EvaluateNode* Parser::parseOperand(TokenIt& it, TokenIt end)
{
	if (it->type() == Operator) {
		UnaryOperatorNode* root = createUnaryOperator(it);
		UnaryOperatorNode* nodeEnd = root;
		while ((++it)->type() == Operator) {
			UnaryOperatorNode* last = nodeEnd;
			nodeEnd = createUnaryOperator(it);
			last->setOperand(nodeEnd);
		}
		EvaluateNode* operand = parseNoUnaryOperatorOperand(it, end);
		while (it != end) {
			if ((it + 1) != end && (it + 1)->type() == Dot) {
				if ((it + 2) != end && (it + 2)->type() == Identifier) {
					if ((it + 3) != end && (it + 3)->type() == OpenParentheses) {
						MemberFunctionNode* func = new MemberFunctionNode;
						func->setMemberFunctionName((it + 2)->value().convertString());
						auto params = parseFunctionParams(it += 3, end);
						func->setParameters(params);
						func->setOwner(operand);
						operand = func;
					}
					else {
						MemberNode* mem = new MemberNode;
						mem->setOwner(operand);
						mem->setMemberName((it += 2)->value().convertString());
						operand = mem;
					}
				}
				else {
					throw XELError("No identifier after dot");
				}
			}
			else {
				break;
			}
		}
		nodeEnd->setOperand(operand);
		return root;
	}
	else {
		EvaluateNode* root = parseNoUnaryOperatorOperand(it, end);
		while (it != end) {
			if ((it + 1) != end && (it + 1)->type() == Dot) {
				if ((it + 2) != end && (it + 2)->type() == Identifier) {
					if ((it + 3) != end && (it + 3)->type() == OpenParentheses) {
						MemberFunctionNode* func = new MemberFunctionNode;
						func->setMemberFunctionName((it + 2)->value().convertString());
						auto params = parseFunctionParams(it += 3, end);
						func->setParameters(params);
						func->setOwner(root);
						root = func;
					}
					else {
						MemberNode* mem = new MemberNode;
						mem->setOwner(root);
						mem->setMemberName((it += 2)->value().convertString());
						root = mem;
					}
				}
				else {
					throw XELError("No identifier after dot");
				}
			}
			else {
				break;
			}
		}
		return root;
	}
}

EvaluateNode* Parser::parseAll(TokenIt begin, TokenIt end) {
	TokenIt it = begin;
	if (it == end) {
		ValueNode* value = new ValueNode;
		value->setValue(Variant());
		return value;
	}

	EvaluateNode* root = nullptr;
	EvaluateNode* operand1 = parseOperand(it, end);
	root = operand1;

	if (++it == end)return root;

	BinaryOperatorNode* operator1;
	int priority1;
	auto tuple = createBinaryOperator(it);
	root = operator1 = std::get<0>(tuple);
	priority1 = std::get<1>(tuple);
	operator1->setLeftOperand(operand1);

	if (++it == end)throw XELError("No value after operator");

	EvaluateNode* operand2 = parseOperand(it, end);
	operator1->setRightOperand(operand2);

	++it;if (it == end)return root;

	while (it != end) {
		auto tuple = createBinaryOperator(it);
		BinaryOperatorNode* operator2 = std::get<0>(tuple);
		int priority2 = std::get<1>(tuple);
		if (++it == end)throw XELError("No value after operator");
		EvaluateNode* operand3 = parseOperand(it, end);

		if (priority2 < priority1) {
			operator2->setLeftOperand(root);
			operator2->setRightOperand(operand3);
			root = operator2;
		}
		else if (priority2 == priority1) {
			Assoc assoc = std::get<2>(tuple);
			if (assoc == LeftToRight) {
				operator2->setLeftOperand(operator1);
				operator2->setRightOperand(operand3);
				if (root == operator1) {
					root = operator2;
				}
				else {
					((BinaryOperatorNode*)root)->setRightOperand(operator2);
				}
			}
			else if (assoc == RightToLeft) {
				operator2->setLeftOperand(operand2);
				operator2->setRightOperand(operand3);
				operator1->setRightOperand(operator2);
			}
		}
		else {
			operator1->setRightOperand(operator2);
			operator2->setLeftOperand(operand2);
			operator2->setRightOperand(operand3);
		}
		operator1 = operator2;
		operand2 = operand3;
		priority1 = priority2;
		++it;
	}
	return root;
}

EvaluateNode* Parser::parse(const std::vector<Token>& tokenList)
{
	return parseAll(tokenList.begin(), tokenList.end());
}

XELContext* Parser::context() const
{
	return mContext;
}

void Parser::setContext(XELContext* context)
{
	mContext = context;
}
