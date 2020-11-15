#include "line-numbers.h"

#include <QFontMetrics>
#include <QPainter>
#include <QRegularExpression>
#include <QTextBlock>

#include <algorithm>
#include <cmath>

namespace CleanEditor::UI {

static constexpr int kLineNumberXOffset{5};

LineNumbers::LineNumbers(QQuickPaintedItem *parent)
    : QQuickPaintedItem(parent)
{
    font_.setStyleHint(QFont::TypeWriter);
}

QQuickTextDocument *LineNumbers::document() const
{
    return document_.data();
}

void LineNumbers::setFont(const QFont &font)
{
    if (font_ == font) {
        return;
    }

    font_ = font;
    line_height_ = QFontMetrics{font}.height();
    update();
}

void LineNumbers::setSelectedBackgroundColor(const QColor &color)
{
    if (selected_background_color_ == color) {
        return;
    }

    selected_background_color_ = color;
    update();
}

void LineNumbers::setCurrentBackgroundColor(const QColor &color)
{
    if (current_background_color_ == color) {
        return;
    }

    current_background_color_ = color;
    update();
}

void LineNumbers::setSelectedTextColor(const QColor &color)
{
    if (selected_text_color_ == color) {
        return;
    }

    selected_text_color_ = color;
    update();
}

void LineNumbers::setCurrentTextColor(const QColor &color)
{
    if (current_text_color_ == color) {
        return;
    }

    current_text_color_ = color;
    update();
}

void LineNumbers::setTextColor(const QColor &color)
{
    if (text_color_ == color) {
        return;
    }

    text_color_ = color;
    update();
}

void LineNumbers::setDocument(QQuickTextDocument *document)
{
    if (document_ == document) {
        return;
    }

    document_ = document;
    if (!document_) {
        return;
    }

    auto text_document = document_->textDocument();
    connect(text_document, &QTextDocument::contentsChanged, this, [this]() { update(); });
    update();
}

void LineNumbers::setOffsetY(const int offset_y)
{
    if (offset_y_ == offset_y) {
        return;
    }

    offset_y_ = offset_y;
    update();
}

void LineNumbers::setCursorPosition(const int cursor_position)
{
    if (cursor_position_ == cursor_position) {
        return;
    }

    cursor_position_ = cursor_position;
    line_cursor_position_ = positionToLine(cursor_position);
    update();
}

void LineNumbers::setSelectionStart(const int selection_start)
{
    if (selection_start_ == selection_start) {
        return;
    }

    selection_start_ = selection_start;
    line_selection_start_ = positionToLine(selection_start);
    update();
}

void LineNumbers::setSelectionEnd(const int selection_end)
{
    if (selection_end_ == selection_end) {
        return;
    }

    selection_end_ = selection_end;
    line_selection_end_ = positionToLine(selection_end);
    update();
}

int LineNumbers::positionToLine(const int position) const
{
    if (!document_) {
        return -1;
    }

    auto text_document = document_->textDocument();
    return countLines(text_document->toPlainText().first(position));
}

void LineNumbers::paint(QPainter *painter)
{
    int first_visible_line = firstVisibleLine();
    int additional_offset = offset_y_ % static_cast<int>(line_height_);
    QColor text_color;
    int visible_lines = numberOfVisibleLines();

    for (int i{0}; i < visible_lines; i++) {
        int line_number = i + first_visible_line;
        qreal line_y_position = i * line_height_ - additional_offset;

        if (isCurrentLine(line_number)) {
            drawLineBackground(*painter, line_y_position, current_background_color_);
            text_color = current_text_color_;
        } else if (isLineSelected(line_number)) {
            drawLineBackground(*painter, line_y_position, selected_background_color_);
            text_color = selected_text_color_;
        } else {
            text_color = text_color_;
        }

        drawLineNumber(*painter, line_y_position, text_color, line_number);
    }
}

int LineNumbers::firstVisibleLine() const
{
    return offset_y_ / static_cast<int>(line_height_) + 1;
}

int LineNumbers::numberOfVisibleLines() const
{
    auto first_visible_line = firstVisibleLine();
    auto possible_visible_lines = static_cast<int>(height() / line_height_);

    // Check if we've reached the bottom of the page
    int possible_page_count = std::min(first_visible_line + possible_visible_lines, lineCount());

    return possible_page_count - first_visible_line + 1;
}

int LineNumbers::lineCount() const
{
    if (!document_) {
        return 0;
    }

    auto text_document = document_->textDocument();
    return countLines(text_document->toPlainText());
}

bool LineNumbers::isLineSelected(const int line) const
{
    return (line >= line_selection_start_) && (line <= line_selection_end_);
}

bool LineNumbers::isCurrentLine(const int line) const
{
    return line == line_cursor_position_;
}

void LineNumbers::drawLineBackground(QPainter &painter,
                                     const qreal y_position,
                                     const QColor &background_color)
{
    QRectF background_rectangle(0, y_position, width(), line_height_);
    painter.setPen(QPen{background_color});
    painter.drawRect(background_rectangle);
    painter.fillRect(background_rectangle, background_color);
}

void LineNumbers::drawLineNumber(QPainter &painter,
                                 const qreal y_position,
                                 const QColor &text_color,
                                 const int line_number)
{
    painter.setFont(font_);
    painter.setPen(QPen{text_color});
    QRectF text_bounding_rectangle{0, y_position, width() - kLineNumberXOffset, line_height_};
    painter.drawText(text_bounding_rectangle, Qt::AlignRight, QString::number(line_number));
}

int LineNumbers::countLines(QStringView text)
{
    int lines = 1;
    lines += std::count_if(std::begin(text), std::end(text), [](const auto &symbol) {
        return (symbol == '\n' || symbol == '\r');
    });
    return lines;
}

} // namespace CleanEditor::UI
