#pragma once

#include <QTemporaryFile>
#include <QTest>
#include <memory>

#include "documents-model.h"
#include "test-runner.h"

namespace CleanEditor::Tests {

class DocumentsModelTests : public QObject
{
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

} //namespace CleanEditor::Tests
