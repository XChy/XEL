#ifndef XELOBJECT_H
#define XELOBJECT_H

#include <XEL/xel_global.h>
#include <XEL/XHashMap.h>
#include <XEL/XString.h>

class Variant;

class XEL_EXPORT XELObject{
public:
	XELObject(){}
	virtual Variant invoke(const XString& funcName,const std::vector<Variant>& params)=0;
	virtual void setMember(const XString& memberName,const Variant& v)=0;
	virtual Variant member(const XString& memberName) const=0;
	virtual bool isVariableMember(const XString& memberName)=0;
	virtual XString toString() const=0;
	virtual ~XELObject(){}
};

class XEL_EXPORT XELObjectWrapper:public XSharedData<XELObject>{
public:
	XELObjectWrapper();
	XELObjectWrapper(XELObject* object);
	XELObjectWrapper(const XELObjectWrapper& other);
	XELObject* object() const;
	virtual Variant invoke(const XString& funcName,const std::vector<Variant>& params);
	virtual void setMember(const XString& memberName,const Variant& v);
	virtual Variant member(const XString& memberName) const;
	virtual bool isVariableMember(const XString& memberName);
	virtual XString toString() const;
};

class XEL_EXPORT XVectorObject:public XELObject{
public:
	virtual Variant invoke(const XString& funcName,const std::vector<Variant>& params);
	virtual void setMember(const XString& memberName,const Variant& v);
	virtual Variant member(const XString& memberName) const;
	virtual bool isVariableMember(const XString& memberName);
	std::vector<Variant>& vector();
	void setVector(const std::vector<Variant>& vec);
	virtual XString toString() const;
private:
	std::vector<Variant> vec;
};
#endif
