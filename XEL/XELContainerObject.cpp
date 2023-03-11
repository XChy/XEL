#include <XEL/XELContainerObject.h>

using namespace XEL;

Variant XVectorObject::invoke(const XString& funcName,
                              const std::vector<Variant>& params,
                              const XELObjectWrapper& thisWrapper)
{
    if (funcName == "size") {
        return (long long)(vec.size());
    } else if (funcName == "at") {
        return vec.at(params[0].convertInterger());
    } else if (funcName == "append") {
        vec.push_back(params[0]);
        return thisWrapper;
    } else if (funcName == "remove") {
        vec.erase(vec.begin() + int(params[0]));
        return thisWrapper;
    }
}

bool XVectorObject::hasMemberFunction(const XString& funcName,
                                      int paramNum) const
{
    return (funcName == "size" && paramNum == 0) ||
           (funcName == "at" && paramNum == 1) ||
           (funcName == "append" && paramNum == 1) ||
           (funcName == "remove" && paramNum == 1);
}

Variant XVectorObject::member(const XString& memberName) { return Variant(); }

bool XVectorObject::hasMember(const XString& memberName) const { return false; }

std::vector<Variant>& XVectorObject::vector() { return vec; }

void XVectorObject::setVector(const std::vector<Variant>& vec)
{
    this->vec = vec;
}

XString XVectorObject::toString() const
{
    if (!vec.empty()) {
        XString result;
        result.append("Vector(").append(vec[0].toString());
        for (auto it = vec.begin() + 1; it != vec.end(); ++it) {
            result.append(',').append((*it).toString());
        }
        result.append(')');
        return result;
    } else {
        return "Vector()";
    }
}

XString XVectorObject::type() const { return "Vector"; }

Variant XMapObject::invoke(const XString& funcName,
                           const std::vector<Variant>& params,
                           const XELObjectWrapper& thisWrapper)
{
    if (funcName == "size") {
        return (long long)(mMap.size());
    } else if (funcName == "value") {
        return mMap[params[0].convertString()];
    } else if (funcName == "insert") {
        mMap.insert(params[0].convertString(), params.at(1));
        return thisWrapper;
    } else if (funcName == "remove") {
        mMap.remove(params[0].convertString());
        return thisWrapper;
    }
}

bool XMapObject::hasMemberFunction(const XString& funcName, int paramNum) const
{
    return (funcName == "size" && paramNum == 0) ||
           (funcName == "value" && paramNum == 1) ||
           (funcName == "insert" && paramNum == 1) ||
           (funcName == "remove" && paramNum == 1);
}

Variant XMapObject::member(const XString& memberName) { return Variant(); }

bool XMapObject::hasMember(const XString& memberName) const { return false; }

XHashMap<XString, Variant>& XMapObject::map() { return mMap; }

void XMapObject::setMap(const XHashMap<XString, Variant>& map) { mMap = map; }

void XMapObject::setMap(XHashMap<XString, Variant>&& map) { mMap = map; }

XString XMapObject::toString() const
{
    if (!mMap.isEmpty()) {
        XString result;
        auto it = mMap.begin();
        result.append("Map(")
            .append(mMap.begin()->first)
            .append(":")
            .append(mMap.begin()->second.toString());
        ++it;
        for (; it != mMap.end(); ++it) {
            result.append(',').append(it->first).append(":").append(
                it->second.toString());
        }
        result.append(')');
        return result;
    } else {
        return "Map()";
    }
}

XString XMapObject::type() const { return "Map"; }
