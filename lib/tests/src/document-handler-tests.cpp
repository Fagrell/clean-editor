#include "document-handler-tests.h"
#include "document-handler.h"

#include <QFile>
#include <QSignalSpy>
#include <QTextStream>

using namespace CleanEditor::Logic;
static const constexpr char *kDummyContent = "dummy content in file";

namespace CleanEditor::Tests {

void DocumentHandlerTests::initTestCase()
{
    if (tmp_file_.exists()) {
        return;
    }
    QVERIFY2(tmp_file_.open(), "Failed creating a temporary file");
    QFile file{tmp_file_.fileName()};

    QVERIFY(file.open(QIODevice::ReadWrite));
    QTextStream stream{&file};

    stream << kDummyContent;
}

void DocumentHandlerTests::checkInitialState_createEmptyFile_allPublicParameters()
{
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

void DocumentHandlerTests::checkInitialState_openedFile_allPublicParameters()
{
    DocumentHandler document;

    QSignalSpy document_opened_spy{&document, &DocumentHandler::fileOpened};
    QUrl file_url{tmp_file_.fileName()};
    document.load(file_url);

    QCOMPARE(document_opened_spy.count(), 1);
    QVERIFY(!document.isNewFile());
    QVERIFY(!document.needsUpdating());
    QVERIFY(!document.needsSaving());
    QCOMPARE(document.textContent(), QString{kDummyContent});
    QCOMPARE(document.fileUrl(), file_url);
    QCOMPARE(document.filename(), QFileInfo(tmp_file_.fileName()).fileName());
    QCOMPARE(document.fileType(), QFileInfo(tmp_file_.fileName()).suffix());
    QVERIFY(document.id() > 0);
}

void DocumentHandlerTests::save_newFile_stillNewFile()
{
    DocumentHandler document;
    document.save();
    QVERIFY(document.isNewFile());
}

void DocumentHandlerTests::saveAs_newFile_noLongerNewFile()
{
    DocumentHandler document;

    QSignalSpy file_url_changed{&document, &DocumentHandler::fileUrlChanged};
    QSignalSpy is_new_file_changed{&document, &DocumentHandler::isNewFileChanged};
    QUrl file_url{tmp_file_.fileName()};
    document.saveAs(file_url);
    QCOMPARE(file_url_changed.count(), 1);
    QCOMPARE(is_new_file_changed.count(), 1);
    QVERIFY(!document.isNewFile());
    QCOMPARE(document.fileUrl(), file_url);
    QCOMPARE(document.filename(), QFileInfo(tmp_file_.fileName()).fileName());
    QCOMPARE(document.fileType(), QFileInfo(tmp_file_.fileName()).suffix());
}

void DocumentHandlerTests::setContent_notNeedsUpdating_contentNotChanged()
{
    DocumentHandler document;

    document.setNeedsUpdating(false); //same as default
    document.setTextContent("test");
    QVERIFY(document.textContent().isEmpty());
}

void DocumentHandlerTests::needsSaving_setNeedsUpdatingThenSave_needsSavingIsStillTrue()
{
    DocumentHandler document;
    QVERIFY(!document.needsSaving());
    QSignalSpy needs_saving_changed{&document, &DocumentHandler::needsSavingChanged};
    document.setNeedsUpdating(true);
    QCOMPARE(needs_saving_changed.count(), 1);
    QVERIFY(document.needsSaving());
    document.save();
    QCOMPARE(needs_saving_changed.count(), 1);
    QVERIFY(document.needsSaving());
}

void DocumentHandlerTests::needsSaving_setNeedsUpdatingThenSaveAs_needsSavingIsNowFalse()
{
    DocumentHandler document;
    QSignalSpy needs_saving_changed{&document, &DocumentHandler::needsSavingChanged};
    document.setNeedsUpdating(true);
    QCOMPARE(needs_saving_changed.count(), 1);
    QVERIFY(document.needsSaving());
    document.saveAs(QUrl{tmp_file_.fileName()});
    QCOMPARE(needs_saving_changed.count(), 2);
    QVERIFY(!document.needsSaving());
    QVERIFY(!document.needsUpdating());
}

void DocumentHandlerTests::textContent_updateTextContentAndSave_checkDifferentParams()
{
    DocumentHandler document;
    document.setNeedsUpdating(true);
    document.setTextContent("test");
    QVERIFY(document.needsSaving());
    QVERIFY(!document.needsUpdating());

    document.saveAs(QUrl{tmp_file_.fileName()});
    QVERIFY(!document.needsSaving());
    QCOMPARE(document.textContent(), QString{"test"});
}

} //namespace CleanEditor::Tests
