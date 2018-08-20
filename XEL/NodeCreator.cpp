#include "NodeCreator.h"

UnaryOperatorCreator::UnaryOperatorCreator()
{

}

BinaryOperatorCreator::BinaryOperatorCreator()
{

}

int BinaryOperatorCreator::priority() const
{
	return mPriority;
}

void BinaryOperatorCreator::setPriority(int priority)
{
	mPriority = priority;
}

Assoc BinaryOperatorCreator::assoc() const
{
	return mAssoc;
}

void BinaryOperatorCreator::setAssoc(const Assoc& assoc)
{
	mAssoc = assoc;
}

XELFunction::XELFunction()
{

}
