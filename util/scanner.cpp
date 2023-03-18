#include "scanner.hpp"

std::vector<std::string> reserved_words {
    "int", "main", "void", "break",
    "do", "else", "if", "while", 
    "return", "scanf", "printf"
};

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
    }
    #undef process_token

    return out << idx;
}

Scanner::Scanner(std::string file_name) {
    try {
        this->in_file.open(file_name, std::ios::in);
    }
    catch(const std::exception& e) {
        std::cout << "Error, unable to open file" << std::endl;
        std::cerr << e.what() << '\n';
    }
}

void Scanner::print() {
    for (auto & elem: this->tokens) {
        std::cout << "Token: " << elem << std::endl;
    }
}

void Scanner::print(std::string file_name) {
    std::ofstream out_file;

    try {
        out_file.open(file_name, std::ios::out);
    }
    catch(const std::exception& e) {
        std::cout << "Error, unable to open file" << std::endl;
        std::cerr << e.what() << '\n';
    }
    
    for (int i = 0; i < this->tokens.size(); i++) {
        if (i == this->tokens.size() - 1) {
            out_file << "Token: " << this->tokens[i];
            return;
        }
        out_file << "Token: " << this->tokens[i] << std::endl;
    }

}

Tokens Scanner::read_number() {
    this->char_buffer += this->next_char;

    while (isdigit(this->in_file.peek())) {
        this->in_file >> this->next_char;
        this->char_buffer += this->next_char;
    }

    this->char_buffer = "";
    return INT_NUM;
}

Tokens Scanner::read_string() {
    this->char_buffer += this->next_char;

    while (isalnum(this->in_file.peek()) || this->in_file.peek() == '_') {
        this->in_file >> this->next_char;
        this->char_buffer += this->next_char;  
    }
    
    for (size_t i = 0; i < reserved_words.size(); i++) {
        if (this->char_buffer == reserved_words[i]) {
            this->char_buffer = "";
            return static_cast<Tokens>(28 + i);
        }
    }
    
    this->char_buffer = "";

    return ID;
}

Tokens Scanner::special_symbol() {
    switch (this->next_char) {
        case '{':
            return LBRACE;
            break;
        case '}':
            return RBRACE;
            break;
        case '[':
            return LSQUARE;
            break;
        case ']':
            return RSQUARE;
            break;
        case '(':
            return LPAR;
            break;
        case ')':
            return RPAR;
            break;
        case ';':
            return SEMI;
            break;
        case '+':
            return PLUS;
            break;
        case '-':
            return MINUS;
            break;
        case '*':
            return MUL_OP;
            break;
        case '/':
            return DIV_OP;
            break;
        case '&': {
            if (this->in_file.peek() == '&') {
                this->in_file >> this->next_char;
                return ANDAND;
            }

            return AND_OP;
            break;
        }
        case '|': {
            if (this->in_file.peek() == '|') {
                this->in_file >> this->next_char;
                return OROR;
            }

            return OR_OP;
            break;
        }
        case '!': {
            if (this->in_file.peek() == '=') {
                this->in_file >> this->next_char;
                return NOTEQ;
            }

            return NOT_OP;
            break;
        }
        case '=': {
            if (this->in_file.peek() == '=') {
                this->in_file >> this->next_char;
                return EQ;
            }

            return ASSIGN;
            break;
        }
        case '<': {
            if (this->in_file.peek() == '<') {
                this->in_file >> this->next_char;
                return SHL_OP;
            }
            else if (this->in_file.peek() == '=') {
                this->in_file >> this->next_char;
                return LTEQ;
            }

            return LT;
            break;
        }
        case '>': {
            if (this->in_file.peek() == '>') {
                this->in_file >> this->next_char;
                return SHR_OP;
            }
            else if (this->in_file.peek() == '=') {
                this->in_file >> this->next_char;
                return GTEQ;
            }

            return GT;
            break;
        }
        case ',':
            return COMMA;
            break;
        
        default:
            break;
    }
}

void Scanner::scan() {
    while(this->in_file >> this->next_char) {

        if (isalpha(this->next_char)) {
            this->tokens.push_back(this->read_string());
        }

        else if (isdigit(this->next_char)) {
            this->tokens.push_back(this->read_number());
        }

        else {this->tokens.push_back(this->special_symbol());}
    }
}