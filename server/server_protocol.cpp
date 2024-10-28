#include "server_protocol.h"

#include <string>
#include <cstdint>

ServerProtocol::ServerProtocol(Socket& skt): ProtocoloCommon(skt) {
    recv_handlers[GenericMsg::typeMsg::LOBBY_MESSAGE] = {
            {LobbyMsg::lobbyType::EXAMPLE,
             [this]() {
                 ExampleMsg* msg;
                 this->handle_recv(&msg);
                 return msg;
             }},
            {LobbyMsg::lobbyType::VIEW_LOBBIES,
             [this]() {
                 ViewLobbiesMsg* msg;
                 this->handle_recv(&msg);
                 return msg;
             }},
            {LobbyMsg::lobbyType::JOINED_LOBBY,
             [this]() {
                 JoinedLobbyMsg* msg;
                 this->handle_recv(&msg);
                 return msg;
             }},
            {LobbyMsg::lobbyType::CREATE_LOBBY,
             [this]() {
                 CreateLobbyMsg* msg;
                 this->handle_recv(&msg);
                 return msg;
             }},
            {LobbyMsg::lobbyType::EXIT_FROM_LOBBY,
             [this]() {
                 ExitMsg* msg;
                 this->handle_recv(&msg);
                 return msg;
             }},
            {LobbyMsg::lobbyType::START_GAME, [this]() {
                 StartGameMsg* msg;
                 this->handle_recv(&msg);
                 return msg;
             }}};

    recv_handlers[GenericMsg::typeMsg::CUSTOMIZED_INFO] = {
            {CustomizedMsg::customizedType::CUSTOMIZER_PLAYER, [this]() {
                 CustomizedPlayerInfoMsg* msg;
                 this->handle_recv(&msg);
                 return msg;
             }}};

    recv_handlers[GenericMsg::typeMsg::GAME_MESSAGE] = {{GameMsg::gameType::PICKUP_DROP_ITEM,
                                                         [this]() {
                                                             PickupDropItemMsg* msg;
                                                             this->handle_recv(&msg);
                                                             return msg;
                                                         }},
                                                        {GameMsg::gameType::START_MOVE_LEFT,
                                                         [this]() {
                                                             StartMoveLeftMsg* msg;
                                                             this->handle_recv(&msg);
                                                             return msg;
                                                         }},
                                                        {GameMsg::gameType::STOP_MOVE_LEFT,
                                                         [this]() {
                                                             StopMoveLeftMsg* msg;
                                                             this->handle_recv(&msg);
                                                             return msg;
                                                         }},
                                                        {GameMsg::gameType::START_MOVE_RIGHT,
                                                         [this]() {
                                                             StartMoveRightMsg* msg;
                                                             this->handle_recv(&msg);
                                                             return msg;
                                                         }},
                                                        {GameMsg::gameType::STOP_MOVE_RIGHT,
                                                         [this]() {
                                                             StopMoveRightMsg* msg;
                                                             this->handle_recv(&msg);
                                                             return msg;
                                                         }},
                                                        {GameMsg::gameType::JUMP,
                                                         [this]() {
                                                             JumpMsg* msg;
                                                             this->handle_recv(&msg);
                                                             return msg;
                                                         }},
                                                        {GameMsg::gameType::PLAY_DEAD,
                                                         [this]() {
                                                             PlayDeadMsg* msg;
                                                             this->handle_recv(&msg);
                                                             return msg;
                                                         }},
                                                        {GameMsg::gameType::SHOOT, [this]() {
                                                             ShootMsg* msg;
                                                             this->handle_recv(&msg);
                                                             return msg;
                                                         }}};
}


void ServerProtocol::handle_send(const EverythingOkey& msg) { 
    sendCabecera(msg); 
    uint16 msg_size = recv_u_int16_t();
    string str = rand
    msg.set_data(str);
}

void ServerProtocol::handle_send(const SomethingWrong& msg) { sendCabecera(msg); }

void ServerProtocol::handle_recv(ExampleMsg** msg) {
    std::string msg_str = recv_string();
    *msg = new ExampleMsg(msg_str);
}

void ServerProtocol::handle_recv(ViewLobbiesMsg** msg) { *msg = new ViewLobbiesMsg(); }

void ServerProtocol::handle_recv(JoinedLobbyMsg** msg) { *msg = new JoinedLobbyMsg(); }

void ServerProtocol::handle_recv(CreateLobbyMsg** msg) { *msg = new CreateLobbyMsg(); }

void ServerProtocol::handle_recv(ExitMsg** msg) { *msg = new ExitMsg(); }

void ServerProtocol::handle_recv(StartGameMsg** msg) { *msg = new StartGameMsg(); }

void ServerProtocol::handle_send(const ExampleMsg& msg) {
    sendCabecera(msg);
    std::string data = msg.getData();
    send_string(data);
}

void ServerProtocol::handle_send(const LobbyListMsg& msg) { sendCabecera(msg); }

void ServerProtocol::handle_recv(CustomizedPlayerInfoMsg** msg) {
    *msg = new CustomizedPlayerInfoMsg();
}

void ServerProtocol::handle_recv(PickupDropItemMsg** msg) { *msg = new PickupDropItemMsg(); }

void ServerProtocol::handle_recv(StartMoveLeftMsg** msg) { *msg = new StartMoveLeftMsg(); }

void ServerProtocol::handle_recv(StopMoveLeftMsg** msg) { *msg = new StopMoveLeftMsg(); }

void ServerProtocol::handle_recv(StartMoveRightMsg** msg) { *msg = new StartMoveRightMsg(); }

void ServerProtocol::handle_recv(StopMoveRightMsg** msg) { *msg = new StopMoveRightMsg(); }

void ServerProtocol::handle_recv(JumpMsg** msg) { *msg = new JumpMsg(); }

void ServerProtocol::handle_recv(PlayDeadMsg** msg) { *msg = new PlayDeadMsg(); }

void ServerProtocol::handle_recv(ShootMsg** msg) { *msg = new ShootMsg(); }

void ServerProtocol::handle_send(const PlayerInfoMsg& msg) { sendCabecera(msg); }

void ServerProtocol::handle_send(const FinishGameMsg& msg) { sendCabecera(msg); }

void ServerProtocol::handle_send(const WinnerMsg& msg) { sendCabecera(msg); }
