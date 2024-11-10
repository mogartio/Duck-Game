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
#include <string>
#include <QTimer>
#include <iostream>
#include "rounded_rectangle.h"
#include "../../common/queue.h"
#include "../../common/messages/generic_msg.h"

class LobbyScreen : public QWidget {
    Q_OBJECT

public: 
    LobbyScreen(Queue<GenericMsg*>* send_queue, Queue<GenericMsg*>* recv_queue);

private:
    Queue<GenericMsg*>* send_queue;
    Queue<GenericMsg*>* recv_queue; 
    QPixmap* white_cuak_sprite_sheet;
    QLabel* white_cuak_label;
    QSound *quakSound;
    int current_frame = 0;
    QTimer* timer;

    void keyPressEvent(QKeyEvent* event) override;
    void updateAnimationFrame();
    void showFirstFrame();
};  

#endif // LOBBY_SCREEN_H
