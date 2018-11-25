#ifndef FILE_NAVIGATION_ROUTER_H
#define FILE_NAVIGATION_ROUTER_H

#include <QObject>
#include <QScopedPointer>
#include <QString>

#include "globals.h"

namespace CleanEditor {
namespace Routers {

class QML_EDITOR_EXPORT FileNavigationRouter : public QObject {
  Q_OBJECT
  Q_DISABLE_COPY(FileNavigationRouter)

public:
  explicit FileNavigationRouter(QObject* parent = nullptr);

Q_SIGNALS:
  void fileOpened(int id);
};

} // namespace Routers
} // namespace CleanEditor

#endif
