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
    std::unique_ptr<QLabel> fadeInLabel;
    std::unique_ptr<QGraphicsOpacityEffect> opacityEffect;
    std::unique_ptr<QPropertyAnimation> fadeInAnimation;
    QPixmap fadeInPixmap;
};

#endif // FADE_IN_IMAGE_H
