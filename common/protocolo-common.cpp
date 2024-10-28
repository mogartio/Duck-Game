#include "protocolo-common.h"

#include <arpa/inet.h>

void ProtocoloCommon::send(GenericMsg* msg) { msg->accept_send(*this); }

GenericMsg* ProtocoloCommon::receive() {
    uint8_t header = recv_u_int8_t();
    GenericMsg* msg = recv_handlers[static_cast<GenericMsg::MsgTypeHeader>(header)]();
    msg->accept_recv(*this);
    return msg;
}

void ProtocoloCommon::sendCabecera(const GenericMsg& msg) {
    uint8_t header = msg.get_header();
    send_u_int8_t(header);
}

ProtocoloCommon::ProtocoloCommon(Socket& socket): socket(socket), was_closed(false) {
    recv_handlers.emplace(GenericMsg::MsgTypeHeader::CUSTOMIZED_PLAYER_INFO_MSG,
                          [this]() { return new CustomizedPlayerInfoMsg(); });
    recv_handlers.emplace(GenericMsg::MsgTypeHeader::VIEW_LOBBIES_MSG,
                          [this]() { return new ViewLobbiesMsg(); });
    recv_handlers.emplace(GenericMsg::MsgTypeHeader::CHOOSE_LOBBY_MSG,
                          [this]() { return new ChooseLobbyMsg(); });
    recv_handlers.emplace(GenericMsg::MsgTypeHeader::CREATE_LOBBY_MSG,
                          [this]() { return new CreateLobbyMsg(); });
    recv_handlers.emplace(GenericMsg::MsgTypeHeader::GO_BACK_MSG,
                          [this]() { return new GoBackMsg(); });
    recv_handlers.emplace(GenericMsg::MsgTypeHeader::EXIT_FROM_LOBBY_MSG,
                          [this]() { return new ExitFromLobbyMsg(); });
    recv_handlers.emplace(GenericMsg::MsgTypeHeader::START_GAME_MSG,
                          [this]() { return new StartGameMsg(); });
    recv_handlers.emplace(GenericMsg::MsgTypeHeader::PICKUP_DROP_MSG,
                          [this]() { return new PickupDropMsg(); });
    recv_handlers.emplace(GenericMsg::MsgTypeHeader::MOVE_LEFT_MSG,
                          [this]() { return new MoveLeftMsg(); });
    recv_handlers.emplace(GenericMsg::MsgTypeHeader::MOVE_RIGHT_MSG,
                          [this]() { return new MoveRightMsg(); });
    recv_handlers.emplace(GenericMsg::MsgTypeHeader::JUMP_MSG, [this]() { return new JumpMsg(); });
    recv_handlers.emplace(GenericMsg::MsgTypeHeader::PLAY_DEAD_MSG,
                          [this]() { return new PlayDeadMsg(); });
    recv_handlers.emplace(GenericMsg::MsgTypeHeader::SHOOT_MSG,
                          [this]() { return new ShootMsg(); });
    recv_handlers.emplace(GenericMsg::MsgTypeHeader::SEND_LOBBIES_LIST_MSG,
                          [this]() { return new SendLobbiesListMsg(); });
    recv_handlers.emplace(GenericMsg::MsgTypeHeader::EVERYTHING_OK_MSG,
                          [this]() { return new EverythingOkMsg(); });
    recv_handlers.emplace(GenericMsg::MsgTypeHeader::ERROR_MSG,
                          [this]() { return new ErrorMsg(); });
    recv_handlers.emplace(GenericMsg::MsgTypeHeader::SEND_MAP_MSG,
                          [this]() { return new SendMapMsg(); });
    recv_handlers.emplace(GenericMsg::MsgTypeHeader::GAME_ENDED_MSG,
                          [this]() { return new GameEndedMsg(); });
    recv_handlers.emplace(GenericMsg::MsgTypeHeader::WINNER_MSG,
                          [this]() { return new WinnerMsg(); });
}

void ProtocoloCommon::chk_closed_andif_fail(const char error_ms[]) const {
    if (was_closed) {
        throw SocketClosedError(error_ms);
    }
}

void ProtocoloCommon::send_u_int8_t(u_int8_t& data) {
    socket.sendall(&data, sizeof(u_int8_t), &was_closed);
    chk_closed_andif_fail("send u_int8_t");
}

u_int8_t ProtocoloCommon::recv_u_int8_t() {
    u_int8_t data;
    socket.recvall(&data, sizeof(u_int8_t), &was_closed);
    chk_closed_andif_fail("recv u_int8_t");
    return data;
}

void ProtocoloCommon::send_u_int16_t(u_int16_t& data) {
    u_int16_t data_net = htons(data);
    socket.sendall(&data_net, sizeof(u_int16_t), &was_closed);
    chk_closed_andif_fail("send u_int16_t");
}

u_int16_t ProtocoloCommon::recv_u_int16_t() {
    u_int16_t data_net;
    socket.recvall(&data_net, sizeof(u_int16_t), &was_closed);
    chk_closed_andif_fail("recv u_int16_t");
    return ntohs(data_net);
}

void ProtocoloCommon::send_string(std::string& data) {
    u_int16_t size = data.size();
    send_u_int16_t(size);
    socket.sendall(data.data(), data.size(), &was_closed);
    chk_closed_andif_fail("send string");
}

std::string ProtocoloCommon::recv_string() {
    u_int16_t size = recv_u_int16_t();
    std::string data(size, 0);
    socket.recvall(data.data(), size, &was_closed);
    chk_closed_andif_fail("recv string");
    data.resize(size);
    return data;
}
