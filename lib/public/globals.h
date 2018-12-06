#pragma once

#include <QtCore/qglobal.h>

#if defined(QML_EDITOR_LIBRARY)
#  define QML_EDITOR_EXPORT Q_DECL_EXPORT
#else
#  define QML_EDITOR_EXPORT Q_DECL_IMPORT
#endif
