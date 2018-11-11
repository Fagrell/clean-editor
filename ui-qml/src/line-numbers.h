#ifndef LINE_NUMBERS_H
#define LINE_NUMBERS_H

#include <QQuickPaintedItem>
#include <QTextCursor>
#include <QPointer>
#include <QFont>

class QQuickTextDocument;

namespace CleanEditor {
namespace UI {

/*!
 * \brief The LineNumbers class paints line numbers (vertically) in an item.
 *        It's possible to define the text color and the background for the currently selected line, see currentTextColor
 *        and currentBackgroundColor.
 *
 *        It's also possible to define the text color and the background for lines that have been selected across multiple rows,
 *        see selectedTextColor and selectedBackgroundColor.
 *
 *        textColor is the color used by the lines that are not selected.
 *
 *        Internally uses the QTextDocument to identify selected lines.
 *
 *        offsetY is used to know if we've scrolled in the document. Top of the page means offsetY == 0.
 *
 */
class LineNumbers : public QQuickPaintedItem {
  Q_OBJECT
  Q_DISABLE_COPY(LineNumbers)

  Q_PROPERTY(QFont font WRITE setFont)
  Q_PROPERTY(QColor selectedBackgroundColor WRITE setSelectedBackgroundColor)
  Q_PROPERTY(QColor currentBackgroundColor WRITE setCurrentBackgroundColor)
  Q_PROPERTY(QColor selectedTextColor WRITE setSelectedTextColor)
  Q_PROPERTY(QColor currentTextColor WRITE setCurrentTextColor)
  Q_PROPERTY(QColor textColor WRITE setTextColor)

  Q_PROPERTY(QQuickTextDocument* document WRITE setDocument)
  Q_PROPERTY(int offsetY WRITE setOffsetY)
  Q_PROPERTY(float lineHeight WRITE setLineHeight)
  Q_PROPERTY(int cursorPosition WRITE setCursorPosition)
  Q_PROPERTY(int selectionStart WRITE setSelectionStart)
  Q_PROPERTY(int selectionEnd WRITE setSelectionEnd)

public:
  explicit LineNumbers(QQuickPaintedItem* parent = nullptr);

public Q_SLOTS:
  void setFont(const QFont& font);
  void setSelectedBackgroundColor(const QColor& color);
  void setCurrentBackgroundColor(const QColor& color);
  void setSelectedTextColor(const QColor& color);
  void setCurrentTextColor(const QColor& color);
  void setTextColor(const QColor& color);

  void setDocument(QQuickTextDocument* document);
  void setOffsetY(int offset_y);
  void setLineHeight(float line_height);
  void setCursorPosition(int cursor_position);
  void setSelectionStart(int selection_start);
  void setSelectionEnd(int selection_end);

protected:
  void paint(QPainter *painter) override;

private:
  int line_count_{0};
  int offset_y_{0};
  float line_height_{0.f};
  int line_cursor_position_{0};
  int line_selection_start_{0};
  int line_selection_end_{0};

  QPointer<QQuickTextDocument> document_;
  QFont font_{"Monospace", 12};
  QColor selected_background_color_{Qt::lightGray};
  QColor current_background_color_{Qt::darkGray};
  QColor selected_text_color_{Qt::darkGray};
  QColor current_text_color_{Qt::white};
  QColor text_color_{Qt::darkGray};

  int positionToLine(int position) const;
  int firstVisibleLine() const;
  int numberOfVisibleLines() const;
  int lineCount() const;
  bool isLineSelected(int line) const;
  bool isCurrentLine(int line) const;

  void drawLineBackground(QPainter* painter, float y_position, QColor background_color);
  void drawLineNumber(QPainter* painter, float y_position, QColor text_color, int line_number);
};

} //namspace UI
} //namespace CleanEditor

#endif // LINE_NUMBERS_H
