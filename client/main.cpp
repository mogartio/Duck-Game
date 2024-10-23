#include <iostream>


int main(int argc, char const* argv[]) {

    if (argc != 3) {
        std::cerr << "Bad number of arguments in client side\n";
        return -1;
    }
    std::cout << argv[1] << " " << argv[2] << std::endl;
    return 0;
}
