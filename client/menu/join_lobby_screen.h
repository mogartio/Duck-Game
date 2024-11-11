#ifndef JOIN_LOBBY_SCREEN_H
#define JOIN_LOBBY_SCREEN_H

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
#include <QHBoxLayout>
#include <iostream>
#include "logo_screen.h"
#include "rounded_rectangle.h"
#include "connection_screen.h"
#include "main_menu_screen.h"
#include "../../common/queue.h"
#include "../../common/messages/generic_msg.h"
#include "../../common/socket/socket.h"
#include "../../common/messages/descripcion-lobby.h"
#include "../client.h"

class JoinLobbyScreen : public QWidget {
    Q_OBJECT

public:
    JoinLobbyScreen(Queue<GenericMsg*>* send_queue, Queue<GenericMsg*>* recv_queue);
    void resizeEvent(QResizeEvent *event) override;

signals:
    void switchToMainMenuScreen();
    void switchToLobbyScreen();

private slots:
    void onJoinButtonClicked();
    void onBackButtonClicked();
    void onRefreshButtonClicked();

private:
    Queue<GenericMsg*>* send_queue;
    Queue<GenericMsg*>* recv_queue;
    QSound *keyPressSound;
    QFont customFont;
    std::vector<DescripcionLobby> lobbies;

    void drawLobbyInList(uint8_t lobbyId, std::string lobbyName, uint8_t players, uint8_t maxPlayers);
};

#endif  // JOIN_LOBBY_SCREEN_H
