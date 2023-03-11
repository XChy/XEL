#include "Variant.h"

namespace XEL {

Variant::Variant() : _type(VariantType::Null) {}

Variant::Variant(double value) { reset(value); }

Variant::Variant(long long value) { reset(value); }

Variant::Variant(int value) { reset((long long)(value)); }

Variant::Variant(long value) { reset((long long)(value)); }

Variant::Variant(const XString &value) { reset(value); }

Variant::Variant(bool value) { reset(value); }

Variant::Variant(const XELObjectWrapper &value) { reset(value); }

Variant::Variant(const Variant &value)
    : _type(value.type()), _holder(value._holder)
{
}

void Variant::set(double value) { _holder.doubleValue = value; }

void Variant::set(long long value) { _holder.intergerValue = value; }

void Variant::set(const XString &value) { _holder.stringValue = value; }

void Variant::set(bool value) { _holder.boolValue = value; }

void Variant::set(const XELObjectWrapper &value)
{
    _holder.objectValue = value;
}

void Variant::reset(double value)
{
    _type = VariantType::Double;
    set(value);
}

void Variant::reset(long long value)
{
    _type = VariantType::Interger;
    set(value);
}

void Variant::reset(const XString &value)
{
    _type = VariantType::String;
    set(value);
}

void Variant::reset(bool value)
{
    _type = VariantType::Bool;
    set(value);
}

void Variant::reset(const XELObjectWrapper &value)
{
    _type = VariantType::Object;
    set(value);
}

void Variant::clear() { _type = VariantType::Null; }

double Variant::convertDouble() const
{
    if (_type == VariantType::Double) {
        return _holder.doubleValue;
    } else if (_type == VariantType::Interger) {
        return double(_holder.intergerValue);
    }
    throw XELError("Cannot convert " + Variant::convertString(_type) +
                   " to Double");
}

long long Variant::convertInterger() const
{
    if (_type == VariantType::Double) {
        return int(_holder.doubleValue);
    } else if (_type == VariantType::Interger) {
        return _holder.intergerValue;
    }
    throw XELError("Cannot convert " + Variant::convertString(_type) +
                   " to Double");
}

XString Variant::convertString() const
{
    if (_type == VariantType::String) {
        return _holder.stringValue;
    }
    throw XELError("Cannot convert " + Variant::convertString(_type) +
                   " to String");
}

bool Variant::convertBool() const
{
    if (_type == VariantType::Bool) {
        return _holder.boolValue;
    } else if (_type == VariantType::Interger) {
        return _holder.intergerValue;
    }
    throw XELError("Cannot convert " + Variant::convertString(_type) +
                   " to Bool");
}

XELObjectWrapper Variant::convertObject() const
{
    if (_type == VariantType::Object) {
        return _holder.objectValue;
    }
    throw XELError("Cannot convert " + Variant::convertString(_type) +
                   " to Object");
}

XString Variant::toString() const
{
    switch (type()) {
        case VariantType::Double:
            return XString::number(_holder.doubleValue);
        case VariantType::Interger:
            return XString::number(_holder.intergerValue);
        case VariantType::String:
            return XString("\"").append(_holder.stringValue).append("\"");
        case VariantType::Bool:
            return _holder.boolValue ? "true" : "false";
        case VariantType::Object:
            return _holder.objectValue.data()->toString();
        case VariantType::Null:
            return "null";
    }
}

double Variant::doubleValue() const { return _holder.doubleValue; }

long long Variant::intergerValue() const { return _holder.intergerValue; }

XString Variant::stringValue() const { return _holder.stringValue; }

bool Variant::boolValue() const { return _holder.boolValue; }

XELObjectWrapper Variant::objectValue() const { return _holder.objectValue; }

Variant &Variant::operator=(const Variant &variant)
{
    _type = variant.type();
    _holder = variant._holder;
    return *this;
}

Variant &Variant::operator=(double value)
{
    reset(value);
    return *this;
}

Variant &Variant::operator=(long long value)
{
    reset(value);
    return *this;
}

Variant &Variant::operator=(const XString &value)
{
    reset(value);
    return *this;
}

Variant &Variant::operator=(bool value)
{
    reset(value);
    return *this;
}

Variant &Variant::operator=(const XELObjectWrapper &value)
{
    reset(value);
    return *this;
}

bool Variant::operator==(const Variant &variant) const
{
    if (type() == VariantType::Double) {
        if (variant.type() == VariantType::Interger) {
            return _holder.doubleValue == double(variant._holder.intergerValue);
        } else if (variant.type() == VariantType::Double) {
            return _holder.doubleValue == variant._holder.doubleValue;
        }
    } else if (type() == VariantType::Interger) {
        if (variant.type() == VariantType::Interger) {
            return _holder.intergerValue == variant._holder.intergerValue;
        } else if (variant.type() == VariantType::Double) {
            return double(_holder.intergerValue) == variant._holder.doubleValue;
        }
    } else if (type() == VariantType::String &&
               variant.type() == VariantType::String) {
        return _holder.stringValue == variant._holder.stringValue;
    } else if (type() == VariantType::Bool &&
               variant.type() == VariantType::Bool) {
        return _holder.boolValue == variant._holder.boolValue;
    }
    return false;
}

VariantType Variant::type() const { return _type; }

XString Variant::convertString(VariantType type)
{
    switch (type) {
        case VariantType::Double:
            return "Double";
        case VariantType::Interger:
            return "Int";
        case VariantType::String:
            return "String";
        case VariantType::Bool:
            return "Bool";
        case VariantType::Null:
            return "Null";
    }
}

Variant::operator double() const { return convertDouble(); }

Variant::operator long long() const { return convertInterger(); }

Variant::operator XString() const { return convertString(); }

Variant::operator bool() const { return convertBool(); }

Variant::operator XELObjectWrapper() const { return convertObject(); }

}  // namespace XEL
