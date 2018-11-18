#ifndef MAIN_ROUTER_H
#define MAIN_ROUTER_H

#include <QObject>
#include <QScopedPointer>
#include <QString>

#include "globals.h"

namespace CleanEditor {
namespace Routers {

class QML_EDITOR_EXPORT MainRouter : public QObject {
  Q_OBJECT
  Q_DISABLE_COPY(MainRouter)

public:
  explicit MainRouter(QObject* parent = nullptr);
  ~MainRouter();
};

} // namespace Routers
} // namespace CleanEditor

#endif
