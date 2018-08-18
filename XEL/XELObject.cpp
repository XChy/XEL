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
	return object()->invoke(funcName,params);
}

void XELObjectWrapper::setMember(const XString& memberName, const Variant& v){
	object()->setMember(memberName,v);
}

Variant XELObjectWrapper::member(const XString& memberName) const
{
	return object()->member(memberName);
}

bool XELObjectWrapper::isVariableMember(const XString& memberName)
{
	return object()->isVariableMember(memberName);
}

XString XELObjectWrapper::toString() const
{
	return object()->toString();
}


Variant XVectorObject::invoke(const XString& funcName, const std::vector<Variant>& paramss)
{
	if(funcName=="size"){
		return int(vec.size());
	}
}

void XVectorObject::setMember(const XString& memberName, const Variant& v)
{

}

bool XVectorObject::isVariableMember(const XString& memberName)
{
	if(memberName=="size"){
		return false;
	}
}

std::vector<Variant>& XVectorObject::vector()
{
	return vec;
}

void XVectorObject::setVector(const std::vector<Variant>& vec)
{
	this->vec=vec;
}

Variant XVectorObject::member(const XString& memberName) const
{
	if(memberName=="size"){
		return int(this->vec.size());
	}
}

XString XVectorObject::toString() const
{
	if(!vec.empty()){
		XString result;
		result.append("Vector(").append(vec[0].toString());
		for(auto it=vec.begin()+1;it!=vec.end();++it){
			result.append(',').append((*it).toString());
		}
		result.append(')');
		return result;
	}else{
		return "Vector()";
	}
}
