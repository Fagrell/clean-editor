#include "main-router.h"

#include "menu-router.h"
#include "editor-router.h"
#include "file-navigation-router.h"

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
  //Update data for documents_model
}

} // namespace Routers
} // namespace CleanEditor
