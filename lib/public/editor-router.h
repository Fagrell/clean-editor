#ifndef EDITOR_ROUTER_H
#define EDITOR_ROUTER_H

#include <QObject>
#include <QPointer>
#include <QString>

#include "globals.h"

namespace CleanEditor {
namespace Models {
  class AbstractEditorModel;
}

namespace Routers {

class QML_EDITOR_EXPORT EditorRouter : public QObject {
  Q_OBJECT
  Q_DISABLE_COPY(EditorRouter)

public:
  explicit EditorRouter(QObject* parent = nullptr);

  //Takes ownership of model
  void setModel(CleanEditor::Models::AbstractEditorModel* model);

  QString text() const;
  void setText(const QString& text);

  int id() const;
  void setId(int id);

Q_SIGNALS:
  void textChanged();

private:
  QPointer<CleanEditor::Models::AbstractEditorModel> model_;
  QMetaObject::Connection text_changed_connection_;
};

} // namespace Routers
} // namespace CleanEditor

#endif
