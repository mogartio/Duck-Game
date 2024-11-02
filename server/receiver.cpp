#include "receiver.h"

Receiver::Receiver(Queue<GenericMsg*>* recv_queue_game, ProtocoloCommon* protocol, Client* client):
        recv_queue_game(recv_queue_game), protocol(protocol), client(client) {}

void Receiver::run() {
    while (_keep_running) {
        try {
            GenericMsg* msg = protocol->receive();
            if (msg->get_type() == GenericMsg::LOBBY_MSG) {
                msg->accept_read(*client);
            } else {
                recv_queue_game->push(msg);
            }
        } catch (const std::exception& e) {
            _keep_running = false;
        }
    }
}

void Receiver::kill() { _keep_running = false; }
