#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QFontDatabase>
#include <QDebug>

#include <main-controller.h>

static const constexpr auto kMainControllerInstance = "mainController";

int main(int argc, char *argv[])
{
  QGuiApplication::setApplicationName("Clean Editor");
  QGuiApplication::setOrganizationName("cleanqt.io");
  QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  QGuiApplication app(argc, argv);

  QFontDatabase fontDatabase;
  if (fontDatabase.addApplicationFont(":/fonts/fontello.ttf") == -1) {
      qWarning() << "Failed to load fontello.ttf";
  }

  qmlRegisterType<CleanEditor::Controllers::MainController>("CleanEditor", 1, 0, kMainControllerInstance);

  CleanEditor::Controllers::MainController mainController;

  QQmlApplicationEngine engine;
  engine.rootContext()->setContextProperty(kMainControllerInstance, &mainController);
  engine.load(QUrl(QStringLiteral("qrc:/views/MainView.qml")));

  if (engine.rootObjects().isEmpty()) {
    return -1;
  }

  return app.exec();
}
