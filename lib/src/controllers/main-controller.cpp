#include "main-controller.h"

#include "editor-controller.h"
#include "file-navigation-controller.h"
#include "menu-controller.h"

#include "documents-model.h"

using namespace CleanEditor::Models;

namespace CleanEditor::Controllers {

MainController::MainController(QObject *parent)
    : QObject{parent}
{
    connect(&editor_controller_,
            &EditorController::textChanged,
            this,
            &MainController::handleEditorTextChanged);
    connect(&menu_controller_,
            &MenuController::saveFileClicked,
            this,
            &MainController::handleSaveFileClicked);
    connect(&menu_controller_,
            &MenuController::saveAsFileClicked,
            this,
            &MainController::handleSaveAsFileClicked);
    connect(&menu_controller_,
            &MenuController::newFileClicked,
            this,
            &MainController::handleNewFileClicked);
    connect(&menu_controller_,
            &MenuController::openFileClicked,
            this,
            &MainController::handleOpenFileClicked);
    connect(&file_navigation_controller_,
            &FileNavigationController::fileOpenedClicked,
            this,
            &MainController::handleOpenedFileClicked);
}

void MainController::setDocumentsModel(CleanEditor::Models::DocumentsModel &documents_model)
{
    disconnect(document_created_connection_);
    documents_model_ = &documents_model;
    document_created_connection_ = connect(documents_model_,
                                           &DocumentsModel::documentCreated,
                                           this,
                                           &MainController::openDocument);
}

MenuController *MainController::menuController()
{
    return &menu_controller_;
}

EditorController *MainController::editorController()
{
    return &editor_controller_;
}

FileNavigationController *MainController::fileNavigationController()
{
    return &file_navigation_controller_;
}

void MainController::handleEditorTextChanged()
{
    if (!documents_model_) {
        return;
    }

    int current_file_id = editor_controller_.id();
    documents_model_->setNeedsUpdating(current_file_id);
}

void MainController::openDocument(const int id)
{
    if (!documents_model_) {
        return;
    }

    editor_controller_.setText(documents_model_->fileContent(id));
    editor_controller_.setId(id);

    menu_controller_.setDocument(*documents_model_->document(id));
    file_navigation_controller_.setSelectedIndex(documents_model_->indexForId(id).row());
}

void MainController::handleSaveFileClicked()
{
    if (!documents_model_) {
        return;
    }

    storeTextToCurrentFile();
    int current_file_id = editor_controller_.id();
    documents_model_->save(current_file_id);
}

void MainController::handleSaveAsFileClicked(const QUrl &url)
{
    if (!documents_model_) {
        return;
    }

    storeTextToCurrentFile();

    int current_file_id = editor_controller_.id();
    documents_model_->saveAs(current_file_id, url);
}

void MainController::handleNewFileClicked()
{
    if (!documents_model_) {
        return;
    }

    storeTextToCurrentFile();
    documents_model_->newFile();
}

void MainController::handleOpenedFileClicked(const int id)
{
    if (!documents_model_) {
        return;
    }

    int current_file_id = editor_controller_.id();
    if (current_file_id == id) {
        return;
    }

    //First set the file content
    storeTextToCurrentFile();
    //Then open
    openDocument(id);
}

void MainController::handleOpenFileClicked(const QUrl &url)
{
    storeTextToCurrentFile();
    documents_model_->openFile(url);
}

void MainController::storeTextToCurrentFile()
{
    int current_file_id = editor_controller_.id();
    documents_model_->setFileContent(current_file_id, editor_controller_.text());
}

} // namespace CleanEditor::Controllers
