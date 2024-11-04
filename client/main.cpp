#include <QApplication>
#include "../client/menu/opening_screen.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    OpeningScreen logo_screen;
    logo_screen.show();

    return app.exec();
}