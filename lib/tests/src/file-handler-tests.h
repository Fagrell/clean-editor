#pragma once

#include <QTemporaryFile>
#include <QTest>

#include "test-runner.h"

namespace CleanEditor::Tests {

class FileHandlerTests : public QObject
{
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

ADD_TEST_CLASS(FileHandlerTests);

} //namespace CleanEditor::Tests
