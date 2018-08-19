#ifndef XELCONTAINEROBJECT_H
#define XELCONTAINEROBJECT_H

#include <XEL/xel_global.h>
#include <XEL/Variant.h>

class XEL_EXPORT XVectorObject:public XELObject{
public:
	virtual Variant invoke(const XString& funcName, const std::vector<Variant>& params, const XELObjectWrapper& thisWrapper);
	virtual void setMember(const XString& memberName,const Variant& v);
	virtual Variant member(const XString& memberName) const;
	std::vector<Variant>& vector();
	void setVector(const std::vector<Variant>& vec);
	virtual XString toString() const;
private:
	std::vector<Variant> vec;
};

class XEL_EXPORT XMapObject:public XELObject{
public:
	virtual Variant invoke(const XString& funcName, const std::vector<Variant>& params, const XELObjectWrapper& thisWrapper);
	virtual void setMember(const XString& memberName,const Variant& v);
	virtual Variant member(const XString& memberName) const;

	XHashMap<XString, Variant>& map();
	void setMap(const XHashMap<XString, Variant>& map);

	virtual XString toString() const;
private:
	XHashMap<XString,Variant> mMap;
};

#endif
