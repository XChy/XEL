#include <XEL/XELFunctions.h>

Variant SinFunction::SinNode::evaluate() const
{
	Variant arg=parameters()[0]->evaluate();
	if(arg.type()==VariantType::Interger){
		return sin(arg.intergerValue());
	}else if(arg.type()==VariantType::Double){
		return sin(arg.doubleValue());
	}
	throw XELError("can not sin("+Variant::convertString(arg.type())+")");
}

FunctionNode* SinFunction::create(int paramSize) const
{
	return paramSize==1?new SinNode:nullptr;
}

Variant CosFunction::CosNode::evaluate() const
{
	Variant arg=parameters()[0]->evaluate();
	if(arg.type()==VariantType::Interger){
		return cos(arg.intergerValue());
	}else if(arg.type()==VariantType::Double){
		return cos(arg.doubleValue());
	}
	throw XELError("can not cos("+Variant::convertString(arg.type())+")");
}

FunctionNode* CosFunction::create(int paramSize) const
{
	return paramSize==1?new CosNode:nullptr;
}

Variant TanFunction::TanNode::evaluate() const
{
	Variant arg=parameters()[0]->evaluate();
	if(arg.type()==VariantType::Interger){
		return tan(arg.intergerValue());
	}else if(arg.type()==VariantType::Double){
		return tan(arg.doubleValue());
	}
	throw XELError("can not cos("+Variant::convertString(arg.type())+")");
}

FunctionNode* TanFunction::create(int paramSize) const
{
	return paramSize==1?new TanNode:nullptr;
}

double cot(double x)
{
	return 1/tan(x);
}

Variant CotFunction::CotNode::evaluate() const
{
	Variant arg=parameters()[0]->evaluate();
	if(arg.type()==VariantType::Interger){
		return cot(arg.intergerValue());
	}else if(arg.type()==VariantType::Double){
		return cot(arg.doubleValue());
	}
	throw XELError("can not cos("+Variant::convertString(arg.type())+")");
}

FunctionNode* CotFunction::create(int paramSize) const
{
	return paramSize==1?new CotNode:nullptr;
}


