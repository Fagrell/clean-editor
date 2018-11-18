#ifndef EDITOR_ROUTER_H
#define EDITOR_ROUTER_H

#include <QObject>
#include <QScopedPointer>
#include <QString>

#include "globals.h"

namespace CleanEditor {
namespace Routers {

class QML_EDITOR_EXPORT EditorRouter : public QObject {
  Q_OBJECT
  Q_DISABLE_COPY(EditorRouter)

public:
  explicit EditorRouter(QObject* parent = nullptr);
  ~EditorRouter();
};

} // namespace Routers
} // namespace CleanEditor

#endif
