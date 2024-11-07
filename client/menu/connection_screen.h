#ifndef CONNECTION_SCREEN_H
#define CONNECTION_SCREEN_H

#include <QWidget>
#include <QPainter>
#include <QResizeEvent>
#include <QLineEdit>
#include "parallax_background.h"
#include "../../common/queue.h"
#include "../../common/messages/generic_msg.h"
#include "../../common/socket/socket.h"
#include <QSound>
#include <QFontDatabase>
class ConnectionScreen : public QWidget {
    Q_OBJECT

public: 
    ConnectionScreen(Queue<std::unique_ptr<GenericMsg>>& send_queue, Queue<std::unique_ptr<GenericMsg>>& recv_queue);
    Socket* getSocket();
signals:
    void switchToMainMenuScreen();
    void quitApplication();


protected:
    void resizeEvent(QResizeEvent *event) override;
    void drawEmptyFieldsError();
    void drawConnectionRefusedError();
private slots:
    void onConnectButtonClicked();
    void onQuitButtonClicked();
    
private:
    Socket *socket;
    ParallaxBackground *layer0;
    ParallaxBackground *layer1;
    ParallaxBackground *layer2;
    ParallaxBackground *layer3;
    QSound *keyPressSound;
    QLineEdit *hostname;
    QLineEdit *port;
    QFont customFont;
    Queue<std::unique_ptr<GenericMsg>>& send_queue;
    Queue<std::unique_ptr<GenericMsg>>& recv_queue;
};

#endif // CONNECTION_SCREEN_H