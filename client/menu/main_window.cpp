#include "main_window.h"

MainWindow::MainWindow(QWidget *parent, Queue<std::shared_ptr<GenericMsg>>* send_queue, Queue<std::shared_ptr<GenericMsg>>* recv_queue, Client* client, std::list<std::string>* local_players)
    : QMainWindow(parent), send_queue(send_queue), recv_queue(recv_queue), client(client), local_players(local_players), isMuted(false) {

    resize(1920, 1080);
    setWindowFlags(Qt::FramelessWindowHint);

    stackedWidget = std::make_unique<QStackedWidget>(this);
    setCentralWidget(stackedWidget.get());

    // Setup the background
    setupBackground();
    
    // Initialize media player
    mediaPlayer = new QMediaPlayer(this);
    connect(mediaPlayer, &QMediaPlayer::stateChanged, this, &MainWindow::onStateChanged);

    // Initialize sound button
    soundOnIcon = std::make_shared<QPixmap>("assets/menu_assets/Speaker-0.png");
    soundOffIcon = std::make_shared<QPixmap>("assets/menu_assets/Speaker-Crossed.png");
    soundButton = new QPushButton(this);
    soundButton->setStyleSheet("background-color: rgba(0, 0, 0, 0); border: none;");
    soundButton->setIcon(QIcon(*soundOnIcon));
    soundButton->setIconSize(QSize(50, 50));
    soundButton->setGeometry(10, 10, 50, 50);

    connect(soundButton, &QPushButton::clicked, this, &MainWindow::onSoundButtonClicked);

    // Convert relative paths to absolute paths
    logoConnectionSongPath = QDir::currentPath() + "/assets/menu_assets/Duck Game - Title.wav";
    menuSongsPaths = {
        QDir::currentPath() + "/assets/menu_assets/Duck Game - DontFWithDuck.wav",
        QDir::currentPath() + "/assets/menu_assets/Duck Game - DrDuck.wav",
        QDir::currentPath() + "/assets/menu_assets/Duck Game - SynthRock.wav",
        QDir::currentPath() + "/assets/menu_assets/Duck Game - TechnoFreak.wav"
    };

    // Create screens
    logoScreen = std::make_unique<LogoScreen>(send_queue, recv_queue);
    connectionScreen = std::make_unique<ConnectionScreen>(send_queue, recv_queue, client);
    mainMenuScreen = std::make_unique<MainMenuScreen>(send_queue, recv_queue);
    createGameScreen = std::make_unique<CreateGameScreen>(send_queue, recv_queue);
    joinLobbyScreen = std::make_unique<JoinLobbyScreen>(send_queue, recv_queue);

    // Add screens to stacked widget
    stackedWidget->addWidget(logoScreen.get());
    stackedWidget->addWidget(connectionScreen.get());
    stackedWidget->addWidget(mainMenuScreen.get());
    stackedWidget->addWidget(createGameScreen.get());
    stackedWidget->addWidget(joinLobbyScreen.get());

    // Ensure the screens are resized to fit the QMainWindow
    logoScreen->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    connectionScreen->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    mainMenuScreen->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    createGameScreen->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    joinLobbyScreen->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // Show the logo screen first
    showLogoScreen();

    // Connect the signal from LogoScreen to switch to ConnectionScreen
    connect(logoScreen.get(), &LogoScreen::switchToConnectionScreen, this, &MainWindow::showConnectionScreen);

    // Connect the quit signal from ConnectionScreen to quit the application
    connect(connectionScreen.get(), &ConnectionScreen::quitApplication, this, &MainWindow::handleQuitApplication);

    // Connect the signal from ConnectionScreen to switch to MainMenuScreen
    connect(connectionScreen.get(), &ConnectionScreen::switchToMainMenuScreen, this, &MainWindow::showMainMenuScreenWithFade);

    // Connect the quit signal from MainMenuScreen to quit the application
    connect(mainMenuScreen.get(), &MainMenuScreen::quitApplication, this, &MainWindow::handleQuitApplication);

    // Connect the signal from MainMenuScreen to switch to CreateGameScreen
    connect(mainMenuScreen.get(), &MainMenuScreen::switchToCreateGameScreen, this, &MainWindow::showCreateGameScreen);

    // Connect the signal from CreateGameScreen to switch to MainMenuScreen
    connect(createGameScreen.get(), &CreateGameScreen::switchToMainMenuScreen, this, &MainWindow::showMainMenuScreen);

    // Connect the signal from CreateGameScreen to switch to LobbyScreen
    connect(createGameScreen.get(), &CreateGameScreen::switchToLobbyScreen, this, &MainWindow::showHostLobbyScreen);

    // Connect the signal from MainMenuScreen to switch to JoinLobbyScreen
    connect(mainMenuScreen.get(), &MainMenuScreen::switchToJoinLobbyScreen, this, &MainWindow::showJoinLobbyScreen);

    // Connect the signal from JoinLobbyScreen to switch to MainMenuScreen
    connect(joinLobbyScreen.get(), &JoinLobbyScreen::switchToMainMenuScreen, this, &MainWindow::showMainMenuScreen);

    // Connect the signal from JoinLobbyScreen to switch to LobbyScreen
    connect(joinLobbyScreen.get(), &JoinLobbyScreen::switchToLobbyScreen, this, &MainWindow::showLobbyScreen);

    // Connect the signal to trigger refresh when JoinLobbyScreen is shown
    connect(this, &MainWindow::joinLobbyScreenShown, joinLobbyScreen.get(), &JoinLobbyScreen::triggerRefresh);

}

void MainWindow::setupBackground() {
    backgroundLabel = std::make_unique<QLabel>(this);
    QPixmap backgroundPixmap("assets/menu_assets/sliding_background.png"); // Load your image
    backgroundLabel->setPixmap(backgroundPixmap);
    backgroundLabel->setScaledContents(true); // Optional: scale the image to fit the window

    // Set the size and initial position (assumes your image height matches window height)
    backgroundLabel->resize(backgroundPixmap.size());
    backgroundLabel->move(0, 0); // Start at the first segment
    backgroundLabel->lower(); // Ensure it stays behind other widgets
}

void MainWindow::slideBackground(int targetX) {
    QPropertyAnimation *animation = new QPropertyAnimation(backgroundLabel.get(), "pos");
    animation->setDuration(1000); // Set duration for the sliding effect
    animation->setStartValue(backgroundLabel->pos());
    animation->setEndValue(QPoint(targetX, backgroundLabel->y()));
    animation->setEasingCurve(QEasingCurve::OutCubic);
    animation->start(QPropertyAnimation::DeleteWhenStopped);
}

void MainWindow::showMainMenuScreen() {
    stackedWidget->setCurrentWidget(mainMenuScreen.get());
    slideBackground(0); // Move to the first third
}

void MainWindow::showLogoScreen() {
    // hide the sound button
    soundButton->hide();
    // start playing the logo connection song
    mediaPlayer->setMedia(QUrl::fromLocalFile(logoConnectionSongPath));
    mediaPlayer->setVolume(20);
    mediaPlayer->play();
    menuMusicPlaying = false;
    isMuted = false;

    stackedWidget->setCurrentWidget(logoScreen.get());
}

void MainWindow::showConnectionScreen() {
    // show the sound button
    soundButton->show();
    stackedWidget->setCurrentWidget(connectionScreen.get());
}

void MainWindow::handleQuitApplication() {
    QApplication::quit();
}

void MainWindow::showMainMenuScreenWithFade() {
    // play the menu songs
    mediaPlayer->stop();
    mediaPlayer->setMedia(QUrl::fromLocalFile(menuSongsPaths[rand() % menuSongsPaths.size()]));
    mediaPlayer->play();
    if (isMuted) {
        // volume 0
        mediaPlayer->setVolume(0);
    } else {
        // volume 20
        mediaPlayer->setVolume(20);
    }
    menuMusicPlaying = true;

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
        stackedWidget->setCurrentWidget(mainMenuScreen.get());
        slideBackground(0); // Move to the first third
        QPropertyAnimation *fadeIn = new QPropertyAnimation(overlay->graphicsEffect(), "opacity");
        fadeIn->setDuration(1000);
        fadeIn->setStartValue(1);
        fadeIn->setEndValue(0);

        connect(fadeIn, &QPropertyAnimation::finished, overlay, &QWidget::deleteLater);
        fadeIn->start(QPropertyAnimation::DeleteWhenStopped);
    });

    fadeOut->start(QPropertyAnimation::DeleteWhenStopped);
}

void MainWindow::showCreateGameScreen() {
    stackedWidget->setCurrentWidget(createGameScreen.get());
    slideBackground(-480); // Move to the second third
}

void MainWindow::showLobbyScreen() {
    lobbyScreen = std::make_unique<LobbyScreen>(send_queue, recv_queue, local_players);
    stackedWidget->addWidget(lobbyScreen.get());
    stackedWidget->setCurrentWidget(lobbyScreen.get());
    slideBackground(-960); // Move to the last third

    // Connect the signal from LobbyScreen to switch to JoinLobbyScreen
    connect(lobbyScreen.get(), &LobbyScreen::switchToJoinLobbyScreen, this, &MainWindow::showJoinLobbyScreen);
    // Connect the start game signal from LobbyScreen to handle game start
    connect(lobbyScreen.get(), &LobbyScreen::startingGame, this, &MainWindow::handleGameStart);
}

void MainWindow::showJoinLobbyScreen() {
    stackedWidget->setCurrentWidget(joinLobbyScreen.get());
    slideBackground(-480); // Move to the last third
    emit joinLobbyScreenShown();
}

void MainWindow::showHostLobbyScreen() {
    hostLobbyScreen = std::make_unique<HostLobbyScreen>(send_queue, recv_queue, local_players);
    stackedWidget->addWidget(hostLobbyScreen.get());
    stackedWidget->setCurrentWidget(hostLobbyScreen.get());
    slideBackground(-960); // Move to the last third
    // Connect the start game signal from HostLobbyScreen to handle game start
    connect(hostLobbyScreen.get(), &HostLobbyScreen::startingGame, this, &MainWindow::handleGameStart);
    // Connect the signal from HostLobbyScreen to switch to MainMenuScreen
    connect(hostLobbyScreen.get(), &HostLobbyScreen::switchToMainMenuScreen, this, &MainWindow::showMainMenuScreen);

}

void MainWindow::handleGameStart() {
    // Create an overlay widget with a black background
    QWidget *overlay = new QWidget(this);
    overlay->setStyleSheet("background-color: black;");
    overlay->setGeometry(this->rect());
    overlay->show();

    QFont customFont;
    int fontId = QFontDatabase::addApplicationFont("assets/menu_assets/HomeVideo-Regular.ttf");
    QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
    customFont = QFont(fontFamily);

    // Add a QLabel to display the message "Starting game ..."
    QLabel *messageLabel = new QLabel("Starting game ...", overlay);
    messageLabel->setStyleSheet("color: white; font-size: 120px;");
    messageLabel->setFont(customFont);
    messageLabel->setAlignment(Qt::AlignCenter);
    messageLabel->setGeometry(660, 340, 600, 400);

    // Use a QVBoxLayout to center the label within the overlay
    QVBoxLayout *layout = new QVBoxLayout(overlay);
    layout->addWidget(messageLabel);
    layout->setAlignment(messageLabel, Qt::AlignCenter);
    overlay->setLayout(layout);

    // Apply a QGraphicsOpacityEffect to the overlay
    QGraphicsOpacityEffect *effect = new QGraphicsOpacityEffect(this);
    overlay->setGraphicsEffect(effect);

    // Create a QPropertyAnimation to animate the opacity of the overlay
    QPropertyAnimation *fadeOut = new QPropertyAnimation(effect, "opacity");
    fadeOut->setDuration(1000);
    fadeOut->setStartValue(0);
    fadeOut->setEndValue(1);

    // Connect the animation's finished signal to quit the application
    connect(fadeOut, &QPropertyAnimation::finished, [this, overlay]() {
        QTimer::singleShot(2000, [this]() { // 2000 milliseconds delay
            QApplication::quit();
        });
    });

    fadeOut->start(QPropertyAnimation::DeleteWhenStopped);
}

void MainWindow::onSoundButtonClicked() {
    if (isMuted) {
        mediaPlayer->setVolume(20);
        soundButton->setIcon(QIcon(*soundOnIcon));
        isMuted = false; // se desmuteo
    } else if (!isMuted) {
        mediaPlayer->setVolume(0);
        soundButton->setIcon(QIcon(*soundOffIcon));
        isMuted = true; // se muteo
    }
}

void MainWindow::onStateChanged(QMediaPlayer::State state) {
    if (state == QMediaPlayer::StoppedState) {
        if (menuMusicPlaying) {
            mediaPlayer->setMedia(QUrl::fromLocalFile(menuSongsPaths[rand() % menuSongsPaths.size()]));
            mediaPlayer->play();
            if (isMuted) {
                mediaPlayer->setVolume(0);
            } else {
                mediaPlayer->setVolume(20);
            }
        }
        mediaPlayer->play();
    } else if (state == QMediaPlayer::PlayingState) {
        if (isMuted) {
            mediaPlayer->setVolume(0);
        } else {
            mediaPlayer->setVolume(20);
        }
    }
}

