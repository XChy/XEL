#include "NodeCreator.h"

UnaryOperatorCreator::UnaryOperatorCreator()
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

FunctionCreator::FunctionCreator()
{

}
