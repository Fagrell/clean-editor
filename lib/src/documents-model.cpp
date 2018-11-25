#include "documents-model.h"
#include "document-handler.h"

namespace CleanEditor {
namespace Model {

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

  if (role != DocumentRole) {
      return {};
  }
  QVariant data;
  data.setValue(data_.at(static_cast<int>(index.row())).get());
  return data;
}

QHash<int, QByteArray> DocumentsModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[DocumentRole] = "document";
    return roles;
}

void DocumentsModel::openFile(const QUrl& file_url) {
  auto document_handler = std::make_unique<CleanEditor::Logic::DocumentHandler>();
  document_handler->load(file_url);

  int index = static_cast<int>(data_.size());
  beginInsertRows({}, index, index);
  data_.emplace_back(std::move(document_handler));
  endInsertRows();

  emit documentCreated(document_handler.get());
}

void DocumentsModel::closeFile(int id) {
  size_t i{0};
  for (; i < data_.size(); i++) {
    if (data_.at(i)->id() == id) {
      break;
    }
  }

  //Not found
  if (i == data_.size()) {
    return;
  }

  int row_to_remove = static_cast<int>(i);
  beginRemoveRows({}, row_to_remove, row_to_remove);
  data_.erase(data_.begin() + row_to_remove);
  endRemoveRows();
}

} //namespace Model
} //namespace CleanEditor
