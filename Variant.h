#ifndef VARIANT_H
#define VARIANT_H

#include <FormulaError.h>

enum class VariantType{
	Double,
	String,
	Bool,
	Unknown
};

template<typename T>
class ConcreteHolder;

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

class FORMULAENGINESHARED_EXPORT Variant
{
public:
	Variant();
	template<typename T>
	Variant(const T& variant)
		:mType(typeOf<T>()),
		  mHolder(new ConcreteHolder<T>(variant))
	{}
	Variant(const Variant& value);

	template<typename T>
	void set(const T& variant){
		mHolder->toConcrete<T>()->setData(variant);
	}

	template<typename T>
	void reset(const T& variant){
		delete mHolder;
		mType=typeOf<T>();
		mHolder=new ConcreteHolder<T>(variant);
	}

	void clear();

	double toDouble() const;
	QString toString() const;
	bool toBool() const;

	double castDouble() const;
	QString castString() const;
	bool castBool() const;

	Variant& operator=(const Variant& variant);
	template<typename T>
	Variant& operator=(const T& variant){
		reset(variant);
		return *this;
	}

	VariantType type() const;

	template<typename T>
	static VariantType typeOf(){
		if(std::is_same<T,double>::value)return VariantType::Double;
		if(std::is_same<T,QString>::value)return VariantType::String;
		if(std::is_same<T,bool>::value)return VariantType::Bool;
		return VariantType::Unknown;
	}

	static QString toString(VariantType type);

	~Variant();

private:
	VariantHolder* mHolder;
	VariantType mType;
};

#endif // VARIANT_H
