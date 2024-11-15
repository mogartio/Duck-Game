#include "lobby_screen.h"
#include <thread>

LobbyScreen::LobbyScreen(Queue<GenericMsg*>* send_queue, Queue<GenericMsg*>* recv_queue) : send_queue(send_queue), recv_queue(recv_queue) {
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

    connect(this, &LobbyScreen::playersUpdated, this, &LobbyScreen::updatePlayersInLobby);

    std::thread(&LobbyScreen::processIncomingMessages, this).detach();

}

void LobbyScreen::processIncomingMessages() {
    while (true) {
        GenericMsg* msg = recv_queue->pop();
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
        } else if (msg->get_header() == GenericMsg::MsgTypeHeader::PLAYER_INFO_MSG) {
            PlayerInfoMsg* player_info_msg = dynamic_cast<PlayerInfoMsg*>(msg);
            myPlayerName = player_info_msg->get_player_name();
        }
    }
}


void LobbyScreen::updatePlayersInLobby() {
    std::map<std::string, QString> playerNameMap;
    for (auto player : players) {
        std::string player_name = player.nombre;
        if (playerNameEdits.find(player_name) != playerNameEdits.end()) {
            playerNameMap[player_name] = playerNameEdits[player_name]->text();
        }
    }

    // Clear scroll area
    QLayoutItem* item;
    while ((item = scrollLayout->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }
    // Draw players in lobby
    for (auto player : players) {
        std::string player_name = player.nombre;
        // Create a QLineEdit to be able to edit the player name. IF the player is myself the input is enabled and the save icon is visible. Otherwise the input is disabled and the save icon is hidden.
        // Create QLineEdit and set its text from the map if it exists
        QLineEdit *playerLabel = new QLineEdit(QString::fromStdString(player_name), this);
        if (playerNameMap.find(player_name) != playerNameMap.end()) {
            playerLabel->setText(playerNameMap[player_name]);
        }
        playerLabel->setStyleSheet(
            "QLineEdit {"
            "background-color: rgba(0, 0, 0, 0);"
            "color: #ced4da;"
            "font-size: 32px;"
            "border: 0px solid #555555;"
            "border-radius: 15px;"
            "padding: 10px;"
            "text-align: center;"
            "}"
            "QLineEdit:disabled {"
            "background-color: rgba(0, 0, 0, 0);"
            "color: #ced4da;"
            "font-size: 32px;"
            "border: 0px solid #555555;"
            "border-radius: 15px;"
            "padding: 10px;"
            "text-align: center;"
            "}"
        );
        playerLabel->setFont(customFont);
        playerLabel->setFixedWidth(200);
        if (player_name != myPlayerName) {
            playerLabel->setDisabled(true);
        }

        playerNameEdits[player_name] = playerLabel;
        
        // Create save button 
        QPushButton *saveButton = new QPushButton(this);
        saveButton->setIcon(QIcon(*saveIcon));
        saveButton->setIconSize(QSize(50, 50));
        saveButton->setStyleSheet("border: none;");
        saveButton->setFixedWidth(50);
        // if the player is myself, the save button is visible
        if (player_name == myPlayerName) {
            saveButton->setVisible(true);
        } else {
            saveButton->setVisible(false);
        }

        connect(saveButton, &QPushButton::clicked, [this, player_name](){onSaveButtonClicked(player_name);});

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

        connect(readyButton, &QPushButton::clicked, this, &LobbyScreen::onReadyButtonClicked);

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
        playerLayout->addWidget(saveButton, 0, Qt::AlignLeft);
        playerLayout->addWidget(duckLabel);
        playerLayout->addWidget(readyButton);
        playerWidget->setLayout(playerLayout);
        scrollLayout->addWidget(playerWidget);
    }
}


void LobbyScreen::onReadyButtonClicked() {
    keyPressSound->play();
    std::cout << "Ready button clicked" << std::endl;
}

void LobbyScreen::onSaveButtonClicked(std::string player_name) {
    keyPressSound->play();
    if (playerNameEdits.find(player_name) != playerNameEdits.end()) {
        std::string new_name = playerNameEdits[player_name]->text().toStdString();
        if (new_name != player_name) {
            uint8_t color = 0;
            for (auto player : players) {
                if (player.nombre == player_name) {
                    color = player.color;
                }
            }
            // update player name
            myPlayerName = new_name;
            playerNameEdits[player_name]->setText(QString::fromStdString(new_name));
            playerNameEdits[new_name] = playerNameEdits[player_name];
            playerNameEdits.erase(player_name);
            CustomizedPlayerInfoMsg* msg = new CustomizedPlayerInfoMsg(lobby_id, color, player_name, new_name);
            send_queue->push(msg);
        }
    }
}