#pragma once

#include "editor-model.h"
class QQuickTextDocument;

namespace CleanEditor::Models {

/*!
* \brief The QmlEditorModel class is used to expose the EditorModel to an
*        Qml-component that's using a QQuickTextDocument internally.
*        See EditorModel for more information.
*
* \sa EditorModel
*/
class QmlEditorModel : public EditorModel
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(QmlEditorModel)

    Q_PROPERTY(QQuickTextDocument *document READ document WRITE setDocument NOTIFY documentChanged)

public:
    explicit QmlEditorModel(QObject *parent = nullptr);

    QQuickTextDocument *document() const;
    void setDocument(QQuickTextDocument *document);

Q_SIGNALS:
    void documentChanged();

private:
    QTextDocument *textDocument() const;

    QQuickTextDocument *document_{nullptr};
};

} //namespace CleanEditor::Models
