#include "document-handler.h"
#include "file-handler.h"

namespace CleanEditor::Logic {

static int next_id{1};

DocumentHandler::DocumentHandler(QObject *parent)
    : QObject{parent}
    , id_{next_id++}
{
    connect(&file_handler_, &FileHandler::fileUrlChanged, this, &DocumentHandler::fileUrlChanged);
    connect(&file_handler_, &FileHandler::error, this, &DocumentHandler::error);
    connect(&file_handler_, &FileHandler::fileOpened, this, &DocumentHandler::onFileOpened);
}

QString DocumentHandler::filename() const
{
    return file_handler_.fileName();
}

QString DocumentHandler::fileType() const
{
    return file_handler_.fileType();
}

QUrl DocumentHandler::fileUrl() const
{
    return file_handler_.fileUrl();
}

QString DocumentHandler::textContent() const
{
    return text_content_;
}

int DocumentHandler::id() const
{
    return id_;
}

bool DocumentHandler::needsUpdating() const
{
    return needs_updating_;
}

void DocumentHandler::setNeedsUpdating(const bool needs_updating)
{
    if (needs_updating_ == needs_updating) {
        return;
    }

    if (needs_updating) {
        setNeedsSaving(true);
    }

    needs_updating_ = needs_updating;
    emit needsUpdatingChanged();
}

bool DocumentHandler::needsSaving() const
{
    return needs_saving_;
}

bool DocumentHandler::isNewFile() const
{
    return is_new_file_;
}

void DocumentHandler::load(const QUrl &file_url)
{
    file_handler_.load(file_url);
}

void DocumentHandler::saveAs(const QUrl &file_url)
{
    if (!file_handler_.saveAs(file_url, text_content_)) {
        return;
    }
    setIsNewFile(false);
    setNeedsSaving(false);
    setNeedsUpdating(false);
}

void DocumentHandler::save()
{
    if (is_new_file_) {
        return;
    }

    if (!file_handler_.save(text_content_)) {
        return;
    }
    setNeedsSaving(false);
    setNeedsUpdating(false);
}

void DocumentHandler::setTextContent(const QString &text)
{
    if (!needs_updating_) {
        return;
    }
    text_content_ = text;
    setNeedsUpdating(false);
    emit contentUpdated();
}

void DocumentHandler::setIsNewFile(const bool is_new_file)
{
    if (is_new_file_ == is_new_file) {
        return;
    }

    is_new_file_ = is_new_file;
    emit isNewFileChanged();
}

void DocumentHandler::setNeedsSaving(bool needs_saving)
{
    if (needs_saving_ == needs_saving) {
        return;
    }

    needs_saving_ = needs_saving;
    emit needsSavingChanged();
}

void DocumentHandler::onFileOpened()
{
    needs_updating_ = true;
    setTextContent(file_handler_.data());
    needs_updating_ = false;
    setIsNewFile(false);
    emit fileOpened();
}

} //namespace CleanEditor::Logic
