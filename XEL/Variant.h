#ifndef VARIANT_H
#define VARIANT_H

#include <XEL/XELError.h>

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
	XString stringValue;
};

class XEL_EXPORT Variant
{
public:
	Variant();
	Variant(double value);
	Variant(int value);
	Variant(const XString& value);
	Variant(bool value);

	Variant(const Variant& value);

	// Don't change data member "type"
	void set(double value);
	void set(int value);
	void set(const XString& value);
	void set(bool value);

	// Change data member "type" as corresponding VariantType
	void reset(double value);
	void reset(int value);
	void reset(const XString& value);
	void reset(bool value);

	// Change data member "type" as VariantType::Null
	void clear();

	// Safe:will throw error,
	// and convert int to double,double to int,int to bool
	// but don't convert double,int,bool to string
	double convertDouble() const;
	int convertInt() const;
	XString convertString() const;
	bool convertBool() const;

	//convert double,int,bool,Null to string
	XString toString() const;

	// Unsafe:read from memory directly
	double doubleValue() const;
	int intValue() const;
	XString stringValue() const;
	bool boolValue() const;

	Variant& operator=(const Variant& variant);

	//reset(value)
	Variant& operator=(double value);
	Variant& operator=(int value);
	Variant& operator=(const XString& value);
	Variant& operator=(bool value);

	// (1==1.0):true
	bool operator==(const Variant& variant) const;

	VariantType type() const;

	static XString convertString(VariantType type);

	// convertXXX()
	operator double() const;
	operator int() const;
	operator XString() const;
	operator bool() const;
private:
	VariantHolder mHolder;
	VariantType mType;
};

#endif // VARIANT_H