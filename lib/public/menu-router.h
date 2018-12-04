#ifndef MENU_ROUTER_H
#define MENU_ROUTER_H

#include <QObject>
#include <QString>
#include <QPointer>

#include "globals.h"

namespace CleanEditor {
namespace Models {
  class MenuModel;
}

namespace Routers {

class QML_EDITOR_EXPORT MenuRouter : public QObject {
  Q_OBJECT
  Q_DISABLE_COPY(MenuRouter)

public:
  explicit MenuRouter(QObject* parent = nullptr);

  //Takes ownership of model
  void setModel(CleanEditor::Models::MenuModel* model);

  void setTitle(const QString& title);
  void setIsNewFile(bool is_new_file);

Q_SIGNALS:
  void newFileClicked();
  void openFileClicked(const QUrl& file_url);
  void saveFileClicked();
  void saveAsFileClicked(const QUrl& file_url);

private:
  QPointer<CleanEditor::Models::MenuModel> model_;

};

} // namespace Routers
} // namespace CleanEditor

#endif
