#include <QFontDatabase>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "editor-controller.h"
#include "file-navigation-controller.h"
#include "main-controller.h"
#include "menu-controller.h"

#include "document-handler.h"
#include "documents-model.h"
#include "file-navigation-model.h"
#include "line-numbers.h"
#include "menu-model.h"
#include "qml-editor-model.h"

using namespace CleanEditor::Controllers;
using namespace CleanEditor::Logic;
using namespace CleanEditor::Models;
using namespace CleanEditor::UI;

int main(int argc, char *argv[])
{
    QGuiApplication::setApplicationName("Clean Editor");
    QGuiApplication::setOrganizationName("cleanqt.io");

    QGuiApplication app(argc, argv);

    const auto addFonts = [](const auto &... fonts) {
        const auto addFont = [](const auto &font) {
            if (QFontDatabase::addApplicationFont(font) == -1) {
                qWarning() << "Failed to load font: " << font;
            }
        };
        (addFont(fonts), ...);
    };

    addFonts(":/fonts/Hack-Regular.ttf",
             ":/fonts/Hack-Bold.ttf",
             ":/fonts/Hack-BoldItalic.ttf",
             ":/fonts/Hack-Italic.ttf",
             ":/fonts/fontello.ttf");

    qmlRegisterType<MainController>("CleanEditor", 1, 0, "MainController");
    qmlRegisterType<MenuController>("CleanEditor", 1, 0, "MenuController");
    qmlRegisterType<FileNavigationController>("CleanEditor", 1, 0, "FileNavigationController");
    qmlRegisterType<DocumentHandler>("CleanEditor", 1, 0, "DocumentHandler");
    qmlRegisterType<LineNumbers>("CleanEditor", 1, 0, "LineNumbers");

    MainController main_controller;
    DocumentsModel documents_model;
    main_controller.setDocumentsModel(documents_model);

    QmlEditorModel editor_model;
    main_controller.editorController()->setModel(editor_model);

    MenuModel menu_model;
    main_controller.menuController()->setModel(menu_model);

    FileNavigationModel file_navigation_model;
    main_controller.fileNavigationController()->setModel(file_navigation_model);

    main_controller.menuController()->newFileClicked(); //Create a new file to start with!

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("mainController", &main_controller);
    engine.rootContext()->setContextProperty("documentsModel", &documents_model);
    engine.rootContext()->setContextProperty("editorModel", &editor_model);
    engine.rootContext()->setContextProperty("menuModel", &menu_model);
    engine.rootContext()->setContextProperty("fileNavigationModel", &file_navigation_model);
    engine.load(QUrl(QStringLiteral("qrc:/views/MainView.qml")));

    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    return app.exec();
}
