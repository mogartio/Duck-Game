#include "comunication/server.h"


int main(int argc, char* argv[]) {

    if (argc < 2) {
        std::cerr << "Bad program call. Expected " << argv[0] << " <port>\n";
        return 1;
    }
    try {
        bool is_testing = false;
        bool is_cheating = false;
        if (argc == 3) {
            if (std::string(argv[2]) == "test") {
                is_testing = true;
            }
            if (std::string(argv[2]) == "cheat") {
                is_cheating = true;
            }
        }
        Server server(argv[1], is_testing, is_cheating);
        server.run();
        return 0;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Unknown error" << std::endl;
        return 1;
    }
}
