#ifndef FADE_IN_IMAGE_H
#define FADE_IN_IMAGE_H

#include <QWidget>
#include <QLabel>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>

class FadeInImage {
public:
    FadeInImage(QWidget *parent, const QString &imagePath, int duration);
    void start();
    void resize();  // Method to center the image when window is resized

private:
    QLabel *fadeInLabel;
    QGraphicsOpacityEffect *opacityEffect;
    QPropertyAnimation *fadeInAnimation;
    QPixmap fadeInPixmap;
};

#endif // FADE_IN_IMAGE_H
