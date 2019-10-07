#ifndef XELOBJECT_H
#define XELOBJECT_H

#include <XEL/xel_global.h>
#include <XEL/XHashMap.h>
#include <XEL/XString.h>

class Variant;
class XELObjectWrapper;

class XEL_EXPORT XELObject{
public:
    XELObject(){}

    //User need to rewrite a static function called "construct" to construct your object in XEL
    //For example:
    //static XELObjectWrapper construct(int value){
    //  YourObject* obj=new YourObject();
    //  obj.setValue(value);
    //  return XELObjectWrapper(obj);
    //}

    virtual Variant invoke(const XString& funcName,const std::vector<Variant>& params,const XELObjectWrapper& thisWrapper)=0;
    virtual bool hasMemberFunction(const XString& funcName,int paramNum) const=0;
    virtual void setMember(const XString& memberName,const Variant& v)=0;
    virtual Variant member(const XString& memberName) const=0;
    virtual bool hasMember(const XString& memberName) const=0;
    virtual XString toString() const=0;
    virtual ~XELObject(){}
};

class XEL_EXPORT XELObjectWrapper:public XSharedData<XELObject>{
public:
    XELObjectWrapper();
    XELObjectWrapper(XELObject* object);
    XELObjectWrapper(const XELObjectWrapper& other);
    XELObject* object() const;
    Variant invoke(const XString& funcName,const std::vector<Variant>& params);
    bool hasMemberFunction(const XString& funcName,int paramNum) const;
    void setMember(const XString& memberName,const Variant& v);
    Variant member(const XString& memberName) const;
    bool hasMember(const XString& memberName) const;
    XString toString() const;
};

#endif
