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
#include <QVBoxLayout>
#include <QScrollArea>
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

public slots:
    void triggerRefresh();

private slots:
    void onJoinButtonClicked(uint8_t lobby_id);
    void onBackButtonClicked();
    void onRefreshButtonClicked();

private:
    Queue<GenericMsg*>* send_queue;
    Queue<GenericMsg*>* recv_queue;
    QSound *keyPressSound;
    QFont customFont;
    std::vector<DescripcionLobby> lobbies;
    std::vector<QWidget*> lobbyWidgets;
    QScrollArea* scrollArea;
    QWidget* scrollWidget;
    QVBoxLayout* scrollLayout;
};

#endif  // JOIN_LOBBY_SCREEN_H
