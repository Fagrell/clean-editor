#pragma once

#include <QObject>
#include <QString>

#include "globals.h"

namespace CleanEditor {
namespace Models {
class AbstractEditorModel;
}

namespace Controllers {

/*!
* \brief The EditorController class is the router that passes data onto the model.
*        The class also recieves user input directly from a corresponding view (using the signals).
*
* \sa AbstractEditorModel
*/
class CLEAN_EDITOR_EXPORT EditorController : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(EditorController)

public:
    explicit EditorController(QObject *parent = nullptr);

    void setModel(CleanEditor::Models::AbstractEditorModel &model);

    QString text() const;
    void setText(const QString &text);

    int id() const;
    void setId(int id);

Q_SIGNALS:
    void textChanged();

private:
    CleanEditor::Models::AbstractEditorModel *model_{nullptr};
    QMetaObject::Connection text_changed_connection_;
};

} // namespace Controllers
} // namespace CleanEditor
