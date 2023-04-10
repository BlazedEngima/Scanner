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
typedef std::set<Token> Token_Set;
typedef std::vector<Rule> State;
typedef std::vector<Rule> Rules;
typedef std::unordered_map<Token, Rules, Hash> Grammar;

class Rule {
    private:
        Tail tail;
        int pos;
        int num_tail;
        Lookahead lookahead;

    public:
        Rule(Tail tail);
        Rule(Tail tail, Lookahead lookahead);
        Rule(Tail tail, int pos, Lookahead lookahead);
        Rule() {};

        Tail get_tail(void) {return this->tail;}
        Token get_first_tail(void) {return this->tail[0];}
        int get_length(void) {return this->num_tail;}
        void print_rule(void);

        Rule & operator=(Rule rhs) {
            this->tail = rhs.tail;
            this->pos = rhs.pos;
            this->num_tail = rhs.num_tail;
            this->lookahead = rhs.lookahead;
        }

        Rule operator+(int const &rhs) {
            Rule new_rule;
            new_rule = *this;
            new_rule.pos = new_rule.pos + rhs;

            return new_rule;
        }
        
        // inline bool operator<(const Rule &rhs) const {return this->head.token_type < rhs.head.token_type;}
        inline bool operator==(const Rule &rhs) const {return this->tail == rhs.tail;}
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

State closure(Rule rule, const Grammar &grammar);
Lookahead get_first_set(const Grammar &grammar, Token token, int idx);

std::vector<std::vector<Rule>> gen_table (void);

void print_grammar(Grammar &grammar);

// std::vector<Rule> prod_rules;


#endif