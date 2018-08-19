#include <XEL/XELObject.h>
#include <XEL/Variant.h>

XELObjectWrapper::XELObjectWrapper():XSharedData<XELObject>(){}

XELObjectWrapper::XELObjectWrapper(XELObject* object):XSharedData<XELObject>(object){}

XELObjectWrapper::XELObjectWrapper(const XELObjectWrapper& other):XSharedData<XELObject>(other){}

XELObject* XELObjectWrapper::object() const
{
	return data();
}

Variant XELObjectWrapper::invoke(const XString& funcName, const std::vector<Variant>& params)
{
	return object()->invoke(funcName,params,*this);
}

void XELObjectWrapper::setMember(const XString& memberName, const Variant& v){
	object()->setMember(memberName,v);
}

Variant XELObjectWrapper::member(const XString& memberName) const
{
	return object()->member(memberName);
}
XString XELObjectWrapper::toString() const
{
	return object()->toString();
}
