#include "editor-router.h"

#include "editor-model.h"

using namespace CleanEditor::Models;

namespace CleanEditor {
namespace Routers {

EditorRouter::EditorRouter(QObject* parent)
  : QObject{parent}
{}

void EditorRouter::setModel(AbstractEditorModel* model) {
  disconnect(text_changed_connection_);

  model_ = model;
  if (!model_) {
    return;
  }
  model_->setParent(this);

  text_changed_connection_ = connect(model, &AbstractEditorModel::textChanged, this, &EditorRouter::textChanged);
}

QString EditorRouter::text() const {
  if (!model_) {
    return "";
  }

  return model_->text();
}
void EditorRouter::setText(const QString& text) {
  if (!model_) {
    return;
  }

  model_->setText(text);
}

int EditorRouter::id() const {
  if (!model_) {
    return 0;
  }

  return model_->id();
}

void EditorRouter::setId(int id) {
  if (!model_) {
    return;
  }

  model_->setId(id);
}

} // namespace Routers
} // namespace CleanEditor
