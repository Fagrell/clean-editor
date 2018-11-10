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
  font_ = font;
}

void LineNumbers::setSelectedBackgroundColor(const QColor& color) {
  selected_background_color_ = color;
}

void LineNumbers::setCurrentBackgroundColor(const QColor& color) {
  current_background_color_ = color;
}

void LineNumbers::setSelectedTextColor(const QColor& color) {
  selected_text_color_ = color;
}

void LineNumbers::setCurrentTextColor(const QColor& color) {
  current_text_color_ = color;
}

void LineNumbers::setTextColor(const QColor& color) {
  text_color_ = color;
}

void LineNumbers::setDocument(QQuickTextDocument* document) {
  document_ = document;
}

void LineNumbers::setLineCount(int line_count) {
  line_count_ = line_count;
}

void LineNumbers::setOffsetY(int offset_y) {
  offset_y_ = offset_y;
}

void LineNumbers::setLineHeight(float line_height) {
  line_height_ = line_height;
}

void LineNumbers::setCursorPosition(int cursor_position) {
  line_cursor_position_ = positionToLine(cursor_position);
}

void LineNumbers::setSelectionStart(int selection_start) {
  line_selection_start_ = positionToLine(selection_start);
}

void LineNumbers::setSelectionEnd(int selection_end) {
  line_selection_end_ = positionToLine(selection_end);
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
  int possible_page_count = std::min(first_visible_line+possible_visible_lines, line_count_);

  return possible_page_count - first_visible_line + 1;
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
