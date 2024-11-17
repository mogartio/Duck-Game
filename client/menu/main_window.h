#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QLabel>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include <QApplication>
#include <iostream>
#include <memory>
#include "logo_screen.h"
#include "connection_screen.h"
#include "main_menu_screen.h"
#include "create_game_screen.h"
#include "join_lobby_screen.h"
#include "lobby_screen.h"
#include "host_lobby_screen.h"
#include "../../common/queue.h"
#include "../../common/messages/generic_msg.h"
#include "../../common/socket/socket.h"
#include "../client.h"
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent, Queue<GenericMsg*>* send_queue, Queue<GenericMsg*>* recv_queue, Client* client, std::list<std::string>* local_players); 
    void handleQuitApplication();
    void handleGameStart();
    void showLogoScreen();
    void showConnectionScreen();
    void showMainMenuScreen();
    void showMainMenuScreenWithFade();
    void showCreateGameScreen();
    void showJoinLobbyScreen();
    void showLobbyScreen();
    void showHostLobbyScreen();

signals:
    void joinLobbyScreenShown();

private:
    std::unique_ptr<QStackedWidget> stackedWidget;
    std::unique_ptr<LogoScreen> logoScreen;
    std::unique_ptr<ConnectionScreen> connectionScreen;
    std::unique_ptr<MainMenuScreen> mainMenuScreen;
    std::unique_ptr<CreateGameScreen> createGameScreen;
    std::unique_ptr<LobbyScreen> lobbyScreen;
    std::unique_ptr<JoinLobbyScreen> joinLobbyScreen;
    std::unique_ptr<HostLobbyScreen> hostLobbyScreen;
    Queue<GenericMsg*>* send_queue;
    Queue<GenericMsg*>* recv_queue;
    Client* client;
    std::unique_ptr<QLabel> backgroundLabel;
    std::list<std::string> *local_players;
    
    void setupBackground();
    void slideBackground(int targetX);
};

#endif // MAIN_WINDOW_H