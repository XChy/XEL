#ifndef SHAREDDATA_H
#define SHAREDDATA_H

#include <XEL/xel_global.h>

template<typename T>
class XEL_EXPORT Ref{
public:
	Ref(T* ptr)
		:mPointer(ptr),
		  mRefCount(1)
	{}
	Ref(const Ref<T>& ref)
		:mRefCount(1)
	{
		mPointer=new T(*ref.pointer());
	}
	int ref(){
		return ++mRefCount;
	}
	int unref(){
		return --mRefCount;
	}
	~Ref()
	{
		delete mPointer;
	}

	T* pointer() const
	{
		return mPointer;
	}
	int refCount() const
	{
		return mRefCount;
	}
private:
	T* mPointer;
	int mRefCount;
};

template<typename T>
class XEL_EXPORT SharedData{
public:
	SharedData(){}
	SharedData(T* p)
		:ref(new Ref<T>(p))
	{}
	SharedData(const SharedData& d)
		:ref(d.ref)
	{
		ref->ref();
	}
	SharedData& operator=(const SharedData& d)
	{
		if(this==&d){
			return *this;
		}
		if(ref->unref()==0){
			delete ref;
		}
		ref=d.ref;
		ref->ref();
		return *this;
	}
	T* data() const
	{
		return ref->pointer();
	}
	~SharedData()
	{
		if(ref->unref()==0)
		{
			delete ref;
		}
	}

	Ref<T>* ref;
};

#endif // SHAREDDATA_H
