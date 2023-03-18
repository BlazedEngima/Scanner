#include "util/scanner.hpp"

int main(int argc, char const *argv[]) {
    if (argc < 2) {
        std::cout << "Please give input file" << std::endl;
        return 0;
    }

    std::string output_file = "./testcases/result/ans";
    for (int i = 1; i <= argc - 1; i++) {
        Scanner scanner(argv[i]);
        scanner.scan();
        scanner.print(output_file + std::to_string(i) + ".c1");
    }

    return 0;
}
