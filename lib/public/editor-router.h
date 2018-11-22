#ifndef EDITOR_ROUTER_H
#define EDITOR_ROUTER_H

#include <QObject>
#include <QPointer>
#include <QString>

#include "globals.h"

namespace CleanEditor {
namespace Models {
  class EditorModel;
}

namespace Routers {

class QML_EDITOR_EXPORT EditorRouter : public QObject {
  Q_OBJECT
  Q_DISABLE_COPY(EditorRouter)

public:
  explicit EditorRouter(QObject* parent = nullptr);
  ~EditorRouter();

  //Takes ownership of model
  void setModel(CleanEditor::Models::EditorModel* model);

Q_SIGNALS:
  void contentsChanged(const QString& text);

private:
  QPointer<CleanEditor::Models::EditorModel> model_;
};

} // namespace Routers
} // namespace CleanEditor

#endif
