#ifndef XELENGINE_H
#define XELENGINE_H

#include <cmath>

#include "XEL/xel_global.h"
#include <XEL/XELContext.h>
#include <XEL/Variant.h>
#include <XEL/Tokenizer.h>
#include <XEL/Parser.h>
#include <XEL/XELUtils.h>
#include <XEL/Expression.h>

class XEL_EXPORT XELEngine
{
   public:
    XELEngine();

    template <typename Func>
    void setUnaryOperator(const XString& name, Func func)
    {
        _context->unaryOperatorTable()[name] =
            XELUtils::creatorForUnaryOperator<Func>(func);
    }

    template <typename Func>
    void setBinaryOperator(const XString& name, Func func, int priority,
                           Assoc assoc = LeftToRight)
    {
        _context->binaryOperatorTable()[name] =
            XELUtils::creatorForBinaryOperator<Func>(func, priority, assoc);
    }

    template <typename R, typename... args>
    void setFunction(const XString& name, const std::function<R(args...)>& func)
    {
        _context->functionTable()[name] =
            XELUtils::creatorForFunction<R, args...>(func);
    }

    template <typename Func>
    void setVariableParamFunction(const XString& name, Func _func)
    {
        _context->functionTable()[name] =
            XELUtils::creatorForVariableParamFunction<Func>(_func);
    }

    Expression compile(const XString& expr);

    Variant& variable(const XString& name);
    void setVariable(const XString& name, const Variant& value);
    void removeVariable(XString name);

    std::shared_ptr<XELContext> context() const;
    void setContext(const std::shared_ptr<XELContext>& context);

    std::shared_ptr<Tokenizer> tokenizer() const;
    void setTokenizer(const std::shared_ptr<Tokenizer>& tokenizer);

    std::shared_ptr<Parser> parser() const;
    void setParser(const std::shared_ptr<Parser>& parser);

   private:
    std::shared_ptr<XELContext> _context;
    std::shared_ptr<Tokenizer> _tokenizer;
    std::shared_ptr<Parser> _parser;
};

#endif  // FORMULAENGINE_H
