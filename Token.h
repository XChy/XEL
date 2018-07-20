#ifndef TOKEN_H
#define TOKEN_H

#include <formulaengine_global.h>
#include <Variant.h>

enum TokenType{
	Literal,
	Operator,
	Identifier,
	OpenParentheses,
	CloseParentheses,
	Comma
};

class FORMULAENGINESHARED_EXPORT Token
{
public:
	Token();
	Token(TokenType type);
	Token(TokenType type,const Variant& value);
	TokenType type() const;
	Variant value() const;

	void setType(const TokenType& type);
	void setValue(const Variant& value);

private:
	TokenType mType;
	Variant mValue;
};

#endif // TOKEN_H
