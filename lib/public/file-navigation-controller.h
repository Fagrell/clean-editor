#pragma once

#include <QObject>
#include <QScopedPointer>
#include <QString>

#include "globals.h"

namespace CleanEditor {
namespace Controllers {

class QML_EDITOR_EXPORT FileNavigationController : public QObject {
  Q_OBJECT
  Q_DISABLE_COPY(FileNavigationController)

public:
  explicit FileNavigationController(QObject* parent = nullptr);

Q_SIGNALS:
  void fileOpenedClicked(int id);
};

} // namespace Controllers
} // namespace CleanEditor
