#ifndef XELOBJECT_H
#define XELOBJECT_H

#include <XEL/xel_global.h>
#include <XEL/XHashMap.h>
#include <XEL/XString.h>
#include "XEL/SharedData.h"

class Variant;
class XELObjectWrapper;

class XEL_EXPORT XELObject
{
   public:
    XELObject() {}

    virtual Variant invoke(const XString& funcName,
                           const std::vector<Variant>& params,
                           const XELObjectWrapper& thisWrapper) = 0;
    virtual bool hasMemberFunction(const XString& funcName,
                                   int paramNum) const = 0;
    virtual Variant member(const XString& memberName) = 0;
    virtual bool hasMember(const XString& memberName) const = 0;
    virtual XString toString() const = 0;

    virtual XString type() const = 0;

    virtual ~XELObject() {}
};

class XEL_EXPORT XELObjectWrapper : public XSharedData<XELObject>
{
   public:
    XELObjectWrapper();
    XELObjectWrapper(XELObject* object);
    XELObjectWrapper(const XELObjectWrapper& other);

    XELObject* object() const;

    Variant invoke(const XString& funcName, const std::vector<Variant>& params);
    bool hasMemberFunction(const XString& funcName, int paramNum) const;
    Variant member(const XString& memberName);
    bool hasMember(const XString& memberName) const;
    XString toString() const;

    XString type();
};

class XEL_EXPORT MappedVariable : public XELObject
{
   public:
    MappedVariable();
    MappedVariable(XHashMap<XString, Variant>* map,
                   const XString& variableName);

    Variant invoke(const XString& funcName, const std::vector<Variant>& params,
                   const XELObjectWrapper& thisWrapper);
    bool hasMemberFunction(const XString& funcName, int paramNum) const;
    Variant member(const XString& memberName);
    bool hasMember(const XString& memberName) const;
    XString toString() const;

    XString type() const;

    Variant variable() const;

    void setMap(XHashMap<XString, Variant>* map);
    XHashMap<XString, Variant>* map();

    XString variableName() const;
    void setVariableName(XString variable);

   protected:
    XHashMap<XString, Variant>* _map;
    XString _variableName;
};
#endif
