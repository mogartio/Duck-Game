#include "host_lobby_screen.h"

HostLobbyScreen::HostLobbyScreen(Queue<std::shared_ptr<GenericMsg>>* send_queue, Queue<std::shared_ptr<GenericMsg>>* recv_queue, std::list<std::string>* local_players) : send_queue(send_queue), recv_queue(recv_queue), local_players(local_players), running(true) {
    setWindowState(Qt::WindowFullScreen); // Set window to full-screen mode
    setFocusPolicy(Qt::StrongFocus);
    // Load key press sound
    keyPressSound = std::make_unique<QSound>("assets/Retro3.wav");
    // Load custom font
    int fontId = QFontDatabase::addApplicationFont("assets/HomeVideo-Regular.ttf");
    QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
    customFont = QFont(fontFamily);
    // Create black opaque background rectangle
    RoundedRectangle * baseRectangle = new RoundedRectangle(this, 200, 100, 1000, 700, QColor(0,0,0, 100), QColor(0,0,0, 100));
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
    localPlayerButton->setGeometry(800, 150, 350, 60);
    // Add scroll area 
    scrollArea = std::make_unique<QScrollArea>(this);
    scrollArea->setGeometry(250, 230, 900, 700);
    scrollArea->setWidgetResizable(true);
    scrollArea->setStyleSheet("background-color: rgba(0,0,0,100);");

    scrollWidget = std::make_unique<QWidget>();
    scrollWidget->setStyleSheet("background: transparent;");
    scrollArea->setWidget(scrollWidget.get());

    scrollLayout = std::make_unique<QVBoxLayout>(scrollWidget.get());
    scrollLayout->setSpacing(20); // Set spacing between widgets
    scrollWidget->setLayout(scrollLayout.get());
    scrollLayout->setAlignment(Qt::AlignTop);

    connect(localPlayerButton, &QPushButton::clicked, this, &HostLobbyScreen::onAddLocalPlayerButtonClicked);

    // Load save icon image
    saveIcon = std::make_unique<QPixmap>("assets/Floppy-Drive.png");

    // Load ducks images
    ducks_images.push_back(std::make_pair(GenericMsg::DuckColor::WHITE, std::make_unique<QPixmap>("assets/white_duck_head.png")));
    ducks_images.push_back(std::make_pair(GenericMsg::DuckColor::YELLOW, std::make_unique<QPixmap>("assets/yellow_duck_head.png")));
    ducks_images.push_back(std::make_pair(GenericMsg::DuckColor::ORANGE, std::make_unique<QPixmap>("assets/orange_duck_head.png")));
    ducks_images.push_back(std::make_pair(GenericMsg::DuckColor::GREY, std::make_unique<QPixmap>("assets/grey_duck_head.png")));

    // Scale images
    for (auto& duck : ducks_images) {
        *duck.second = duck.second->scaled(100, 100, Qt::KeepAspectRatio);
    }

    // Draw start game button
    startGameButton = new QPushButton("Start\nGame", this);
    startGameButton->setStyleSheet(
        "QPushButton {"
        "background-color: rgba(235, 64, 52, 100);" // Darker color for READY state
        "color: #ced4da;"                     
        "font-size: 65px;"                  
        "border: 0px solid #555555;"        
        "border-radius: 25px;"              
        "padding: 10px;"                    
        "text-align: center;"               
        "}"
    );
    startGameButton->setFont(customFont);
    startGameButton->setGeometry(1400, 440, 300, 200);
    // initialially disable start game button
    startGameButton->setEnabled(false);

    connect(startGameButton, &QPushButton::clicked, this, &HostLobbyScreen::onStartGameButtonClicked);

    connect(this, &HostLobbyScreen::playersUpdated, this, &HostLobbyScreen::updatePlayersInLobby);

    recv_thread = std::thread(&HostLobbyScreen::processIncomingMessages, this);
}

void HostLobbyScreen::processIncomingMessages() {
    while (running) {
        std::shared_ptr<GenericMsg> msg = recv_queue->pop();
        if (msg->get_header() == GenericMsg::MsgTypeHeader::INFO_LOBBY_MSG) {
            // Ensure dynamic_cast is successful
            std::shared_ptr<InfoLobbyMsg> info_lobby_msg = std::dynamic_pointer_cast<InfoLobbyMsg>(msg);
            if (info_lobby_msg) {
                lobby_id = info_lobby_msg->get_lobby_id();
                std::lock_guard<std::mutex> lock(players_mutex);
                players = info_lobby_msg->get_players();
                emit playersUpdated();
            } else {
                // Handle the error if dynamic_cast fails
                std::cerr << "Failed to cast to InfoLobbyMsg" << std::endl;
            }
        } else if (msg->get_header() == GenericMsg::MsgTypeHeader::PLAYER_INFO_MSG) {
            // Ensure dynamic_cast is successful
            std::shared_ptr<PlayerInfoMsg> player_info_msg = std::dynamic_pointer_cast<PlayerInfoMsg>(msg);
            if (player_info_msg) {
                myLocalPlayerName = player_info_msg->get_player_name();
            } else {
                // Handle the error if dynamic_cast fails
                std::cerr << "Failed to cast to PlayerInfoMsg" << std::endl;
            }
        }
    }
}


void HostLobbyScreen::updatePlayersInLobby() {
    std::lock_guard<std::mutex> lock(players_mutex);
    // Clear scroll area
    QLayoutItem* item;
    while ((item = scrollLayout->takeAt(0)) != nullptr) {
        if (item->widget()) {
            delete item->widget();
        }
        delete item;
    }


    // Draw players in lobby
    for (auto player : players) {
        std::string player_name = player.nombre;

        QWidget *editContainer = new QWidget(this);
        QHBoxLayout *layout = new QHBoxLayout(editContainer);
        layout->setContentsMargins(5,5,5,5);
        layout->setSpacing(5);

        QLineEdit *playerLabel = new QLineEdit(this);
        playerLabel->setText(player_name.c_str());
        playerLabel->setStyleSheet(
            "QLineEdit {"
            "color: #ced4da;"
            "font-size: 32px;"
            "border: 0px solid #555555;"
            "}"
        );
        playerLabel->setFont(customFont);
        playerLabel->setFixedWidth(300);

        // Restore the text from the map if it exists
        if (playerEdits.find(player_name) != playerEdits.end()) {
            playerLabel->setText(playerEdits[player_name].c_str());
        }

        // Enable or disable the QLineEdit based on the player name
        if (player_name == myPlayerName || player_name == myLocalPlayerName) {
            playerLabel->setEnabled(true);
        } else {
            playerLabel->setEnabled(false);
        }
        
        // Update the map whenever the text changes
        connect(playerLabel, &QLineEdit::textChanged, [this, player_name](const QString &text) {
            playerEdits[player_name] = text.toStdString();
        });

        // Create save button 
        QPushButton *saveButton = new QPushButton(this);
        saveButton->setIcon(QIcon(*saveIcon));
        saveButton->setIconSize(QSize(50, 50));
        saveButton->setStyleSheet("border: none;");
        saveButton->setFixedWidth(50);

        // if the player is myself or my local player, the save button is visible
        if (player_name == myPlayerName || player_name == myLocalPlayerName) {
            saveButton->setVisible(true);
            editContainer->setStyleSheet(
                "QWidget {"
                "border: 1px solid #ced4da;"
                "border-radius: 10px;"
                "padding: 5px;"
                "}"
            );
        } else {
            saveButton->setVisible(false);
            editContainer->setStyleSheet("border: 0px solid #ced4da;");
        }


        connect(saveButton, &QPushButton::clicked, [this, player_name, playerLabel]() {
        // Check if the QLineEdit is empty
        if (playerLabel->text().isEmpty()) {
            playerLabel->setText(QString::fromStdString(playerEdits[player_name]));
        }
        // Save the current text
        onSaveButtonClicked(player_name);
        // Remove the saved text from the map after saving
        playerEdits.erase(player_name);
        });

        layout->addWidget(playerLabel);
        layout->addWidget(saveButton);

        QLabel *duckLabel = new QLabel(this);
        uint8_t color = player.color;
        for (const auto& duck : ducks_images) {
            if (duck.first == color) {
                QPixmap *duckImage = duck.second.get();
                duckLabel->setPixmap(*duckImage);
                duckLabel->setFixedWidth(100);
                duckLabel->setStyleSheet("border: 0px solid #555555;");
                break; // Exit the loop once the correct duck image is found
            }
        }
        // create ready button
        QPushButton *readyButton = new QPushButton("Ready", this);

        uint8_t is_ready = player.is_ready;

        if (is_ready == GenericMsg::PlayerReadyState::READY) {
            readyButton->setStyleSheet(
                "QPushButton {"
                "background-color: rgba(47, 133, 28, 100);" // Darker color for READY state
                "color: #ced4da;"                     
                "font-size: 32px;"                  
                "border: 0px solid #555555;"        
                "border-radius: 15px;"              
                "padding: 10px;"                    
                "text-align: center;"               
                "}"
            );
        } else {
            readyButton->setStyleSheet(
                "QPushButton {"
                "background-color: rgba(235, 64, 52, 100);" // Lighter color for not READY state
                "color: #ced4da;"                     
                "font-size: 32px;"                  
                "border: 0px solid #555555;"        
                "border-radius: 15px;"              
                "padding: 10px;"                    
                "text-align: center;"               
                "}"
                "QPushButton:hover {"
                "background-color: rgba(184, 48, 39, 100);" // Darker color on hover
                "}"
            );
        }
        readyButton->setFont(customFont);
        readyButton->setFixedWidth(130);
        // if it isn't myself or my local player, the ready button is disabled
        if (player_name != myPlayerName && player_name != myLocalPlayerName) {
            readyButton->setEnabled(false);
        } else {
            readyButton->setEnabled(true);
        }


        connect(readyButton, &QPushButton::clicked, [this, player_name]() { onReadyButtonClicked(player_name); });
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
        
        playerLayout->addWidget(editContainer, 0, Qt::AlignLeft);
        playerLayout->addWidget(duckLabel, 0, Qt::AlignRight);
        playerLayout->addWidget(readyButton, 0, Qt::AlignRight);
        playerWidget->setLayout(playerLayout);
        scrollLayout->addWidget(playerWidget);
    }
    updateStartGameButton();
}


void HostLobbyScreen::updateStartGameButton() {
    // update start game button if necessary
    for (auto player : players) {
        if (player.is_ready == GenericMsg::PlayerReadyState::NOT_READY || players.size() < 2) {
            startGameButton->setStyleSheet(
                "QPushButton {"
                "background-color: rgba(235, 64, 52, 100);" // Darker color for READY state
                "color: #ced4da;"                     
                "font-size: 65px;"                  
                "border: 0px solid #555555;"        
                "border-radius: 25px;"              
                "padding: 10px;"                    
                "text-align: center;"               
                "}"
            );
            startGameButton->setEnabled(false);
            return;
        }
    }
    startGameButton->setStyleSheet(
        "QPushButton {"
        "background-color: rgba(47, 133, 28, 100);" // Darker color for READY state
        "color: #ced4da;"                     
        "font-size: 65px;"                  
        "border: 0px solid #555555;"        
        "border-radius: 25px;"              
        "padding: 10px;"                    
        "text-align: center;"               
        "}"
        "QPushButton:hover {"
        "background-color: rgba(39, 112, 22, 100);" // Darker color on hover
        "}"
    );
    startGameButton->setEnabled(true);
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
        // ExitFromLobbyMsg* exit_from_lobby_msg = new ExitFromLobbyMsg(myLocalPlayerName);
        std::shared_ptr<ExitFromLobbyMsg> exit_from_lobby_msg = std::make_shared<ExitFromLobbyMsg>(myLocalPlayerName);
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
        myLocalPlayerName = local_player;
        // ChooseLobbyMsg* choose_lobby_msg = new ChooseLobbyMsg(lobby_id, local_player);
        std::shared_ptr<ChooseLobbyMsg> choose_lobby_msg = std::make_shared<ChooseLobbyMsg>(lobby_id, local_player);
        send_queue->push(choose_lobby_msg);
    }

}


void HostLobbyScreen::onReadyButtonClicked(std::string player_name) {
    keyPressSound->play();
    uint8_t color; 
    uint8_t is_ready;
    for (auto player : players) {
        if (player.nombre == player_name) {
            color = player.color;
            is_ready = player.is_ready;
            break;
        } 
    }
    if (is_ready == GenericMsg::PlayerReadyState::NOT_READY) {
        is_ready = GenericMsg::PlayerReadyState::READY;
    } else {
        is_ready = GenericMsg::PlayerReadyState::NOT_READY;
    }

    // CustomizedPlayerInfoMsg* customized_player_info_msg = new CustomizedPlayerInfoMsg(lobby_id, color, player_name, player_name, is_ready);
    std::shared_ptr<CustomizedPlayerInfoMsg> customized_player_info_msg = std::make_shared<CustomizedPlayerInfoMsg>(lobby_id, color, player_name, player_name, is_ready);
    send_queue->push(customized_player_info_msg);
}


void HostLobbyScreen::onSaveButtonClicked(std::string player_name) {
    keyPressSound->play();
    // Send the updated player info
    std::string new_name = playerEdits[player_name];
    if (new_name.empty()) {
        return;
    }
    uint8_t color = 0;
    uint8_t is_ready = 0;
    for (auto player : players) {
        if (player.nombre == player_name) {
            color = player.color;
            is_ready = player.is_ready;
            break;
        }
    }
    // CustomizedPlayerInfoMsg* customized_player_info_msg = new CustomizedPlayerInfoMsg(lobby_id, color, player_name, new_name, is_ready);
    std::shared_ptr<CustomizedPlayerInfoMsg> customized_player_info_msg = std::make_shared<CustomizedPlayerInfoMsg>(lobby_id, color, player_name, new_name, is_ready);
    send_queue->push(customized_player_info_msg);
    if (player_name == myPlayerName) {
        myPlayerName = new_name;
    } else if (player_name == myLocalPlayerName) {
        myLocalPlayerName = new_name;
    }
}


void HostLobbyScreen::stopProcessing() {
    running = false;
    if (recv_thread.joinable()) {
        recv_thread.join();
    }
}


void HostLobbyScreen::onStartGameButtonClicked() {
    keyPressSound->play();
    // StartGameMsg* start_game_msg = new StartGameMsg();
    std::shared_ptr<StartGameMsg> start_game_msg = std::make_shared<StartGameMsg>();
    send_queue->push(start_game_msg);
    // set local players list
    local_players->push_back(myPlayerName);
    if (isLocalPlayerAdded) {
        local_players->push_back(myLocalPlayerName);
    }
    // stop thread
    stopProcessing();
    emit startingGame();
}


HostLobbyScreen::~HostLobbyScreen() {
    stopProcessing();
}