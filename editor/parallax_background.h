#ifndef PARALLAX_BACKGROUND_H
#define PARALLAX_BACKGROUND_H

#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QDebug>   

class ParallaxBackground : public QObject {
    Q_OBJECT

public:
    ParallaxBackground(QWidget *parent, const QString &imagePath, float speed);
    void start();
    void resizeImages();

private slots:
    void updatePosition();

private:
    float speed;
    int offset;
    QWidget *parent;
    QLabel *label;
    QLabel *label_dup;
    QPixmap pixmap;
    QTimer timer;
};

#endif // PARALLAX_BACKGROUND_H