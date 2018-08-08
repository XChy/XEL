#ifndef FORMULACONTEXT_H
#define FORMULACONTEXT_H

#include <xel_global.h>
#include <NodeCreator.h>
#include <Variant.h>

class XELSHARED_EXPORT XELContext
{
public:
	XELContext();
	QString operatorChars() const;
	void setOperatorChars(const QString& operatorChars);

	QHash<QString, UnaryOperatorCreator*>& unaryOperatorTable();
	void setUnaryOperatorTable(const QHash<QString, UnaryOperatorCreator*>& unaryOperatorTable);

	QHash<QString, BinaryOperatorCreator*>& binaryOperatorTable();
	void setBinaryOperatorTable(const QHash<QString, BinaryOperatorCreator*>& binaryOperatorTable);

	QHash<QString, FunctionCreator*>& functionTable();
	void setFunctionTable(const QHash<QString, FunctionCreator*>& functionTable);

	QHash<QString, Variant>& variableTable();
	void setVariableTable(const QHash<QString, Variant>& variableTable);

private:
	QHash<QString,Variant> mVariableTable;
	QHash<QString,UnaryOperatorCreator*> mUnaryOperatorTable;
	QHash<QString,BinaryOperatorCreator*> mBinaryOperatorTable;
	QHash<QString,FunctionCreator*> mFunctionTable;
	QString mOperatorChars;
};

#endif // FORMULACONTEXT_H
