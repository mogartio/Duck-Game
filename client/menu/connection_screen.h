#ifndef CONNECTION_SCREEN_H
#define CONNECTION_SCREEN_H

#include <QWidget>
#include "parallax_background.h"
#include "fade_in_image.h"

class ConnectionScreen : public QWidget {
    Q_OBJECT

public:
    ConnectionScreen();

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    ParallaxBackground *layer0;
    ParallaxBackground *layer1;
    ParallaxBackground *layer2;
    ParallaxBackground *layer3;
    FadeInImage *fadeInImage;
};

#endif // CONNECTION_SCREEN_H