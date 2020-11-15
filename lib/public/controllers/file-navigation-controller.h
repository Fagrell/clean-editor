#pragma once

#include <QObject>

#include "globals.h"

namespace CleanEditor {
namespace Models {
class FileNavigationModel;
}
namespace Controllers {

class CLEAN_EDITOR_EXPORT FileNavigationController : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(FileNavigationController)

public:
    explicit FileNavigationController(QObject *parent = nullptr);

    void setModel(CleanEditor::Models::FileNavigationModel &model);

    int selectedIndex() const;
    void setSelectedIndex(int index);

Q_SIGNALS:
    void fileOpenedClicked(int id);

private:
    CleanEditor::Models::FileNavigationModel *model_{nullptr};
};

} // namespace Controllers
} // namespace CleanEditor
