#include "file-navigation-model.h"

namespace CleanEditor {
namespace Models {

FileNavigationModel::FileNavigationModel(QObject* parent) : QObject{parent} {
}

int FileNavigationModel::selectedIndex() const {
  return selected_index_;
}

void FileNavigationModel::setSelectedIndex(int index) {
  if (selected_index_ == index) {
    return;
  }

  selected_index_ = index;
  emit selectedIndexChanged();
}

} //namespace Models
} //namespace CleanEditor
