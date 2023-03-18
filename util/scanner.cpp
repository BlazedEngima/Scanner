#include "scanner.hpp"

// Vector that stores reserved words
std::vector<std::string> reserved_words {
    "int", "main", "void", "break",
    "do", "else", "if", "while", 
    "return", "scanf", "printf"
};

// Overloading << operator so it can print out the enum type token_list
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

// Constructor for Scanner object, opens file
Scanner::Scanner(std::string file_name, std::vector<Token> *out_vector) {
    try {
        this->in_file.open(file_name, std::ios::in);
        this->out_vector = out_vector;
    }
    catch(const std::exception& e) {
        std::cout << "Error, unable to open file" << std::endl;
        std::cerr << e.what() << '\n';
    }
}

// Destructor for Scanner object, closes file
Scanner::~Scanner() {
    this->in_file.close();
}

// Print function to print to std::cout
void Scanner::print() {
    for (auto & elem: *(this->out_vector)) {
        std::cout << "Token: " << elem.token_type << std::endl;
    }
}

// Print function to print to output file
void Scanner::print(std::string file_name) {
    std::ofstream out_file;

    // Open output file
    try {
        out_file.open(file_name, std::ios::out);
    }
    catch(const std::exception& e) {
        std::cout << "Error, unable to open file" << std::endl;
        std::cerr << e.what() << '\n';
    }
    
    for (int i = 0; i < this->out_vector->size(); i++) {
        // If last token, ignore adding '\n' 
        if (i == this->out_vector->size() - 1) {
            out_file << "Token: " << this->out_vector->at(i).token_type;
            break;
        }
        out_file << "Token: " << this->out_vector->at(i).token_type << std::endl;
    }

    out_file.close();

}

// Function that handles reading integers
Token Scanner::read_number() {
    // Appends first character into character buffer
    this->char_buffer += this->cur_char;

    // Checks to see if the next character is a digit
    while (isdigit(this->in_file.peek())) {
        this->in_file >> this->cur_char;
        this->char_buffer += this->cur_char;
    }

    // Create an integer token
    Token int_token(INT_NUM, char_buffer, char_buffer);
    // Clear char_buffer
    this->char_buffer = "";

    return int_token;
}

// Function that handles reading strings
Token Scanner::read_string() {
    // Appends first character into character buffer
    this->char_buffer += this->cur_char;
    
    // Checks to see if the next character is an alphanumeric or underscore
    while (isalnum(this->in_file.peek()) || this->in_file.peek() == '_') {
        this->in_file >> this->cur_char;
        this->char_buffer += this->cur_char;  
    }
    
    // Checks to see if string is a reserved keyword
    for (size_t i = 0; i < reserved_words.size(); i++) {
        if (this->char_buffer == reserved_words[i]) {
            // Create reserved word token
            Token reserved_word_token(static_cast<token_list>(28 + i), char_buffer);
            // Clear char_buffer
            this->char_buffer = "";
            return reserved_word_token;
        }
    }
    
    // Create id token
    Token id_token(ID, char_buffer, char_buffer);
    // Clear char_buffer
    this->char_buffer = "";

    return id_token;
}

// Function that handles special symbols
Token Scanner::read_special_symbol() {
    // Checks if current character is a special symbol and returns associated token
    switch (this->cur_char) {
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
            // Checks next character and move the character pointer
            // Returns associated token
            if (this->in_file.peek() == '&') {
                this->in_file >> this->cur_char;
                Token special_token(ANDAND, "&&");
                return special_token;
            }

            Token special_token(AND_OP, "&");
            return special_token;
            break;
        }
        case '|': {
            if (this->in_file.peek() == '|') {
                this->in_file >> this->cur_char;
                Token special_token(OROR, "||");
                return special_token;
            }

            Token special_token(OR_OP, "|");
            return special_token;
            break;
        }
        case '!': {
            if (this->in_file.peek() == '=') {
                this->in_file >> this->cur_char;
                Token special_token(NOTEQ, "!=");
                return special_token;
            }

            Token special_token(NOT_OP, "!");
            return special_token;
            break;
        }
        case '=': {
            if (this->in_file.peek() == '=') {
                this->in_file >> this->cur_char;
                Token special_token(EQ, "==");
                return special_token;
            }

            Token special_token(ASSIGN, "=");
            return special_token;
            break;
        }
        case '<': {
            if (this->in_file.peek() == '<') {
                this->in_file >> this->cur_char;
                Token special_token(SHL_OP, "<<");
                return special_token;
            }
            else if (this->in_file.peek() == '=') {
                this->in_file >> this->cur_char;
                Token special_token(LTEQ, "<=");
                return special_token;
            }

            Token special_token(LT, "<");
            return special_token;
            break;
        }
        case '>': {
            if (this->in_file.peek() == '>') {
                this->in_file >> this->cur_char;
                Token special_token(SHR_OP, ">>");
                return special_token;
            }
            else if (this->in_file.peek() == '=') {
                this->in_file >> this->cur_char;
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

// Main scan function that wraps the previous three functions
void Scanner::scan() {
    while(this->in_file >> this->cur_char) {

        if (isalpha(this->cur_char)) {
            this->out_vector->push_back(this->read_string());
        }

        else if (isdigit(this->cur_char)) {
            this->out_vector->push_back(this->read_number());
        }

        else {this->out_vector->push_back(this->read_special_symbol());}
    }
}