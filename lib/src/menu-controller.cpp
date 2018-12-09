#include "menu-controller.h"
#include "menu-model.h"

namespace CleanEditor {
namespace Controllers {

MenuController::MenuController(QObject* parent)
  : QObject{parent}
{}

void MenuController::setModel(CleanEditor::Models::MenuModel* model) {
  model_ = model;
  if (!model_) {
    return;
  }
  model_->setParent(this);
}

void MenuController::setDocument(CleanEditor::Logic::DocumentHandler* document_handler) {
  if (!model_) {
    return;
  }

  model_->setDocument(document_handler);
}
} // namespace Controllers
} // namespace CleanEditor
