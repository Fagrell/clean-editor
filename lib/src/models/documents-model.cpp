#include "documents-model.h"

using namespace CleanEditor::Logic;

namespace CleanEditor::Models {

DocumentsModel::DocumentsModel(QObject *parent)
    : QAbstractListModel{parent}
{}

int DocumentsModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0;
    }

    return static_cast<int>(data_.size());
}

QVariant DocumentsModel::data(const QModelIndex &index, const int role) const
{
    Q_ASSERT(checkIndex(index,
                        QAbstractItemModel::CheckIndexOption::IndexIsValid
                            | QAbstractItemModel::CheckIndexOption::ParentIsInvalid));

    const auto document = data_.at(static_cast<size_t>(index.row())).get();
    QVariant data;
    switch (role) {
    case FileDocumentRole:
        data.setValue(document);
        break;
    case FileIdRole:
        data.setValue(document->id());
        break;
    case FilenameRole:
    case Qt::DisplayRole:
        data.setValue(document->filename());
        break;
    case FileTypeRole:
        data.setValue(document->fileType());
        break;
    case FileUrlRole:
        data.setValue(document->fileUrl());
        break;
    case FileContentRole:
        data.setValue(document->textContent());
        break;
    case FileNeedsUpdatingRole:
        data.setValue(document->needsUpdating());
        break;
    case FileNeedsSavingRole:
        data.setValue(document->needsSaving());
        break;
    case FileIsNewRole:
        data.setValue(document->isNewFile());
        break;
    default:
        return {};
    }
    return data;
}

QHash<int, QByteArray> DocumentsModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[FileDocumentRole] = "fileDocumentRole";
    roles[FileIdRole] = "fileId";
    roles[FilenameRole] = "filename";
    roles[FileTypeRole] = "fileType";
    roles[FileUrlRole] = "fileUrl";
    roles[FileContentRole] = "fileContent";
    roles[FileNeedsUpdatingRole] = "fileNeedsUpdating";
    roles[FileNeedsSavingRole] = "fileNeedsSaving";
    return roles;
}

DocumentHandler *DocumentsModel::document(const int id) const
{
    return getData<DocumentHandler *>(id, FileDocumentRole, nullptr);
}

QString DocumentsModel::filename(const int id) const
{
    return getData(id, FilenameRole, QString{""});
}

QString DocumentsModel::fileType(const int id) const
{
    return getData(id, FileTypeRole, QString{""});
}

QUrl DocumentsModel::fileUrl(const int id) const
{
    return getData(id, FileUrlRole, QUrl{""});
}

bool DocumentsModel::isFileNew(const int id) const
{
    return getData(id, FileIsNewRole, false);
}

bool DocumentsModel::needsUpdating(const int id) const
{
    return getData(id, FileNeedsUpdatingRole, false);
}

bool DocumentsModel::needsSaving(const int id) const
{
    return getData(id, FileNeedsSavingRole, false);
}

QString DocumentsModel::fileContent(const int id) const
{
    return getData(id, FileContentRole, QString{""});
}

void DocumentsModel::setFileContent(const int id, const QString &text)
{
    setData(id, &DocumentHandler::setTextContent, text);
}

void DocumentsModel::save(const int id)
{
    setData(id, &DocumentHandler::save);
}

void DocumentsModel::saveAs(const int id, const QUrl &file_url)
{
    setData(id, &DocumentHandler::saveAs, file_url);
}

void DocumentsModel::setNeedsUpdating(const int id)
{
    setData(id, &DocumentHandler::setNeedsUpdating, true);
}

void DocumentsModel::newFile()
{
    auto document_handler = std::make_unique<CleanEditor::Logic::DocumentHandler>();
    appendNewDocument(std::move(document_handler));
}

void DocumentsModel::openFile(const QUrl &file_url)
{
    auto document_handler = std::make_unique<CleanEditor::Logic::DocumentHandler>();
    document_handler->load(file_url);

    appendNewDocument(std::move(document_handler));
}

void DocumentsModel::closeFile(const int id)
{
    QModelIndex index = indexForId(id);

    if (!index.isValid()) {
        return;
    }

    const auto row_to_remove = static_cast<int>(index.row());
    beginRemoveRows({}, row_to_remove, row_to_remove);
    data_.erase(data_.begin() + row_to_remove);
    endRemoveRows();
}

QModelIndex DocumentsModel::indexForId(const int id) const
{
    size_t i{0};
    for (; i < data_.size(); i++) {
        if (data_.at(i)->id() == id) {
            break;
        }
    }

    //Not found
    if (i == data_.size()) {
        return QModelIndex{};
    }

    return index(static_cast<int>(i), 0);
}

void DocumentsModel::appendNewDocument(std::unique_ptr<DocumentHandler> document)
{
    if (!document) {
        return;
    }

    const auto id = document->id();
    const auto index = static_cast<int>(data_.size());
    beginInsertRows({}, index, index);
    data_.emplace_back(std::move(document));
    endInsertRows();

    emit documentCreated(id);
}

} //namespace CleanEditor::Models
