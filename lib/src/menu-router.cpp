#include "menu-router.h"
#include "menu-model.h"

namespace CleanEditor {
namespace Routers {

MenuRouter::MenuRouter(QObject* parent)
  : QObject{parent}
{}

void MenuRouter::setModel(CleanEditor::Models::MenuModel* model) {
  model_ = model;
  if (!model_) {
    return;
  }
  model_->setParent(this);
}

void MenuRouter::setDocument(CleanEditor::Logic::DocumentHandler* document_handler) {
  if (!model_) {
    return;
  }

  model_->setDocument(document_handler);
}
} // namespace Routers
} // namespace CleanEditor
