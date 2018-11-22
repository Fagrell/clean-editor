#ifndef EDITOR_ROUTER_H
#define EDITOR_ROUTER_H

#include <QObject>
#include <QPointer>
#include <QString>

#include "globals.h"

namespace CleanEditor {
namespace Models {
<<<<<<< HEAD
  class EditorModel;
=======
  class AbstractEditorModel;
>>>>>>> Added AbstractEditorModel to the EditorRouter
}

namespace Routers {

class QML_EDITOR_EXPORT EditorRouter : public QObject {
  Q_OBJECT
  Q_DISABLE_COPY(EditorRouter)

public:
  explicit EditorRouter(QObject* parent = nullptr);
  ~EditorRouter();

  //Takes ownership of model
<<<<<<< HEAD
  void setModel(CleanEditor::Models::EditorModel* model);
=======
  void setModel(CleanEditor::Models::AbstractEditorModel* model);
>>>>>>> Added AbstractEditorModel to the EditorRouter

  QString text() const;
  void setText(const QString& text);

Q_SIGNALS:
  void textChanged();

private:
<<<<<<< HEAD
  QPointer<CleanEditor::Models::EditorModel> model_;
=======
  QPointer<CleanEditor::Models::AbstractEditorModel> model_;
>>>>>>> Added AbstractEditorModel to the EditorRouter
};

} // namespace Routers
} // namespace CleanEditor

#endif
