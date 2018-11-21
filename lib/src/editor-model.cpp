#include "editor-model.h"

#include <QTextDocument>

namespace CleanEditor {
namespace Models {

EditorModel::EditorModel(QObject* parent) : QObject{parent} {
}

QString EditorModel::text() const {
  if (!text_document_) {
    return "";
  }

  return text_document_->toPlainText();
}

void EditorModel::setText(const QString& text) {
  if (!text_document_) {
    return;
  }

  text_document_->setPlainText(text);
}

void EditorModel::setTextDocument(QTextDocument* text_document) {
  text_document_ = text_document;
  if (!text_document_) {
    return;
  }

  connect(text_document_, &QTextDocument::contentsChanged, this, &EditorModel::textChanged);
}

} //namespace Models
} //namespace CleanEditor
