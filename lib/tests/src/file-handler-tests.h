#ifndef FILE_HANDLER_TESTS_H
#define FILE_HANDLER_TESTS_H

#include <QTest>

#include "test-runner.h"

namespace CleanEditor {
namespace Tests {

class FileHandlerTests: public QObject
{
  Q_OBJECT

private slots:
  void initTestCase();
  void myFirstTest();
};

} //namespace Tests
} //namespace CleanEditor

ADD_TEST_CLASS(CleanEditor::Tests::FileHandlerTests);

#endif
