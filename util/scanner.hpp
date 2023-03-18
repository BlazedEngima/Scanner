#ifndef scanner_h
#define scanner_h

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

enum token_list {
    ID, INT_NUM, LBRACE, RBRACE, LSQUARE, RSQUARE,
    LPAR, RPAR, SEMI, PLUS, MINUS, MUL_OP, DIV_OP,
    AND_OP, OR_OP, NOT_OP, ASSIGN, LT, GT, SHL_OP,
    SHR_OP, EQ, NOTEQ, LTEQ, GTEQ, ANDAND, OROR, COMMA,
    INT, MAIN, VOID, BREAK, DO, ELSE, IF, WHILE,
    RETURN, READ, WRITE

};

typedef struct Token {
    std::string value;
    std::string lexeme;
    token_list token_type;
    
    Token(token_list token_type, std::string lexeme, std::string value = "") {
        this->value = value;
        this->lexeme = lexeme;
        this->token_type = token_type;
    }

} Token;

class Scanner {
    private:
        std::ifstream in_file;
        char next_char;
        std::vector<Token> tokens;
        std::string char_buffer;

        Token read_number();
        Token read_string();
        Token special_symbol();

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