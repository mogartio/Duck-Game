#include "join_lobby_screen.h" 

JoinLobbyScreen::JoinLobbyScreen(Queue<GenericMsg*>* send_queue, Queue<GenericMsg*>* recv_queue) : send_queue(send_queue), recv_queue(recv_queue) {
    setWindowState(Qt::WindowFullScreen); // Set window to full-screen mode

    // Set focus policy to receive key events
    setFocusPolicy(Qt::StrongFocus);

    // Load key press sound
    keyPressSound = new QSound("client/menu/assets/Retro3.wav", this);
    
    // Load custom font
    int fontId = QFontDatabase::addApplicationFont("client/menu/assets/HomeVideo-Regular.ttf");
    QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
    customFont = QFont(fontFamily);

    // Create black opaque background rectangle
    RoundedRectangle * baseRectangle = new RoundedRectangle(this, 560, 260, 800, 560, QColor(0,0,0, 100), QColor(0,0,0, 100));
    baseRectangle->setParent(this);

    // Create game label
    QLabel *joinLobbyLabel = new QLabel("Join a Lobby", this);
    joinLobbyLabel->setStyleSheet(
        "QLabel {"
        "color: #ced4da;"
        "font-size: 52px;"
        "}"
    );
    joinLobbyLabel->setFont(customFont);
    joinLobbyLabel->setGeometry(780, 285, 500, 100);

    // Create go back button
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
    backButton->setGeometry(385, 260, 160, 80);

    QPixmap goBackIcon("client/menu/assets/Left-Arrow.png");
    QPixmap goBackIconScaled = goBackIcon.scaled(30, 30);
    QPixmap transparentIcon(goBackIconScaled.size());
    transparentIcon.fill(Qt::transparent);
    QPainter painter(&transparentIcon);
    painter.setOpacity(0.75);
    painter.drawPixmap(0, 0, goBackIconScaled);
    painter.end();

    backButton->setIcon(QIcon(transparentIcon));
    backButton->setIconSize(QSize(30, 30));

    connect(backButton, &QPushButton::clicked, this, &JoinLobbyScreen::onBackButtonClicked);

    // Create refresh button
    QPushButton *refreshButton = new QPushButton("Refresh", this);
    refreshButton->setStyleSheet(
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
    refreshButton->setFont(customFont);
    refreshButton->setGeometry(1375, 260, 240, 80);

    // Add refresh icon
    QPixmap refreshIcon("client/menu/assets/refresh_button.png");
    QPixmap refreshIconScaled = refreshIcon.scaled(40, 40);
    QPixmap transparentRefreshIcon(refreshIconScaled.size());
    transparentRefreshIcon.fill(Qt::transparent);
    QPainter refreshPainter(&transparentRefreshIcon);
    refreshPainter.setOpacity(0.75);
    refreshPainter.drawPixmap(0, 0, refreshIconScaled);
    refreshPainter.end();

    refreshButton->setIcon(QIcon(transparentRefreshIcon));
    refreshButton->setIconSize(QSize(40, 40));

    connect(refreshButton, &QPushButton::clicked, this, &JoinLobbyScreen::onRefreshButtonClicked);

    // Create first lobby list from SendLobbiesListMsg
    //onRefreshButtonClicked();

}; 

void JoinLobbyScreen::resizeEvent(QResizeEvent *event) {   
    update();
}

void JoinLobbyScreen::onBackButtonClicked() {
    keyPressSound->play();
    emit switchToMainMenuScreen();
}

void JoinLobbyScreen::onRefreshButtonClicked() {
    keyPressSound->play();
    send_queue->push(new ViewLobbiesMsg());
    GenericMsg* msg = recv_queue->pop();
    if (msg->get_header() == GenericMsg::MsgTypeHeader::SEND_LOBBIES_LIST_MSG) {
        SendLobbiesListMsg* lobbyListMsg = dynamic_cast<SendLobbiesListMsg*>(msg);
        lobbies = lobbyListMsg->get_lobbies();
        for (std::vector<DescripcionLobby>::size_type i = 0; i < lobbies.size(); i++) {
            DescripcionLobby lobby = lobbies[i];
            uint8_t lobbyId = lobby.idLobby;
            std::string lobbyName = lobby.nombreLobby;
            uint8_t players = lobby.cantidadJugadores;
            uint8_t maxPlayers = lobby.maxJugadores;
            // Draw all lobbies in the list
            drawLobbyInList(lobbyId, lobbyName, players, maxPlayers);
        }
    }
}

void JoinLobbyScreen::onJoinButtonClicked() {
    keyPressSound->play();
}

void JoinLobbyScreen::drawLobbyInList(uint8_t lobbyId, std::string lobbyName, uint8_t players, uint8_t maxPlayers) {
    QString lobbyLabelStr = QString::fromStdString(lobbyName + "          " + std::to_string(static_cast<int>(players)) + "/" + std::to_string(static_cast<int>(maxPlayers)));
    std::cout << "Drawing lobby: " << lobbyLabelStr.toStdString() << std::endl;
    QLabel *lobbyLabel = new QLabel(lobbyLabelStr, this);
    lobbyLabel->setStyleSheet(
        "QLabel {"
        "color: #ced4da;"
        "font-size: 42px;"
        "}"
    );
    lobbyLabel->setFont(customFont);
    int x = 780;
    int y = 400 + 60 * lobbies.size();
    int width = 500;
    int height = 100;
    std::cout << "Setting geometry: x=" << x << " y=" << y << " width=" << width << " height=" << height << std::endl;
    lobbyLabel->setGeometry(x, y, width, height);
    lobbyLabel->show();
}