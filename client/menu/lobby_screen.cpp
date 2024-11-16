#include "lobby_screen.h"


LobbyScreen::LobbyScreen(Queue<GenericMsg*>* send_queue, Queue<GenericMsg*>* recv_queue) : send_queue(send_queue), recv_queue(recv_queue), running(true) {
    setWindowState(Qt::WindowFullScreen); // Set window to full-screen mode
    setFocusPolicy(Qt::StrongFocus);
    // Load key press sound
    keyPressSound = new QSound("assets/Retro3.wav", this);
    // Load custom font
    int fontId = QFontDatabase::addApplicationFont("assets/HomeVideo-Regular.ttf");
    QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
    customFont = QFont(fontFamily);

    // Add Exit Lobby button
    QPushButton *exitLobbyButton = new QPushButton("Exit Lobby", this);
    exitLobbyButton->setStyleSheet(
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
    exitLobbyButton->setFont(customFont);
    exitLobbyButton->setGeometry(600, 150, 350, 60);

    connect(exitLobbyButton, &QPushButton::clicked, this, &LobbyScreen::onExitLobbyButtonClicked);

    recv_thread = std::thread(&LobbyScreen::processIncomingMessages, this);
}

void LobbyScreen::processIncomingMessages() {
    while (running) {
        GenericMsg* msg = recv_queue->pop();
        if (msg->get_header() == GenericMsg::MsgTypeHeader::INFO_LOBBY_MSG) {
            InfoLobbyMsg* info_lobby_msg = dynamic_cast<InfoLobbyMsg*>(msg);
            lobby_id = info_lobby_msg->get_lobby_id();
            players = info_lobby_msg->get_players();
            running = false;
            // if i am not in the lobby, running = false
            for (auto& player: players) {
                if (player.nombre == myPlayerName) {
                    running = true;
                    break;
                }
            }
            emit playersUpdated();
        } else if (msg->get_header() == GenericMsg::MsgTypeHeader::PLAYER_INFO_MSG) {
            PlayerInfoMsg* player_info_msg = dynamic_cast<PlayerInfoMsg*>(msg);
            myPlayerName = player_info_msg->get_player_name();
            std::cout << "My player name: " << myPlayerName << std::endl;
        }
    }
}


void LobbyScreen::updatePlayersInLobby() {

}


void LobbyScreen::onReadyButtonClicked() {
    keyPressSound->play();
}

void LobbyScreen::onSaveButtonClicked(std::string player_name) {
    keyPressSound->play();

}

void LobbyScreen::onExitLobbyButtonClicked() {
    keyPressSound->play();
    std::cout << "Trying to send ExitFromLobbyMsg" << std::endl;
    ExitFromLobbyMsg* exit_lobby_msg = new ExitFromLobbyMsg(myPlayerName);
    send_queue->push(exit_lobby_msg);
    stopProcessing();

    emit switchToJoinLobbyScreen();
}

void LobbyScreen::stopProcessing() {
    running = false;
    if (recv_thread.joinable()) {
        recv_thread.join();
    }
}

LobbyScreen::~LobbyScreen() {
    stopProcessing();
}