#include "menu-model.h"
#include "document-handler.h"

using namespace CleanEditor::Logic;

namespace CleanEditor::Models {

MenuModel::MenuModel(QObject *parent)
    : QObject{parent}
{}

void MenuModel::setDocument(DocumentHandler &document_handler)
{
    if (document_handler_ == &document_handler) {
        return;
    }

    if (document_handler_) {
        disconnect(document_handler_.data(),
                   &DocumentHandler::fileUrlChanged,
                   this,
                   &MenuModel::titleChanged);
        disconnect(document_handler_.data(),
                   &DocumentHandler::isNewFileChanged,
                   this,
                   &MenuModel::isNewFileChanged);
    }

    document_handler_ = &document_handler;
    if (!document_handler_) {
        return;
    }

    connect(document_handler_.data(),
            &DocumentHandler::fileUrlChanged,
            this,
            &MenuModel::titleChanged);
    connect(document_handler_.data(),
            &DocumentHandler::isNewFileChanged,
            this,
            &MenuModel::isNewFileChanged);

    emit titleChanged();
    emit isNewFileChanged();
}

QString MenuModel::title() const
{
    if (!document_handler_) {
        return {};
    }

    return document_handler_->filename();
}

bool MenuModel::isNewFile() const
{
    if (!document_handler_) {
        return false;
    }
    return document_handler_->isNewFile();
}

} //namespace CleanEditor::Models
