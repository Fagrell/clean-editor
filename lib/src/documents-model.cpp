#include "documents-model.h"

using namespace CleanEditor::Logic;

namespace CleanEditor {
namespace Models {

DocumentsModel::DocumentsModel(QObject* parent) : QAbstractListModel{parent} {
}

int DocumentsModel::rowCount(const QModelIndex& parent) const {
  if (parent.isValid()) {
    return 0;
  }

  return static_cast<int>(data_.size());
}

QVariant DocumentsModel::data(const QModelIndex& index, int role) const {
  Q_ASSERT(checkIndex(index, QAbstractItemModel::CheckIndexOption::IndexIsValid | QAbstractItemModel::CheckIndexOption::ParentIsInvalid));

  DocumentHandler* document = data_.at(static_cast<size_t>(index.row())).get();
  QVariant data;
  switch (role) {
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
    case FileUpdatedRole:
      data.setValue(document->contentUpdated());
      break;
    default:
      return {};
  }
  return data;
}

QHash<int, QByteArray> DocumentsModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[FileIdRole] = "FileId";
    roles[FilenameRole] = "Filename";
    roles[FileTypeRole] = "FileType";
    roles[FileUrlRole] = "FileUrl";
    roles[FileContentRole] = "FileContent";
    roles[FileUpdatedRole] = "FileUpdated";
    return roles;
}

QString DocumentsModel::filename(int id) const {
  return getData(id, FilenameRole, QString{""});
}

QString DocumentsModel::fileType(int id) const {
  return getData(id, FileTypeRole, QString{""});
}

QUrl DocumentsModel::fileUrl(int id) const {
  return getData(id, FileUrlRole, QUrl{""});
}

QString DocumentsModel::fileContent(int id) const {
  return getData(id, FileContentRole, QString{""});
}

void DocumentsModel::setFileContent(int id, const QString& text) {
  setData(id, &DocumentHandler::setTextContent, text);
}

void DocumentsModel::save(int id) {
  setData(id, &DocumentHandler::save);
}

void DocumentsModel::saveAs(int id, const QUrl& file_url) {
  setData(id, &DocumentHandler::saveAs, file_url);
}

void DocumentsModel::openFile(const QUrl& file_url) {
  auto document_handler = std::make_unique<CleanEditor::Logic::DocumentHandler>();
  document_handler->load(file_url);

  auto index = static_cast<int>(data_.size());
  beginInsertRows({}, index, index);
  data_.emplace_back(std::move(document_handler));
  endInsertRows();

  emit documentCreated(document_handler.get());
}

void DocumentsModel::closeFile(int id) {
  QModelIndex index = indexForId(id);

  if (!index.isValid()) {
    return;
  }

  auto row_to_remove = static_cast<int>(index.row());
  beginRemoveRows({}, row_to_remove, row_to_remove);
  data_.erase(data_.begin() + row_to_remove);
  endRemoveRows();
}

QModelIndex DocumentsModel::indexForId(int id) const {
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

  return index(static_cast<int>(i),0);
}

} //namespace Models
} //namespace CleanEditor
