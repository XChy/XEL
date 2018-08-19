#include <XEL/XELContainerObject.h>

Variant XVectorObject::invoke(const XString& funcName, const std::vector<Variant>& params,const XELObjectWrapper& thisWrapper)
{
	if(funcName=="size"){
		return int(vec.size());
	}else if(funcName=="at"){
		return vec.at(params.at(0).convertInt());
	}else if(funcName=="append"){
		vec.push_back(params.at(0));
		return thisWrapper;
	}else if(funcName=="remove"){
		vec.erase(vec.begin()+int(params.at(0)));
		return thisWrapper;
	}
}

void XVectorObject::setMember(const XString& memberName, const Variant& v)
{}

std::vector<Variant>& XVectorObject::vector()
{
	return vec;
}

void XVectorObject::setVector(const std::vector<Variant>& vec)
{
	this->vec=vec;
}

Variant XVectorObject::member(const XString& memberName) const{}

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

Variant XMapObject::invoke(const XString& funcName, const std::vector<Variant>& params, const XELObjectWrapper& thisWrapper)
{
	if(funcName=="size"){
		return int(mMap.size());
	}else if(funcName=="value"){
		return mMap[params.at(0).convertString()];
	}else if(funcName=="insert"){
		mMap.insert(params.at(0).convertString(),params.at(1));
		return thisWrapper;
	}else if(funcName=="remove"){
		mMap.remove(params.at(0).convertString());
		return thisWrapper;
	}
}

void XMapObject::setMember(const XString& memberName, const Variant& v){}

Variant XMapObject::member(const XString& memberName) const{}

XHashMap<XString, Variant>& XMapObject::map()
{
	return mMap;
}

void XMapObject::setMap(const XHashMap<XString, Variant>& map)
{
	mMap = map;
}

XString XMapObject::toString() const
{
	if(!mMap.isEmpty()){
		XString result;
		auto it=mMap.begin();
		result.append("Map(").append(mMap.begin()->first).append(":").append(mMap.begin()->second.toString());
		++it;
		for(;it!=mMap.end();++it){
			result.append(',').append(it->first).append(":").append(it->second.toString());
		}
		result.append(')');
		return result;
	}else{
		return "Map()";
	}
}
