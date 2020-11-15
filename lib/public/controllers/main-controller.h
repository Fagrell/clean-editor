#pragma once

#include <QObject>
#include <QString>

#include "editor-controller.h"
#include "file-navigation-controller.h"
#include "menu-controller.h"

#include "globals.h"

namespace CleanEditor {
namespace Models {
class DocumentsModel;
}

namespace Controllers {

class CLEAN_EDITOR_EXPORT MainController : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(MainController)

    Q_PROPERTY(CleanEditor::Controllers::MenuController *menuController READ menuController CONSTANT)
    Q_PROPERTY(
        CleanEditor::Controllers::EditorController *editorController READ editorController CONSTANT)
    Q_PROPERTY(CleanEditor::Controllers::FileNavigationController *fileNavigationController READ
                   fileNavigationController CONSTANT)

public:
    explicit MainController(QObject *parent = nullptr);

    void setDocumentsModel(CleanEditor::Models::DocumentsModel &documents_model);

    MenuController *menuController();
    EditorController *editorController();
    FileNavigationController *fileNavigationController();

private:
    void storeTextToCurrentFile();

    MenuController menu_controller_;
    EditorController editor_controller_;
    FileNavigationController file_navigation_controller_;
    CleanEditor::Models::DocumentsModel *documents_model_{nullptr};
    QMetaObject::Connection document_created_connection_;

private Q_SLOTS:
    void handleEditorTextChanged();
    void openDocument(int id);
    void handleSaveFileClicked();
    void handleSaveAsFileClicked(const QUrl &url);
    void handleNewFileClicked();
    void handleOpenedFileClicked(int id);
    void handleOpenFileClicked(const QUrl &url);
};

} // namespace Controllers
} // namespace CleanEditor
