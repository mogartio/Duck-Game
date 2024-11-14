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
    RoundedRectangle * baseRectangle = new RoundedRectangle(this, 560, 200, 800, 560, QColor(0,0,0, 100), QColor(0,0,0, 100));
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
    joinLobbyLabel->setGeometry(780, 225, 500, 100);

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
    backButton->setGeometry(385, 200, 160, 80);

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
    refreshButton->setGeometry(1375, 200, 240, 80);

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

    // Create scroll area for lobbies
    scrollArea = new QScrollArea(this);
    scrollArea->setGeometry(635, 325, 650, 500);
    scrollArea->setWidgetResizable(true);
    scrollArea->setStyleSheet("background-color: rgba(255,0,0,0);");

    scrollWidget = new QWidget();
    scrollWidget->setStyleSheet("background: transparent;");
    scrollArea->setWidget(scrollWidget);

    scrollLayout = new QVBoxLayout(scrollWidget);
    scrollLayout->setSpacing(20); // Set spacing between widgets
    scrollWidget->setLayout(scrollLayout);
    scrollLayout->setAlignment(Qt::AlignTop);

}; 

void JoinLobbyScreen::resizeEvent(QResizeEvent *event) {   
    update();
}

void JoinLobbyScreen::triggerRefresh() {
    onRefreshButtonClicked();
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

        QLayoutItem* item;
        while ((item = scrollLayout->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
        for (std::vector<DescripcionLobby>::size_type i = 0; i < lobbies.size(); i++) {
            DescripcionLobby lobby = lobbies[i];
            std::string lobbyName = lobby.nombreLobby;
            uint8_t players = lobby.cantidadJugadores;
            uint8_t maxPlayers = lobby.maxJugadores;

            // Create lobby rectangle
            QLabel *lobbyLabel = new QLabel(QString::fromStdString(lobbyName), this);
            lobbyLabel->setStyleSheet(
                "QLabel {"
                "color: #ced4da;"
                "border: 0px solid #555555;"
                "font-size: 32px;"
                "}"
            );
            lobbyLabel->setFont(customFont);
            lobbyLabel->setFixedWidth(240);  // Set fixed size

            QLabel *playersLabel = new QLabel(QString::number(players) + "/" + QString::number(maxPlayers), this);
            playersLabel->setStyleSheet(
                "QLabel {"
                "color: #ced4da;"
                "border: 0px solid #555555;"
                "font-size: 32px;"
                "}"
            );
            playersLabel->setFont(customFont);
            playersLabel->setFixedWidth(240);  // Set fixed size

            QWidget *lobbyWidget = new QWidget(this);
            lobbyWidget->setStyleSheet(
                "background-color: rgba(0, 0, 0, 0);"
                "color: #ced4da;"
                "font-size: 32px;"
                "border: 2px solid #ced4da;"
                "border-radius: 10px;"
                "padding: 10px;"
            );
            // add join button 
            QPushButton *joinButton = new QPushButton("Join", this);
            joinButton->setStyleSheet(
                "QPushButton {"
                "background-color: rgba(240, 140, 0, 100);"        
                "color: #ced4da;"                     
                "font-size: 32px;"                  
                "border: 0px solid #555555;"        
                "border-radius: 15px;"              
                "padding: 10px;"                    
                "text-align: center;"               
                "}"
                "QPushButton:hover {"
                "background-color: rgba(232, 89, 12, 100);"
                "}"
            );
            if (players == maxPlayers) {
                joinButton->setDisabled(true);
                // change the buttons message to "Full"
                joinButton->setText("Full");
                joinButton->setStyleSheet(
                    "QPushButton {"
                    "background-color: rgba(232, 89, 12, 100);"        
                    "color: #ced4da;"                     
                    "font-size: 32px;"                  
                    "border: 0px solid #555555;"        
                    "border-radius: 15px;"              
                    "padding: 10px;"                    
                    "text-align: center;"               
                    "}"
                );
            }
            joinButton->setFont(customFont);
            joinButton->setFixedWidth(100);  // Set fixed size
            connect(joinButton, &QPushButton::clicked, this, [this, lobby]() { onJoinButtonClicked(lobby.idLobby); });

            lobbyWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
            QHBoxLayout *lobbyLayout = new QHBoxLayout(lobbyWidget);
            lobbyLayout->addWidget(lobbyLabel);
            lobbyLayout->addWidget(playersLabel);
            lobbyLayout->addWidget(joinButton);
            lobbyWidget->setLayout(lobbyLayout);
            scrollLayout->addWidget(lobbyWidget);
            lobbyWidgets.push_back(lobbyWidget);
        }
    }
}

void JoinLobbyScreen::onJoinButtonClicked(uint8_t lobby_id) {
    keyPressSound->play();
    std::string player_name = "player";
    for (auto lobby : lobbies) {
        if (lobby.idLobby == lobby_id) {
            player_name += std::to_string(static_cast<int>(lobby.cantidadJugadores+1));
            std::cout << "Player name: " << player_name << std::endl;
            break;
        }
    }
    send_queue->push(new ChooseLobbyMsg(lobby_id, player_name));
    GenericMsg* msg = recv_queue->pop();
    if (msg->get_header() == GenericMsg::MsgTypeHeader::EVERYTHING_OK_MSG) {
        emit switchToLobbyScreen();
    } else if (msg->get_header() == GenericMsg::MsgTypeHeader::ERROR_MSG) {
        ErrorMsg* errorMsg = dynamic_cast<ErrorMsg*>(msg);
        // draw error message
        QLabel *errorLabel = new QLabel(errorMsg->get_error_msg().c_str(), this);
        errorLabel->setStyleSheet("QLabel { color: #800404; font-size: 24px; }");
        errorLabel->setFont(QFont(customFont));
        errorLabel->setGeometry(710, 850, 500, 100);
        errorLabel->setAlignment(Qt::AlignCenter);
        errorLabel->show();
        QTimer::singleShot(2000, errorLabel, &QObject::deleteLater);
    }
}
