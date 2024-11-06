#ifndef CONNECTION_SCREEN_H
#define CONNECTION_SCREEN_H

#include <QWidget>
#include <QPainter>
#include <QResizeEvent>
#include "parallax_background.h"
#include "../../common/queue.h"
#include "../../common/messages/generic_msg.h"

class ConnectionScreen : public QWidget {
    Q_OBJECT

public: 
    ConnectionScreen(Queue<std::unique_ptr<GenericMsg>>& send_queue, Queue<std::unique_ptr<GenericMsg>>& recv_queue);

protected:
    void resizeEvent(QResizeEvent *event) override;
    
private:
    ParallaxBackground *layer0;
    ParallaxBackground *layer1;
    ParallaxBackground *layer2;
    ParallaxBackground *layer3;
    Queue<std::unique_ptr<GenericMsg>>& send_queue;
    Queue<std::unique_ptr<GenericMsg>>& recv_queue;
};

#endif // CONNECTION_SCREEN_H