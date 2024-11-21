#include "sender.h"

#include "client.h"
SenderServer::SenderServer(Queue<std::shared_ptr<GenericMsg>>* send_queue,
                           ProtocoloCommon* protocol, Client* client):
        Sender(send_queue, protocol), client(client) {}
void SenderServer::execute(std::shared_ptr<GenericMsg> msg) {
    if (msg->get_header() == GenericMsg::MsgTypeHeader::GAME_ENDED_MSG) {
        client->killGameAndLobby();
    }
}
