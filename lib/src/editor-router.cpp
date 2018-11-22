#include "editor-router.h"

#include "editor-model.h"

using namespace CleanEditor::Models;

namespace CleanEditor {
namespace Routers {

EditorRouter::EditorRouter(QObject* parent)
  : QObject{parent}
{}

EditorRouter::~EditorRouter() {
  if (!model_) {
    return;
  }

  delete model_.data();
}

void EditorRouter::setModel(AbstractEditorModel* model) {
  model_ = model;

  disconnect();
  if (!model_) {
    return;
  }

  connect(model, &AbstractEditorModel::textChanged, this, &EditorRouter::textChanged);
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

} // namespace Routers
} // namespace CleanEditor
