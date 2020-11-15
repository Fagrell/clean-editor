#include "file-handler-tests.h"
#include "file-handler.h"

#include <QFile>
#include <QSignalSpy>
#include <QTextStream>

using namespace CleanEditor::Logic;
static const constexpr char *kDummyContent = "dummy content in file";

namespace CleanEditor::Tests {

void FileHandlerTests::initTestCase()
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

void FileHandlerTests::load_validFile_fileOpened()
{
    FileHandler file_handler;
    QSignalSpy file_opened_spy(&file_handler, &FileHandler::fileOpened);
    file_handler.load(QUrl{tmp_file_.fileName()});

    QCOMPARE(file_opened_spy.count(), 1);
}

void FileHandlerTests::load_invalidFile_fileNotOpened()
{
    FileHandler file_handler;
    QSignalSpy file_opened_spy(&file_handler, &FileHandler::fileOpened);
    file_handler.load(QUrl{"file_doesnt_exist"});

    QCOMPARE(file_opened_spy.count(), 0);
}

void FileHandlerTests::load_validFile_fileNameIsCorrect()
{
    FileHandler file_handler;
    file_handler.load(QUrl{tmp_file_.fileName()});
    QCOMPARE(file_handler.fileName(), QFileInfo(tmp_file_.fileName()).fileName());
}

void FileHandlerTests::load_validFile_fileTypeIsCorrect()
{
    FileHandler file_handler;
    file_handler.load(QUrl{tmp_file_.fileName()});
    QCOMPARE(file_handler.fileType(), QFileInfo(tmp_file_.fileName()).suffix());
}

void FileHandlerTests::load_validFile_fileUrlIsCorrect()
{
    FileHandler file_handler;
    QUrl url{tmp_file_.fileName()};
    file_handler.load(url);
    QCOMPARE(file_handler.fileUrl(), url);
}

void FileHandlerTests::load_validFile_fileContentIsCorrect()
{
    FileHandler file_handler;
    file_handler.load(QUrl{tmp_file_.fileName()});
    QCOMPARE(file_handler.data(), QString{kDummyContent});
}

void FileHandlerTests::load_validFile_noErrorsRecieved()
{
    FileHandler file_handler;
    QSignalSpy error_spy(&file_handler, &FileHandler::error);
    file_handler.load(QUrl{tmp_file_.fileName()});

    QVERIFY(error_spy.count() == 0);
}

void FileHandlerTests::load_invalidFile_errorsRecieved()
{
    FileHandler file_handler;
    QSignalSpy error_spy(&file_handler, &FileHandler::error);
    file_handler.load(QUrl{"file_doesnt_exist"});

    QVERIFY(error_spy.count() == 1);
}

void FileHandlerTests::save_emptyData_updatedData()
{
    QTemporaryFile tmp_file;
    QVERIFY(tmp_file.open());

    FileHandler file_handler;
    file_handler.load(QUrl{tmp_file.fileName()});
    file_handler.save("new data saved");

    QCOMPARE(file_handler.data().toLocal8Bit().data(), "new data saved");
}

void FileHandlerTests::saveAs_emptyData_updatedData()
{
    QTemporaryFile tmp_file;
    QVERIFY(tmp_file.open());

    FileHandler file_handler;
    file_handler.saveAs(QUrl{tmp_file.fileName()}, "new data saved");

    QFile file{tmp_file.fileName()};
    QVERIFY(file.open(QIODevice::ReadWrite));

    QTextStream stream{&file};
    QCOMPARE(stream.readAll().toLocal8Bit().data(), "new data saved");
}

} //namespace CleanEditor::Tests
