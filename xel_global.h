#ifndef XEL_GLOBAL_H
#define XEL_GLOBAL_H

#include <QtCore>
#include <memory>

#if defined(XEL_LIBRARY)
#  define XELSHARED_EXPORT Q_DECL_EXPORT
#else
#  define XELSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // FORMULAENGINE_GLOBAL_H
