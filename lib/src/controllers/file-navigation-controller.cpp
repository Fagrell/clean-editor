#include "file-navigation-controller.h"
#include "file-navigation-model.h"

namespace CleanEditor::Controllers {

FileNavigationController::FileNavigationController(QObject *parent)
    : QObject{parent}
{}

void FileNavigationController::setModel(CleanEditor::Models::FileNavigationModel* model) {
    model_ = model;
    if (!model_) {
        return;
    }

    model_->setParent(this);
}

int FileNavigationController::selectedIndex() const {
    if (!model_) {
        return -1;
    }

    return model_->selectedIndex();
}

void FileNavigationController::setSelectedIndex(int index) {
    if (!model_) {
        return;
    }

    model_->setSelectedIndex(index);
}

} // namespace CleanEditor::Controllers
