#pragma once

#include <QObject>
#include <QString>
#include <QPointer>

#include "globals.h"

namespace CleanEditor {
namespace Models {
  class MenuModel;
}
namespace Logic {
  class DocumentHandler;
}

namespace Controllers {

class QML_EDITOR_EXPORT MenuController : public QObject {
  Q_OBJECT
  Q_DISABLE_COPY(MenuController)

public:
  explicit MenuController(QObject* parent = nullptr);

  //Takes ownership of model
  void setModel(CleanEditor::Models::MenuModel* model);

  void setDocument(CleanEditor::Logic::DocumentHandler* document_handler);

Q_SIGNALS:
  void newFileClicked();
  void openFileClicked(const QUrl& file_url);
  void saveFileClicked();
  void saveAsFileClicked(const QUrl& file_url);

private:
  QPointer<CleanEditor::Models::MenuModel> model_;

};

} // namespace Controllers
} // namespace CleanEditor
