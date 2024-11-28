#include <iostream>
#include <QApplication>
#include "editor_main_window.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    EditorMainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
