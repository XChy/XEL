#ifndef FORMULACONTEXT_H
#define FORMULACONTEXT_H

#include <formulaengine_global.h>
#include <Variant.h>

class FORMULAENGINESHARED_EXPORT FormulaContext
{
public:
	FormulaContext();
	QString operatorChars() const;

	void setOperatorChars(const QString& operatorChars);
private:
	QHash<QString,Variant> mVariableMap;
	QString mOperatorChars;
};

#endif // FORMULACONTEXT_H
