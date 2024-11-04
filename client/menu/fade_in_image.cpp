#include "fade_in_image.h"

FadeInImage::FadeInImage(QWidget *parent, const QString &imagePath, int duration) {
    // Load the logo image with original size or larger
    fadeInLabel = new QLabel(parent);
    fadeInPixmap.load(imagePath);

    // fadeInPixmap = fadeInPixmap; // Keep the original size

    // Make the logo Larger (e.g., 1.2 times its original size)
    fadeInPixmap = fadeInPixmap.scaled(fadeInPixmap.size() * 1.1, Qt::KeepAspectRatio);

    fadeInLabel->setPixmap(fadeInPixmap);

    // Set up opacity effect
    opacityEffect = new QGraphicsOpacityEffect(fadeInLabel);
    fadeInLabel->setGraphicsEffect(opacityEffect);

    // Set up fade-in animation
    fadeInAnimation = new QPropertyAnimation(opacityEffect, "opacity");
    fadeInAnimation->setDuration(duration);
    fadeInAnimation->setStartValue(0.0);
    fadeInAnimation->setEndValue(1.0);

    // Center the image initially
    resize();
}

void FadeInImage::start() {
    fadeInAnimation->start();
}

// Center the image in the parent window
void FadeInImage::resize() {
    int x = (fadeInLabel->parentWidget()->width() - fadeInPixmap.width()) / 2;
    int y = (fadeInLabel->parentWidget()->height() - fadeInPixmap.height()) / 2;
    fadeInLabel->setGeometry(x, y, fadeInPixmap.width(), fadeInPixmap.height());
}
