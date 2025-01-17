#ifndef CONNECTION_SCREEN_H
#define CONNECTION_SCREEN_H

#include <QBoxLayout>
#include <QFontDatabase>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QResizeEvent>
#include <QSound>
#include <memory>
#include <string>

#include "../comunication/client.h"

#include "parallax_background.h"
#include "rounded_rectangle.h"
class ConnectionScreen: public QWidget {
    Q_OBJECT

public:
    ConnectionScreen(Queue<std::shared_ptr<GenericMsg>>* send_queue,
                     Queue<std::shared_ptr<GenericMsg>>* recv_queue, Client* client);

signals:
    void switchToMainMenuScreen();
    void quitApplication();

protected:
    void resizeEvent(QResizeEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
    void drawEmptyFieldsError();
    void drawConnectionRefusedError();

private slots:
    void onConnectButtonClicked();
    void onQuitButtonClicked();

private:
    std::shared_ptr<ParallaxBackground> layer0;
    std::shared_ptr<ParallaxBackground> layer1;
    std::shared_ptr<ParallaxBackground> layer2;
    std::shared_ptr<ParallaxBackground> layer3;
    std::shared_ptr<QSound> keyPressSound;
    std::shared_ptr<QLineEdit> hostname;
    std::shared_ptr<QLineEdit> port;
    QFont customFont;
    Queue<std::shared_ptr<GenericMsg>>* send_queue;
    Queue<std::shared_ptr<GenericMsg>>* recv_queue;
    Client* client;
};

#endif  // CONNECTION_SCREEN_H
