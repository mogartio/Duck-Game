#ifndef ROUNDEDRECTANGLE_H
#define ROUNDEDRECTANGLE_H

#include <QWidget>
#include <QPainter>
#include <QColor>

class RoundedRectangle : public QWidget {
    Q_OBJECT

private:
    int rectX;
    int rectY;
    int rectWidth;
    int rectHeight;
    QColor rectColor;
    QColor originalColor;
    QColor hoverColor;
    int cornerRadius;

public:
    explicit RoundedRectangle(QWidget *parent, int x, int y, int width, int height, const QColor &color, const QColor &hoverColor, int radius = 20)
        : QWidget(parent), rectX(x), rectY(y), rectWidth(width), rectHeight(height), rectColor(color), originalColor(color), hoverColor(hoverColor), cornerRadius(radius) {
        setAttribute(Qt::WA_Hover, true); // Enable hover events
        setGeometry(rectX, rectY, rectWidth, rectHeight); // Set the position and size of the widget
    }

protected:
    void paintEvent(QPaintEvent *event) override {
        QWidget::paintEvent(event);

        QPainter painter(this);
        painter.setBrush(rectColor);
        painter.setPen(Qt::NoPen);

        painter.drawRoundedRect(0, 0, rectWidth, rectHeight, cornerRadius, cornerRadius);
    }

    void enterEvent(QEvent *event) override {
        QWidget::enterEvent(event);
        rectColor = hoverColor;
        update(); // Trigger a repaint
    }

    void leaveEvent(QEvent *event) override {
        QWidget::leaveEvent(event);
        rectColor = originalColor;
        update(); // Trigger a repaint
    }

    void hideRectangle() {
        rectColor = QColor(0, 0, 0, 0);
        update();
    }

    void showRectangle() {
        rectColor = originalColor;
        update();
    }
};

#endif // ROUNDEDRECTANGLE_H