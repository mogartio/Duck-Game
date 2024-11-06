#include "connection_screen.h"
#include "rounded_rectangle.h"
#include <QPainter>
#include <QResizeEvent>
#include <qboxlayout.h>

ConnectionScreen::ConnectionScreen(Queue<std::unique_ptr<GenericMsg>>& send_queue, Queue<std::unique_ptr<GenericMsg>>& recv_queue) : send_queue(send_queue), recv_queue(recv_queue) {
    setWindowState(Qt::WindowFullScreen); // Set window to full-screen mode

    // Set focus policy to receive key events
    setFocusPolicy(Qt::StrongFocus);

    // Create ParallaxBackground layers
    layer0 = new ParallaxBackground(this, "client/img_src/front_window_background/parallax_background_layer_1.png", 0.5f);
    layer1 = new ParallaxBackground(this, "client/img_src/front_window_background/parallax_background_layer_2.png", 0.75f);
    layer2 = new ParallaxBackground(this, "client/img_src/front_window_background/parallax_background_layer_3.png", 1.0f);
    layer3 = new ParallaxBackground(this, "client/img_src/front_window_background/parallax_background_layer_4.png", 1.25f);

    layer0->start();
    layer1->start();
    layer2->start();
    layer3->start();

    // Center of the screen: (1920 / 2, 1080 / 2) = (960, 540)
    // Top-left corner of the rectangle: (960 - 500 / 2, 540 - 400 / 2) = (710, 340)
    int offset = 100;
    // Add the rounded rectangles to the parent widget
    RoundedRectangle * baseRectangle = new RoundedRectangle(this, 710-offset, 340, 500+offset, 400, QColor(213, 226, 224, 100), QColor(213, 226, 224, 100));
    RoundedRectangle * hostnameInputRectangle = new RoundedRectangle(this, 760-offset, 400, 400+offset, 50, QColor(206, 212, 218, 100), QColor(189, 194, 199, 100));
    RoundedRectangle * portInputRectangle = new RoundedRectangle(this, 760-offset, 500, 400+offset, 50, QColor(206, 212, 218, 100), QColor(189, 194, 199, 100));
    // Add the rectangles to the parent widget
    hostnameInputRectangle->setParent(this);
    baseRectangle->setParent(this);
    portInputRectangle->setParent(this);
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
