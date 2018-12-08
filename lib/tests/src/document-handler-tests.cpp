#include "document-handler-tests.h"
#include "document-handler.h"

#include <QSignalSpy>
#include <QFile>
#include <QTextStream>

using namespace CleanEditor::Logic;
static const constexpr char * dummy_content = "dummy content in file";

namespace CleanEditor {
namespace Tests {

void DocumentHandlerTests::initTestCase() {
  if (tmp_file_.exists()) {
    return;
  }
  QVERIFY2(tmp_file_.open(), "Failed creating a temporary file");
  QFile file{tmp_file_.fileName()};

  QVERIFY(file.open(QIODevice::ReadWrite));
  QTextStream stream{&file};

  stream << dummy_content;
}

void DocumentHandlerTests::checkInitialState_createEmptyfile_allPublicParameters() {
  DocumentHandler document;

  QVERIFY(document.isNewFile());
  QVERIFY(!document.needsUpdating());
  QVERIFY(!document.needsSaving());
  QCOMPARE(document.filename(), "untitled");
  QCOMPARE(document.fileType(), "");
  QVERIFY(document.fileUrl().isEmpty());
  QCOMPARE(document.textContent(), "");
  QVERIFY(document.id() > 0);
}

} //namespace Tests
} //namespace CleanEditor
