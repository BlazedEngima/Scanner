#include "parser.hpp"

Rule::Rule(Token head, Tail tail, Lookahead lookahead) {
    this->head = head;
    this->tail = tail;
    this->pos = 0;
    this->num_tail = tail.size();
    this->lookahead = lookahead;
}

Rule::Rule(Token head, Tail tail, int pos, Lookahead lookahead) {
    this->head = head;
    this->tail = tail;
    this->pos = pos;
    this->num_tail = tail.size();
    this->lookahead = lookahead;
}

void Rule::print_rule(void) {

    std::cout << this->head << "\t: ";
    for (size_t i = 0; i < num_tail; i++) {
        if (i == pos) std::cout << ". ";
        std::cout << this->tail[i] << " ";
    }

    for (auto elem : this->lookahead)
        std::cout << '{' << elem << " " << '}';

    std::cout << std::endl; 
}

Lookahead get_first_set(Grammar &grammar, Token_Set &visited, Token token) {
    Lookahead first_set;
    visited.insert(token);

    std::vector<Rule> rules = grammar[token];
    for (auto elem : rules) {
        Rule prod_rule = elem;
        Token next_token = elem.get_first_tail();
        
        if (next_token.isTerminal)
            first_set.insert(next_token);
        
        if (next_token == token) {
            if (!visited.count(next_token)) {
                Lookahead temp = get_first_set(grammar, visited, next_token);
                first_set.insert(temp.begin(), temp.end());
            }
            
        } else {
            Lookahead temp = get_first_set(grammar, visited, next_token);
            first_set.insert(temp.begin(), temp.end());
        }
    }

    return first_set;
}

// Lookahead get_first_set(State &grammar, Lookahead &visited, Token token) {
//     Lookahead first_set;
//     visited.insert(token);

//     for (auto elem : grammar) {
//         if (elem.get_head() != token) 
//             continue;

//         Rule prod_rule = elem;
//         Token next_token = elem.get_first_tail();

//         // std::cout << "Current token: " << token << '\t';
//         // std::cout << "Next token: " << next_token << '\t';
//         // std::cout << "Terminal: " << next_token.isTerminal << std::endl;
        
//         if (next_token.isTerminal)
//             first_set.insert(next_token);

//         if (next_token == token) {
//             if (!visited.count(next_token)) {
//                 Lookahead temp = get_first_set(grammar, visited, next_token);
//                 first_set.insert(temp.begin(), temp.end());
//             }
//             // if (prod_rule.get_tail().size() > 1) {
//             //     Lookahead temp = get_first_set(grammar, visited, prod_rule.get_tail()[1]);
//             //     first_set.insert(temp.begin(), temp.end());
//             // }

//         } else {
//             Lookahead temp = get_first_set(grammar, visited, next_token);
//             first_set.insert(temp.begin(), temp.end());
//         }
//     }

//     return first_set;
// }

State closure(Rule rule, Lookahead &visited, State grammar) {
    State closure_set;

    Token head = rule.get_head();
    for (auto elem : grammar) {
        if (elem.get_head() != head)
            continue;

        Rule prod_rule = elem;
        Token next_token = elem.get_first_tail();

        closure_set.push_back(elem);
    }

    return closure_set;
}

Parser::Parser() {

}

