#include "util/scanner.hpp"

// Main function
int main(int argc, char const *argv[]) {
    std::vector<Token> tokens {}; // vector that stores input file tokens

    if (argc < 2) {
        std::cout << "Please give input file" << std::endl;
        return 0;
    }
    // Writes the output tokens to std::cout and to a file called ans.c1
    else if (argc == 2) {
        Scanner scanner(argv[1], &tokens);
        scanner.scan();
        scanner.print("./testcases/result/ans.c1");
    } 
    // Writes the output tokens to file
    else {
        std::string output_file = "./testcases/result/ans";
        for (int i = 1; i <= argc - 1; i++) {
            Scanner scanner(argv[i], &tokens);
            scanner.scan();
            scanner.print(output_file + std::to_string(i) + ".c1");
            tokens.clear();
        }
    }
    return 0;
}
