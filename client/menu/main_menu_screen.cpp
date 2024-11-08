#include "main_menu_screen.h"

MainMenuScreen::MainMenuScreen(Queue<std::unique_ptr<GenericMsg>>& send_queue, Queue<std::unique_ptr<GenericMsg>>& recv_queue) : send_queue(send_queue), recv_queue(recv_queue) {
    setWindowState(Qt::WindowFullScreen); // Set window to full-screen mode

    // Set focus policy to receive key events
    setFocusPolicy(Qt::StrongFocus);

    // Load key press sound
    keyPressSound = new QSound("client/menu/assets/Retro3.wav", this);

    // Set background image using QLabel
    QLabel *backgroundLabel = new QLabel(this);
    background.load("client/menu/assets/sliding_background.png");
    background = background.scaled(size(), Qt::KeepAspectRatioByExpanding);
    backgroundLabel->setPixmap(background);
    backgroundLabel->setGeometry(0, 0, this->width(), this->height());

    // Create black opaque background rectangle
    RoundedRectangle * baseRectangle = new RoundedRectangle(this, 710, 260, 500, 560, QColor(0,0,0, 100), QColor(0,0,0, 100));
    baseRectangle->setParent(this);

    // Load custom font
    int fontId = QFontDatabase::addApplicationFont("client/menu/assets/HomeVideo-Regular.ttf");
    QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
    customFont = QFont(fontFamily);

    // Create buttons
    int buttonWidth = 300;
    int buttonHeight = 100;
    int buttonX = 820;
    int buttonSpacing = 50; // Space between buttons
    // Join Game button
    QPushButton *joinGameButton = new QPushButton("Join Game", this);
    joinGameButton->setStyleSheet(
        "QPushButton {"
        "background-color: rgba(240, 140, 0, 100);"        
        "color: #ced4da;"                     
        "font-size: 42px;"                  
        "border: 0px solid #555555;"        
        "border-radius: 15px;"              
        "padding: 10px;"                    
        "text-align: center;"               
        "}"
        "QPushButton:hover {"
        "background-color: rgba(232, 89, 12, 100);"
        "}"
    );
    joinGameButton->setFont(customFont);
    joinGameButton->setGeometry(buttonX, 293, buttonWidth, buttonHeight);

    connect(joinGameButton, &QPushButton::clicked, this, &MainMenuScreen::onJoinGameButtonClicked);

    // Create Game button
    QPushButton *createGameButton = new QPushButton("Create Game", this);
    createGameButton->setStyleSheet(
        "QPushButton {"
        "background-color: rgba(240, 140, 0, 100);"        
        "color: #ced4da;"                     
        "font-size: 42px;"                  
        "border: 0px solid #555555;"        
        "border-radius: 15px;"              
        "padding: 10px;"                    
        "text-align: center;"               
        "}"
        "QPushButton:hover {"
        "background-color: rgba(232, 89, 12, 100);"
        "}"
    );
    createGameButton->setFont(customFont);
    createGameButton->setGeometry(buttonX, 293 + buttonHeight + buttonSpacing, buttonWidth, buttonHeight);
    connect(createGameButton, &QPushButton::clicked, this, &MainMenuScreen::onCreateGameButtonClicked);

    // Quit button
    QPushButton *quitButton = new QPushButton("Quit", this);
    quitButton->setStyleSheet(
        "QPushButton {"
        "background-color: rgba(240, 140, 0, 100);"        
        "color: #ced4da;"                     
        "font-size: 42px;"                  
        "border: 0px solid #555555;"        
        "border-radius: 15px;"              
        "padding: 10px;"                    
        "text-align: center;"               
        "}"
        "QPushButton:hover {"
        "background-color: rgba(232, 89, 12, 100);"
        "}"
    );
    quitButton->setFont(customFont);
    quitButton->setGeometry(buttonX, 293 + 2 * (buttonHeight + buttonSpacing), buttonWidth, buttonHeight);
    connect(quitButton, &QPushButton::clicked, this, &MainMenuScreen::onQuitButtonClicked);
}

void MainMenuScreen::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    // Trigger a repaint to adjust the background and rectangle
    QPixmap background("client/menu/assets/sliding_background.png");
    if (!background.isNull()) {
        int centerX = background.width() / 2;
        int centerY = background.height() / 2 - 150;
        int halfHeight = height() / 2;
        QRect centerRect(centerX - width(), centerY - halfHeight, width(), height());

        QPixmap centeredBackground = background.copy(centerRect);
        centeredBackground = centeredBackground.scaled(size(), Qt::KeepAspectRatioByExpanding);
        QLabel *backgroundLabel = findChild<QLabel *>();
        if (backgroundLabel) {
            backgroundLabel->setPixmap(centeredBackground);
            backgroundLabel->setGeometry(0, 0, this->width(), this->height());
        }
    }
    update();
}

void MainMenuScreen::onJoinGameButtonClicked() {
    keyPressSound->play();
    // emit switchToJoinGameScreen();
}

void MainMenuScreen::onCreateGameButtonClicked() {
    keyPressSound->play();
    // emit switchToCreateGameScreen();
}

void MainMenuScreen::onQuitButtonClicked() {
    keyPressSound->play();
    emit quitApplication();
}