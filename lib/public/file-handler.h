#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <QObject>
#include <QUrl>

#include "globals.h"

namespace CleanEditor {
namespace Logic {

class QML_EDITOR_EXPORT FileHandler : public QObject {
  Q_OBJECT
  Q_DISABLE_COPY(FileHandler)

  Q_PROPERTY(QString fileName READ fileName NOTIFY fileUrlChanged)
  Q_PROPERTY(QString fileType READ fileType NOTIFY fileUrlChanged)
  Q_PROPERTY(QUrl fileUrl READ fileUrl NOTIFY fileUrlChanged)
  Q_PROPERTY(QString data READ data)

public:
  explicit FileHandler(QObject* parent = nullptr);

  QString fileName() const;
  QString fileType() const;
  QUrl fileUrl() const;
  QString data() const;

public Q_SLOTS:
  void load(const QUrl &fileUrl);
  void saveAs(const QUrl &fileUrl, const QString& data);
  void save(const QString& data);

Q_SIGNALS:
  void fileUrlChanged();

  void fileOpened();
  void error(const QString &message);

private:
  QUrl file_url_;
};

} //namespace Logic
} //namespace CleanEditor

#endif // DOCUMENTHANDLER_H
