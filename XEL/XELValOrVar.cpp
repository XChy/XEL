#include <XEL/XELValOrVar.h>

bool XELValOrVar::isVariable() const
{
	return node->isVariable();
}

void XELValOrVar::setVariable(const Variant& var) const
{
	node->setVariable(var);
}

Variant XELValOrVar::value() const
{
	return node->evaluate();
}

XELValOrVar::operator double() const
{
	return value();
}

XELValOrVar::operator long long() const
{
	return value();
}

XELValOrVar::operator bool() const
{
	return value();
}

XELValOrVar::operator XString() const
{
	return value();
}

XELValOrVar::operator Variant() const
{
	return value();
}
