#include "Variant.h"

Variant::Variant()
	:mType(VariantType::Unknown),
	  mHolder(nullptr)
{}

Variant::Variant(const Variant& value)
	:mType(value.type())
{
	switch (value.type()) {
		case VariantType::Double:
			mHolder=new ConcreteHolder<double>(value.castDouble());
			break;
		case VariantType::String:
			mHolder=new ConcreteHolder<QString>(value.castString());
			break;
		case VariantType::Bool:
			mHolder=new ConcreteHolder<bool>(value.castBool());
			break;
		default:
			mHolder=nullptr;
	}
}

void Variant::clear()
{
	mType=VariantType::Unknown;
	delete mHolder;
	mHolder=nullptr;
}

double Variant::toDouble() const
{
	if(mType==VariantType::Double){
		return mHolder->toConcrete<double>()->data();
	}
	throw XELError("Cannot cast "+Variant::toString(mType)+" to Double");
}

QString Variant::toString() const
{
	if(mType==VariantType::String){
		return mHolder->toConcrete<QString>()->data();
	}
	throw XELError("Cannot cast "+Variant::toString(mType)+" to String");
}

bool Variant::toBool() const
{
	if(mType==VariantType::Bool){
		return mHolder->toConcrete<bool>()->data();
	}
	throw XELError("Cannot cast "+Variant::toString(mType)+" to Bool");
}

double Variant::castDouble() const
{
	return mHolder->toConcrete<double>()->data();
}

QString Variant::castString() const
{
	return mHolder->toConcrete<QString>()->data();
}

bool Variant::castBool() const
{
	return mHolder->toConcrete<bool>()->data();
}

Variant& Variant::operator=(const Variant& variant)
{
	delete mHolder;
	if(variant.type()==VariantType::Unknown){
		mHolder=nullptr;
	}else{
		switch (variant.type()) {
			case VariantType::Double:
				mHolder=new ConcreteHolder<double>(variant.castDouble());
				break;
			case VariantType::String:
				mHolder=new ConcreteHolder<QString>(variant.castString());;
				break;
			case VariantType::Bool:
				mHolder=new ConcreteHolder<bool>(variant.castBool());;
				break;
		}
	}
	mType=variant.type();
	return *this;
}


VariantType Variant::type() const
{
	return mType;
}

Variant::~Variant()
{
	delete mHolder;
}

QString Variant::toString(VariantType type)
{
	switch(type){
		case VariantType::Double:
			return "Double";
		case VariantType::String:
			return "String";
		case VariantType::Bool:
			return "Bool";
		case VariantType::Unknown:
			return "Unknown";
	}
}
