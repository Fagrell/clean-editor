#include "main-controller.h"

namespace CleanEditor {
namespace Controllers {

MainController::MainController(QObject* parent)
  : QObject{parent}
{}

MainController::~MainController()
{}

QString MainController::welcomeMessage() const {
  return "Hello world!";
}

} // namespace Controllers
} // namespace CleanEditor
