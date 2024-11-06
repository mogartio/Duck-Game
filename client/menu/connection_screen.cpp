#include "connection_screen.h"
#include <QPainter>
#include <QResizeEvent>
#include <qboxlayout.h>

ConnectionScreen::ConnectionScreen(Queue<std::unique_ptr<GenericMsg>>& send_queue, Queue<std::unique_ptr<GenericMsg>>& recv_queue) : send_queue(send_queue), recv_queue(recv_queue) {
    setWindowState(Qt::WindowFullScreen); // Set window to full-screen mode

    // Set focus policy to receive key events
    setFocusPolicy(Qt::StrongFocus);

    // Create ParallaxBackground layers
    QVBoxLayout *layout = new QVBoxLayout(this);
    layer0 = new ParallaxBackground(this, "client/img_src/front_window_background/parallax_background_layer_1.png", 0.5f);
    layer1 = new ParallaxBackground(this, "client/img_src/front_window_background/parallax_background_layer_2.png", 0.75f);
    layer2 = new ParallaxBackground(this, "client/img_src/front_window_background/parallax_background_layer_3.png", 1.0f);
    layer3 = new ParallaxBackground(this, "client/img_src/front_window_background/parallax_background_layer_4.png", 1.25f);
    layer0->start();
    layer1->start();
    layer2->start();
    layer3->start();
    setLayout(layout);
}

void ConnectionScreen::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    // Trigger a repaint to adjust the background and rectangle
    layer0->resizeImages();
    layer1->resizeImages();
    layer2->resizeImages();
    layer3->resizeImages();
    update();
}

void ConnectionScreen::paintEvent(QPaintEvent *event) {
    QWidget::paintEvent(event); // Call the base class implementation

    QPainter painter(this);

    // Now draw the rounded rectangle on top of the layers
    QColor rectColor(0, 0, 0, 127); // Semi-opaque black
    painter.setBrush(rectColor);
    painter.setPen(Qt::NoPen);

    int rectWidth = width() * 0.8;
    int rectHeight = height() * 0.6;
    int rectX = (width() - rectWidth) / 2;
    int rectY = (height() - rectHeight) / 2;

    // Draw the rounded rectangle on top
    painter.drawRoundedRect(rectX, rectY, rectWidth, rectHeight, 20, 20);
}