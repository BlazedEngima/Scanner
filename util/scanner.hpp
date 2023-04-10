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
    RETURN, READ, WRITE, _EOF, _NULL, 
    
    S, E, T, F, EE, TT,
    A, C, B, b, a, d, g, h,
    
    program, var_declarations, var_declaration,
    declaration_list, declaration, code_block, statement,
    statements, assign_statement, control_statement, read_write_statement,
    if_statement, while_statement, do_while_statement, return_statement,
    read_statement, write_statement, exp, if_stmt,
    
    ERROR

    /* Testing */


};

// Token struct object
typedef struct Token {
    std::string value;
    std::string lexeme;
    token_list token_type;
    bool isTerminal;
    
    Token(token_list token_type, std::string lexeme, std::string value = "") {
        this->value = value;
        this->lexeme = lexeme;
        this->token_type = token_type;
        this->isTerminal = true;
    }

    Token(token_list token_type) {
        this->value = "";
        this->lexeme = "";
        this->token_type = token_type;
        this->isTerminal = false;
    }

    Token() {
        this->isTerminal = false;
        this->token_type = _NULL;
        this->value = "";
        this->lexeme = "";
    };

    friend std::ostream & operator<<(std::ostream& out, const Token token) {
        const char* idx = 0;

        #define process_token(p) case p: idx = #p; break;
        switch (token.token_type) {
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
            process_token(INT);
            process_token(MAIN);
            process_token(VOID);
            process_token(BREAK);
            process_token(DO);
            process_token(ELSE);
            process_token(IF);
            process_token(WHILE);
            process_token(RETURN);
            process_token(READ);
            process_token(WRITE);
            process_token(_EOF);
            process_token(_NULL);

            /* Test cases */
            process_token(S);
            process_token(E);
            process_token(T);
            process_token(EE);
            process_token(TT);
            process_token(F);
            process_token(A);
            process_token(B);
            process_token(C);
            process_token(a);
            process_token(b);
            process_token(d);
            process_token(g);
            process_token(h);

        }
        #undef process_token

        return out << idx;
    }
    Token & operator=(Token rhs) {
        this->value = rhs.value;
        this->lexeme = rhs.lexeme;
        this->isTerminal = rhs.isTerminal;
        this->token_type = rhs.token_type;
    }
    inline bool operator==(const Token &t) const {return this->token_type == t.token_type;}
    inline bool operator!=(const Token &t) const {return this->token_type != t.token_type;}
    inline bool operator<(const Token &rhs) const {return this->token_type < rhs.token_type;}


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