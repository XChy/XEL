#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <xel_global.h>
#include <Token.h>
#include <XELContext.h>

class XELSHARED_EXPORT Tokenizer
{
public:
	Tokenizer();
	virtual QList<Token> analyze(QString expression) const;

	XELContext* context() const;
	void setContext(XELContext* context);
private:
	XELContext* mContext;
	void analyzeDecAndNext(QString::const_iterator& it, QString& value, QList<Token>& tokens) const;
	void analyzeHexAndNext(QString::const_iterator& it, QString& value, QList<Token>& tokens) const;
	void analyzeBinAndNext(QString::const_iterator& it, QString& value, QList<Token>& tokens) const;
};

#endif // TOKENIZER_H
