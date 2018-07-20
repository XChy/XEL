#include "Variant.h"
class VariantHolder{
public:
	template<typename T>
	ConcreteHolder<T>* toConcrete(){
		return static_cast<ConcreteHolder<T>*>(this);
	}
	virtual ~VariantHolder(){}
};

template<typename T>
class ConcreteHolder:public VariantHolder{
public:
	ConcreteHolder(){}
	ConcreteHolder(T data){
		mData=data;
	}
	T data(){
		return mData;
	}
	void setData(const T& data){
		mData=data;
	}
private:
	T mData;
};

Variant::Variant()
	:mType(VariantType::Unknown),
	  mHolder(nullptr)
{}

Variant::Variant(const Variant& value)
	:mType(value.type())
{
	switch (value.type()) {
		case VariantType::Double:
			mHolder=new ConcreteHolder<double>(value.toDouble());
			break;
		case VariantType::String:
			mHolder=new ConcreteHolder<QString>(value.toString());
			break;
		case VariantType::Bool:
			mHolder=new ConcreteHolder<bool>(value.toBool());
			break;
		default:
			mHolder=nullptr;
	}
}

template<typename T>
Variant::Variant(const T& variant)
	:mType(typeOf<T>()),
	  mHolder(new ConcreteHolder<T>(variant))
{
}

template<typename T>
void Variant::set(const T& variant)
{
	mHolder->toConcrete<T>()->setData(variant);
}

template<typename T>
void Variant::reset(const T& variant)
{
	delete mHolder;
	mType=typeOf<T>();
	mHolder=new ConcreteHolder<T>(variant);
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
	throw FormulaError("Cannot cast "+Variant::toString(mType)+" to Double");
}

QString Variant::toString() const
{
	if(mType==VariantType::String){
		return mHolder->toConcrete<QString>()->data();
	}
	throw FormulaError("Cannot cast "+Variant::toString(mType)+" to String");
}

bool Variant::toBool() const
{
	if(mType==VariantType::Bool){
		return mHolder->toConcrete<bool>()->data();
	}
	throw FormulaError("Cannot cast "+Variant::toString(mType)+" to Bool");
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
				mHolder=new ConcreteHolder<double>;
				break;
			case VariantType::String:
				mHolder=new ConcreteHolder<QString>;
				break;
			case VariantType::Bool:
				mHolder=new ConcreteHolder<bool>;
				break;
		}
	}
	mType=variant.type();
	return *this;
}

template<typename T>
Variant& Variant::operator=(const T& variant)
{
	reset(variant);
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

template<typename T>
VariantType Variant::typeOf()
{
	if(std::is_same<T,double>::value)return VariantType::Double;
	if(std::is_same<T,QString>::value)return VariantType::String;
	if(std::is_same<T,bool>::value)return VariantType::Bool;
	return VariantType::Unknown;
}

template FORMULAENGINESHARED_EXPORT Variant::Variant(const double& variant);
template FORMULAENGINESHARED_EXPORT Variant::Variant(const QString& variant);
template FORMULAENGINESHARED_EXPORT Variant::Variant(const bool& variant);

template FORMULAENGINESHARED_EXPORT void Variant::set(const double& variant);
template FORMULAENGINESHARED_EXPORT void Variant::set(const QString& variant);
template FORMULAENGINESHARED_EXPORT void Variant::set(const bool& variant);

template FORMULAENGINESHARED_EXPORT void Variant::reset(const double& variant);
template FORMULAENGINESHARED_EXPORT void Variant::reset(const QString& variant);
template FORMULAENGINESHARED_EXPORT void Variant::reset(const bool& variant);

template FORMULAENGINESHARED_EXPORT VariantType Variant::typeOf<double>();
template FORMULAENGINESHARED_EXPORT VariantType Variant::typeOf<QString>();
template FORMULAENGINESHARED_EXPORT VariantType Variant::typeOf<bool>();
