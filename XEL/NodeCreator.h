#ifndef NODECREATOR_H
#define NODECREATOR_H

#include <XEL/xel_global.h>
#include <XEL/EvaluateNode.h>

class XEL_EXPORT UnaryOperatorCreator{
public:
	UnaryOperatorCreator();
	virtual UnaryOperatorNode* create() const=0;
};

enum Assoc{//Associativity
	LeftToRight,
	RightToLeft
};

class XEL_EXPORT BinaryOperatorCreator{
public:
	BinaryOperatorCreator();
	virtual BinaryOperatorNode* create() const=0;

	int priority() const;
	void setPriority(int priority);

	Assoc assoc() const;
	void setAssoc(const Assoc& assoc);
private:
	int _priority;
	Assoc _assoc;
};

class XEL_EXPORT FunctionCreator{
public:
	FunctionCreator() {};
	virtual FunctionNode* create() const=0;
	virtual FunctionNode* create(int paramSize) const=0;
	virtual bool isVariableParam() const=0;
	virtual bool isSupportParamSize(int paramSize) const=0;
};

#endif // NODECREATOR_H
