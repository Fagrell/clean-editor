#include "editor-controller.h"

#include "editor-model.h"

using namespace CleanEditor::Models;

namespace CleanEditor::Controllers {

EditorController::EditorController(QObject *parent)
    : QObject{parent}
{}

void EditorController::setModel(AbstractEditorModel &model)
{
    disconnect(text_changed_connection_);
    model_ = &model;
    text_changed_connection_ = connect(model_,
                                       &AbstractEditorModel::textChanged,
                                       this,
                                       &EditorController::textChanged);
}

QString EditorController::text() const
{
    if (!model_) {
        return "";
    }

    return model_->text();
}
void EditorController::setText(const QString &text)
{
    if (!model_) {
        return;
    }

    model_->setText(text);
}

int EditorController::id() const
{
    if (!model_) {
        return 0;
    }

    return model_->id();
}

void EditorController::setId(const int id)
{
    if (!model_) {
        return;
    }

    model_->setId(id);
}

} // namespace CleanEditor::Controllers
