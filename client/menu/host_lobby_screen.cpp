#include "host_lobby_screen.h"
#include <thread>

HostLobbyScreen::HostLobbyScreen(Queue<GenericMsg*>* send_queue, Queue<GenericMsg*>* recv_queue) : send_queue(send_queue), recv_queue(recv_queue) {
    setWindowState(Qt::WindowFullScreen); // Set window to full-screen mode
    setFocusPolicy(Qt::StrongFocus);
    // Load key press sound
    keyPressSound = new QSound("assets/Retro3.wav", this);
    // Load custom font
    int fontId = QFontDatabase::addApplicationFont("assets/HomeVideo-Regular.ttf");
    QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
    customFont = QFont(fontFamily);
    // Create black opaque background rectangle
    RoundedRectangle * baseRectangle = new RoundedRectangle(this, 200, 100, 800, 700, QColor(0,0,0, 100), QColor(0,0,0, 100));
    baseRectangle->setParent(this);
    // Create game label
    QLabel *lobbyLabel = new QLabel("Players", this);
    lobbyLabel->setStyleSheet(
        "QLabel {"
        "color: #ced4da;"
        "font-size: 52px;"
        "}"
    );
    lobbyLabel->setFont(customFont);
    lobbyLabel->setGeometry(250, 130, 500, 100);
    // Add button
    localPlayerButton = new QPushButton("Add Local Player", this);
    localPlayerButton->setStyleSheet(
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
    localPlayerButton->setFont(customFont);
    localPlayerButton->setGeometry(600, 150, 350, 60);
    // Add scroll area 
    scrollArea = new QScrollArea(this);
    scrollArea->setGeometry(250, 230, 700, 700);
    scrollArea->setWidgetResizable(true);
    scrollArea->setStyleSheet("background-color: rgba(0,0,0,100);");

    scrollWidget = new QWidget();
    scrollWidget->setStyleSheet("background: transparent;");
    scrollArea->setWidget(scrollWidget);

    scrollLayout = new QVBoxLayout(scrollWidget);
    scrollLayout->setSpacing(20); // Set spacing between widgets
    scrollWidget->setLayout(scrollLayout);
    scrollLayout->setAlignment(Qt::AlignTop);

    connect(localPlayerButton, &QPushButton::clicked, this, &HostLobbyScreen::onAddLocalPlayerButtonClicked);

    // Load save icon image
    saveIcon = new QPixmap("assets/Floppy-Drive.png");

    // Load ducks images
    ducks_images.push_back(std::make_pair(GenericMsg::DuckColor::WHITE, new QPixmap("assets/white_duck_head.png")));
    ducks_images.push_back(std::make_pair(GenericMsg::DuckColor::YELLOW, new QPixmap("assets/yellow_duck_head.png")));
    ducks_images.push_back(std::make_pair(GenericMsg::DuckColor::ORANGE, new QPixmap("assets/orange_duck_head.png")));
    ducks_images.push_back(std::make_pair(GenericMsg::DuckColor::GREY, new QPixmap("assets/grey_duck_head.png")));

    // Scale images
    for (auto& duck : ducks_images) {
        *duck.second = duck.second->scaled(100, 100, Qt::KeepAspectRatio);
    }

    connect(this, &HostLobbyScreen::playersUpdated, this, &HostLobbyScreen::updatePlayersInLobby);

    std::thread(&HostLobbyScreen::processIncomingMessages, this).detach();

}

void HostLobbyScreen::processIncomingMessages() {
    while (true) {
        GenericMsg* msg = recv_queue->pop();
        std::cout << "MESSAGE IN THREAD 0x" << std::hex << std::setw(2) << std::setfill('0')<< static_cast<int>(msg->get_header())<< std::endl;
        if (msg->get_header() == GenericMsg::MsgTypeHeader::INFO_LOBBY_MSG) {
            InfoLobbyMsg* info_lobby_msg = dynamic_cast<InfoLobbyMsg*>(msg);
            lobby_id = info_lobby_msg->get_lobby_id();
            players = info_lobby_msg->get_players();
            // Update scroll area
            for (auto player : players) {
                std::cout << "Player name: " << player.nombre << " Color " << static_cast<int>(player.color) << std::endl;
            }
            emit playersUpdated();
        } else if (msg->get_header() == GenericMsg::MsgTypeHeader::ERROR_MSG) {
            ErrorMsg* error_msg = dynamic_cast<ErrorMsg*>(msg);
            std::string error = error_msg->get_error_msg();
            std::cout << error << std::endl;
        } else if (msg->get_header() == GenericMsg::MsgTypeHeader::EVERYTHING_OK_MSG) {
            continue;
        }
    }
}


void HostLobbyScreen::updatePlayersInLobby() {
    // Clear scroll area
    QLayoutItem* item;
    while ((item = scrollLayout->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }
    // Draw players in lobby
    for (auto player : players) {
        std::string player_name = player.nombre;
        QLabel *playerLabel = new QLabel(player_name.c_str(), this);
        playerLabel->setStyleSheet(
            "QLabel {"
            "color: #ced4da;"
            "font-size: 32px;"
            "border: 0px solid #555555;"
            "}"
        );
        playerLabel->setFont(customFont);
        playerLabel->setFixedWidth(250);

        // create duck image
        QLabel *duckLabel = new QLabel(this);
        uint8_t color = player.color;
        for (auto duck : ducks_images) {
            if (duck.first == color) {
                QPixmap *duckImage = duck.second;
                duckLabel->setPixmap(*duckImage);
                duckLabel->setFixedWidth(100);
                duckLabel->setStyleSheet("border: 0px solid #555555;");
            }
        }

        // create ready button
        QPushButton *readyButton = new QPushButton("Ready", this);
        readyButton->setStyleSheet(
            "QPushButton {"
            "background-color: rgba(21, 153, 43, 100);"        
            "color: #ced4da;"                     
            "font-size: 32px;"                  
            "border: 0px solid #555555;"        
            "border-radius: 15px;"              
            "padding: 10px;"                    
            "text-align: center;"               
            "}"
            "QPushButton:hover {"
            "background-color: rgba(15, 115, 32, 100);"
            "}"
        );
        readyButton->setFont(customFont);
        readyButton->setFixedWidth(130);

        connect(readyButton, &QPushButton::clicked, this, &HostLobbyScreen::onReadyButtonClicked);

        QWidget *playerWidget = new QWidget(this);
        playerWidget->setStyleSheet(
            "background-color: rgba(0, 0, 0, 0);"
            "color: #ced4da;"
            "font-size: 32px;"
            "border: 2px solid #ced4da;"
            "border-radius: 15px;"
            "padding: 10px;"
            "text-align: center;"
        );
        playerWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        QHBoxLayout *playerLayout = new QHBoxLayout(playerWidget);
        playerLayout->setContentsMargins(20, 10, 20, 10);
        playerLayout->addWidget(playerLabel, 0, Qt::AlignLeft);
        playerLayout->addWidget(duckLabel);
        playerLayout->addWidget(readyButton);
        playerWidget->setLayout(playerLayout);
        scrollLayout->addWidget(playerWidget);
    }
}


void HostLobbyScreen::onAddLocalPlayerButtonClicked() {
    keyPressSound->play();
    if (isLocalPlayerAdded) {
        // remove local player from lobby
        localPlayerButton->setText("Add Local Player");
        isLocalPlayerAdded = false;
        localPlayerButton->setStyleSheet(
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
        std::string name = "localPlayer";
        ExitFromLobbyMsg* exit_from_lobby_msg = new ExitFromLobbyMsg(name);
        send_queue->push(exit_from_lobby_msg);
    } else {
        // add local player to lobby
        localPlayerButton->setText("Remove Local Player");
        isLocalPlayerAdded = true;
        localPlayerButton->setStyleSheet(
            "QPushButton {"
            "background-color: rgba(232, 89, 12, 100);"        
            "color: #ced4da;"                     
            "font-size: 28px;"                  
            "border: 0px solid #555555;"        
            "border-radius: 15px;"              
            "padding: 10px;"                    
            "text-align: center;"               
            "}"
            "QPushButton:hover {"
            "background-color: rgba(240, 140, 0, 100);"
            "}"
        );
        std::string local_player = "localPlayer";
        ChooseLobbyMsg* choose_lobby_msg = new ChooseLobbyMsg(lobby_id, local_player);
        send_queue->push(choose_lobby_msg);
    }

}


void HostLobbyScreen::onReadyButtonClicked() {
    keyPressSound->play();
    std::cout << "Ready button clicked" << std::endl;
}