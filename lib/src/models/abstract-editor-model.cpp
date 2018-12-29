#include "abstract-editor-model.h"

namespace CleanEditor {
namespace Models {

AbstractEditorModel::AbstractEditorModel(QObject* parent) : QObject{parent} {
}

int AbstractEditorModel::id() const {
  return id_;
}

void AbstractEditorModel::setId(int id) {
  if (id_ == id) {
    return;
  }

  id_ = id;

  emit idChanged();
}

} //namespace Models
} //namespace CleanEditor
