#ifndef NODECREATOR_H
#define NODECREATOR_H

#include <formulaengine_global.h>
#include <EvaluateNode.h>

class FORMULAENGINESHARED_EXPORT UnaryOperatorCreator{
public:
	UnaryOperatorCreator();
	virtual UnaryOperatorNode* create() const=0;
};

class FORMULAENGINESHARED_EXPORT BinaryOperatorCreator{
public:
	BinaryOperatorCreator();
	virtual BinaryOperatorNode* create() const=0;
	int priority() const;

	void setPriority(int priority);
private:
	int mPriority;
};

class FORMULAENGINESHARED_EXPORT FunctionCreator{
public:
	FunctionCreator();
	virtual FunctionNode* create() const=0;
};

#endif // NODECREATOR_H
