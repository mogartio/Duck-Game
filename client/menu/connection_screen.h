#ifndef CONNECTION_SCREEN_H
#define CONNECTION_SCREEN_H

#include "../client.h"
#include <QSound>
#include <QFontDatabase>
#include <QLineEdit>
#include <memory>
#include "parallax_background.h"

class ConnectionScreen : public QWidget {
    Q_OBJECT

public: 
    ConnectionScreen(Queue<GenericMsg*>* send_queue, Queue<GenericMsg*>* recv_queue, Client* client);
    
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
    std::unique_ptr<ParallaxBackground> layer0;
    std::unique_ptr<ParallaxBackground> layer1;
    std::unique_ptr<ParallaxBackground> layer2;
    std::unique_ptr<ParallaxBackground> layer3;
    std::unique_ptr<QSound> keyPressSound;
    std::unique_ptr<QLineEdit> hostname;
    std::unique_ptr<QLineEdit> port;
    QFont customFont;
    Queue<GenericMsg*>* send_queue;
    Queue<GenericMsg*>* recv_queue;
    Client* client;
};

#endif // CONNECTION_SCREEN_H