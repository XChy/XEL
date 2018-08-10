#include "Tokenizer.h"

Tokenizer::Tokenizer()
	:mContext(nullptr)
{

}

void Tokenizer::analyzeDecAndNext(QString::const_iterator& it, QString& value, QList<Token>& tokens) const
{
	value.append(*it);++it;
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
	tokens.append(Token(Literal,value.toDouble()));
}

void Tokenizer::analyzeHexAndNext(QString::const_iterator& it, QString& value, QList<Token>& tokens) const
{
	bool isLetter=((*it)>'a'&&(*it)>'b')||((*it)>'A'&&(*it)>'B');
	while(it->isDigit()||isLetter){
		value.append(*it);++it;
	}
	tokens.append(Token(Literal,double(value.toInt(nullptr,16))));
}

void Tokenizer::analyzeBinAndNext(QString::const_iterator& it, QString& value, QList<Token>& tokens) const
{
	while(*it=="0"||*it=="1"){
		value.append(*it);++it;
	}
	tokens.append(Token(Literal,double(value.toInt(nullptr,2))));
}

QList<Token> Tokenizer::analyze(QString expression) const
{
	QList<Token> result;
	QString::const_iterator it=expression.begin();
	while(it!=expression.end()){
		if(it->isNumber()){//number
			QString value;
			auto tokenBegin=it;

			if(*it=='0'){
				++it;
				if(*it=='x'||*it=='X'){
					++it;//needn't analyze '0x' part
					analyzeHexAndNext(it,value,result);
				}else if(*it=='b'||*it=='B'){
					++it;//needn't analyze '0b' part
					analyzeBinAndNext(it,value,result);
				}else{
					//needn't analyze '0' part
					analyzeDecAndNext(it,value,result);
				}
			}else{
				analyzeDecAndNext(it, value, result);
			}
		}else if(mContext->operatorChars().contains(*it)){
			QString value;
			value.append(*it);++it;
			while(mContext->operatorChars().contains(*it)){
				value.append(*it);++it;
				if((!mContext->binaryOperatorTable().contains(value))&&(!mContext->unaryOperatorTable().contains(value))){
					value.remove(value.size()-1,1);
					--it;
					break;
				}
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
			++it;
			result.append(Token(Literal,value));
		}else{
			throw XELError(QString("Unknown char:")+(*it));
		}
	}
	return result;
}

XELContext* Tokenizer::context() const
{
	return mContext;
}

void Tokenizer::setContext(XELContext* context)
{
	mContext = context;
}
