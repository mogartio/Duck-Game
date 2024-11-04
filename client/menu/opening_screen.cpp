#include "opening_screen.h"

OpeningScreen::OpeningScreen() {
    setWindowState(Qt::WindowFullScreen); // Set window to full-screen mode

    // Create ParallaxBackground layers
    layer0 = new ParallaxBackground(this, "client/img_src/front_window_background/parallax_background_layer_1.png", 0.5f);
    layer1 = new ParallaxBackground(this, "client/img_src/front_window_background/parallax_background_layer_2.png", 0.75f);
    layer2 = new ParallaxBackground(this, "client/img_src/front_window_background/parallax_background_layer_3.png", 1.0f);
    layer3 = new ParallaxBackground(this, "client/img_src/front_window_background/parallax_background_layer_4.png", 1.25f);

    layer0->start();
    layer1->start();
    layer2->start();
    layer3->start();

    // Create FadeInImage
    fadeInImage = new FadeInImage(this, "client/img_src/duck_game_logo.png", 2000);
    fadeInImage->start();
}

void OpeningScreen::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    
    // Call resizeImages on each layer when the window size changes
    layer0->resizeImages();
    layer1->resizeImages();
    layer2->resizeImages();
    layer3->resizeImages();
    // Center the fade-in logo image
    fadeInImage->resize();
}