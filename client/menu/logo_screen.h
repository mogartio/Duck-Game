#ifndef LOGO_SCREEN_H
#define LOGO_SCREEN_H

#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QTimer>
#include <QVBoxLayout>
#include <QFontDatabase>
#include <memory>
#include "parallax_background.h"
#include "fade_in_image.h"
#include "../../common/queue.h"
#include "../../common/messages/generic_msg.h"
#include <QSound>

class LogoScreen : public QWidget {
    Q_OBJECT

public:
    LogoScreen(Queue<std::shared_ptr<GenericMsg>>* send_queue, Queue<std::shared_ptr<GenericMsg>>* recv_queue);
    ~LogoScreen() = default;
signals:
    void switchToConnectionScreen();

protected:
    void resizeEvent(QResizeEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void toggleTextVisibility();

private:
    std::shared_ptr<ParallaxBackground> layer0;
    std::shared_ptr<ParallaxBackground> layer1;
    std::shared_ptr<ParallaxBackground> layer2;
    std::shared_ptr<ParallaxBackground> layer3;
    std::shared_ptr<FadeInImage> fadeInImage;
    std::shared_ptr<QLabel> flickeringText;
    std::shared_ptr<QTimer> timer;
    std::shared_ptr<QSound> keyPressSound;
    Queue<std::shared_ptr<GenericMsg>>* send_queue;
    Queue<std::shared_ptr<GenericMsg>>* recv_queue;
    bool initialized = false;
};

#endif // LOGO_SCREEN_H