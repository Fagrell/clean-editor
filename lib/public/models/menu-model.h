#pragma once

#include "globals.h"

#include <QObject>
#include <QPointer>
#include <QString>

class QTextDocument;

namespace CleanEditor {
namespace Logic {
class DocumentHandler;
}
namespace Models {

class CLEAN_EDITOR_EXPORT MenuModel : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(MenuModel)

    Q_PROPERTY(QString title READ title NOTIFY titleChanged)
    Q_PROPERTY(bool isNewFile READ isNewFile NOTIFY isNewFileChanged)

public:
    explicit MenuModel(QObject *parent = nullptr);

    void setDocument(CleanEditor::Logic::DocumentHandler &document_handler);

    QString title() const;
    bool isNewFile() const;

Q_SIGNALS:
    void titleChanged();
    void isNewFileChanged();

private:
    QPointer<CleanEditor::Logic::DocumentHandler> document_handler_;
};

} // namespace Models
} // namespace CleanEditor
