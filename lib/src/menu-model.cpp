#include "menu-model.h"

namespace CleanEditor {
namespace Models {

MenuModel::MenuModel(QObject* parent) : QObject{parent} {
}

QString MenuModel::title() const {
  return title_;
}

void MenuModel::setTitle(const QString& title) {
  if (title_ == title) {
    return;
  }

  title_ = title;
  emit titleChanged();
}

bool MenuModel::isNewFile() const {
  return is_new_file_;
}

void MenuModel::setIsNewFile(bool is_new_file) {
  if (is_new_file_ == is_new_file) {
    return;
  }

  is_new_file_ = is_new_file;
  emit isNewFileChanged();
}

} //namespace Models
} //namespace CleanEditor
