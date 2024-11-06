#include <QApplication>
#include "../client/menu/main_window.h"
#include "../client/menu/connection_screen.h"
#include "../common/queue.h"
#include "../common/messages/generic_msg.h"
#include "../client/menu/logo_screen.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // ConnectionScreen connectionScreen;
    // connectionScreen.show();
    Queue<std::unique_ptr<GenericMsg>> send_queue;
    Queue<std::unique_ptr<GenericMsg>> recv_queue;

    // LogoScreen logoScreen(send_queue, recv_queue);
    // logoScreen.show();

    MainWindow mainWindow(nullptr, send_queue, recv_queue);
    mainWindow.show();

    return app.exec();
}