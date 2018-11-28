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
}

void MainRouter::setDocumentsModel(CleanEditor::Models::DocumentsModel* documents_model) {
  documents_model_ = documents_model;

  disconnect();
  if (!documents_model_) {
    return;
  }

  documents_model_->setParent(this);
  connect(documents_model_, &DocumentsModel::documentCreated, this, &MainRouter::openDocument);
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

}

void MainRouter::openDocument(int id) {
  if (!documents_model_) {
    return;
  }

  QString file_content = documents_model_->fileContent(id);
  editor_router_->setText(file_content);
  editor_router_->setId(id);
}

} // namespace Routers
} // namespace CleanEditor
