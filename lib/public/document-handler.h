#ifndef DOCUMENT_HANDLER_H
#define DOCUMENT_HANDLER_H

#include <QObject>
#include <QUrl>
#include <QPointer>

#include "globals.h"

class QTextDocument;
class QQuickTextDocument;

namespace CleanEditor {
namespace Logic {

class FileHandler;

class QML_EDITOR_EXPORT DocumentHandler : public QObject {
  Q_OBJECT
  Q_DISABLE_COPY(DocumentHandler)

  Q_PROPERTY(QString filename READ filename)
  Q_PROPERTY(QString fileType READ fileType)
  Q_PROPERTY(QUrl fileUrl READ fileUrl NOTIFY fileUrlChanged)
  Q_PROPERTY(QString textContent READ textContent WRITE setTextContent)
  Q_PROPERTY(bool contentUpdated READ contentUpdated NOTIFY contentUpdatedChanged)
  Q_PROPERTY(int id READ id)
  Q_PROPERTY(bool needsUpdating READ needsUpdating WRITE setNeedsUpdating NOTIFY needsUpdatingChanged)

public:
  explicit DocumentHandler(QObject *parent = nullptr);

  QString filename() const;
  QString fileType() const;
  QUrl fileUrl() const;
  QString textContent() const;
  bool contentUpdated() const;
  int id() const;

  bool needsUpdating() const;
  void setNeedsUpdating(bool needs_updating);

public Q_SLOTS:
  void load(const QUrl& file_url);
  void saveAs(const QUrl& file_url);
  void save();
  void setTextContent(const QString& text);

Q_SIGNALS:
  void fileUrlChanged();
  void fileOpened();
  void error(const QString &message);
  void contentUpdatedChanged();
  void needsUpdatingChanged();

private:
  void setContentUpdated(bool content_updated);

  int id_{0};
  QPointer<FileHandler> file_handler_;
  QString text_content_;
  bool content_updated_{false};
  bool needs_updating_{false};

private Q_SLOTS:
  void onFileOpened();

};

} //namespace Logic
} //namespace CleanEditor

Q_DECLARE_METATYPE(CleanEditor::Logic::DocumentHandler*)

#endif // DOCUMENT_HANDLER_H
