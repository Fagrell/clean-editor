#pragma once

#include <QObject>
#include <QPointer>
#include <QString>

#include "globals.h"

namespace CleanEditor {
namespace Models {
  class DocumentsModel;
}

namespace Controllers {

class MenuController;
class EditorController;
class FileNavigationController;

class CLEAN_EDITOR_EXPORT MainController : public QObject {
  Q_OBJECT
  Q_DISABLE_COPY(MainController)

  Q_PROPERTY(CleanEditor::Controllers::MenuController* menuController READ menuController CONSTANT)
  Q_PROPERTY(CleanEditor::Controllers::EditorController* editorController READ editorController CONSTANT)
  Q_PROPERTY(CleanEditor::Controllers::FileNavigationController* fileNavigationController READ fileNavigationController CONSTANT)

public:
  explicit MainController(QObject* parent = nullptr);

  //Takes ownership of model
  void setDocumentsModel(CleanEditor::Models::DocumentsModel* documents_model);

  MenuController* menuController() const;
  EditorController* editorController() const;
  FileNavigationController* fileNavigationController() const;

private:
  void storeTextToCurrentFile();

  MenuController* menu_controller_{nullptr};
  EditorController* editor_controller_{nullptr};
  FileNavigationController* file_navigation_controller_{nullptr};
  QPointer<CleanEditor::Models::DocumentsModel> documents_model_;
  QMetaObject::Connection document_created_connection_;

private Q_SLOTS:
  void handleEditorTextChanged();
  void openDocument(int id);
  void handleSaveFileClicked();
  void handleSaveAsFileClicked(const QUrl& url);
  void handleNewFileClicked();
  void handleOpenedFileClicked(int id);
  void handleOpenFileClicked(const QUrl& url);
};

} // namespace Controllers
} // namespace CleanEditor
