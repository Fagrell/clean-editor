#include "documents-model-tests.h"

#include <QSignalSpy>
#include <QFile>
#include <QTextStream>
#include <QAbstractItemModelTester>

using namespace CleanEditor::Logic;
using namespace CleanEditor::Models;
static const constexpr char * kDummyContent = "dummy content in file";

namespace CleanEditor {
namespace Tests {

void DocumentsModelTests::initTestCase() {
  if (tmp_file_.exists()) {
    return;
  }
  QVERIFY2(tmp_file_.open(), "Failed creating a temporary file");
  QFile file{tmp_file_.fileName()};

  QVERIFY(file.open(QIODevice::ReadWrite));
  QTextStream stream{&file};

  stream << kDummyContent;
}

std::unique_ptr<DocumentsModel> DocumentsModelTests::createEmptyModel() {
  auto documents_model = std::make_unique<DocumentsModel>();
  new QAbstractItemModelTester{documents_model.get(), QAbstractItemModelTester::FailureReportingMode::QtTest, documents_model.get()};
  return documents_model;
}

void DocumentsModelTests::newFile_empty_newEmptyFileHasBeenCreated() {
  auto documents_model = createEmptyModel();
  QSignalSpy document_created{documents_model.get(), &DocumentsModel::documentCreated};
  documents_model->newFile();

  QCOMPARE(document_created.count(), 1);
  QCOMPARE(documents_model->rowCount(), 1);

  int id = document_created.first().first().toInt();
  QVERIFY(documents_model->isFileNew(id));
  QVERIFY(!documents_model->needsUpdating(id));
  QVERIFY(!documents_model->needsSaving(id));
  QCOMPARE(documents_model->filename(id), "untitled");
  QCOMPARE(documents_model->fileType(id), "");
  QVERIFY(documents_model->fileUrl(id).isEmpty());
  QCOMPARE(documents_model->fileContent(id), "");
  QVERIFY(documents_model->document(id) != nullptr);

}

} //namespace Tests
} //namespace CleanEditor
