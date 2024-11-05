#ifndef LOGO_SCREEN_H
#define LOGO_SCREEN_H

#include <QWidget>
#include "parallax_background.h"
#include "fade_in_image.h"

class LogoScreen : public QWidget {
    Q_OBJECT

public:
    LogoScreen();

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    ParallaxBackground *layer0;
    ParallaxBackground *layer1;
    ParallaxBackground *layer2;
    ParallaxBackground *layer3;
    FadeInImage *fadeInImage;
};

#endif // LOGO_SCREEN_H