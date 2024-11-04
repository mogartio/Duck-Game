#include "receiver.h"

#include "client.h"

ReceiverServer::ReceiverServer(Queue<GenericMsg*>* recv_queue_game, Client* client, Socket& skt):
        Receiver(recv_queue_game, skt), client(client) {}

void ReceiverServer::executeMsg(GenericMsg* msg) {
    msg->set_id_client(client->get_id());
    if (msg->get_type() == GenericMsg::LOBBY_MSG) {
        msg->accept_read(*client);
        delete msg;
    } else {
        recv_queue->push(msg);
    }
}

void ReceiverServer::assingProtocol() { protocol = new ServerProtocol(skt); }
