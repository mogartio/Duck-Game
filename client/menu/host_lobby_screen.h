#ifndef HOST_LOBBY_SCREEN_H
#define HOST_LOBBY_SCREEN_H

#include <QPainter>
#include <QResizeEvent>
#include <qboxlayout.h>
#include <QLabel>
#include <QLineEdit>
#include <qfontdatabase.h>
#include <QPushButton>
#include <QDebug> 
#include <iostream>
#include <QSound>
#include <QScrollArea>
#include <thread>
#include <mutex>
#include <string>
#include <QTimer>
#include <iostream>
#include <map>
#include "rounded_rectangle.h"
#include "../../common/queue.h"
#include "../../common/messages/generic_msg.h"

class HostLobbyScreen : public QWidget {
    Q_OBJECT

public: 
    HostLobbyScreen(Queue<std::shared_ptr<GenericMsg>>* send_queue, Queue<std::shared_ptr<GenericMsg>>* recv_queue, std::list<std::string>* local_players);
    ~HostLobbyScreen();

    void stopProcessing();

private slots: 
    void onAddLocalPlayerButtonClicked();
    void updatePlayersInLobby();
    void onReadyButtonClicked(std::string player_name);
    void onSaveButtonClicked(std::string player_name);
    void onStartGameButtonClicked();
signals: 
    void playersUpdated();
    void startingGame();
private:
    Queue<std::shared_ptr<GenericMsg>>* send_queue;
    Queue<std::shared_ptr<GenericMsg>>* recv_queue; 
    std::list<std::string>* local_players;
    std::atomic<bool> running;
    std::mutex players_mutex;

    QFont customFont;
    std::shared_ptr<QPixmap> saveIcon;
    std::shared_ptr<QSound> keyPressSound;
    QPushButton *localPlayerButton;
    std::shared_ptr<QScrollArea> scrollArea;
    std::shared_ptr<QWidget> scrollWidget;
    std::shared_ptr<QVBoxLayout> scrollLayout;
    QPushButton *startGameButton;

    uint8_t lobby_id;
    std::string myPlayerName = "Player1";
    std::string myLocalPlayerName = "localPlayer";
    bool isLocalPlayerAdded = false;
    std::thread recv_thread;
    std::list<DescipcionPlayer> players;
    std::vector<QWidget*> lobbyWidgets;
    // color de pato y su imagen
    std::list<std::pair<uint8_t, std::shared_ptr<QPixmap>>> ducks_images;
    std::map<std::string, std::string> playerEdits;

    void processIncomingMessages();
    void updateStartGameButton();
};

#endif // LOBBY_SCREEN_H
