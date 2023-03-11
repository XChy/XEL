#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <XEL/xel_global.h>
#include <XEL/Token.h>
#include <XEL/XELContext.h>

namespace XEL {

class XEL_EXPORT Tokenizer
{
   public:
    Tokenizer();
    virtual std::vector<Token> analyze(const XString& expression) const;

    XELContext* context() const;
    void setContext(XELContext* context);

   private:
    XELContext* _context;
    void analyzeDecAndNext(XString::const_iterator& it, XString& value,
                           std::vector<Token>& tokens) const;
    void analyzeHexAndNext(XString::const_iterator& it, XString& value,
                           std::vector<Token>& tokens) const;
    void analyzeBinAndNext(XString::const_iterator& it, XString& value,
                           std::vector<Token>& tokens) const;
};

}  // namespace XEL
#endif  // TOKENIZER_H
