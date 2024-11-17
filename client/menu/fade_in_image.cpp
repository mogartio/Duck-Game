#include "fade_in_image.h"

FadeInImage::FadeInImage(QWidget *parent, const QString &imagePath, int duration)
    : fadeInLabel(std::make_unique<QLabel>(parent)),
      opacityEffect(std::make_unique<QGraphicsOpacityEffect>(fadeInLabel.get())),
      fadeInAnimation(std::make_unique<QPropertyAnimation>(opacityEffect.get(), "opacity")) {
    // Load the logo image with original size or larger
    fadeInPixmap.load(imagePath);
    fadeInPixmap = fadeInPixmap.scaled(fadeInPixmap.size() * 1.1, Qt::KeepAspectRatio);
    fadeInLabel->setPixmap(fadeInPixmap);
    // Set up opacity effect
    fadeInLabel->setGraphicsEffect(opacityEffect.get());
    // Set up fade-in animation
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