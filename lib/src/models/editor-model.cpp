#include "editor-model.h"

#include <QSignalBlocker>
#include <QTextDocument>

namespace CleanEditor::Models {

EditorModel::EditorModel(QObject *parent)
    : AbstractEditorModel{parent}
{}

QString EditorModel::text() const
{
    if (!text_document_) {
        return "";
    }

    return text_document_->toPlainText();
}

void EditorModel::setText(const QString &text)
{
    if (!text_document_) {
        return;
    }

    { // Only block signals in scope
        QSignalBlocker block_signals{this};
        text_document_->setPlainText(text);
    }

    emit textReplaced();
}

void EditorModel::setTextDocument(QTextDocument *text_document)
{
    text_document_ = text_document;
    if (!text_document_) {
        return;
    }

    connect(text_document_,
            &QTextDocument::contentsChanged,
            this,
            &AbstractEditorModel::textChanged);
}

} //namespace CleanEditor::Models
