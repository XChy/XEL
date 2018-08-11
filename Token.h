#ifndef TOKEN_H
#define TOKEN_H

#include <xel_global.h>
#include <Variant.h>

enum TokenType{
	Literal,
	Operator,
	Identifier,
	OpenParentheses,
	CloseParentheses,
	Comma
};

class XEL_EXPORT Token{
public:
	Token();
	Token(TokenType type);
	Token(TokenType type,const Variant& value);

	TokenType type() const;
	void setType(const TokenType& type);

	Variant value() const;
	void setValue(const Variant& value);

private:
	TokenType mType;
	Variant mValue;
};

#endif // TOKEN_H
