#ifndef XEL_GLOBAL_H
#define XEL_GLOBAL_H

#include <QtCore>
#include <memory>

#if defined(XEL_SHARED_LIBRARY)
#  define XEL_EXPORT Q_DECL_EXPORT
#elif defined(XEL_STATIC_LIBRARY)
#  define XEL_EXPORT
#else
#  define XEL_EXPORT Q_DECL_IMPORT
#endif

#endif // FORMULAENGINE_GLOBAL_H
