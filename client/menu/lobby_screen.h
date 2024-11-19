#ifndef LOBBY_SCREEN_H
#define LOBBY_SCREEN_H

#include <qboxlayout.h>
#include <QLabel>
#include <QLineEdit>
#include <qfontdatabase.h>
#include <QPushButton>
#include <thread>
#include <QSound>
#include <QScrollArea>
#include <mutex>
#include <map>
#include "rounded_rectangle.h"
#include "../../common/queue.h"
#include "../../common/messages/generic_msg.h"

class LobbyScreen : public QWidget {
    Q_OBJECT

public: 
    explicit LobbyScreen(Queue<std::shared_ptr<GenericMsg>>* send_queue, Queue<std::shared_ptr<GenericMsg>>* recv_queue, std::list<std::string>* local_players);
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
    Queue<std::shared_ptr<GenericMsg>>* send_queue;
    Queue<std::shared_ptr<GenericMsg>>* recv_queue; 
    std::list<std::string>* local_players;
    std::atomic<bool> running;
    std::mutex players_mutex;
    std::thread recv_thread;
    std::string myPlayerName;
    QFont customFont;
    std::shared_ptr<QPixmap> saveIcon;
    std::shared_ptr<QSound> keyPressSound;
    std::shared_ptr<QScrollArea> scrollArea;
    std::shared_ptr<QWidget> scrollWidget;
    std::shared_ptr<QVBoxLayout> scrollLayout;
    uint8_t lobby_id;
    uint8_t is_ready;
    std::list<DescripcionPlayer> players;
    std::vector<QWidget*> lobbyWidgets;
    std::map<std::string, std::string> playerEdits;
    // color de pato y su imagen
    std::list<std::pair<uint8_t, std::shared_ptr<QPixmap>>> ducks_images;
    void processIncomingMessages();
};   

#endif // LOBBY_SCREEN_H
