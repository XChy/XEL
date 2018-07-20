#include "Tokenizer.h"

Tokenizer::Tokenizer()
	:mContext(nullptr)
{

}

QList<Token> Tokenizer::analyze(QString expression) const
{
	QList<Token> result;
	auto it=expression.begin();
	while(it!=expression.end()){
		if(it->isNumber()){//number part
			QString value;
			value.append(*it);++it;//add number before decimal point
			while(it->isNumber()){
				value.append(*it);++it;
			}
			if(*it=='.'){
				value.append(*it);++it;;//add decimal point
				while(it->isNumber()){
					value.append(*it);++it;//add number behind decimal point
				}
			}
			if(*it=='e'){// 'e' part
				value.append(*it);++it;
				if(*it=='+'||*it=="-"){
					value.append(*it);++it;
				}
				while(it->isNumber()){
					value.append(*it);++it;
				}
			}
			result.append(Token(Literal,value.toDouble()));
		}else if(mContext->operatorChars().contains(*it)){
			QString value;
			value.append(*it);++it;
			while(mContext->operatorChars().contains(*it)){
				value.append(*it);++it;
			}
			result.append(Token(Operator,value));
		}else if(it->isLetter()||*it=='_'){
			QString value;
			value.append(*it);++it;;
			while(it->isLetterOrNumber()||*it=='_'){
				value.append(*it);++it;;
			}
			if(value=="true"){
				result.append(Token(Literal,true));
			}else if(value=="false"){
				result.append(Token(Literal,false));
			}else{
				result.append(Token(Identifier,value));
			}
		}else if(*it=='('){
			result.append(Token(OpenParentheses));++it;
		}else if(*it==')'){
			result.append(Token(CloseParentheses));++it;
		}else if(*it==','){
			result.append(Token(Comma));++it;;
		}else if(*it=='\"'){
			++it;
			QString value;
			while(*it!='\"'){
				value.append(*it);++it;
			}
			result.append(Token(Literal,value));
			++it;
		}else{
			throw FormulaError(QString("Unknown char:")+(*it));
		}
	}
	return result;
}

FormulaContext* Tokenizer::context() const
{
	return mContext;
}

void Tokenizer::setContext(FormulaContext* context)
{
	mContext = context;
}
