#ifndef parser_h
#define parser_h

#include "scanner.hpp"
#include <unordered_map>
#include <map>
#include <stack>
#include <set>
#include <algorithm>

typedef enum parse_table_instruction_types {
    shift, reduce, go_to

} instr_type;

typedef struct parse_table_instruction {
    instr_type instr;
    int state_rule;

    parse_table_instruction (instr_type type, int state_rule) {
        this->instr = type;
        this->state_rule = state_rule;
    }

} instruction;

struct Hash {size_t operator()(const Token &t) const {return t.token_type;}};

class Rule;

typedef std::vector<Token> Tail;
typedef std::set<Token> Lookahead;
typedef std::unordered_map<Token, Lookahead, Hash> Lookahead_Set;
typedef std::set<Token> Token_Set;
typedef std::vector<Rule> Rules;
typedef std::vector<Rule> State;
typedef std::unordered_map<Token, Rules, Hash> Grammar;
// typedef std::unordered_map<Token, Rules, Hash> State;

class Rule {
    private:
        Token head;
        Tail tail;
        int pos;
        int num_tail;
        Token lookahead_token;

    public:
        Rule(Token head, Tail tail);
        Rule(Token head, Tail tail, Token lookahead_token);
        Rule(Token head, Tail tail, int pos, Token lookahead_token);
        Rule() {};

        Token get_head(void) {return this->head;}
        Tail get_tail(void) {return this->tail;}
        Token get_first_tail(void) {return this->tail[0];}
        Token get_lookahead(void) {return this->lookahead_token;}
        Token get_next_token(void) {return (this->pos >= num_tail) ? Token() : this->tail[pos];}
        void increment_pointer(void) {this->pos++;}
        int get_current_pos(void) {return this->pos;}
        void set_lookahead(Token lookahead_token) {this->lookahead_token = lookahead_token;}
        int get_length(void) {return this->num_tail;}
        void print_rule(void);

        Rule & operator=(Rule rhs) {
            this->tail = rhs.tail;
            this->pos = rhs.pos;
            this->num_tail = rhs.num_tail;
            this->lookahead_token = rhs.lookahead_token;
        }

        Rule operator+(int const &rhs) {
            // if (this->pos + rhs >= this->num_tail) {
            //     std::cout << "Cannot add past length of vector, cancelling add" << std::endl;
            //     return *this;
            //     // exit(0);
            // } else {
                Rule new_rule;
                new_rule = *this;
                new_rule.pos = new_rule.pos + rhs;

                return new_rule;
            // }
        }
        
        // inline bool operator<(const Rule &rhs) const {return this->head.token_type < rhs.head.token_type;}
        inline bool operator==(const Rule &rhs) const {return this->tail == rhs.tail 
                                                        && this->lookahead_token == rhs.lookahead_token
                                                        && this->head == rhs.head
                                                        && this->pos == rhs.pos
                                                        && this->lookahead_token == rhs.lookahead_token;
                                                    }
        inline bool operator!=(const Rule &rhs) const {return !(this->tail == rhs.tail 
                                                        && this->lookahead_token == rhs.lookahead_token
                                                        && this->head == rhs.head
                                                        && this->pos == rhs.pos
                                                        && this->lookahead_token == rhs.lookahead_token);
                                                    }
        Token & operator[](int idx) {
            if (idx >= this->num_tail) {
                std::cout << "Array index out of bounds" << std::endl;
                exit(0);
            }
            return this->tail[idx];
        }
        // ~Rule();
};

class Parser {
    private:
        std::unordered_map<int, std::unordered_map<token_list, instruction>> lookup_table;
        std::stack<int> state_stack;
        std::stack<Token> symbol_stack;

    public:
        void parse(void);

        Parser();
        // ~Parser();


};

bool contains_null(const Grammar &grammar, const Token &token);    
State closure(Rule &rule, const Lookahead_Set &first_set_table, const Grammar &grammar);
Lookahead get_first_set(const Grammar &grammar, Token token, int idx);
Lookahead_Set get_first_set_table(const Grammar &grammar);
std::vector<std::vector<Rule>> gen_table (void);

void print_grammar(Grammar &grammar);
void print_first_set_table(Lookahead_Set &first_set_table);
// std::vector<Rule> prod_rules;


#endif