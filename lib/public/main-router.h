#ifndef MAIN_CONTROLLER_H
#define MAIN_CONTROLLER_H

#include <QObject>
#include <QScopedPointer>
#include <QString>

#include "globals.h"

namespace CleanEditor {
namespace Controllers {

class QML_EDITOR_EXPORT MainController : public QObject {
  Q_OBJECT
  Q_DISABLE_COPY(MainController)

  Q_PROPERTY(QString ui_welcomeMessage READ welcomeMessage CONSTANT)

public:
  explicit MainController(QObject* parent = nullptr);
  ~MainController();

  QString welcomeMessage() const;
};

} // namespace Controllers
} // namespace CleanEditor

#endif
