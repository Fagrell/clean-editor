#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <main-controller.h>

static const constexpr auto kMainControllerInstance = "mainController";

int main(int argc, char *argv[])
{
#if defined(Q_OS_WIN)
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

  QGuiApplication app(argc, argv);

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
