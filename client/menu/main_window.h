#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QApplication>
#include <QDir>
#include <QGraphicsOpacityEffect>
#include <QLabel>
#include <QMainWindow>
#include <QMediaPlayer>
#include <QPropertyAnimation>
#include <QStackedWidget>
#include <iostream>
#include <memory>
#include <vector>

#include "../../common/messages/generic_msg.h"
#include "../../common/queue.h"
#include "../../common/socket/socket.h"
#include "../comunication/client.h"

#include "connection_screen.h"
#include "create_game_screen.h"
#include "host_lobby_screen.h"
#include "join_lobby_screen.h"
#include "lobby_screen.h"
#include "logo_screen.h"
#include "main_menu_screen.h"
class MainWindow: public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent, Queue<std::shared_ptr<GenericMsg>>* send_queue,
               Queue<std::shared_ptr<GenericMsg>>* recv_queue, Client* client,
               std::list<std::string>* local_players);

signals:
    void joinLobbyScreenShown();
    void soundButtonClicked();

private slots:
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
    void onSoundButtonClicked();
    void onStateChanged(QMediaPlayer::State state);

private:
    // screens
    std::shared_ptr<QStackedWidget> stackedWidget;
    std::shared_ptr<LogoScreen> logoScreen;
    std::shared_ptr<ConnectionScreen> connectionScreen;
    std::shared_ptr<MainMenuScreen> mainMenuScreen;
    std::shared_ptr<CreateGameScreen> createGameScreen;
    std::shared_ptr<LobbyScreen> lobbyScreen;
    std::shared_ptr<JoinLobbyScreen> joinLobbyScreen;
    std::shared_ptr<HostLobbyScreen> hostLobbyScreen;
    std::shared_ptr<QLabel> backgroundLabel;
    // cosas del main y del juego
    Queue<std::shared_ptr<GenericMsg>>* send_queue;
    Queue<std::shared_ptr<GenericMsg>>* recv_queue;
    Client* client;
    std::list<std::string>* local_players;
    // cosas del sonido
    QPushButton* soundButton;
    std::shared_ptr<QPixmap> soundOnIcon;
    std::shared_ptr<QPixmap> soundOffIcon;
    bool isMuted;
    bool menuMusicPlaying;
    QMediaPlayer* mediaPlayer;
    QString logoConnectionSongPath;
    std::vector<QString> menuSongsPaths;

    void setupBackground();
    void slideBackground(int targetX);
    void playLogoConnectionMusic();
    void playMenuMusic();
    void toggleSound();
};

#endif  // MAIN_WINDOW_H
