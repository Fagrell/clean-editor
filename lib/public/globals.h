#pragma once

#include <QtCore/qglobal.h>

#if defined(CLEAN_EDITOR_LIBRARY)
#define CLEAN_EDITOR_EXPORT Q_DECL_EXPORT
#else
#define CLEAN_EDITOR_EXPORT Q_DECL_IMPORT
#endif
