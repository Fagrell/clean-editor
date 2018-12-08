#pragma once

#include <QTest>
#include <QTemporaryFile>

#include "test-runner.h"

namespace CleanEditor {
namespace Tests {

class DocumentHandlerTests: public QObject {
  Q_OBJECT

private slots:
  void initTestCase();
  void checkInitialState_createEmptyfile_allPublicParameters();

private:
  QTemporaryFile tmp_file_;
};

ADD_TEST_CLASS(DocumentHandlerTests);

} //namespace Tests
} //namespace CleanEditor


