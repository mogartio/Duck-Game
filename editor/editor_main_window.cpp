#include "editor_main_window.h"

EditorMainWindow::EditorMainWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("Duck Game - Level Editor");
    resize(1920, 1080);

    stackedWidget = std::make_shared<QStackedWidget>(this);
    setCentralWidget(stackedWidget.get());

    setInitialValuesScreen = std::make_shared<SetInitialValuesScreen>();

    stackedWidget->addWidget(setInitialValuesScreen.get());

    stackedWidget->setCurrentWidget(setInitialValuesScreen.get());
    
}