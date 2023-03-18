#include "scanner.hpp"

std::vector<std::string> reserved_words {
    "int", "main", "void", "break",
    "do", "else", "if", "while", 
    "return", "scanf", "printf"
};

std::ostream & operator<<(std::ostream& out, const token_list token) {
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
        std::cout << "Token: " << elem.token_type << "\t" << "Value: " << elem.value << std::endl;
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
            out_file << "Token: " << this->tokens[i].token_type;
            return;
        }
        out_file << "Token: " << this->tokens[i].token_type << std::endl;
    }

}

Token Scanner::read_number() {
    this->char_buffer += this->next_char;

    while (isdigit(this->in_file.peek())) {
        this->in_file >> this->next_char;
        this->char_buffer += this->next_char;
    }

    Token int_token(INT_NUM, char_buffer, char_buffer);
    this->char_buffer = "";
    return int_token;
}

Token Scanner::read_string() {
    this->char_buffer += this->next_char;
    
    while (isalnum(this->in_file.peek()) || this->in_file.peek() == '_') {
        this->in_file >> this->next_char;
        this->char_buffer += this->next_char;  
    }
    
    for (size_t i = 0; i < reserved_words.size(); i++) {
        if (this->char_buffer == reserved_words[i]) {
            Token reserved_word_token(static_cast<token_list>(28 + i), char_buffer);
            this->char_buffer = "";
            return reserved_word_token;
        }
    }
    
    Token id_token(ID, char_buffer, char_buffer);
    this->char_buffer = "";

    return id_token;
}

Token Scanner::special_symbol() {
    switch (this->next_char) {
        case '{': {
            Token special_token(LBRACE, "{");
            return special_token;
            break;
        }
        case '}': {
            Token special_token(RBRACE, "}");
            return special_token;
            break;
        }
        case '[': {
            Token special_token(LSQUARE, "[");
            return special_token;
            break;
        }
        case ']': {
            Token special_token(RSQUARE, "]");
            return special_token;
            break;
        }
        case '(': {
            Token special_token(LPAR, "(");
            return special_token;
            break;
        }
        case ')': {
            Token special_token(RPAR, ")");
            return special_token;
            break;
        }
        case ';': {
            Token special_token(SEMI, ";");
            return special_token;
            break;
        }
        case '+': {
            Token special_token(PLUS, "+");
            return special_token;
            break;
        }
        case '-': {
            Token special_token(MINUS, "-");
            return special_token;
            break;
        }
        case '*': {
            Token special_token(MUL_OP, "*");
            return special_token;
            break;
        }
        case '/': {
            Token special_token(DIV_OP, "/");
            return special_token;
            break;
        }
        case '&': {
            if (this->in_file.peek() == '&') {
                this->in_file >> this->next_char;
                Token special_token(ANDAND, "&&");
                return special_token;
            }

            Token special_token(AND_OP, "&");
            return special_token;
            break;
        }
        case '|': {
            if (this->in_file.peek() == '|') {
                this->in_file >> this->next_char;
                Token special_token(OROR, "||");
                return special_token;
            }

            Token special_token(OR_OP, "|");
            return special_token;
            break;
        }
        case '!': {
            if (this->in_file.peek() == '=') {
                this->in_file >> this->next_char;
                Token special_token(NOTEQ, "!=");
                return special_token;
            }

            Token special_token(NOT_OP, "!");
            return special_token;
            break;
        }
        case '=': {
            if (this->in_file.peek() == '=') {
                this->in_file >> this->next_char;
                Token special_token(EQ, "==");
                return special_token;
            }

            Token special_token(ASSIGN, "=");
            return special_token;
            break;
        }
        case '<': {
            if (this->in_file.peek() == '<') {
                this->in_file >> this->next_char;
                Token special_token(SHL_OP, "<<");
                return special_token;
            }
            else if (this->in_file.peek() == '=') {
                this->in_file >> this->next_char;
                Token special_token(LTEQ, "<=");
                return special_token;
            }

            Token special_token(LT, "<");
            return special_token;
            break;
        }
        case '>': {
            if (this->in_file.peek() == '>') {
                this->in_file >> this->next_char;
                Token special_token(SHR_OP, ">>");
                return special_token;
            }
            else if (this->in_file.peek() == '=') {
                this->in_file >> this->next_char;
                Token special_token(GTEQ, ">=");
                return special_token;
            }

            Token special_token(GT, ">");
            return special_token;
            break;
        }
        case ',': {
            Token special_token(COMMA, ",");
            return special_token;
            break;
        }
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