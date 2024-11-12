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
#include "logo_screen.h"
#include "connection_screen.h"
#include "main_menu_screen.h"
#include "create_game_screen.h"
#include "join_lobby_screen.h"
#include "lobby_screen.h"
#include "../../common/queue.h"
#include "../../common/messages/generic_msg.h"
#include "../../common/socket/socket.h"
#include "../client.h"
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent, Queue<GenericMsg*>* send_queue, Queue<GenericMsg*>* recv_queue, Client* client); 
    ~MainWindow();
    void handleQuitApplication();
    void showLogoScreen();
    void showConnectionScreen();
    void showMainMenuScreen();
    void showMainMenuScreenWithFade();
    void showCreateGameScreen();
    void showJoinLobbyScreen();
    void showLobbyScreen();

private:
    QStackedWidget *stackedWidget;
    LogoScreen *logoScreen;
    ConnectionScreen *connectionScreen;
    MainMenuScreen *mainMenuScreen;
    CreateGameScreen *createGameScreen;
    LobbyScreen *lobbyScreen;
    JoinLobbyScreen *joinLobbyScreen;
    Queue<GenericMsg*>* send_queue;
    Queue<GenericMsg*>* recv_queue;
    Client* client;
    QLabel *backgroundLabel;
    
    void setupBackground();
    void slideBackground(int targetX);
};

#endif // MAIN_WINDOW_H