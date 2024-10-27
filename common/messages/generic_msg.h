#ifndef GENERIC_MSG_H
#define GENERIC_MSG_H

#include "handler.h"
#include <vector>
#include <cstdint>
#include <string>
#include <iostream>

class GenericMsg {
public:
    const static uint8_t SERVER_EXAMPLE_MSG1_H = 0x01;
    const static uint8_t CLIENT_EXAMPLE_MSG1_H = 0x02;
    const static uint8_t CLIENT_EXAMPLE_MSG2_H = 0x03;

    virtual void print_data() = 0;
    virtual void accept_send(Handler& handler) = 0;
    virtual void accept_recv(Handler& handler) = 0;
    virtual ~GenericMsg() = default;
};



class ServerExampleMsg1 : public GenericMsg {
    private: 
        std::string data;
    public: 
    ServerExampleMsg1(std::string data) : data(data) {}
    
    void accept_send(Handler& handler) override {
        handler.handle_send(*this);
    }

    void accept_recv(Handler& handler) override {
        handler.handle_recv(*this);
    }

    std::string get_data() {
        return data;
    }

    void set_data(std::string data) {
        this->data = data;
    }

    uint8_t get_header() {
        return SERVER_EXAMPLE_MSG1_H;
    }

    void print_data() override {
        std::cout << data << std::endl;
    }
};

class ClientExampleMsg1 : public GenericMsg {
    private: 
        std::string data;
    public: 
    ClientExampleMsg1(std::string data) : data(data) {}
    
    void accept_send(Handler& handler) override {
        handler.handle_send(*this);
    }

    void accept_recv(Handler& handler) override {
        handler.handle_recv(*this);
    }
    
    std::string get_data() {
        return data;
    }

    void set_data(std::string data) {
        this->data = data;
    }

    uint8_t get_header() {
        return CLIENT_EXAMPLE_MSG1_H;
    }

    void print_data() override {
        std::cout << data << std::endl;
    }
};


class ClientExampleMsg2 : public GenericMsg {
    private: 
        uint8_t data;
    public: 
    ClientExampleMsg2(int data) : data(data) {}
    
    void accept_send(Handler& handler) override {
        handler.handle_send(*this);
    }

    void accept_recv(Handler& handler) override {
        handler.handle_recv(*this);
    }
    
    uint8_t get_data() {
        return data;
    }

    void set_data(uint8_t data) {
        this->data = data;
    }

    uint8_t get_header() {
        return CLIENT_EXAMPLE_MSG2_H;
    }

    void print_data() override {
        std::cout << static_cast<int>(data) << std::endl;
    }
};


#endif
