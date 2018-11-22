#ifndef ABSTRACT_EDITOR_MODEL_H
#define ABSTRACT_EDITOR_MODEL_H

#include <QObject>
#include <QString>

#include "globals.h"

class QTextDocument;

namespace CleanEditor {
namespace Models {

class QML_EDITOR_EXPORT AbstractEditorModel : public QObject {
  Q_OBJECT
  Q_DISABLE_COPY(AbstractEditorModel)

  Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)

public:
  explicit AbstractEditorModel(QObject* parent = nullptr);

  virtual QString text() const = 0;
  virtual void setText(const QString& text) = 0;

  virtual void setTextDocument(QTextDocument* text_document) = 0;

Q_SIGNALS:
  void textChanged();

private:
  QTextDocument* text_document_{nullptr};
};

} // namespace Routers
} // namespace CleanEditor

#endif
