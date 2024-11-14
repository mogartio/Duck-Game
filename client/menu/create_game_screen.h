#ifndef CREATE_GAME_SCREEN_H
#define CREATE_GAME_SCREEN_H

#include <QWidget>
#include <QPainter>
#include <QResizeEvent>
#include <QLineEdit>
#include <QSound>
#include <QFontDatabase>
#include <QLabel>
#include <QPushButton>
#include <QPixmap>
#include <QKeyEvent>
#include <iostream>
#include "logo_screen.h"
#include "rounded_rectangle.h"
#include "connection_screen.h"
#include "main_menu_screen.h"
#include "../../common/queue.h"
#include "../../common/messages/generic_msg.h"
#include "../../common/socket/socket.h"
#include "../client.h"
#define MAX_PLAYERS 6
#define MIN_PLAYERS 2

class CreateGameScreen : public QWidget {
    Q_OBJECT

public:
    CreateGameScreen(Queue<GenericMsg*>* send_queue, Queue<GenericMsg*>* recv_queue);
    void resizeEvent(QResizeEvent *event) override;
signals:
    void switchToMainMenuScreen();
    void switchToLobbyScreen();
private slots:
    void onCreateGameButtonClicked();
    void onBackButtonClicked();
    void onUpArrowClicked();
    void onDownArrowClicked();

private:
    QSound *keyPressSound;
    QFont customFont;
    Queue<GenericMsg*>* send_queue;
    Queue<GenericMsg*>* recv_queue;
    QLineEdit *lobbyName;
    QLabel *maxPlayersBox;
    int maxPlayers = MIN_PLAYERS;

    void drawLobbyNameError();
};

#endif // CREATE_GAME_SCREEN_H
