#include "file-navigation-model.h"

namespace CleanEditor::Models {

FileNavigationModel::FileNavigationModel(QObject *parent)
    : QObject{parent}
{}

int FileNavigationModel::selectedIndex() const
{
    return selected_index_;
}

void FileNavigationModel::setSelectedIndex(const int index)
{
    if (selected_index_ == index) {
        return;
    }

    selected_index_ = index;
    emit selectedIndexChanged();
}

} //namespace CleanEditor::Models
