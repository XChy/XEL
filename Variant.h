#ifndef VARIANT_H
#define VARIANT_H

#include <FormulaError.h>

enum class VariantType{
	Double,
	String,
	Bool,
	Unknown
};

class VariantHolder;
template<typename T>
class ConcreteHolder;

class FORMULAENGINESHARED_EXPORT Variant
{
public:
	Variant();
	template<typename T>
	Variant(const T& variant);
	Variant(const Variant& value);

	template<typename T>
	void set(const T& variant);

	template<typename T>
	void reset(const T& variant);

	void clear();

	double toDouble() const;
	QString toString() const;
	bool toBool() const;

	double castDouble() const;
	QString castString() const;
	bool castBool() const;

	Variant& operator=(const Variant& variant);
	template<typename T>
	Variant& operator=(const T& variant);

	VariantType type() const;

	template<typename T>
	static VariantType typeOf();

	~Variant();

private:
	static QString toString(VariantType type);
	VariantHolder* mHolder;
	VariantType mType;
};

#endif // VARIANT_H
