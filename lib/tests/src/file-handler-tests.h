#pragma once

#include <QTest>
#include <QTemporaryFile>

#include "test-runner.h"

namespace CleanEditor {
namespace Tests {

class FileHandlerTests: public QObject {
  Q_OBJECT

private slots:
  void initTestCase();
  void load_validFile_fileOpened();
  void load_invalidFile_fileNotOpened();
  void load_validFile_fileNameIsCorrect();
  void load_validFile_fileTypeIsCorrect();
  void load_validFile_fileUrlIsCorrect();
  void load_validFile_fileContentIsCorrect();
  void load_validFile_noErrorsRecieved();
  void load_invalidFile_errorsRecieved();
  void save_emptyData_updatedData();
  void saveAs_emptyData_updatedData();

private:
  QTemporaryFile tmp_file_;
};

} //namespace Tests
} //namespace CleanEditor

ADD_TEST_CLASS(CleanEditor::Tests::FileHandlerTests);
