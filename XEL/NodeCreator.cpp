#include "NodeCreator.h"

UnaryOperatorCreator::UnaryOperatorCreator()
{

}

BinaryOperatorCreator::BinaryOperatorCreator()
	:_priority(0), _assoc(LeftToRight)
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
