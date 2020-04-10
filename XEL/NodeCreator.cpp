#include "NodeCreator.h"

UnaryOperatorCreator::UnaryOperatorCreator()
{

}

BinaryOperatorCreator::BinaryOperatorCreator()
{

}

int BinaryOperatorCreator::priority() const
{
	return _priority;
}

void BinaryOperatorCreator::setPriority(int priority)
{
	_priority = priority;
}

Assoc BinaryOperatorCreator::assoc() const
{
	return _assoc;
}

void BinaryOperatorCreator::setAssoc(const Assoc& assoc)
{
	_assoc = assoc;
}
