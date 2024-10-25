#ifndef CLIENT_GENERIC_MSG_H
#define CLIENT_GENERIC_MSG_H

#include "generic_msg.h"
#include "client_handler.h"

class CustomizedPlayerInfoMsg : public GenericMsg<ClientHandler> {
    void accept(ClientHandler& handler) override {
        handler.handle(*this);
    }
};

class ViewLobbiesMsg : public GenericMsg<ClientHandler> {
    void accept(ClientHandler& handler) override {
        handler.handle(*this);
    }
};

class ChooseLobbyMsg : public GenericMsg<ClientHandler> {
    void accept(ClientHandler& handler) override {
        handler.handle(*this);
    }
};

class CreateLobbyMsg : public GenericMsg<ClientHandler> {
    void accept(ClientHandler& handler) override {
        handler.handle(*this);
    }
};

class StartGameMsg : public GenericMsg<ClientHandler> {
    void accept(ClientHandler& handler) override {
        handler.handle(*this);
    }
};

class GoBackMsg : public GenericMsg<ClientHandler> {
    void accept(ClientHandler& handler) override {
        handler.handle(*this);
    }
};

class PickupDropItemMsg : public GenericMsg<ClientHandler> {
    void accept(ClientHandler& handler) override {
        handler.handle(*this);
    }
};

class StartMoveLeftMsg : public GenericMsg<ClientHandler> {
    void accept(ClientHandler& handler) override {
        handler.handle(*this);
    }
};

class StopMoveLeftMsg : public GenericMsg<ClientHandler> {
    void accept(ClientHandler& handler) override {
        handler.handle(*this);
    }
};

class StartMoveRightMsg : public GenericMsg<ClientHandler> {
    void accept(ClientHandler& handler) override {
        handler.handle(*this);
    }
};

class StopMoveRightMsg : public GenericMsg<ClientHandler> {
    void accept(ClientHandler& handler) override {
        handler.handle(*this);
    }
};

class JumpMsg : public GenericMsg<ClientHandler> {
    void accept(ClientHandler& handler) override {
        handler.handle(*this);
    }
};

class PlayDeadMsg : public GenericMsg<ClientHandler> {
    void accept(ClientHandler& handler) override {
        handler.handle(*this);
    }
};

class ShootMsg : public GenericMsg<ClientHandler> {
    void accept(ClientHandler& handler) override {
        handler.handle(*this);
    }
};

#endif // CLIENT_GENERIC_MSG_H