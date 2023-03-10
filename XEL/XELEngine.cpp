#include "XELEngine.h"
#include <XEL/XELContainerObject.h>
#include <cmath>
#include "XEL/EvaluateNode.h"

XELEngine::XELEngine()
    : _context(new XELContext), _parser(new Parser), _tokenizer(new Tokenizer)
{
    _parser->setContext(_context.get());
    _tokenizer->setContext(_context.get());
    setUnaryOperator("-", [](const Variant& v) -> Variant {
        if (v.type() == VariantType::Interger) {
            return -v.intergerValue();
        } else if (v.type() == VariantType::Double) {
            return -v.doubleValue();
        } else {
            throw XELError("Unary operator '-' cannot eval value as " +
                           Variant::convertString(v.type()));
        }
    });
    setUnaryOperator("!", [](bool o) -> bool { return !o; });
    setBinaryOperator(
        ">",
        [](const Variant& left, const Variant& right) {
            switch (left.type()) {
                case VariantType::Double:
                    return left.doubleValue() > double(right);
                case VariantType::Interger:
                    if (right.type() == VariantType::Interger)
                        return left.intergerValue() > right.intergerValue();
                    else if (right.type() == VariantType::Double)
                        return double(left.intergerValue()) >
                               right.doubleValue();
                default:
                    return false;
            }
        },
        1);
    setBinaryOperator(
        ">=",
        [](const Variant& left, const Variant& right) {
            switch (left.type()) {
                case VariantType::Double:
                    return left.doubleValue() >= double(right);
                case VariantType::Interger:
                    if (right.type() == VariantType::Interger)
                        return left.intergerValue() >= right.intergerValue();
                    else if (right.type() == VariantType::Double)
                        return double(left.intergerValue()) >=
                               right.doubleValue();
                default:
                    return false;
            }
        },
        1);
    setBinaryOperator(
        "<",
        [](const Variant& left, const Variant& right) {
            switch (left.type()) {
                case VariantType::Double:
                    return left.doubleValue() < double(right);
                case VariantType::Interger:
                    if (right.type() == VariantType::Interger)
                        return left.intergerValue() < right.intergerValue();
                    else if (right.type() == VariantType::Double)
                        return double(left.intergerValue()) <
                               right.doubleValue();
                default:
                    return false;
            }
        },
        1);
    setBinaryOperator(
        "<=",
        [](const Variant& left, const Variant& right) {
            switch (left.type()) {
                case VariantType::Double:
                    return left.doubleValue() <= double(right);
                case VariantType::Interger:
                    if (right.type() == VariantType::Interger)
                        return left.intergerValue() <= right.intergerValue();
                    else if (right.type() == VariantType::Double)
                        return double(left.intergerValue()) <=
                               right.doubleValue();
                default:
                    return false;
            }
        },
        1);
    setBinaryOperator(
        "==",
        [](const Variant& left, const Variant& right) { return left == right; },
        0);
    setBinaryOperator(
        "||", [](bool left, bool right) { return left || right; }, 1);
    setBinaryOperator(
        "&&", [](bool left, bool right) { return left && right; }, 1);
    setBinaryOperator(
        "+", [](double left, double right) { return left + right; }, 1);
    setBinaryOperator(
        "-", [](double left, double right) { return left - right; }, 1);
    setBinaryOperator(
        "*", [](double left, double right) { return left * right; }, 2);
    setBinaryOperator(
        "/", [](double left, double right) { return left / right; }, 2);
    setBinaryOperator(
        "**", [](double left, double right) { return pow(left, right); }, 2);
    setBinaryOperator(
        "|", [](long long left, long long right) { return left | right; }, 3,
        RightToLeft);
    setBinaryOperator(
        "&", [](long long left, long long right) { return left & right; }, 3,
        RightToLeft);
    setBinaryOperator(
        "^", [](long long left, long long right) { return left ^ right; }, 3,
        RightToLeft);
    setFunction("sin", std::function<double(double)>(
                           static_cast<double (*)(double)>(sin)));
    setFunction("tan", std::function<double(double)>(
                           static_cast<double (*)(double)>(tan)));
    setFunction("cos", std::function<double(double)>(
                           static_cast<double (*)(double)>(&cos)));
    setFunction("abs", std::function<double(double)>(
                           static_cast<double (*)(double)>(&fabs)));
    setFunction("exp", std::function<double(double)>(
                           static_cast<double (*)(double)>(&exp)));
    setFunction("log10", std::function<double(double)>(
                             static_cast<double (*)(double)>(&log10)));
    setFunction("log2", std::function<double(double)>(
                            static_cast<double (*)(double)>(&log2)));
    setFunction("ln", std::function<double(double)>(
                          static_cast<double (*)(double)>(&log)));
    setFunction("log", std::function<double(double, double)>(
                           [](double base, double n) -> double {
                               return log(n) / log(base);
                           }));
    setFunction("reverse",
                std::function<XString(XString)>(
                    [](XString str) -> XString { return str.reverse(); }));
    setFunction("size", std::function<int(XString)>(
                            [](XString str) -> int { return str.size(); }));
    setVariableParamFunction("vector",
                             [](const std::vector<Variant> params) -> Variant {
                                 XVectorObject* obj = new XVectorObject;
                                 obj->setVector(params);
                                 return XELObjectWrapper(obj);
                             });
    setVariableParamFunction(
        "map", [](const std::vector<Variant> params) -> Variant {
            XMapObject* obj = new XMapObject;
            XHashMap<XString, Variant> map;
            if (params.size() % 2 != 0) {
                throw XELError("Params are not applied to the map");
            } else {
                for (size_t i = 0; i < params.size(); i += 2) {
                    map[params[i]] = params[i + 1];
                }
            }
            obj->setMap(std::move(map));
            return XELObjectWrapper(obj);
        });
}

Expression XELEngine::compile(const XString& expr)
{
    EvaluateNode* node = _parser->parse(_tokenizer->analyze(expr));
    return std::move(Expression(node));
}

Variant& XELEngine::variable(const XString& name)
{
    return _context->variableTable()[name];
}

void XELEngine::setVariable(const XString& name, const Variant& value)
{
    _context->variableTable()[name] = value;
}

void XELEngine::removeVariable(XString name)
{
    _context->variableTable().remove(name);
}

std::shared_ptr<XELContext> XELEngine::context() const { return _context; }

void XELEngine::setContext(const std::shared_ptr<XELContext>& context)
{
    _parser->setContext(context.get());
    _tokenizer->setContext(context.get());
    _context = context;
}

std::shared_ptr<Tokenizer> XELEngine::tokenizer() const { return _tokenizer; }

void XELEngine::setTokenizer(const std::shared_ptr<Tokenizer>& tokenizer)
{
    _tokenizer = tokenizer;
}

std::shared_ptr<Parser> XELEngine::parser() const { return _parser; }

void XELEngine::setParser(const std::shared_ptr<Parser>& parser)
{
    _parser = parser;
}
