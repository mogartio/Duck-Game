#include "receiver.h"

#include "client.h"

ReceiverServer::ReceiverServer(Queue<std::shared_ptr<GenericMsg>>* recv_queue_game, ProtocoloCommon* protocol,
                               Client* client):
        Receiver(recv_queue_game, protocol), client(client) {}


void ReceiverServer::executeMsg(std::shared_ptr<GenericMsg> msg) {
    msg->set_id_client(client->get_id());
    if (msg->get_type() == GenericMsg::LOBBY_MSG) {
        msg->accept_read(*client);
    } else {
        recv_queue->push(msg);
    }
}
