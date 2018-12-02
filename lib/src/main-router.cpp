#include "main-router.h"

#include "menu-router.h"
#include "editor-router.h"
#include "file-navigation-router.h"

#include "documents-model.h"

using namespace CleanEditor::Models;

namespace CleanEditor {
namespace Routers {

MainRouter::MainRouter(QObject* parent) :
  QObject{parent},
  menu_router_{new MenuRouter{this}},
  editor_router_{new EditorRouter{this}},
  file_navigation_router_{new FileNavigationRouter{this}}
{
  connect(editor_router_, &EditorRouter::textChanged, this, &MainRouter::handleEditorTextChanged);
  connect(menu_router_, &MenuRouter::saveFileClicked, this, &MainRouter::handleSaveFileClicked);
  connect(menu_router_, &MenuRouter::saveAsFileClicked, this, &MainRouter::handleSaveAsFileClicked);
  connect(menu_router_, &MenuRouter::newFileClicked, this, &MainRouter::handleNewFileClicked);

}

void MainRouter::setDocumentsModel(CleanEditor::Models::DocumentsModel* documents_model) {
  disconnect(document_created_connection_);
  disconnect(open_file_clicked_connection_);
  documents_model_ = documents_model;
  if (!documents_model_) {
    return;
  }

  documents_model_->setParent(this);
  document_created_connection_ = connect(documents_model_, &DocumentsModel::documentCreated, this, &MainRouter::openDocument);
  open_file_clicked_connection_ = connect(menu_router_, &MenuRouter::openFileClicked, documents_model_, &DocumentsModel::openFile);
  documents_model->newFile();
}

MenuRouter* MainRouter::menuRouter() const {
  return menu_router_;
}

EditorRouter* MainRouter::editorRouter() const {
  return editor_router_;
}

FileNavigationRouter* MainRouter::fileNavigationRouter() const {
  return file_navigation_router_;
}

void MainRouter::handleEditorTextChanged() {
  if (!documents_model_) {
    return;
  }

  documents_model_->setNeedsUpdating(true);
}

void MainRouter::openDocument(int id) {
  if (!documents_model_) {
    return;
  }

  QString file_content = documents_model_->fileContent(id);
  editor_router_->setText(file_content);
  editor_router_->setId(id);
}

void MainRouter::handleSaveFileClicked() {
  if (!documents_model_) {
    return;
  }

  int current_file_id = editor_router_->id();
  QUrl current_url = documents_model_->fileUrl(current_file_id);
  handleSaveAsFileClicked(current_url);
}

void MainRouter::handleSaveAsFileClicked(const QUrl& url) {
  if (!documents_model_) {
    return;
  }

  int current_file_id = editor_router_->id();
  documents_model_->setFileContent(current_file_id, editor_router_->text());
  documents_model_->saveAs(current_file_id, url);
}

void MainRouter::handleNewFileClicked() {
  if (!documents_model_) {
    return;
  }

  documents_model_->newFile();
}

} // namespace Routers
} // namespace CleanEditor
