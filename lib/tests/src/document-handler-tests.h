#pragma once

#include <QTemporaryFile>
#include <QTest>

#include "test-runner.h"

namespace CleanEditor::Tests {

class DocumentHandlerTests : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void checkInitialState_createEmptyFile_allPublicParameters();
    void checkInitialState_openedFile_allPublicParameters();
    void save_newFile_stillNewFile();
    void saveAs_newFile_noLongerNewFile();
    void setContent_notNeedsUpdating_contentNotChanged();
    void needsSaving_setNeedsUpdatingThenSave_needsSavingIsStillTrue();
    void needsSaving_setNeedsUpdatingThenSaveAs_needsSavingIsNowFalse();
    void textContent_updateTextContentAndSave_checkDifferentParams();

private:
    QTemporaryFile tmp_file_;
};

ADD_TEST_CLASS(DocumentHandlerTests);

} //namespace CleanEditor::Tests
