#include <QApplication>
#include "../client/menu/logo_screen.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    LogoScreen logo_screen;
    logo_screen.show();

    return app.exec();
}