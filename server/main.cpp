#include "server.h"


int main(int argc, char* argv[]) {

    if (argc < 2) {
        std::cerr << "Bad program call. Expected " << argv[0] << " <port>\n";
        return 1;
    }
    try {
        bool is_testing = false;
        if (argc == 3) {
            is_testing = true;
        }
        Server server(argv[1], is_testing);
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
