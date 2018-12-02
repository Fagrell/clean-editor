#ifndef DOCUMENTS_MODEL_H
#define DOCUMENTS_MODEL_H

#include <QAbstractListModel>
#include <QUrl>

#include <unordered_map>
#include <memory>
#include <utility>

#include "globals.h"
#include "document-handler.h"

namespace CleanEditor {

namespace Logic {
  class DocumentHandler;
}

namespace Models {

class QML_EDITOR_EXPORT DocumentsModel : public QAbstractListModel {
  Q_OBJECT
  Q_DISABLE_COPY(DocumentsModel)

public:
  enum DocumentsRoles {
    FileIdRole = Qt::UserRole + 1,
    FilenameRole,
    FileTypeRole,
    FileUrlRole,
    FileContentRole,
    FileUpdatedRole,
    FileNeedsUpdatingRole,
  };

  explicit DocumentsModel(QObject* parent = nullptr);

  int rowCount(const QModelIndex& parent = QModelIndex()) const override;
  QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
  QHash<int, QByteArray> roleNames() const override;

  QString filename(int id) const;
  QString fileType(int id) const;
  QUrl fileUrl(int id) const;

  QString fileContent(int id) const;
  void setFileContent(int id, const QString& text);

  void save(int id);
  void saveAs(int id, const QUrl& file_url);

  void setNeedsUpdating(int id);

public Q_SLOTS:
  void newFile();
  void openFile(const QUrl& file_url);
  void closeFile(int id);

Q_SIGNALS:
  void documentCreated(int id);

private:
  std::vector<std::unique_ptr<CleanEditor::Logic::DocumentHandler>> data_;

  QModelIndex indexForId(int id) const;
  void appendNewDocument(std::unique_ptr<CleanEditor::Logic::DocumentHandler> document);

  template <class T>
  T getData(int id, DocumentsRoles role, const T& default_value) const {
    QModelIndex index = indexForId(id);
    if (!index.isValid()) {
      return default_value;
    }

    return data(index, role).value<T>();
  }

  template <class TFunc, class... Values>
  void setData(int id, TFunc function, Values&&... values) {
    for (size_t i{0}; i < data_.size(); i++) {
      if (data_.at(i)->id() == id) {
        std::bind(function, data_.at(i).get(), std::forward<Values>(values)...)();
        auto model_index = index(static_cast<int>(i),0);
        emit dataChanged(model_index, model_index);
        return;
      }
    }
  }

};

} //namespace Models
} //namespace CleanEditor

#endif // DOCUMENTS_MODEL_H
