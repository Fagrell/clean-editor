#ifndef MENU_ROUTER_H
#define MENU_ROUTER_H

#include <QObject>
#include <QScopedPointer>
#include <QString>

#include "globals.h"

namespace CleanEditor {
namespace Routers {

class QML_EDITOR_EXPORT MenuRouter : public QObject {
  Q_OBJECT
  Q_DISABLE_COPY(MenuRouter)

public:
  explicit MenuRouter(QObject* parent = nullptr);

Q_SIGNALS:
  void openFileClicked(const QUrl& file_url);

};

} // namespace Routers
} // namespace CleanEditor

#endif
