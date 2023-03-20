#include "util/scanner.hpp"
#include <sys/stat.h>

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
        scanner.print();
    } 
    // Writes the output tokens to file (made for debugging and testing)
    else {
        // Make result directory if it doesnt exist
        const char *output_dir = "./output";
        struct stat sb;

        if (stat(output_dir, &sb) != 0)
            mkdir(output_dir, 0777);
        
        // Write output files to output directory
        std::string output_file = "./output/ans";
        for (int i = 1; i <= argc - 1; i++) {
            Scanner scanner(argv[i], &tokens);
            scanner.scan();
            scanner.print(output_file + std::to_string(i) + ".c1");
            tokens.clear();
        }
    }
    return 0;
}
