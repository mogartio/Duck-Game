#ifndef OPENING_SCREEN_H
#define OPENING_SCREEN_H

#include <QWidget>
#include "parallax_background.h"
#include "fade_in_image.h"

class OpeningScreen : public QWidget {
    Q_OBJECT

public:
    OpeningScreen();

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    ParallaxBackground *layer0;
    ParallaxBackground *layer1;
    ParallaxBackground *layer2;
    ParallaxBackground *layer3;
    FadeInImage *fadeInImage;
};

#endif // OPENING_SCREEN_H