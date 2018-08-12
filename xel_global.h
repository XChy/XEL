#ifndef XEL_GLOBAL_H
#define XEL_GLOBAL_H

#include <string.h>
#include <vector>
#include <memory>
#include <unordered_map>
#include <string>
#include <algorithm>

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef unsigned long long ulonglong;

#ifdef _WIN32
#  define DECL_EXPORT __declspec(dllexport)
#  define DECL_IMPORT __declspec(dllimport)
# elif defined(QT_VISIBILITY_AVAILABLE)
#  define DECL_EXPORT __attribute__((visibility("default")))
#  define DECL_IMPORT __attribute__((visibility("default")))
#  define DECL_HIDDEN __attribute__((visibility("hidden")))
# endif

#if defined(XEL_SHARED_LIBRARY)
#  define XEL_EXPORT DECL_EXPORT
#elif defined(XEL_STATIC_LIBRARY)
#  define XEL_EXPORT
#else
#  define XEL_EXPORT Q_DECL_IMPORT
#endif

#endif // FORMULAENGINE_GLOBAL_H
