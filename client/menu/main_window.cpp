#include "main_window.h"

MainWindow::MainWindow(QWidget *parent, Queue<GenericMsg*>* send_queue, Queue<GenericMsg*>* recv_queue, Client* client) : QMainWindow(parent), send_queue(send_queue), recv_queue(recv_queue), client(client) {
    
    resize(1920, 1080);
    //setWindowFlags(Qt::FramelessWindowHint);

    stackedWidget = new QStackedWidget(this);
    setCentralWidget(stackedWidget);

    // Create screens
    logoScreen = new LogoScreen(send_queue, recv_queue);
    connectionScreen = new ConnectionScreen(send_queue, recv_queue, client);
    mainMenuScreen = new MainMenuScreen(send_queue, recv_queue);

    // Add screens to stacked widget
    stackedWidget->addWidget(logoScreen);
    stackedWidget->addWidget(connectionScreen);
    stackedWidget->addWidget(mainMenuScreen);

    // Ensure the screens are resized to fit the QMainWindow
    logoScreen->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    connectionScreen->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    mainMenuScreen->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // Show the logo screen initially
    showLogoScreen();

    // Connect the signal from LogoScreen to switch to ConnectionScreen
    connect(logoScreen, &LogoScreen::switchToConnectionScreen, this, &MainWindow::showConnectionScreen);

    // Connect the quir signal from ConnectionScreen to quit the application
    connect(connectionScreen, &ConnectionScreen::quitApplication, this, &MainWindow::handleQuitApplication);

    // Connect the signal from ConnectionScreen to switch to MainMenuScreen
    connect(connectionScreen, &ConnectionScreen::switchToMainMenuScreen, this, &MainWindow::showMainMenuScreen);

    // Connect the quit signal from MainMenuScreen to quit the application
    connect(mainMenuScreen, &MainMenuScreen::quitApplication, this, &MainWindow::handleQuitApplication);
}

void MainWindow::showLogoScreen() {
    stackedWidget->setCurrentWidget(logoScreen);
}

void MainWindow::showConnectionScreen() {
    stackedWidget->setCurrentWidget(connectionScreen);
}

void MainWindow::handleQuitApplication() {
    QApplication::quit();
}

void MainWindow::showMainMenuScreen() {
    QWidget *overlay = new QWidget(this);
    overlay->setStyleSheet("background-color: black;");
    overlay->setGeometry(this->rect());
    overlay->show();

    QGraphicsOpacityEffect *effect = new QGraphicsOpacityEffect(this);
    overlay->setGraphicsEffect(effect);

    QPropertyAnimation *fadeOut = new QPropertyAnimation(effect, "opacity");
    fadeOut->setDuration(1000);
    fadeOut->setStartValue(0);
    fadeOut->setEndValue(1);

    connect(fadeOut, &QPropertyAnimation::finished, [this, overlay]() {
        stackedWidget->setCurrentWidget(mainMenuScreen);

        QPropertyAnimation *fadeIn = new QPropertyAnimation(overlay->graphicsEffect(), "opacity");
        fadeIn->setDuration(1000);
        fadeIn->setStartValue(1);
        fadeIn->setEndValue(0);

        connect(fadeIn, &QPropertyAnimation::finished, overlay, &QWidget::deleteLater);
        fadeIn->start(QPropertyAnimation::DeleteWhenStopped);
    });

    fadeOut->start(QPropertyAnimation::DeleteWhenStopped);
}


MainWindow::~MainWindow() {
    delete connectionScreen;
}