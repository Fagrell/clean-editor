#pragma once

#include <QObject>
#include <QString>

#include "globals.h"

class QTextDocument;

namespace CleanEditor::Models {

/*!
* \brief The AbstractEditorModel class defines an abstract class that wraps around
*        data and functionality and is used in a text editor.
*
*        text() and setText() needs to be overridden. When the text has been replaced (i.e. when
*        setText is called), textReplaced needs to be emitted.
*
*        id_ (id() and setId) is used to identify the currently opened document that's being edited.
*/
class CLEAN_EDITOR_EXPORT AbstractEditorModel : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(AbstractEditorModel)

    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textReplaced)
    Q_PROPERTY(int id READ id WRITE setId NOTIFY idChanged)

public:
    explicit AbstractEditorModel(QObject *parent = nullptr);

    virtual QString text() const = 0;
    virtual void setText(const QString &text) = 0;

    int id() const;
    void setId(int id);

Q_SIGNALS:
    //! Used when the a minor change has been made in the text
    void textChanged();

    //! Used when setText is called (and therefore replaced).
    void textReplaced();
    void idChanged();

private:
    int id_{0};
};

} // namespace CleanEditor::Models
