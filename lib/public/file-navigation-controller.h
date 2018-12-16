#pragma once

#include <QObject>
#include <QPointer>

#include "globals.h"

namespace CleanEditor {
namespace Models {
  class FileNavigationModel;
}
namespace Controllers {

class QML_EDITOR_EXPORT FileNavigationController : public QObject {
  Q_OBJECT
  Q_DISABLE_COPY(FileNavigationController)

public:
  explicit FileNavigationController(QObject* parent = nullptr);

  //Takes ownership of model
  void setModel(CleanEditor::Models::FileNavigationModel* model);

  int selectedIndex() const;
  void setSelectedIndex(int index);

Q_SIGNALS:
  void fileOpenedClicked(int id);

private:
  QPointer<CleanEditor::Models::FileNavigationModel> model_;

};

} // namespace Controllers
} // namespace CleanEditor
