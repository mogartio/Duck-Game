#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include "logo_screen.h"
#include "connection_screen.h"
#include "main_menu_screen.h"
#include "../../common/queue.h"
#include "../../common/messages/generic_msg.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent,Queue<std::unique_ptr<GenericMsg>>& send_queue, Queue<std::unique_ptr<GenericMsg>>& recv_queue);
    ~MainWindow();
    void handleQuitApplication();
    void showLogoScreen();
    void showConnectionScreen();
    void showMainMenuScreen();
    // void showJoinGammeScreen();
    // void showCreateGameScreen();
    // void showLobbyScreen();

private:
    QStackedWidget *stackedWidget;
    LogoScreen *logoScreen;
    ConnectionScreen *connectionScreen;
    MainMenuScreen *mainMenuScreen;
    Queue<std::unique_ptr<GenericMsg>>& send_queue;
    Queue<std::unique_ptr<GenericMsg>>& recv_queue;
};

#endif // MAIN_WINDOW_H