#include "parallax_background.h"

ParallaxBackground::ParallaxBackground(QWidget *parent, const QString &imagePath, float speed)
    : QObject(parent), speed(speed), offset(0), parent(parent) {
    label = new QLabel(parent);
    label_dup = new QLabel(parent);
    pixmap.load(imagePath);
    pixmap = pixmap.scaled(parent->size(), Qt::KeepAspectRatioByExpanding);
    label->setPixmap(pixmap);
    label->setGeometry(0, 0, parent->width(), parent->height());
    label_dup->setPixmap(pixmap);
    label_dup->setGeometry(parent->width(), 0, parent->width(), parent->height());

    connect(&timer, &QTimer::timeout, this, &ParallaxBackground::updatePosition);
}

void ParallaxBackground::start() {
    timer.start(30); // Update every 30 ms
}

void ParallaxBackground::updatePosition() {
    offset = static_cast<int>((offset + speed)) % parent->width();
    label->move(-offset, 0);
    label_dup->move(parent->width() - offset, 0);
}

void ParallaxBackground::resizeImages() {
    pixmap = pixmap.scaled(parent->size(), Qt::KeepAspectRatioByExpanding);
    label->setPixmap(pixmap);
    label->setGeometry(0, 0, parent->width(), parent->height());
    label_dup->setPixmap(pixmap);
    label_dup->setGeometry(parent->width(), 0, parent->width(), parent->height());
}
