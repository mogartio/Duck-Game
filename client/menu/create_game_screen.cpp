#include "create_game_screen.h"
#include <QSpinBox>

CreateGameScreen::CreateGameScreen(Queue<GenericMsg*>* send_queue, Queue<GenericMsg*>* recv_queue) : send_queue(send_queue), recv_queue(recv_queue) {
    setWindowState(Qt::WindowFullScreen); // Set window to full-screen mode

    // Set focus policy to receive key events
    setFocusPolicy(Qt::StrongFocus);

    // Set background image using QLabel
    QLabel *backgroundLabel = new QLabel(this);
    background.load("client/menu/assets/sliding_background.png");
    background = background.scaled(size(), Qt::KeepAspectRatioByExpanding);
    backgroundLabel->setPixmap(background);
    backgroundLabel->setGeometry(0, 0, this->width(), this->height());

    // Load key press sound
    keyPressSound = new QSound("client/menu/assets/Retro3.wav", this);

    // Create black opaque background rectangle
    RoundedRectangle * baseRectangle = new RoundedRectangle(this, 635, 260, 650, 560, QColor(0,0,0, 100), QColor(0,0,0, 100));
    baseRectangle->setParent(this);
    
    // Load custom font
    int fontId = QFontDatabase::addApplicationFont("client/menu/assets/HomeVideo-Regular.ttf");
    QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
    customFont = QFont(fontFamily);

    // Create game label
    QLabel *createGameLabel = new QLabel("Create Game", this);
    createGameLabel->setStyleSheet(
        "QLabel {"
        "color: #ced4da;"
        "font-size: 52px;"
        "}"
    );
    createGameLabel->setFont(customFont);
    createGameLabel->setGeometry(780, 285, 500, 100);

    // Create back button
    QPushButton *backButton = new QPushButton("Back", this);
    backButton->setStyleSheet(
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
    backButton->setFont(customFont);
    backButton->setGeometry(460, 260, 160, 80);

    // Load the original icon
    QPixmap goBackIcon("client/menu/assets/Left-Arrow.png");
    QPixmap goBackIconScaled = goBackIcon.scaled(30, 30);

    // Create a transparent QPixmap
    QPixmap transparentIcon(goBackIconScaled.size());
    transparentIcon.fill(Qt::transparent);

    // Use QPainter to draw the original icon with opacity
    QPainter painter(&transparentIcon);
    painter.setOpacity(0.75); // Set the desired opacity (0.0 to 1.0)
    painter.drawPixmap(0, 0, goBackIconScaled);
    painter.end();

    // Set the resulting QPixmap as the icon of the QPushButton
    backButton->setIcon(QIcon(transparentIcon));
    backButton->setIconSize(QSize(30, 30));

    connect(backButton, &QPushButton::clicked, this, &CreateGameScreen::onBackButtonClicked);

    // Create game name label
    QLabel *gameNameLabel = new QLabel("enter lobby Name", this);
    gameNameLabel->setStyleSheet(
        "QLabel {"
        "color: #ced4da;"
        "font-size: 38px;"
        "}"
    );
    gameNameLabel->setFont(customFont);
    gameNameLabel->setGeometry(700, 405, 500, 50);

    // Create game name input field
    lobbyName = new QLineEdit(this);
    lobbyName->setStyleSheet(
        "QLineEdit {"
        "background-color: rgba(0, 0, 0, 0);"
        "color: #ced4da;"
        "font-size: 30px;"
        "border: 2px solid #ced4da;"
        "border-radius: 10px;"
        "padding: 10px;"
        "}"
    );
    lobbyName->setFont(customFont);
    lobbyName->setGeometry(700, 460, 500, 50);

    // Create max players label
    QLabel *maxPlayersLabel = new QLabel("enter max players", this);
    maxPlayersLabel->setStyleSheet(
        "QLabel {"
        "color: #ced4da;"
        "font-size: 38px;"
        "}"
    );
    maxPlayersLabel->setFont(customFont);
    maxPlayersLabel->setGeometry(700, 535, 500, 50);

    // Create up arrow 
    QPushButton *upArrow = new QPushButton(this);
    upArrow->setStyleSheet(
        "QPushButton {"
        "background-color: rgba(0,0,0,0);"        
        "color: #ced4da;"                     
        "font-size: 42px;"                  
        "border: 0px solid #555555;"        
        "border-radius: 15px;"              
        "padding: 10px;"                    
        "text-align: center;"               
        "}"
        "QPushButton:hover {"
        "background-color: rgba(0,0,0,0);"
        "}"
    );
    // Load up arrow icon
    QPixmap upArrowIcon("client/menu/assets/Chevron-Arrow-Up.png");
    QPixmap upArrowIconScaled = upArrowIcon.scaled(30, 25);
    QPixmap transparentUpArrowIcon(upArrowIconScaled.size());
    transparentUpArrowIcon.fill(Qt::transparent);
    QPainter upArrowPainter(&transparentUpArrowIcon);
    upArrowPainter.setOpacity(0.75);
    upArrowPainter.drawPixmap(0, 0, upArrowIconScaled);
    upArrowPainter.end();
    upArrow->setIcon(QIcon(transparentUpArrowIcon));
    upArrow->setIconSize(QSize(30, 25));
    upArrow->setGeometry(710, 590, 30, 25);
    connect(upArrow, &QPushButton::clicked, this, &CreateGameScreen::onUpArrowClicked);
    // Create number box for max players
    maxPlayersBox = new QLabel(QString::number(maxPlayers), this);
    maxPlayersBox->setStyleSheet(
        "QLabel {"
        "color: #ced4da;"
        "font-size: 38px;"
        "border: 2px solid #ced4da;"
        "}"
    );
    maxPlayersBox->setFont(customFont);
    maxPlayersBox->setGeometry(700, 620, 50, 55);
    // Load down arrow icon
    QPushButton *downArrow = new QPushButton(this);
    downArrow->setStyleSheet(
        "QPushButton {"
        "background-color: rgba(0,0,0,0);"        
        "color: #ced4da;"                     
        "font-size: 42px;"                  
        "border: 0px solid #555555;"        
        "border-radius: 15px;"              
        "padding: 10px;"                    
        "text-align: center;"               
        "}"
        "QPushButton:hover {"
        "background-color: rgba(0,0,0,0);"
        "}"
    );
    QPixmap downArrowIcon("client/menu/assets/Chevron-Arrow-Down.png");
    QPixmap downArrowIconScaled = downArrowIcon.scaled(30, 25);
    QPixmap transparentDownArrowIcon(downArrowIconScaled.size());
    transparentDownArrowIcon.fill(Qt::transparent);
    QPainter downArrowPainter(&transparentDownArrowIcon);
    downArrowPainter.setOpacity(0.75);
    downArrowPainter.drawPixmap(0, 0, downArrowIconScaled);
    downArrowPainter.end();
    downArrow->setIcon(QIcon(transparentDownArrowIcon));
    downArrow->setIconSize(QSize(30, 25));
    downArrow->setGeometry(710, 680, 30, 25);
    connect(downArrow, &QPushButton::clicked, this, &CreateGameScreen::onDownArrowClicked);

    // Create create game button
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
    createGameButton->setGeometry(805, 780, 310, 100);
    connect(createGameButton, &QPushButton::clicked, this, &CreateGameScreen::onCreateGameButtonClicked);
}
   

void CreateGameScreen::resizeEvent(QResizeEvent *event) {
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

void CreateGameScreen::onBackButtonClicked() {
    keyPressSound->play();
    emit switchToMainMenuScreen();
}

void CreateGameScreen::onUpArrowClicked() {
    keyPressSound->play();
    if (maxPlayers < 6) {
        maxPlayers++;
        maxPlayersBox->setText(QString::number(maxPlayers));
    }
    std::cout << maxPlayers << std::endl;
}

void CreateGameScreen::onDownArrowClicked() {
    keyPressSound->play();
    if (maxPlayers > 2) {
        maxPlayers--;
        maxPlayersBox->setText(QString::number(maxPlayers));
    }
    std::cout << maxPlayers << std::endl;
}

void CreateGameScreen::onCreateGameButtonClicked() {
    keyPressSound->play();
    std::string lobbyNameStr = lobbyName->text().toStdString();
    if (lobbyNameStr.empty()) {
        drawLobbyNameError();
        return;
    }
    // Send a create game message to the server. 
    // Por ahora no manda estas especificaciones
    CreateLobbyMsg* createLobbyMsg = new CreateLobbyMsg(lobbyNameStr);
    send_queue->push(createLobbyMsg);
    GenericMsg* response = recv_queue->pop();
    if (response->get_header() == GenericMsg::MsgTypeHeader::EVERYTHING_OK_MSG) {
        emit switchToLobbyScreen();
    } else {
        throw std::runtime_error("No me llego lo que esperaba");
    }
}

void CreateGameScreen::drawLobbyNameError() {
    // Create a QLabel to display the error message
    QLabel *errorLabel = new QLabel("Please enter a lobby name", this);
    errorLabel->setStyleSheet("QLabel { color: #800404; font-size: 24px; }");
    errorLabel->setFont(QFont(customFont));
    errorLabel->setGeometry(700, 730, 500, 50);
    errorLabel->show();
    // Remove the error message after 2 seconds
    QTimer::singleShot(2000, errorLabel, &QObject::deleteLater);
}