#ifndef scanner_h
#define scanner_h

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

// Tokens
enum token_list {
    ID, INT_NUM, LBRACE, RBRACE, LSQUARE, RSQUARE,
    LPAR, RPAR, SEMI, PLUS, MINUS, MUL_OP, DIV_OP,
    AND_OP, OR_OP, NOT_OP, ASSIGN, LT, GT, SHL_OP,
    SHR_OP, EQ, NOTEQ, LTEQ, GTEQ, ANDAND, OROR, COMMA,
    INT, MAIN, VOID, BREAK, DO, ELSE, IF, WHILE,
    RETURN, READ, WRITE, ERROR

};

// Token struct object
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

// Scanner class
class Scanner {
    private:
        std::ifstream in_file; // input file
        std::vector<Token> *out_vector; // pointer to output vector;
        char cur_char; // current character pointer
        std::string char_buffer; // character buffer to analyze tokens

        // Member functions
        Token read_number();
        Token read_string();
        Token read_special_symbol();

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
        Scanner(std::string file_name, std::vector<Token> *out_vector);

        // Destructor
        ~Scanner();
};

#endif