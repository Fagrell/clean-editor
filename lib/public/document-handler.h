#pragma once

#include <QObject>
#include <QPointer>
#include <QString>
#include <QUrl>

#include "file-handler.h"

#include "globals.h"

class QTextDocument;
class QQuickTextDocument;

namespace CleanEditor::Logic {
/*!
* \brief The DocumentHandler class handles a document that has been opened or is newly created.
*
*        A newly created DocumentHandler is automatically considered a new file until load() or
*        saveAs() is called. An id is generated automatically.
*
*        The document can be flagged as 'needsUpdating' which needs to be set in order to update
*        the content using setContent().
*
*        needsSaving is automatically set when the content has been updated but not saved.
*
*        filename and fileType are parsed from the fileUrl.
*
* \sa FileHandler
*
*/
class CLEAN_EDITOR_EXPORT DocumentHandler : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(DocumentHandler)

    Q_PROPERTY(QString filename READ filename)
    Q_PROPERTY(QString fileType READ fileType)
    Q_PROPERTY(QUrl fileUrl READ fileUrl NOTIFY fileUrlChanged)
    Q_PROPERTY(QString textContent READ textContent WRITE setTextContent)
    Q_PROPERTY(int id READ id)
    Q_PROPERTY(
        bool needsUpdating READ needsUpdating WRITE setNeedsUpdating NOTIFY needsUpdatingChanged)
    Q_PROPERTY(bool needsSaving READ needsSaving WRITE setNeedsSaving NOTIFY needsSavingChanged)
    Q_PROPERTY(bool isNewFile READ isNewFile WRITE setIsNewFile NOTIFY isNewFileChanged)

public:
    explicit DocumentHandler(QObject *parent = nullptr);

    QString filename() const;
    QString fileType() const;
    QUrl fileUrl() const;
    QString textContent() const;
    int id() const;

    bool needsUpdating() const;
    void setNeedsUpdating(bool needs_updating);

    bool needsSaving() const;

    bool isNewFile() const;

public Q_SLOTS:
    void load(const QUrl &file_url);
    void saveAs(const QUrl &file_url);
    void save();
    void setTextContent(const QString &text);

Q_SIGNALS:
    void fileUrlChanged();
    void fileOpened();
    void error(const QString &message);
    void contentUpdated();
    void needsUpdatingChanged();
    void isNewFileChanged();
    void needsSavingChanged();

private:
    void setIsNewFile(bool new_file);
    void setNeedsSaving(bool needs_saving);

    int id_{0};
    FileHandler file_handler_;
    QString text_content_;
    bool needs_updating_{false};
    bool is_new_file_{true};
    bool needs_saving_{false};

private Q_SLOTS:
    void onFileOpened();
};

} //namespace CleanEditor::Logic

Q_DECLARE_METATYPE(CleanEditor::Logic::DocumentHandler *)
