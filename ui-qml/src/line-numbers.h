#pragma once

#include <QFont>
#include <QPointer>
#include <QQuickPaintedItem>
#include <QQuickTextDocument>
#include <QStringView>
#include <QTextCursor>

namespace CleanEditor::UI {

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
class LineNumbers : public QQuickPaintedItem
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(LineNumbers)

    Q_PROPERTY(QFont font MEMBER font_ WRITE setFont)
    Q_PROPERTY(QColor selectedBackgroundColor MEMBER selected_background_color_ WRITE
                   setSelectedBackgroundColor)
    Q_PROPERTY(QColor currentBackgroundColor MEMBER current_background_color_ WRITE
                   setCurrentBackgroundColor)
    Q_PROPERTY(QColor selectedTextColor MEMBER selected_text_color_ WRITE setSelectedTextColor)
    Q_PROPERTY(QColor currentTextColor MEMBER current_text_color_ WRITE setCurrentTextColor)
    Q_PROPERTY(QColor textColor MEMBER text_color_ WRITE setTextColor)

    Q_PROPERTY(QQuickTextDocument *document READ document WRITE setDocument)
    Q_PROPERTY(int offsetY MEMBER offset_y_ WRITE setOffsetY)
    Q_PROPERTY(int cursorPosition MEMBER cursor_position_ WRITE setCursorPosition)
    Q_PROPERTY(int selectionStart MEMBER selection_start_ WRITE setSelectionStart)
    Q_PROPERTY(int selectionEnd MEMBER selection_end_ WRITE setSelectionEnd)

public:
    explicit LineNumbers(QQuickPaintedItem *parent = nullptr);

    QQuickTextDocument *document() const;

public Q_SLOTS:
    //! Set the font (and internally also sets the line height)
    void setFont(const QFont &font);
    void setSelectedBackgroundColor(const QColor &color);
    void setCurrentBackgroundColor(const QColor &color);
    void setSelectedTextColor(const QColor &color);
    void setCurrentTextColor(const QColor &color);
    void setTextColor(const QColor &color);

    void setDocument(QQuickTextDocument *document);
    void setOffsetY(int offset_y);
    void setCursorPosition(int cursor_position);
    void setSelectionStart(int selection_start);
    void setSelectionEnd(int selection_end);

protected:
    void paint(QPainter *painter) override;

private:
    int line_count_{0};
    int offset_y_{0};
    qreal line_height_{0};

    int cursor_position_{-1};
    int selection_start_{-1};
    int selection_end_{-1};

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

    void drawLineBackground(QPainter &painter, qreal y_position, const QColor &background_color);
    void drawLineNumber(QPainter &painter,
                        qreal y_position,
                        const QColor &text_color,
                        int line_number);

    static int countLines(QStringView text);
};

} // namespace CleanEditor::UI
