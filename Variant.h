#ifndef VARIANT_H
#define VARIANT_H

#include <XELError.h>

enum class VariantType{
	Double,
	Int,
	String,
	Bool,
	Null
};

struct VariantHolder{
public:
	union{
	double doubleValue;
	int intValue;
	bool boolValue;
	};
	QString stringValue;
};

class XEL_EXPORT Variant
{
public:
	Variant();
	Variant(double value);
	Variant(int value);
	Variant(const QString value);
	Variant(bool value);

	Variant(const Variant& value);

	// Don't change data member "type"
	void set(double value);
	void set(int value);
	void set(const QString& value);
	void set(bool value);

	// Change data member "type" as corresponding VariantType
	void reset(double value);
	void reset(int value);
	void reset(const QString& value);
	void reset(bool value);

	// Change data member "type" as VariantType::Null
	void clear();

	// Safe:will throw error,
	// and convert int to double,double to int,int to bool
	// but don't convert double,int,bool to string
	double convertDouble() const;
	int convertInt() const;
	QString convertString() const;
	bool convertBool() const;

	//convert double,int,bool,Null to string
	QString toString() const;

	// Unsafe:read from memory directly
	double doubleValue() const;
	int intValue() const;
	QString stringValue() const;
	bool boolValue() const;

	Variant& operator=(const Variant& variant);

	//reset(value)
	Variant& operator=(double value);
	Variant& operator=(int value);
	Variant& operator=(const QString& value);
	Variant& operator=(bool value);

	// (1==1.0):true
	bool operator==(const Variant& variant) const;

	VariantType type() const;

	static QString convertString(VariantType type);

	// convertXXX()
	operator double() const;
	operator int() const;
	operator QString() const;
	operator bool() const;
private:
	VariantHolder mHolder;
	VariantType mType;
};

#endif // VARIANT_H
