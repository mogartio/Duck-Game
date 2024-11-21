#include "protocolo-common.h"

#include <iostream>

#include <arpa/inet.h>

void ProtocoloCommon::send(std::shared_ptr<GenericMsg> msg) { msg->accept_send(*this); }

std::shared_ptr<GenericMsg> ProtocoloCommon::receive() {
    uint8_t header = recv_u_int8_t();
    std::shared_ptr<GenericMsg> msg =
            recv_handlers[static_cast<GenericMsg::MsgTypeHeader>(header)]();
    msg->accept_recv(*this);
    return msg;
}

ProtocoloCommon::ProtocoloCommon(Socket& socket): socket(socket), was_closed(false) {
    recv_handlers.emplace(GenericMsg::MsgTypeHeader::INFO_LOBBY_MSG,
                          [this]() { return std::make_shared<InfoLobbyMsg>(); });
    recv_handlers.emplace(GenericMsg::MsgTypeHeader::CUSTOMIZED_PLAYER_INFO_MSG,
                          [this]() { return std::make_shared<CustomizedPlayerInfoMsg>(); });
    recv_handlers.emplace(GenericMsg::MsgTypeHeader::VIEW_LOBBIES_MSG,
                          [this]() { return std::make_shared<ViewLobbiesMsg>(); });
    recv_handlers.emplace(GenericMsg::MsgTypeHeader::CHOOSE_LOBBY_MSG,
                          [this]() { return std::make_shared<ChooseLobbyMsg>(); });
    recv_handlers.emplace(GenericMsg::MsgTypeHeader::CREATE_LOBBY_MSG,
                          [this]() { return std::make_shared<CreateLobbyMsg>(); });
    recv_handlers.emplace(GenericMsg::MsgTypeHeader::GO_BACK_MSG,
                          [this]() { return std::make_shared<GoBackMsg>(); });
    recv_handlers.emplace(GenericMsg::MsgTypeHeader::EXIT_FROM_LOBBY_MSG,
                          [this]() { return std::make_shared<ExitFromLobbyMsg>(); });
    recv_handlers.emplace(GenericMsg::MsgTypeHeader::START_GAME_MSG,
                          [this]() { return std::make_shared<StartGameMsg>(); });
    recv_handlers.emplace(GenericMsg::MsgTypeHeader::PICKUP_DROP_MSG,
                          [this]() { return std::make_shared<PickupDropMsg>(); });
    recv_handlers.emplace(GenericMsg::MsgTypeHeader::START_ACTION_MSG,
                          [this]() { return std::make_shared<StartActionMsg>(); });
    recv_handlers.emplace(GenericMsg::MsgTypeHeader::STOP_ACTION_MSG,
                          [this]() { return std::make_shared<StopActionMsg>(); });
    recv_handlers.emplace(GenericMsg::MsgTypeHeader::SEND_LOBBIES_LIST_MSG,
                          [this]() { return std::make_shared<SendLobbiesListMsg>(); });
    recv_handlers.emplace(GenericMsg::MsgTypeHeader::EVERYTHING_OK_MSG,
                          [this]() { return std::make_shared<EverythingOkMsg>(); });
    recv_handlers.emplace(GenericMsg::MsgTypeHeader::ERROR_MSG,
                          [this]() { return std::make_shared<ErrorMsg>(); });
    recv_handlers.emplace(GenericMsg::MsgTypeHeader::SEND_MAP_MSG,
                          [this]() { return std::make_shared<SendMapMsg>(); });
    recv_handlers.emplace(GenericMsg::MsgTypeHeader::GAME_ENDED_MSG,
                          [this]() { return std::make_shared<GameEndedMsg>(); });
    recv_handlers.emplace(GenericMsg::MsgTypeHeader::WINNER_MSG,
                          [this]() { return std::make_shared<WinnerMsg>(); });
    recv_handlers.emplace(GenericMsg::MsgTypeHeader::UPDATED_PLAYER_INFO_MSG,
                          [this]() { return std::make_shared<UpdatedPlayerInfoMsg>(); });
    recv_handlers.emplace(GenericMsg::MsgTypeHeader::PROJECTILE_INFO_MSG,
                          [this]() { return std::make_shared<ProjectileInfoMsg>(); });
    recv_handlers.emplace(GenericMsg::MsgTypeHeader::PLAYER_INFO_MSG,
                          [this]() { return std::make_shared<PlayerInfoMsg>(); });
    recv_handlers.emplace(GenericMsg::MsgTypeHeader::NOT_PROJECTILE_INFO,
                          [this]() { return std::make_shared<NotProyectileInfo>(); });
    recv_handlers.emplace(GenericMsg::MsgTypeHeader::SHOOT_MSG,
                          [this]() { return std::make_shared<ShootMsg>(); });
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
