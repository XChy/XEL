#ifndef VARIANT_H
#define VARIANT_H

#include <XEL/XELObject.h>
#include <XEL/XELError.h>

enum class VariantType {
	Double,
	Interger,
	String,
	Bool,
	Object,
	Null
};

struct VariantHolder {
public:
	union {
		double doubleValue;
		long long intergerValue;
		bool boolValue;
	};
	XString stringValue;
	XELObjectWrapper objectValue;
};

class XEL_EXPORT Variant
{
public:
	Variant();
	Variant(double value);
	Variant(long long value);
	Variant(int value);
	Variant(long value);
	Variant(const XString& value);
	Variant(bool value);
	Variant(const XELObjectWrapper& value);

	Variant(const Variant& value);

	// Don't change data member "type"
	void set(double value);
	void set(long long value);
	void set(const XString& value);
	void set(bool value);
	void set(const XELObjectWrapper& value);

	// Change data member "type" as corresponding VariantType
	void reset(double value);
	void reset(long long value);
	void reset(const XString& value);
	void reset(bool value);
	void reset(const XELObjectWrapper& value);

	// Change data member "type" as VariantType::Null
	void clear();

	// Safe:will throw error,
	// and convert int to double,double to int,int to bool
	// but don't convert double,int,bool to string
	double convertDouble() const;
	long long convertInterger() const;
	XString convertString() const;
	bool convertBool() const;
	XELObjectWrapper convertObject() const;

	//convert double,int,bool,Null to string
	XString toString() const;

	// Unsafe:read from memory directly
	double doubleValue() const;
	long long intergerValue() const;
	XString stringValue() const;
	bool boolValue() const;
	XELObjectWrapper objectValue() const;

	Variant& operator=(const Variant& variant);

	//reset(value)
	Variant& operator=(double value);
	Variant& operator=(long long value);
	Variant& operator=(const XString& value);
	Variant& operator=(bool value);
	Variant& operator=(const XELObjectWrapper& value);

	// (1==1.0):true
	bool operator==(const Variant& variant) const;

	VariantType type() const;

	static XString convertString(VariantType type);

	// convertXXX()
	operator double() const;
	operator long long() const;
	operator XString() const;
	operator bool() const;
	operator XELObjectWrapper() const;
private:
	VariantHolder _holder;
	VariantType _type;
};

//namespace std{

//template<>
//struct hash<Variant>
//{
//	size_t operator()(const Variant& v) const
//	{

//	}
//};

//}
#endif // VARIANT_H
