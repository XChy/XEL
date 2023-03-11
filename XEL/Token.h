#ifndef TOKEN_H
#define TOKEN_H

#include <XEL/xel_global.h>
#include <XEL/Variant.h>
namespace XEL {

enum TokenType {
    Literal,
    Operator,
    Identifier,
    OpenParentheses,
    CloseParentheses,
    Comma,
    Dot
};

class XEL_EXPORT Token
{
   public:
    Token();
    Token(TokenType type);
    Token(TokenType type, const Variant& value);

    TokenType type() const;
    void setType(const TokenType& type);

    Variant value() const;
    void setValue(const Variant& value);

   private:
    TokenType _type;
    Variant _value;
};

}  // namespace XEL

#endif  // TOKEN_H
