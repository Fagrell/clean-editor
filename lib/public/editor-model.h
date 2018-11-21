#ifndef EDITOR_MODEL_H
#define EDITOR_MODEL_H

#include <QObject>
#include <QString>

#include "globals.h"

class QTextDocument;

namespace CleanEditor {
namespace Models {

class QML_EDITOR_EXPORT EditorModel : public QObject {
  Q_OBJECT
  Q_DISABLE_COPY(EditorModel)

  Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)

public:
  explicit EditorModel(QObject* parent = nullptr);

  QString text() const;
  void setText(const QString& text);

  void setTextDocument(QTextDocument* text_document);

signals:
  void textChanged();

private:
  QTextDocument* text_document_{nullptr};
};

} // namespace Routers
} // namespace CleanEditor

#endif
