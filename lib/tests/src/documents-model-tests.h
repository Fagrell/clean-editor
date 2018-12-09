#pragma once

#include <QTest>
#include <QTemporaryFile>
#include <memory>

#include "test-runner.h"
#include "documents-model.h"


namespace CleanEditor {
namespace Tests {

class DocumentsModelTests : public QObject {
  Q_OBJECT

private slots:
  void initTestCase();
  void newFile_empty_newEmptyFileHasBeenCreated();
  void saveAs_newFile_openFileWithNewContent();

private:
  QTemporaryFile tmp_file_;
  static std::unique_ptr<CleanEditor::Models::DocumentsModel> createEmptyModel();
};

ADD_TEST_CLASS(DocumentsModelTests);

} //namespace Tests
} //namespace CleanEditor


