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
  ~EditorRouter();

  //Takes ownership of model
  void setModel(CleanEditor::Models::AbstractEditorModel* model);

  QString text() const;
  void setText(const QString& text);

Q_SIGNALS:
  void textChanged();

private:
  QPointer<CleanEditor::Models::AbstractEditorModel> model_;
};

} // namespace Routers
} // namespace CleanEditor

#endif
