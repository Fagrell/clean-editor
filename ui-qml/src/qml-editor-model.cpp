#include "qml-editor-model.h"

#include <QQuickTextDocument>

namespace CleanEditor::Models {

QmlEditorModel::QmlEditorModel(QObject *parent)
    : EditorModel{parent}
{}

QQuickTextDocument *QmlEditorModel::document() const
{
    return document_;
}

void QmlEditorModel::setDocument(QQuickTextDocument *document)
{
    setTextDocument(nullptr);
    document_ = document;

    if (!document_) {
        return;
    }

    setTextDocument(document_->textDocument());
}

} //namespace CleanEditor::Models
