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

void EditorRouter::setModel(EditorModel* model) {
  model_ = model;
}

} // namespace Routers
} // namespace CleanEditor
