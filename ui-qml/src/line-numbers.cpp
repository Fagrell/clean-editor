#include "line-numbers.h"

#include <QPainter>
#include <QQuickTextDocument>
#include <QTextBlock>

#include <algorithm>
#include <cmath>

namespace CleanEditor {
namespace UI {

static constexpr const int kLineNumberXOffset{5};

LineNumbers::LineNumbers(QQuickPaintedItem* parent) :
  QQuickPaintedItem(parent)
{
  font_.setStyleHint(QFont::TypeWriter);
}

void LineNumbers::setFont(const QFont& font) {
  if (font_ == font) {
    return;
  }

  font_ = font;
  update();
}

void LineNumbers::setSelectedBackgroundColor(const QColor& color) {
  if (selected_background_color_ == color) {
    return;
  }

  selected_background_color_ = color;
  update();
}

void LineNumbers::setCurrentBackgroundColor(const QColor& color) {
  if (current_background_color_ == color) {
    return;
  }

  current_background_color_ = color;
  update();
}

void LineNumbers::setSelectedTextColor(const QColor& color) {
  if (selected_text_color_ == color) {
    return;
  }

  selected_text_color_ = color;
  update();
}

void LineNumbers::setCurrentTextColor(const QColor& color) {
  if (current_text_color_ == color) {
    return;
  }

  current_text_color_ = color;
  update();
}

void LineNumbers::setTextColor(const QColor& color) {
  if (text_color_ == color) {
    return;
  }

  text_color_ = color;
  update();
}

void LineNumbers::setDocument(QQuickTextDocument* document) {
  if (document_ == document) {
    return;
  }

  document_ = document;
  update();
}

void LineNumbers::setOffsetY(int offset_y) {
  if (offset_y_ == offset_y) {
    return;
  }

  offset_y_ = offset_y;
  update();
}

void LineNumbers::setLineHeight(float line_height) {
  if (line_height_ == line_height) {
    return;
  }

  line_height_ = line_height;
  update();
}

void LineNumbers::setCursorPosition(int cursor_position) {
  auto line_cursor_position = positionToLine(cursor_position);
  if (line_cursor_position_ == line_cursor_position) {
    return;
  }

  line_cursor_position_ = line_cursor_position;
  update();
}

void LineNumbers::setSelectionStart(int selection_start) {
  auto line_selection_start = positionToLine(selection_start);
  if (line_selection_start_ == line_selection_start) {
    return;
  }

  line_selection_start_ = line_selection_start;
  update();
}

void LineNumbers::setSelectionEnd(int selection_end) {
  auto line_selection_end = positionToLine(selection_end);
  if (line_selection_end_ == line_selection_end) {
    return;
  }

  line_selection_end_ = line_selection_end;
  update();
}

int LineNumbers::positionToLine(int position) const {
  if (!document_) {
    return -1;
  }

  auto text_document = document_->textDocument();
  QTextBlock block = text_document->findBlock(position);
  return block.firstLineNumber() + 1;
}

void LineNumbers::paint(QPainter* painter) {
  int first_visible_line = firstVisibleLine();
  int additional_offset = offset_y_ % static_cast<int>(line_height_);
  QColor text_color;
  int visible_lines = numberOfVisibleLines();

  for (int i{0}; i < visible_lines; i++) {
    int line_number = i + first_visible_line;
    float line_y_position = i*line_height_ - additional_offset;

    if (isCurrentLine(line_number)) {
      drawLineBackground(painter, line_y_position, current_background_color_);
      text_color = current_text_color_;
    } else if (isLineSelected(line_number)) {
      drawLineBackground(painter, line_y_position, selected_background_color_);
      text_color = selected_text_color_;
    } else {
      text_color = text_color_;
    }

    drawLineNumber(painter, line_y_position, text_color, line_number);

  }
}

int LineNumbers::firstVisibleLine() const {
  return offset_y_ / line_height_ + 1;
}

int LineNumbers::numberOfVisibleLines() const {
  auto first_visible_line = firstVisibleLine();
  auto possible_visible_lines = static_cast<int>(height() / line_height_);

  // Check if we've reached the bottom of the page
  int possible_page_count = std::min(first_visible_line+possible_visible_lines, lineCount());

  return possible_page_count - first_visible_line + 1;
}

int LineNumbers::lineCount() const {
  if (!document_) {
    return 0;
  }

  auto text_document = document_->textDocument();
  return text_document->lineCount();
}

bool LineNumbers::isLineSelected(int line) const {
  return (line >= line_selection_start_) && (line <= line_selection_end_);
}

bool LineNumbers::isCurrentLine(int line) const {
  return line == line_cursor_position_;
}

void LineNumbers::drawLineBackground(QPainter* painter, float y_position, QColor background_color) {
  QRectF background_rectangle(0, y_position, width(), line_height_);
  painter->setPen(background_color);
  painter->drawRect(background_rectangle);
  painter->fillRect(background_rectangle, background_color);
}

void LineNumbers::drawLineNumber(QPainter* painter, float y_position, QColor text_color, int line_number) {
  painter->setFont(font_);
  painter->setPen(text_color);
  painter->drawText(0, y_position, width() - kLineNumberXOffset, line_height_, Qt::AlignRight, QString::number(line_number));
}

} //namspace UI
} //namespace CleanEditor
