#include "document-handler.h"
#include "file-handler.h"

#include <QDebug>

namespace CleanEditor {
namespace Logic {

static int next_id{1};

DocumentHandler::DocumentHandler(QObject *parent) :
  QObject{parent},
  id_{next_id++},
  file_handler_{new FileHandler{this}}
{
  connect(file_handler_, &FileHandler::fileUrlChanged, this, &DocumentHandler::fileUrlChanged);
  connect(file_handler_, &FileHandler::error, this, &DocumentHandler::error);
  connect(file_handler_, &FileHandler::fileOpened, this, &DocumentHandler::onFileOpened);
}

QString DocumentHandler::filename() const {
  return file_handler_->fileName();
}

QString DocumentHandler::fileType() const {
  return file_handler_->fileType();
}

QUrl DocumentHandler::fileUrl() const {
  return file_handler_->fileUrl();
}

QString DocumentHandler::textContent() const {
  return text_content_;
}

bool DocumentHandler::contentUpdated() const {
  return content_updated_;
}

int DocumentHandler::id() const {
  return id_;
}

bool DocumentHandler::needsUpdating() const {
  return needs_updating_;
}

void DocumentHandler::setNeedsUpdating(bool needs_updating) {
  if (needs_updating_ == needs_updating) {
    return;
  }

  needs_updating_ = needs_updating;
  emit needsUpdatingChanged();
}

void DocumentHandler::load(const QUrl& file_url) {
  file_handler_->load(file_url);
}

void DocumentHandler::saveAs(const QUrl& file_url) {
  file_handler_->saveAs(file_url, text_content_);
  setContentUpdated(false);
}

void DocumentHandler::save() {
  file_handler_->save(text_content_);
  setContentUpdated(false);
}

void DocumentHandler::setTextContent(const QString& text) {
  text_content_ = text;
  setContentUpdated(true);
  setNeedsUpdating(false);
}

void DocumentHandler::setContentUpdated(bool content_updated) {
  content_updated_ = content_updated;
  emit contentUpdatedChanged();
}

void DocumentHandler::onFileOpened() {
  setTextContent(file_handler_->data());
  setContentUpdated(false);
  emit fileOpened();
}

} //namespace Logic
} //namespace CleanEditor
