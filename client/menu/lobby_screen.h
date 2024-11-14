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
    //void onReceivedMsg(); // updatea la lista de jugadores en el lobby

private:
    Queue<GenericMsg*>* send_queue;
    Queue<GenericMsg*>* recv_queue; 
    QFont customFont;
    QSound *keyPressSound;
    QScrollArea* scrollArea;
    QWidget* scrollWidget;
    QVBoxLayout* scrollLayout;
    uint8_t lobby_id;
    // la key del map es el nombre inicial del jugador, el value es el nombre actual y el color
    std::map<std::string, std::pair<std::string, uint8_t>> players; 

};  

#endif // LOBBY_SCREEN_H
