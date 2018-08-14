#ifndef NODECREATOR_H
#define NODECREATOR_H

#include <xel_global.h>
#include <EvaluateNode.h>

class XEL_EXPORT UnaryOperatorCreator{
public:
	UnaryOperatorCreator();
	virtual UnaryOperatorNode* create() const=0;
};

class XEL_EXPORT BinaryOperatorCreator{
public:
	BinaryOperatorCreator();
	virtual BinaryOperatorNode* create() const=0;

	int priority() const;
	void setPriority(int priority);
private:
	int mPriority;
};

class XEL_EXPORT FunctionCreator{
public:
	FunctionCreator();
	virtual FunctionNode* create() const=0;
};

#endif // NODECREATOR_H
