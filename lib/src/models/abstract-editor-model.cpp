#include "abstract-editor-model.h"

namespace CleanEditor::Models {

AbstractEditorModel::AbstractEditorModel(QObject *parent)
    : QObject{parent}
{}

int AbstractEditorModel::id() const
{
    return id_;
}

void AbstractEditorModel::setId(const int id)
{
    if (id_ == id) {
        return;
    }

    id_ = id;

    emit idChanged();
}

} //namespace CleanEditor::Models
