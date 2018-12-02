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

  Q_PROPERTY(QString text READ text WRITE setText NOTIFY textReplaced)
  Q_PROPERTY(int id READ id WRITE setId NOTIFY idChanged)

public:
  explicit AbstractEditorModel(QObject* parent = nullptr);

  virtual QString text() const = 0;
  virtual void setText(const QString& text) = 0;

  int id() const;
  void setId(int id);

Q_SIGNALS:
  //! Used when the a minor change has been made in the text
  void textChanged();

  //! Used when setText is called (and therefore replaced).
  void textReplaced();
  void idChanged();

private:
  int id_{0};

};

} // namespace Routers
} // namespace CleanEditor

#endif
