#ifndef HANDLE_H
#define HANDLE_H

class ServerExampleMsg1;
class ClientExampleMsg1;
class ClientExampleMsg2;

class Handler {
public:

    virtual void handle_send(ServerExampleMsg1& msg) {
        (void)msg; // Suppress unused parameter warning
    }
    virtual void handle_send(ClientExampleMsg1& msg) {
        (void)msg; // Suppress unused parameter warning
    }
    virtual void handle_send(ClientExampleMsg2& msg) {
        (void)msg; // Suppress unused parameter warning
    }
    virtual void handle_recv(ServerExampleMsg1& msg) {
        (void)msg; // Suppress unused parameter warning
    }
    virtual void handle_recv(ClientExampleMsg1& msg) {
        (void)msg; // Suppress unused parameter warning
    }
    virtual void handle_recv(ClientExampleMsg2& msg) {
        (void)msg; // Suppress unused parameter warning
    }
    virtual ~Handler() = default;
};

#endif // HANDLE_H