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
#include <iostream>
#include <QSound>
#include <QScrollArea>
#include <string>
#include <QTimer>
#include <iostream>
#include <map>
#include "rounded_rectangle.h"
#include "../../common/queue.h"
#include "../../common/messages/generic_msg.h"

class LobbyScreen : public QWidget {
    Q_OBJECT

public: 
    LobbyScreen(Queue<GenericMsg*>* send_queue, Queue<GenericMsg*>* recv_queue);


private slots: 
    void updatePlayersInLobby();
    void onReadyButtonClicked();
    void onSaveButtonClicked(std::string player_name);
signals: 
    void playersUpdated();

private:
    Queue<GenericMsg*>* send_queue;
    Queue<GenericMsg*>* recv_queue; 
    std::string myPlayerName;
    std::map<std::string, QLineEdit*> playerNameEdits;
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
