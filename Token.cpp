#include "Token.h"

Token::Token()
{
	
}

Token::Token(TokenType type)
	:mType(type)
{

}

Token::Token(TokenType type, const Variant& value)
	:mType(type),
	  mValue(value)
{
}

TokenType Token::type() const
{
	return mType;
}

void Token::setType(const TokenType& type)
{
	mType = type;
}

Variant Token::value() const
{
	return mValue;
}

void Token::setValue(const Variant& value)
{
	mValue = value;
}
