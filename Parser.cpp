#include "Parser.h"

Parser::Parser()
	:mContext(nullptr)
{

}

TokenIt findNextCloseParenthese(TokenIt begin,TokenIt end)
{
	int numOpenParentheses=1;
	for(auto it=begin;it!=end;++it){
		if(it->type()==OpenParentheses){
			++numOpenParentheses;
		}else if(it->type()==CloseParentheses){
			--numOpenParentheses;
		}
		if(!numOpenParentheses){
			return it;
		}
	}
	return end;
}

QList<TokenIt> findFunctionComma(TokenIt begin,TokenIt end)
{
	QList<TokenIt> result;
	int numOpenParentheses=0;
	for(auto it=begin;it!=end;++it){
		if(it->type()==OpenParentheses){
			++numOpenParentheses;
		}else if(it->type()==CloseParentheses){
			--numOpenParentheses;
		}
		if(it->type()==Comma){
			if(!numOpenParentheses){
				result.append(it);
			}
		}
	}
	return result;
}

ValueNode* Parser::createValue(TokenIt it)
{
	ValueNode* value=new ValueNode;
	value->setValue(it->value());
	return value;
}

VariableNode* Parser::createVariable(TokenIt it)
{
	VariableNode* variable=new VariableNode;
	variable->setVariableName(it->value().toString());
	variable->setVariableTable(&mContext->variableTable());
	return variable;
}

UnaryOperatorNode* Parser::createUnaryOperator(TokenIt it)
{
	if(it->type()==Operator){
		if(!mContext->unaryOperatorTable().contains(it->value().toString())){
			throw XELError("No unary Operator called "+it->value().toString());
		}
		return mContext->unaryOperatorTable()[it->value().toString()]->create();
	}else{
		throw XELError("Is not unary operator");
	}
}

std::tuple<BinaryOperatorNode*,int> Parser::createBinaryOperator(TokenIt it){
	if(it->type()==Operator){
		if(!mContext->binaryOperatorTable().contains(it->value().toString())){
			throw XELError("No binary Operator called "+it->value().toString());
		}
		auto creator=mContext->binaryOperatorTable()[it->value().toString()];
		return std::make_tuple(creator->create(),creator->priority());
	}else{
		throw XELError("Is not binary operator");
	}
}

FunctionNode* Parser::createFunction(TokenIt it)
{
	if(!mContext->functionTable().contains(it->value().toString())){
		throw XELError("No function called "+it->value().castString());
	}
	auto creator=mContext->functionTable()[it->value().castString()];
	return creator->create();
}

EvaluateNode* Parser::parseNoUnaryOperatorOperand(TokenIt& it,TokenIt end)
{
	if(it->type()==Literal){
		return createValue(it);
	}else if(it->type()==Identifier){
		if(it+1==end){
			return createVariable(it);
		}
		if((it+1)->type()==OpenParentheses){
			FunctionNode* func1=createFunction(it);
			auto subFunctionEnd=findNextCloseParenthese(it+2,end);
			if(subFunctionEnd!=it+2){
				QList<TokenIt> commas=findFunctionComma(it+2,subFunctionEnd);
				if(commas.empty()){
					func1->setParameters({parseAll(it+2,subFunctionEnd)});
				}else{
					QList<EvaluateNode*> params;
					params.append(parseAll(it+2,commas[0]));
					for(auto itOfIt=commas.begin();itOfIt!=commas.end();++itOfIt){
						if(itOfIt==commas.end()-1){
							params.append(parseAll((*itOfIt)+1,subFunctionEnd));
						}else{
							params.append(parseAll((*itOfIt)+1,*(itOfIt+1)));
						}
					}
					func1->setParameters(params);
				}
			}
			it=subFunctionEnd;
			return func1;
		}else{
			return createVariable(it);
		}
	}else if(it->type()==OpenParentheses){
		auto subParsingEnd=findNextCloseParenthese(it+1,end);
		if(subParsingEnd==end){
			throw XELError("missing closeparenthese");
		}
		EvaluateNode* result=parseAll(it+1,subParsingEnd);
		it=subParsingEnd;
		return result;
	}else{
		throw XELError("Unknown operand");
	}
}

EvaluateNode* Parser::parseOperand(TokenIt& it, TokenIt end)
{
	if(it->type()==Operator){
		UnaryOperatorNode* unary=createUnaryOperator(it);
		if(++it==end)throw XELError("No value after operator");
		unary->setOperand(parseNoUnaryOperatorOperand(it,end));
		return unary;
	}else{
		return parseNoUnaryOperatorOperand(it,end);
	}
}

EvaluateNode* Parser::parseAll(TokenIt begin, TokenIt end){
	TokenIt it=begin;
	if(it==end)throw XELError("Cannot be null");

	EvaluateNode* root=nullptr;
	EvaluateNode* operand1=parseOperand(it,end);
	root=operand1;

	if(++it==end)return root;

	BinaryOperatorNode* operator1;
	int priority1;
	auto tuple=createBinaryOperator(it);
	root=operator1=std::get<0>(tuple);
	priority1=std::get<1>(tuple);
	operator1->setLeftOperand(operand1);
	if(++it==end)throw XELError("No value after operator");

	EvaluateNode* operand2=parseOperand(it,end);
	operator1->setRightOperand(operand2);

	++it;if(it==end)return root;

	while(it!=end){
		auto tuple=createBinaryOperator(it);
		BinaryOperatorNode* operator2=std::get<0>(tuple);
		int priority2=std::get<1>(tuple);
		if(++it==end)throw XELError("No value after operator");

		EvaluateNode* operand3=parseOperand(it,end);

		if(priority2<priority1){
			operator2->setLeftOperand(root);
			operator2->setRightOperand(operand3);
			root=operator2;
		}else if(priority2==priority1){
			operator2->setLeftOperand(operator1);
			operator2->setRightOperand(operand3);
			if(root==operator1){
				root=operator2;
			}else{
				((BinaryOperatorNode*)root)->setRightOperand(operator2);
			}
		}else{
			operator1->setRightOperand(operator2);
			operator2->setLeftOperand(operand2);
			operator2->setRightOperand(operand3);
		}
		operator1=operator2;
		operand2=operand3;
		priority1=priority2;
		++it;
	}
	return root;
}


EvaluateNode* Parser::parse(const QList<Token>& tokenList)
{
	return parseAll(tokenList.begin(),tokenList.end());
}

XELContext* Parser::context() const
{
	return mContext;
}

void Parser::setContext(XELContext* context)
{
	mContext = context;
}
