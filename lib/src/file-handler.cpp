#include <QFile>
#include <QFileInfo>
#include <QTextStream>

#include "file-handler.h"

namespace CleanEditor {
namespace Logic {

FileHandler::FileHandler(QObject* parent) : QObject{parent} {}

QString FileHandler::fileName() const {
  const QString file_path = file_url_.path();
  const QString file_name = QFileInfo(file_path).fileName();
  if (file_name.isEmpty()) {
    return QStringLiteral("untitled");
  }
  return file_name;
}

QString FileHandler::fileType() const {
  return QFileInfo(fileName()).suffix();
}

QUrl FileHandler::fileUrl() const {
  return file_url_;
}

QString FileHandler::data() const {
  QFile file(file_url_.path());
  if (!file.open(QFile::ReadOnly)) {
    return "";
  }

  return file.readAll();
}

void FileHandler::load(const QUrl& file_url) {
  if (file_url == file_url_) {
    return;
  }

  const QString file_name = file_url.path();
  if (!QFile::exists(file_name)) {
    emit error(tr("File not found"));
    return;
  }

  QFile file(file_name);
  if (!file.open(QFile::ReadOnly)) {
    emit error(tr("Failed to open file"));
  }

  file_url_ = file_url;
  emit fileUrlChanged();
  emit fileOpened();
}

bool FileHandler::saveAs(const QUrl& file_url, const QString& data) {
  const QString file_path = file_url.path();

  QFile file(file_path);
  if (!file.open(QFile::WriteOnly | QFile::Truncate | QFile::Text)) {
      emit error(tr("Cannot save: ") + file.errorString());
      return false;
  }

  QTextStream stream{&file};
  stream << data;

  if (file_url == file_url_) {
      return true;
  }

  file_url_ = file_url;
  emit fileUrlChanged();
  return true;
}

bool FileHandler::save(const QString& data) {
  return saveAs(file_url_, data);
}

} //namespace Logic
} //namespace CleanEditor
