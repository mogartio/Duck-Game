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
    HostLobbyScreen(Queue<GenericMsg*>* send_queue, Queue<GenericMsg*>* recv_queue);
    ~HostLobbyScreen();

    void stopProcessing();

private slots: 
    void onAddLocalPlayerButtonClicked();
    void updatePlayersInLobby();
    void onReadyButtonClicked();
    void onSaveButtonClicked(std::string player_name);
signals: 
    void playersUpdated();

private:
    Queue<GenericMsg*>* send_queue;
    Queue<GenericMsg*>* recv_queue; 
    std::atomic<bool> running;
    std::mutex players_mutex;

    QFont customFont;
    QPixmap *saveIcon;
    QSound *keyPressSound;
    QPushButton *localPlayerButton;
    QScrollArea* scrollArea;
    QWidget* scrollWidget;
    QVBoxLayout* scrollLayout;

    uint8_t lobby_id;
    std::string myPlayerName = "Player1";
    std::string myLocalPlayerName = "localPlayer";
    bool isLocalPlayerAdded = false;
    std::thread recv_thread;
    std::list<DescipcionPlayer> players;
    std::vector<QWidget*> lobbyWidgets;
    uint8_t is_ready;
    // color de pato y su imagen
    std::list<std::pair<uint8_t, QPixmap*>> ducks_images;
    std::map<std::string, std::string> playerEdits;

    void processIncomingMessages();
};  

#endif // LOBBY_SCREEN_H
