#include "Tokenizer.h"

using namespace XEL;
Tokenizer::Tokenizer() : _context(nullptr) {}

void Tokenizer::analyzeDecAndNext(XString::const_iterator& it, XString& value,
                                  std::vector<Token>& tokens) const
{
    bool isDouble = false;
    value.append(*it);
    ++it;
    while (it->isDigit()) {
        value.append(*it);
        ++it;
    }
    if (*it == '.') {
        isDouble = true;
        value.append(*it);
        ++it;
        ;  // add decimal point
        while (it->isDigit()) {
            value.append(*it);
            ++it;  // add number behind decimal point
        }
    }
    if (*it == 'e') {  // 'e' part
        value.append(*it);
        ++it;
        if (*it == '+' || *it == '-') {
            value.append(*it);
            ++it;
        }
        while (it->isDigit()) {
            value.append(*it);
            ++it;
        }
    }
    if (isDouble) {
        tokens.push_back(Token(Literal, value.toDouble()));
    } else {
        tokens.push_back(Token(Literal, value.toLongLong()));
    }
}

void Tokenizer::analyzeHexAndNext(XString::const_iterator& it, XString& value,
                                  std::vector<Token>& tokens) const
{
    while (it->isDigit() || ((*it) >= 'a' && (*it) <= 'f') ||
           ((*it) >= 'A' && (*it) <= 'F')) {
        value.append(*it);
        ++it;
    }
    tokens.push_back(Token(Literal, value.toLongLong(16)));
}

void Tokenizer::analyzeBinAndNext(XString::const_iterator& it, XString& value,
                                  std::vector<Token>& tokens) const
{
    while (*it == '0' || *it == '1') {
        value.append(*it);
        ++it;
    }
    tokens.push_back(Token(Literal, value.toLongLong(2)));
}

std::vector<Token> Tokenizer::analyze(const XString& expression) const
{
    std::vector<Token> result;
    XString::const_iterator it = expression.begin();
    while (it != expression.end()) {
        if (it->isDigit()) {  // number
            XString value;
            auto tokenBegin = it;

            if (*it == '0') {
                ++it;
                if (*it == 'x' || *it == 'X') {
                    ++it;  // needn't analyze '0x' part
                    analyzeHexAndNext(it, value, result);
                } else if (*it == 'b' || *it == 'B') {
                    ++it;  // needn't analyze '0b' part
                    analyzeBinAndNext(it, value, result);
                } else {
                    it = tokenBegin;
                    analyzeDecAndNext(it, value, result);
                }
            } else {
                analyzeDecAndNext(it, value, result);
            }
        } else if (_context->operatorChars().contains(*it)) {
            XString value;
            value.append(*it);
            ++it;
            while (_context->operatorChars().contains(*it)) {
                value.append(*it);
                ++it;
                if ((!_context->binaryOperatorTable().contains(value)) &&
                    (!_context->unaryOperatorTable().contains(value))) {
                    value.remove(value.size() - 1, 1);
                    --it;
                    break;
                }
            }
            result.push_back(Token(Operator, value));
        } else if (it->isLetter() || *it == '_') {
            XString value;
            value.append(*it);
            ++it;
            ;
            while (it->isLetterOrDigit() || *it == '_') {
                value.append(*it);
                ++it;
                ;
            }
            if (value == "true") {
                result.push_back(Token(Literal, true));
            } else if (value == "false") {
                result.push_back(Token(Literal, false));
            } else if (value == "null") {
                result.push_back(Token(Literal, Variant()));
            } else {
                result.push_back(Token(Identifier, value));
            }
        } else if (*it == '(') {
            result.push_back(Token(OpenParentheses));
            ++it;
        } else if (*it == ')') {
            result.push_back(Token(CloseParentheses));
            ++it;
        } else if (*it == ',') {
            result.push_back(Token(Comma));
            ++it;
            ;
        } else if (*it == '\"') {
            ++it;
            XString value;
            while (*it != '\"') {
                value.append(*it);
                ++it;
            }
            ++it;
            result.push_back(Token(Literal, value));
        } else if (*it == '.') {
            ++it;
            result.push_back(Token(Dot));
        } else if (it->isSpace()) {
            ++it;
        } else {
            throw XELError(XString("Unknown char:").append(*it));
        }
    }
    return result;
}

XELContext* Tokenizer::context() const { return _context; }

void Tokenizer::setContext(XELContext* context) { _context = context; }
