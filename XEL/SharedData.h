#ifndef SHAREDDATA_H
#define SHAREDDATA_H

#include <XEL/xel_global.h>

class XEL_EXPORT XRefCount
{
   public:
    XRefCount() : mRefCount(1) {}
    XRefCount(const XRefCount& other) : mRefCount(other.refCount()) {}
    int ref() { return ++mRefCount; }
    int unref() { return --mRefCount; }
    int refCount() const { return mRefCount; }

   private:
    int mRefCount;
};

template <typename T>
class XEL_EXPORT XSharedData
{
   public:
    XSharedData() : ref(new XRefCount), mData(nullptr) {}
    XSharedData(T* p) : ref(new XRefCount), mData(p) {}
    XSharedData(const XSharedData& other) : ref(other.ref), mData(other.data())
    {
        ref->ref();
    }
    XSharedData& operator=(const XSharedData& other)
    {
        if (this == &other) {
            return *this;
        }
        if (ref->unref() == 0) {
            delete ref;
            delete mData;
        }
        ref = other.ref;
        mData = other.data();
        ref->ref();
        return *this;
    }
    T* data() const { return mData; }
    ~XSharedData()
    {
        if (ref->unref() == 0) {
            delete ref;
            delete mData;
        }
    }

    XRefCount* ref;
    T* mData;
};

#endif  // SHAREDDATA_H
