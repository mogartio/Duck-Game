#ifndef MAIN_MENU_SCREEN_H
#define MAIN_MENU_SCREEN_H

#include "../../common/queue.h"
#include "../../common/messages/generic_msg.h"
#include "rounded_rectangle.h"
#include <QWidget>
#include <QPainter>
#include <QResizeEvent>
#include <QLineEdit>
#include <QSound>
#include <QFontDatabase>
#include <QLabel>
#include <QPushButton>

class MainMenuScreen : public QWidget {
    Q_OBJECT

public:
    MainMenuScreen(Queue<GenericMsg*>* send_queue, Queue<GenericMsg*>* recv_queue);

signals:
    void switchToJoinGameScreen();
    void switchToCreateGameScreen();
    void quitApplication(); 

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void onJoinGameButtonClicked();
    void onCreateGameButtonClicked();
    void onQuitButtonClicked();

private:
    QSound *keyPressSound;
    QFont customFont;
    QPixmap background;
    Queue<GenericMsg*>* send_queue;
    Queue<GenericMsg*>* recv_queue;
};
#endif