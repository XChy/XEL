#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <formulaengine_global.h>
#include <Token.h>
#include <FormulaContext.h>

class FORMULAENGINESHARED_EXPORT Tokenizer
{
public:
	Tokenizer();
	QList<Token> analyze(QString expression) const;
	FormulaContext* context() const;

	void setContext(FormulaContext* context);
private:
	FormulaContext* mContext;
};

#endif // TOKENIZER_H
