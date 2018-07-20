#ifndef FORMULACONTEXT_H
#define FORMULACONTEXT_H

#include <formulaengine_global.h>
#include <NodeCreator.h>
#include <Variant.h>

class FORMULAENGINESHARED_EXPORT FormulaContext
{
public:
	FormulaContext();
	QString operatorChars() const;

	QHash<QString, UnaryOperatorCreator*>& unaryOperatorTable();
	QHash<QString, BinaryOperatorCreator*>& binaryOperatorTable();
	QHash<QString, FunctionCreator*>& functionTable();
	QHash<QString, Variant>& variableTable();

	void setOperatorChars(const QString& operatorChars);
	void setUnaryOperatorTable(const QHash<QString, UnaryOperatorCreator*>& unaryOperatorTable);
	void setBinaryOperatorTable(const QHash<QString, BinaryOperatorCreator*>& binaryOperatorTable);
	void setFunctionTable(const QHash<QString, FunctionCreator*>& functionTable);
	void setVariableTable(const QHash<QString, Variant>& variableTable);

private:
	QHash<QString,Variant> mVariableTable;
	QHash<QString,UnaryOperatorCreator*> mUnaryOperatorTable;
	QHash<QString,BinaryOperatorCreator*> mBinaryOperatorTable;
	QHash<QString,FunctionCreator*> mFunctionTable;
	QString mOperatorChars;
};

#endif // FORMULACONTEXT_H
