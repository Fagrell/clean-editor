#pragma once

#include <QAbstractListModel>
#include <QUrl>

#include <memory>
#include <unordered_map>
#include <utility>

#include "document-handler.h"
#include "globals.h"

namespace CleanEditor {

namespace Logic {
class DocumentHandler;
}

namespace Models {

/*!
* \brief The DocumentsModel class is a Qt List Model and can be shown using a Qt View.
*        The class wraps around a list of DocumentHandlers (Documents).
*
*        A new document is created by calling newFile() or openFile(), which will then signal
*        documentCreated(), including a document ID.
*
*        The ID is used to GET specific data from the document using one of the getters.
*        Or, likewise, the ID can be used to SET specific data for the document using one
*        of the setters.
*
* \sa DocumentHandler
*/
class CLEAN_EDITOR_EXPORT DocumentsModel : public QAbstractListModel
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(DocumentsModel)

public:
    enum DocumentsRoles {
        FileIdRole = Qt::UserRole + 1,
        FileDocumentRole,
        FilenameRole,
        FileTypeRole,
        FileUrlRole,
        FileContentRole,
        FileNeedsUpdatingRole,
        FileNeedsSavingRole,
        FileIsNewRole,
    };

    explicit DocumentsModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    CleanEditor::Logic::DocumentHandler *document(int id) const;

    QString filename(int id) const;
    QString fileType(int id) const;
    QUrl fileUrl(int id) const;
    bool isFileNew(int id) const;

    bool needsUpdating(int id) const;
    bool needsSaving(int id) const;

    QString fileContent(int id) const;
    void setFileContent(int id, const QString &text);

    void save(int id);
    void saveAs(int id, const QUrl &file_url);

    void setNeedsUpdating(int id);

    QModelIndex indexForId(int id) const;

public Q_SLOTS:
    void newFile();
    void openFile(const QUrl &file_url);
    void closeFile(int id);

Q_SIGNALS:
    void documentCreated(int id);

private:
    std::vector<std::unique_ptr<CleanEditor::Logic::DocumentHandler>> data_;

    void appendNewDocument(std::unique_ptr<CleanEditor::Logic::DocumentHandler> document);

    template<class T>
    T getData(const int id, const DocumentsRoles role, const T &default_value) const
    {
        const auto index = indexForId(id);
        if (!index.isValid()) {
            return default_value;
        }

        return data(index, role).value<T>();
    }

    template<class TFunc, class... Values>
    void setData(const int id, const TFunc function, Values &&... values)
    {
        for (size_t i{0}; i < data_.size(); i++) {
            if (data_.at(i)->id() == id) {
                std::bind(function, data_.at(i).get(), std::forward<Values>(values)...)();
                auto model_index = index(static_cast<int>(i), 0);
                emit dataChanged(model_index, model_index);
                return;
            }
        }
    }
};

} //namespace Models
} //namespace CleanEditor
