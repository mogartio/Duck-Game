#include "logo_screen.h"
#include <QKeyEvent>
#include <iostream>
#include <chrono>
#include <thread>
LogoScreen::LogoScreen(Queue<std::unique_ptr<GenericMsg>>& send_queue, Queue<std::unique_ptr<GenericMsg>>& recv_queue) : send_queue(send_queue), recv_queue(recv_queue) {
    //setWindowState(Qt::WindowFullScreen); // Set window to full-screen mode

    // Set focus policy to receive key events
    setFocusPolicy(Qt::StrongFocus);
    
    // Create ParallaxBackground layers
    QVBoxLayout *layout = new QVBoxLayout(this);
    layer0 = new ParallaxBackground(this, "client/img_src/front_window_background/parallax_background_layer_1.png", 0.5f);
    layer1 = new ParallaxBackground(this, "client/img_src/front_window_background/parallax_background_layer_2.png", 0.60f);
    layer2 = new ParallaxBackground(this, "client/img_src/front_window_background/parallax_background_layer_3.png", 0.75f);
    layer3 = new ParallaxBackground(this, "client/img_src/front_window_background/parallax_background_layer_4.png", 1.00f);

    layer0->start();
    layer1->start();
    layer2->start();
    layer3->start();
    setLayout(layout);

    // Create FadeInImage
    fadeInImage = new FadeInImage(this, "client/img_src/duck_game_logo.png", 2000);
    fadeInImage->start();

    // Load custom font
    int fontId = QFontDatabase::addApplicationFont("client/text_font_src/PixelBook-Regular.ttf");
    QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
    QFont customFont(fontFamily);

    // Create flickering text
    flickeringText = new QLabel("press any key", this);
    flickeringText->setAlignment(Qt::AlignCenter);
    flickeringText->setStyleSheet("QLabel { color: #ced4da; font-size: 42px; }");
    QFont font("Arial", 42, QFont::Bold);
    flickeringText->setFont(customFont);
    flickeringText->setVisible(false);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &LogoScreen::toggleTextVisibility);
    timer->start(700);
}

void LogoScreen::resizeEvent(QResizeEvent *event) {
    // Call resizeImages on each layer when the window size changes
    layer0->resizeImages();
    layer1->resizeImages();
    layer2->resizeImages();
    layer3->resizeImages();

    // Center the fade-in logo image
    fadeInImage->resize();

    // Center the flickering text
    flickeringText->setGeometry(0, height() / 2 + height() / 3, width(), 50);
}

void LogoScreen::toggleTextVisibility() {
    flickeringText->setVisible(!flickeringText->isVisible());
}

void LogoScreen::keyPressEvent(QKeyEvent *event) {
    // If any key is pressed, emit the signal to switch to the connection screen
    emit switchToConnectionScreen();
}