#ifndef LOBBY_SCREEN_H
#define LOBBY_SCREEN_H

#include <QPainter>
#include <QResizeEvent>
#include <qboxlayout.h>
#include <QLabel>
#include <QLineEdit>
#include <qfontdatabase.h>
#include <QPushButton>
#include <QDebug> 
#include <thread>
#include <iostream>
#include <QSound>
#include <QScrollArea>
#include <string>
#include <QTimer>
#include <mutex>
#include <iostream>
#include <map>
#include "rounded_rectangle.h"
#include "../../common/queue.h"
#include "../../common/messages/generic_msg.h"

class LobbyScreen : public QWidget {
    Q_OBJECT

public: 
    explicit LobbyScreen(Queue<GenericMsg*>* send_queue, Queue<GenericMsg*>* recv_queue, std::list<std::string>* local_players);
    ~LobbyScreen();

    void stopProcessing();
private slots: 
    void updatePlayersInLobby();
    void onReadyButtonClicked(std::string player_name);
    void onSaveButtonClicked(std::string player_name);
    void onExitLobbyButtonClicked();
    void onStartingGame();
signals: 
    void playersUpdated();
    void switchToJoinLobbyScreen();
    void startingGame();
    void starting(); 
    
private:
    Queue<GenericMsg*>* send_queue;
    Queue<GenericMsg*>* recv_queue; 
    std::list<std::string>* local_players;
    std::atomic<bool> running;
    std::mutex players_mutex;
    std::thread recv_thread;
    std::string myPlayerName;
    QFont customFont;
    std::unique_ptr<QPixmap> saveIcon;
    std::unique_ptr<QSound> keyPressSound;
    std::unique_ptr<QScrollArea> scrollArea;
    std::unique_ptr<QWidget> scrollWidget;
    std::unique_ptr<QVBoxLayout> scrollLayout;
    uint8_t lobby_id;
    uint8_t is_ready;
    std::list<DescipcionPlayer> players;
    std::vector<std::unique_ptr<QWidget>> lobbyWidgets;
    std::map<std::string, std::string> playerEdits;
    // color de pato y su imagen
    std::list<std::pair<uint8_t, std::unique_ptr<QPixmap>>> ducks_images;
    void processIncomingMessages();
};   

#endif // LOBBY_SCREEN_H
