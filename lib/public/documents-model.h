#ifndef DOCUMENTS_MODEL_H
#define DOCUMENTS_MODEL_H

#include <QAbstractListModel>
#include <QUrl>

#include <unordered_map>
#include <memory>

namespace CleanEditor {

namespace Logic {
  class DocumentHandler;
}

namespace Model {

class DocumentsModel : public QAbstractListModel {
  Q_OBJECT
  Q_DISABLE_COPY(DocumentsModel)

public:
  enum DocumentsRoles {
    DocumentRole = Qt::UserRole + 1,
  };

  explicit DocumentsModel(QObject* parent = nullptr);

  int rowCount(const QModelIndex& parent = QModelIndex()) const override;
  QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
  QHash<int, QByteArray> roleNames() const override;

public Q_SLOTS:
  void openFile(const QUrl& file_url);
  void closeFile(int id);

Q_SIGNALS:
  void documentCreated(CleanEditor::Logic::DocumentHandler* document);

private:
  std::vector<std::unique_ptr<CleanEditor::Logic::DocumentHandler>> data_;

};

} //namespace Model
} //namespace CleanEditor

#endif // DOCUMENTS_MODEL_H
