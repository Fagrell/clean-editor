#ifndef EDITOR_MODEL_H
#define EDITOR_MODEL_H

#include "abstract-editor-model.h"
#include "globals.h"

#include <QString>

class QTextDocument;

namespace CleanEditor {
namespace Models {
class QML_EDITOR_EXPORT EditorModel : public AbstractEditorModel {
  Q_OBJECT
  Q_DISABLE_COPY(EditorModel)

public:
  explicit EditorModel(QObject* parent = nullptr);

  QString text() const override;
  void setText(const QString& text) override;

  void setTextDocument(QTextDocument* text_document);

private:
  QTextDocument* text_document_{nullptr};
};

} // namespace Routers
} // namespace CleanEditor

#endif
