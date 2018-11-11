#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QFontDatabase>
#include <QDebug>

#include "main-controller.h"
#include "document-handler.h"
#include "documents-model.h"
#include "line-numbers.h"

static const constexpr auto kMainControllerInstance = "mainController";

int main(int argc, char *argv[])
{
  QGuiApplication::setApplicationName("Clean Editor");
  QGuiApplication::setOrganizationName("cleanqt.io");
  QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  QGuiApplication app(argc, argv);

  QStringList fonts = QStringList{} << ":/fonts/Hack-Regular.ttf" << ":/fonts/Hack-Bold.ttf"
                                    << ":/fonts/Hack-BoldItalic.ttf" << ":/fonts/Hack-Italic.ttf"
                                    << ":/fonts/fontello.ttf";
  QFontDatabase fontDatabase;
  for (const auto& font : fonts) {
    if (fontDatabase.addApplicationFont(font) == -1) {
        qWarning() << "Failed to load font: " << font;
    }
  }

  qmlRegisterType<CleanEditor::Controllers::MainController>("CleanEditor", 1, 0, kMainControllerInstance);
  qmlRegisterType<CleanEditor::Logic::DocumentHandler>("CleanEditor", 1, 0, "DocumentHandler");
  qmlRegisterType<CleanEditor::UI::LineNumbers>("CleanEditor", 1, 0, "LineNumbers");

  CleanEditor::Controllers::MainController mainController;
  CleanEditor::Model::DocumentsModel documentsModel;

  QQmlApplicationEngine engine;
  engine.rootContext()->setContextProperty(kMainControllerInstance, &mainController);
  engine.rootContext()->setContextProperty("documentsModel", &documentsModel);
  engine.load(QUrl(QStringLiteral("qrc:/views/MainView.qml")));

  if (engine.rootObjects().isEmpty()) {
    return -1;
  }

  return app.exec();
}
