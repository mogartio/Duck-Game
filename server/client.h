#ifndef CLIENT_H
#define CLIENT_H
#include <string>
#include <utility>

#include "../common/messages/generic_msg.h"
#include "../common/messages/handler_read.h"
#include "../common/sender.h"

#include "lobbys_monitor.h"
#include "receiver.h"
#include "send_queues_monitor.h"
#include "server_protocol.h"

class Client: public HandlerReader {
private:
    Socket client_skt;
    Queue<GenericMsg*> send_queue;
    Queue<GenericMsg*>* recv_queue;
    SendQueuesMonitor<GenericMsg*>& send_queues;
    uint id;  // a chequear, para la funcionalidad futura
    ServerProtocol protocol;
    ReceiverServer receiver;
    Sender sender;
    LobbysMonitor& lobbys;
    uint lobby_unido_id;
    bool is_testing;

    void start_client();

public:
    Client(Socket&& client_skt, uint id, SendQueuesMonitor<GenericMsg*>& send_queues,
           LobbysMonitor& lobbys, bool is_testing);
    bool operator==(const Client* other) const;

    void stop();
    bool is_alive();
    uint get_id() const;
    void switch_queues(Queue<GenericMsg*>* recv_queue);

    using HandlerReader::handle_read;

    virtual void handle_read(const CustomizedPlayerInfoMsg& msg) override;
    virtual void handle_read(const ViewLobbiesMsg& msg) override;
    virtual void handle_read(const ChooseLobbyMsg& msg) override;
    virtual void handle_read(const CreateLobbyMsg& msg) override;
    virtual void handle_read(const GoBackMsg& msg) override;
    virtual void handle_read(const ExitFromLobbyMsg& msg) override;
    virtual void handle_read(const StartGameMsg& msg) override;
};

#endif  // CLIENT_H
