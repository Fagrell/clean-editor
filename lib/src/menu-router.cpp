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

void MenuRouter::setTitle(const QString& title) {
  if (!model_) {
    return;
  }

  model_->setTitle(title);
}

void MenuRouter::setIsNewFile(bool is_new_file) {
  if (!model_) {
    return;
  }

  model_->setIsNewFile(is_new_file);
}

} // namespace Routers
} // namespace CleanEditor
