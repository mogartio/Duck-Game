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
    MainWindow(QWidget *parent, Queue<std::shared_ptr<GenericMsg>>* send_queue, Queue<std::shared_ptr<GenericMsg>>* recv_queue, Client* client, std::list<std::string>* local_players); 
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
    std::shared_ptr<QStackedWidget> stackedWidget;
    std::shared_ptr<LogoScreen> logoScreen;
    std::shared_ptr<ConnectionScreen> connectionScreen;
    std::shared_ptr<MainMenuScreen> mainMenuScreen;
    std::shared_ptr<CreateGameScreen> createGameScreen;
    std::shared_ptr<LobbyScreen> lobbyScreen;
    std::shared_ptr<JoinLobbyScreen> joinLobbyScreen;
    std::shared_ptr<HostLobbyScreen> hostLobbyScreen;
    Queue<std::shared_ptr<GenericMsg>>* send_queue;
    Queue<std::shared_ptr<GenericMsg>>* recv_queue;
    Client* client;
    std::shared_ptr<QLabel> backgroundLabel;
    std::list<std::string> *local_players;
    
    void setupBackground();
    void slideBackground(int targetX);
};

#endif // MAIN_WINDOW_H