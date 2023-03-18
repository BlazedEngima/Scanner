#include "scanner.hpp"

Scanner::Scanner(std::string file_name) {
    try {
        this->in_file.open(file_name, std::ios::in);
    }
    catch(const std::exception& e) {
        std::cout << "Error, unable to open file" << std::endl;
        std::cerr << e.what() << '\n';
    }
}

void Scanner::read_int() {
    this->in_file.get(this->next_char);

}

void Scanner::read_string() {

}

void Scanner::scan() {
    while(next_char != EOF) {
        this->in_file.get(this->next_char);

        switch (this->next_char) {
            case '{':
                this->tokens.push_back(LBRACE);
                break;
            case '}':
                this->tokens.push_back(RBRACE);
                break;
            case '[':
                this->tokens.push_back(LSQUARE);
                break;
            case ']':
                this->tokens.push_back(RSQUARE);
                break;
            case '(':
                this->tokens.push_back(LPAR);
                break;
            case ')':
                this->tokens.push_back(RPAR);
                break;
            case ';':
                this->tokens.push_back(SEMI);
                break;
            case '+':
                this->tokens.push_back(PLUS);
                break;
            case '-':
                this->tokens.push_back(MINUS);
                break;
            case '*':
                this->tokens.push_back(MUL_OP);
                break;
            case '/':
                this->tokens.push_back(DIV_OP);
                break;
            case '&':
                this->tokens.push_back(AND_OP);
                break;
            case '|':
                this->tokens.push_back(OR_OP);
                break;
            case '!':
                this->tokens.push_back(NOT_OP);
                break;
            case '=':
                this->tokens.push_back(ASSIGN);
                break;
            case '<':
                this->tokens.push_back(LT);
                break;
            case '>':
                this->tokens.push_back(GT);
                break;
            case ',':
                this->tokens.push_back(COMMA);
                break;
            
            default:
                break;
        }
    }

}