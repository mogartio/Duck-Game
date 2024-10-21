#ifndef READ_INPUT_H
#define READ_INPUT_H

#include <atomic>
#include <string>
#include <utility>

#include "../common/thread.h"

class ReadInput: public Thread {
public:
    ReadInput() {}

    void run() override {
        while (_keep_running) {
            std::string input;
            std::getline(std::cin, input);
            if (input == "q") {
                _keep_running = false;
            }
        }
    }

    bool is_alive() const override { return _keep_running.load(); }
};

#endif