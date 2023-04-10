#include "parser.hpp"

Rule::Rule(Tail tail) {
    this->tail = tail;
    this->pos = 0;
    this->num_tail = tail.size();

    Lookahead empty_set({Token()});

    this->lookahead = empty_set;
}

Rule::Rule(Tail tail, Lookahead lookahead) {
    this->tail = tail;
    this->pos = 0;
    this->num_tail = tail.size();
    this->lookahead = lookahead;
}

Rule::Rule(Tail tail, int pos, Lookahead lookahead) {
    this->tail = tail;
    this->pos = pos;
    this->num_tail = tail.size();
    this->lookahead = lookahead;
}

void Rule::print_rule(void) {

    for (size_t i = 0; i < num_tail; i++) {
        if (i == pos) std::cout << ". ";
        std::cout << this->tail[i] << " ";
    }

    for (auto elem : this->lookahead)
        std::cout << '{' << elem << " " << '}';

}

bool contains_zero(Lookahead set) {
    Token Null = Token();
    return !(set.count(Null) == 0);
}

bool check_zero(const Grammar &grammar, Token_Set &visited, Token token) {
    std::vector<Token> has_zero;
    Token null = Token();

    if (token.isTerminal || token == null)
        return false;
    
    for (auto items : grammar.at(token)) {
        if (visited.find(items.get_first_tail()) != visited.end())
            continue;

        if (items.get_first_tail() == null)
            return true;

        if (!(items.get_first_tail().isTerminal)) {
            visited.insert(token);
            return check_zero(grammar, visited, items.get_first_tail());
        }
    }
    return false;
}

// Lookahead get_first_set(Grammar &grammar, Token_Set &visited, Token token) {
//     Lookahead first_set;

//     std::vector<Token> has_zero = check_rule(grammar);

//     if (std::find(has_zero.begin(), has_zero.end(), token) == has_zero.end())
//         return first_set;

//     std::vector<Rule> rules = grammar[token];

//     for (auto rule : rules) {
//         for (auto search : rule.get_head())
//         if (std::find(has_zero.begin(), has_zero.end(), search) == has_zero.end())
//             break;
        
//         std
//     }

//     // for (auto search : has_zero) {
//     //     for (auto elem : rules) {
//     //         if (std::find(elem.get_tail().begin(), elem.get_tail().end(), search) == elem.get_tail().end())
//     //             break;
//     //     }
//     // }
//     // }
    
//     for (size_t i = 0; i < rules.size(); i++) {
//         Rule prod_rule = rules[i];
//         Token next_token = rules[i].get_first_tail();

        
//         if (next_token.isTerminal)
//             first_set.insert(next_token);
        
//         else if (next_token == token) {
//             if (!visited.count(next_token)) {
//                 Lookahead temp = get_first_set(grammar, visited, next_token);
//             }
//         }
//     }
    
// }

Lookahead get_first_set(const Grammar &grammar, Token token, int idx) {
    Lookahead first_set;
    Token null = Token();

    // Terminating condition in recursion
    if (token.isTerminal || token == null) {
        first_set.insert(token);
        return first_set;   
    }

    std::vector<Rule> rules = grammar.at(token);
    Token_Set zero_set;

    // Check if the current token contains the null token
    if (check_zero(grammar, zero_set, token)) {
        first_set.insert(null);
    }

    bool all_empty = true;

    for (size_t i = 0; i < rules.size(); i++) {
        Rule prod_rule = rules[i];
        Token next_token = rules[i].get_tail()[idx];

        // Check if any of the other tokens/non-terminals in the rule contain a null token
        bool left_token_null = true;
        for (size_t j = 0; j < prod_rule.get_tail().size() - 1; j++) {
            zero_set.clear();

            if (!check_zero(grammar, zero_set, prod_rule.get_tail()[j])) {
                left_token_null = (j == 0) ? false : true;

                all_empty = false;
                break;
            }
        }
        
        if (idx < prod_rule.get_length() && next_token != token) {
            Lookahead temp = get_first_set(grammar, next_token, idx);
            
            if (left_token_null)
                temp.erase(null);

            first_set.insert(temp.begin(), temp.end());
        }

        if (left_token_null && idx + 1 < prod_rule.get_length() && next_token != token) {
            Token next_next_token = prod_rule.get_tail()[idx + 1];
            Lookahead temp = get_first_set(grammar, next_next_token, idx);

            if (temp.count(null) != 0)
                temp.erase(null);

            first_set.insert(temp.begin(), temp.end());
        }

    }

    if (all_empty)
        first_set.insert(null);

    return first_set;
}

// State closure(Rule rule, Lookahead &visited, State grammar) {
//     State closure_set;

//     Token head = rule.get_head();
//     for (auto elem : grammar) {
//         if (elem.get_head() != head)
//             continue;

//         Rule prod_rule = elem;
//         Token next_token = elem.get_first_tail();

//         closure_set.push_back(elem);
//     }

//     return closure_set;
// }

void print_grammar(Grammar &grammar) {
    for (auto &pair : grammar) {
        std::cout << pair.first << "\t: ";

        for (size_t i = 0; i < pair.second.size(); i++) {
            pair.second[i].print_rule();

            if (i == pair.second.size() - 1)
                break;

            std::cout << " | ";
        }
        std::cout << std::endl;
    }
}

Parser::Parser() {

}

