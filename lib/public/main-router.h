#ifndef MAIN_ROUTER_H
#define MAIN_ROUTER_H

#include <QObject>
#include <QPointer>
#include <QString>

#include "globals.h"

namespace CleanEditor {
namespace Models {
  class DocumentsModel;
}

namespace Routers {

class MenuRouter;
class EditorRouter;
class FileNavigationRouter;

class QML_EDITOR_EXPORT MainRouter : public QObject {
  Q_OBJECT
  Q_DISABLE_COPY(MainRouter)

  Q_PROPERTY(CleanEditor::Routers::MenuRouter* menuRouter READ menuRouter CONSTANT)
  Q_PROPERTY(CleanEditor::Routers::EditorRouter* editorRouter READ editorRouter CONSTANT)
  Q_PROPERTY(CleanEditor::Routers::FileNavigationRouter* fileNavigationRouter READ fileNavigationRouter CONSTANT)

public:
  explicit MainRouter(QObject* parent = nullptr);

  //Takes ownership of model
  void setDocumentsModel(CleanEditor::Models::DocumentsModel* documents_model);

  MenuRouter* menuRouter() const;
  EditorRouter* editorRouter() const;
  FileNavigationRouter* fileNavigationRouter() const;

private:
  MenuRouter* menu_router_{nullptr};
  EditorRouter* editor_router_{nullptr};
  FileNavigationRouter* file_navigation_router_{nullptr};
  QPointer<CleanEditor::Models::DocumentsModel> documents_model_;
  QMetaObject::Connection document_created_connection_;
  QMetaObject::Connection open_file_clicked_connection_;

private Q_SLOTS:
  void handleEditorTextChanged();
  void openDocument(int id);
  void handleSaveFileClicked();
  void handleSaveAsFileClicked(const QUrl& url);
};

} // namespace Routers
} // namespace CleanEditor

#endif
