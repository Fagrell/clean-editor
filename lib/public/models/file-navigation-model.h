#pragma once

#include "globals.h"

#include <QObject>

namespace CleanEditor::Models {

class CLEAN_EDITOR_EXPORT FileNavigationModel : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(FileNavigationModel)

    Q_PROPERTY(
        int selectedIndex READ selectedIndex WRITE setSelectedIndex NOTIFY selectedIndexChanged)

public:
    explicit FileNavigationModel(QObject *parent = nullptr);

    int selectedIndex() const;
    void setSelectedIndex(int index);

Q_SIGNALS:
    void selectedIndexChanged();

private:
    int selected_index_{-1};
};

} // namespace CleanEditor::Models
