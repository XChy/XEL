#include <XEL/XELObject.h>
#include <XEL/Variant.h>

using namespace XEL;

XELObjectWrapper::XELObjectWrapper() : XSharedData<XELObject>() {}

XELObjectWrapper::XELObjectWrapper(XELObject* object)
    : XSharedData<XELObject>(object)
{
}

XELObjectWrapper::XELObjectWrapper(const XELObjectWrapper& other)
    : XSharedData<XELObject>(other)
{
}

XELObject* XELObjectWrapper::object() const { return data(); }

Variant XELObjectWrapper::invoke(const XString& funcName,
                                 const std::vector<Variant>& params)
{
    return object()->invoke(funcName, params, *this);
}

bool XELObjectWrapper::hasMemberFunction(const XString& funcName,
                                         int paramNum) const
{
    return object()->hasMemberFunction(funcName, paramNum);
}

Variant XELObjectWrapper::member(const XString& memberName)
{
    return object()->member(memberName);
}

bool XELObjectWrapper::hasMember(const XString& memberName) const
{
    return object()->hasMember(memberName);
}
XString XELObjectWrapper::toString() const { return object()->toString(); }

XString XELObjectWrapper::type() { return object()->type(); }

MappedVariable::MappedVariable() : _map(nullptr) {}

MappedVariable::MappedVariable(XHashMap<XString, Variant>* map,
                               const XString& variableName)
    : _map(map), _variableName(variableName)
{
}

Variant MappedVariable::invoke(const XString& funcName,
                               const std::vector<Variant>& params,
                               const XELObjectWrapper& thisWrapper)
{
    if (variable().type() == VariantType::Object)
        return variable().objectValue().invoke(funcName, params);
    else
        throw XELError(
            "Try to invoke the member function of a non-object variant");
}

bool MappedVariable::hasMemberFunction(const XString& funcName,
                                       int paramNum) const
{
    if (variable().type() == VariantType::Object)
        return variable().objectValue().hasMemberFunction(funcName, paramNum);
    else
        return false;
}

Variant MappedVariable::member(const XString& memberName)
{
    if (variable().type() == VariantType::Object)
        return variable().objectValue().member(memberName);
    else
        throw XELError("Try to get the member of a non-object variant");
}

bool MappedVariable::hasMember(const XString& memberName) const
{
    if (variable().type() == VariantType::Object)
        return variable().objectValue().hasMember(memberName);
    else
        return false;
}

XString MappedVariable::toString() const { return variable().toString(); }

XString MappedVariable::type() const { return "MappedVariable"; }

Variant MappedVariable::variable() const { return _map->value(_variableName); }

void MappedVariable::setMap(XHashMap<XString, Variant>* map) { _map = map; }

XHashMap<XString, Variant>* MappedVariable::map() { return _map; }

XString MappedVariable::variableName() const { return _variableName; }

void MappedVariable::setVariableName(XString variable)
{
    _variableName = variable;
}
