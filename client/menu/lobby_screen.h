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
    explicit LobbyScreen(Queue<GenericMsg*>* send_queue, Queue<GenericMsg*>* recv_queue);
    ~LobbyScreen();

    void stopProcessing();
private slots: 
    void updatePlayersInLobby();
    void onReadyButtonClicked();
    void onSaveButtonClicked(std::string player_name);
    void onExitLobbyButtonClicked();
signals: 
    void playersUpdated();
    void switchToJoinLobbyScreen();
private:
    Queue<GenericMsg*>* send_queue;
    Queue<GenericMsg*>* recv_queue; 
    std::atomic<bool> running;
    std::mutex players_mutex;
    std::thread recv_thread;
    std::string myPlayerName;
    QFont customFont;
    QPixmap *saveIcon;
    QSound *keyPressSound;
    QScrollArea* scrollArea;
    QWidget* scrollWidget;
    QVBoxLayout* scrollLayout;
    uint8_t lobby_id;
    std::list<DescipcionPlayer> players;
    std::vector<QWidget*> lobbyWidgets;
    // color de pato y su imagen
    std::list<std::pair<uint8_t, QPixmap*>> ducks_images;
    void processIncomingMessages();
};  

#endif // LOBBY_SCREEN_H
