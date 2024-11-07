#ifndef LOGO_SCREEN_H
#define LOGO_SCREEN_H

#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QTimer>
#include <QVBoxLayout>
#include <QFontDatabase>
#include "parallax_background.h"
#include "fade_in_image.h"
#include "../../common/queue.h"
#include "../../common/messages/generic_msg.h"
#include <QSound>
class LogoScreen : public QWidget {
    Q_OBJECT

public:
    LogoScreen(Queue<std::unique_ptr<GenericMsg>>& send_queue, Queue<std::unique_ptr<GenericMsg>>& recv_queue);

signals:
    void switchToConnectionScreen();

protected:
    void resizeEvent(QResizeEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void toggleTextVisibility();

private:
    ParallaxBackground *layer0;
    ParallaxBackground *layer1;
    ParallaxBackground *layer2;
    ParallaxBackground *layer3;
    FadeInImage *fadeInImage;
    QLabel *flickeringText;
    QTimer *timer;
    QSound *keyPressSound;
    Queue<std::unique_ptr<GenericMsg>>& send_queue;
    Queue<std::unique_ptr<GenericMsg>>& recv_queue;
    bool initialized = false;
};

#endif // LOGO_SCREEN_H