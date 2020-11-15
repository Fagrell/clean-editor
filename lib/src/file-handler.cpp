#include <QFile>
#include <QFileInfo>
#include <QTextStream>

#include "file-handler.h"

namespace CleanEditor::Logic {

FileHandler::FileHandler(QObject *parent)
    : QObject{parent}
{}

QString FileHandler::fileName() const
{
    const auto file_path = localPathFromUrl(file_url_);
    const auto file_name = QFileInfo(file_path).fileName();
    if (file_name.isEmpty()) {
        return QStringLiteral("untitled");
    }
    return file_name;
}

QString FileHandler::fileType() const
{
    return QFileInfo(fileName()).suffix();
}

QUrl FileHandler::fileUrl() const
{
    return file_url_;
}

QString FileHandler::data() const
{
    QFile file(localPathFromUrl(file_url_));
    if (!file.open(QFile::ReadOnly)) {
        return "";
    }

    return file.readAll();
}

void FileHandler::load(const QUrl &file_url)
{
    if (file_url == file_url_) {
        return;
    }

    file_url_ = file_url;
    emit fileUrlChanged();
    const auto file_name = localPathFromUrl(file_url_);
    if (!QFile::exists(file_name)) {
        emit error(tr("File not found"));
        return;
    }

    QFile file(file_name);
    if (!file.open(QFile::ReadOnly)) {
        emit error(tr("Failed to open file"));
    }

    emit fileOpened();
}

bool FileHandler::saveAs(const QUrl &file_url, const QString &data)
{
    const auto file_path = localPathFromUrl(file_url);

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

bool FileHandler::save(const QString &data)
{
    return saveAs(file_url_, data);
}

QString FileHandler::localPathFromUrl(const QUrl &file_url)
{
    const auto path = file_url.toLocalFile();
    if (!path.isEmpty()) {
        return path;
    }

    return file_url.path();
}

} //namespace CleanEditor::Logic
