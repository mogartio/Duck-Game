#include "main_menu_screen.h"

MainMenuScreen::MainMenuScreen(Queue<GenericMsg*>* send_queue, Queue<GenericMsg*>* recv_queue) : send_queue(send_queue), recv_queue(recv_queue) {
    setWindowState(Qt::WindowFullScreen); // Set window to full-screen mode

    // Set focus policy to receive key events
    setFocusPolicy(Qt::StrongFocus);

    // Load key press sound
    keyPressSound = new QSound("client/menu/assets/Retro3.wav", this);

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