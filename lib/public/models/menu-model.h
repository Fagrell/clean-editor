#pragma once

#include "globals.h"

#include <QString>
#include <QObject>
#include <QPointer>

class QTextDocument;

namespace CleanEditor {
namespace Logic {
  class DocumentHandler;
}
namespace Models {

class QML_EDITOR_EXPORT MenuModel : public QObject {
  Q_OBJECT
  Q_DISABLE_COPY(MenuModel)

  Q_PROPERTY(QString title READ title NOTIFY titleChanged)
  Q_PROPERTY(bool isNewFile READ isNewFile NOTIFY isNewFileChanged)

public:
  explicit MenuModel(QObject* parent = nullptr);

  void setDocument(CleanEditor::Logic::DocumentHandler* document_handler);

  QString title() const;
  bool isNewFile() const;

Q_SIGNALS:
  void titleChanged();
  void isNewFileChanged();

private:
  QPointer<CleanEditor::Logic::DocumentHandler> document_handler_;
};

} // namespace Models
} // namespace CleanEditor
