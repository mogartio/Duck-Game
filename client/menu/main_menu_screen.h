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
    MainMenuScreen(Queue<std::shared_ptr<GenericMsg>>* send_queue, Queue<std::shared_ptr<GenericMsg>>* recv_queue);

signals:
    void switchToJoinLobbyScreen();
    void switchToCreateGameScreen();
    void quitApplication(); 

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void onJoinLobbyButtonClicked();
    void onCreateGameButtonClicked();
    void onQuitButtonClicked();

private:
    std::shared_ptr<QSound> keyPressSound;
    QFont customFont;
    QPixmap background;
    Queue<std::shared_ptr<GenericMsg>>* send_queue;
    Queue<std::shared_ptr<GenericMsg>>* recv_queue;
};
#endif