#ifndef FORMULAENGINE_H
#define FORMULAENGINE_H

#include "formulaengine_global.h"
#include <Variant.h>

class FORMULAENGINESHARED_EXPORT FormulaEngine
{

public:
	FormulaEngine();
	void setExpression(QString expression);
	QString expression() const;

	Variant evaluate();
private:
	QString mExpression;
};

#endif // FORMULAENGINE_H
