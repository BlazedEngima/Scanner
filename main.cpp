#include "util/scanner.hpp"

int main(int argc, char const *argv[])
{
    if (argc == 1) {
        std::cout << "Please give input file" << std::endl;
        return 0;
    }
    
    for (int i = 0; i < argc; i++) {
        std::cout << argv[i] << std::endl;
    }

    return 0;
}
