#ifndef scanner_h
#define scanner_h

#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>

std::vector<std::string> reserved_words {
    "int", "main", "void", "break",
    "do", "else", "if", "while", 
    "return", "scanf", "printf"
};

typedef enum Tokens {
    ID, INT_NUM, LBRACE, RBRACE, LSQUARE, RSQUARE,
    LPAR, RPAR, SEMI, PLUS, MINUS, MUL_OP, DIV_OP,
    AND_OP, OR_OP, NOT_OP, ASSIGN, LT, GT, SHL_OP,
    SHR_OP, EQ, NOTEQ, LTEQ, GTEQ, ANDAND, OROR, COMMA,
    INT, MAIN, VOID, BREAK, DO, ELSE, IF, WHILE,
    RETURN, READ, WRITE

} token;

std::ostream & operator<<(std::ostream& out, const Tokens token) {
    const char* idx = 0;

    #define process_token(p) case p: idx = #p; break;
    switch (token) {
        process_token(ID);
        process_token(INT_NUM);
        process_token(LBRACE);
        process_token(RBRACE);
        process_token(LSQUARE);
        process_token(RSQUARE);
        process_token(LPAR);
        process_token(RPAR);
        process_token(SEMI);
        process_token(PLUS);
        process_token(MINUS);
        process_token(MUL_OP);
        process_token(DIV_OP);
        process_token(AND_OP);
        process_token(OR_OP);
        process_token(NOT_OP);
        process_token(ASSIGN);
        process_token(LT);
        process_token(GT);
        process_token(SHL_OP);
        process_token(SHR_OP);
        process_token(EQ);
        process_token(NOTEQ);
        process_token(LTEQ);
        process_token(GTEQ);
        process_token(ANDAND);
        process_token(OROR);
        process_token(COMMA);
    }
    #undef process_token

    return out << idx;
}

class Scanner {
    private:
        std::ifstream in_file;
        char next_char;
        std::vector<Tokens> tokens;

        void read_int();
        void read_string();

    public:
        // Ban copying and assignment
        Scanner(Scanner const &) = delete;
        Scanner & operator=(Scanner const &) = delete;

        // Get next token
        void scan();

        // Constructor
        Scanner(std::string file_name);

        // Destructor
        ~Scanner();

};

#endif