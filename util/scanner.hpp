#ifndef scanner_h
#define scanner_h

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

typedef enum Tokens {
    ID, INT_NUM, LBRACE, RBRACE, LSQUARE, RSQUARE,
    LPAR, RPAR, SEMI, PLUS, MINUS, MUL_OP, DIV_OP,
    AND_OP, OR_OP, NOT_OP, ASSIGN, LT, GT, SHL_OP,
    SHR_OP, EQ, NOTEQ, LTEQ, GTEQ, ANDAND, OROR, COMMA,
    INT, MAIN, VOID, BREAK, DO, ELSE, IF, WHILE,
    RETURN, READ, WRITE

} token;

class Scanner {
    private:
        std::ifstream in_file;
        char next_char;
        std::vector<Tokens> tokens;
        std::string char_buffer;

        Tokens read_number();
        Tokens read_string();
        Tokens special_symbol();

    public:
        // Ban copying and assignment
        Scanner(Scanner const &) = delete;
        Scanner & operator=(Scanner const &) = delete;

        // Get scans file and puts token into tokens vector
        void scan();

        // Prints out token vector
        void print();
        void print(std::string out_file);

        // Constructor
        Scanner(std::string file_name);
};

#endif