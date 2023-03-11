#include "Token.h"

using namespace XEL;
Token::Token() {}

Token::Token(TokenType type) : _type(type) {}

Token::Token(TokenType type, const Variant& value) : _type(type), _value(value)
{
}

TokenType Token::type() const { return _type; }

void Token::setType(const TokenType& type) { _type = type; }

Variant Token::value() const { return _value; }

void Token::setValue(const Variant& value) { _value = value; }
