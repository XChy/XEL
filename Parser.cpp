#include "Parser.h"

Parser::Parser()
	:mContext(nullptr)
{

}

EvaluateNode* Parser::parseValue(QList<Token>::const_iterator it){
	if(it->type()==Literal){
		ValueNode* value=new ValueNode;
		value->setValue(it->value());
		return value;
	}else if(it->type()==Identifier){
		VariableNode* variable=new VariableNode;
		variable->setVariableName(it->value().toString());
		variable->setVariableTable(&mContext->variableTable());
		return variable;
	}else{
		throw XELError("Is not Literal or Identifier");
	}
}

UnaryOperatorNode* Parser::parseUnaryOperator(QList<Token>::const_iterator it){
	if(it->type()==Operator){
		if(!mContext->unaryOperatorTable().contains(it->value().toString())){
			throw XELError("No unary Operator called "+it->value().toString());
		}
		return mContext->unaryOperatorTable()[it->value().toString()]->create();
	}else{
		throw XELError("Is not unary operator");
	}
}

std::tuple<BinaryOperatorNode*,int> Parser::parseBinaryOperator(QList<Token>::const_iterator it){
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

EvaluateNode* Parser::parseNoParenthesesMiddle(QList<Token>::const_iterator begin, QList<Token>::const_iterator end){
	auto it=begin;

	EvaluateNode* root;
	EvaluateNode* operand1;
	if(it->type()==Operator){
		auto unaryOper=parseUnaryOperator(it);
		++it;if(it==end)throw XELError("cannot end in unary operator");
		EvaluateNode* value1=parseValue(it);
		unaryOper->setOperand(value1);
		root=operand1=unaryOper;
	}else{
		EvaluateNode* value1=parseValue(it);
		root=operand1=value1;
	}
	if(++it==end)return root;

	BinaryOperatorNode* operator1;
	auto tuple=parseBinaryOperator(it);
	operator1=std::get<0>(tuple);
	int priority1=std::get<1>(tuple);
	operator1->setLeftOperand(operand1);
	root=operator1;
	if(++it==end)throw XELError("No value after operator");

	EvaluateNode* operand2=parseValue(it);
	operator1->setRightOperand(operand2);

	++it;if(it==end)return root;

	while(it!=end){
		auto tuple=parseBinaryOperator(it);
		BinaryOperatorNode* operator2=std::get<0>(tuple);
		int priority2=std::get<1>(tuple);
		if(++it==end)throw XELError("No value after operator");
		EvaluateNode* operand3=parseValue(it);
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
	return parseNoParenthesesMiddle(tokenList.begin(),tokenList.end());
}

XELContext* Parser::context() const
{
	return mContext;
}

void Parser::setContext(XELContext* context)
{
	mContext = context;
}
