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

bool contains_zero(Lookahead set) {
    Token Null = Token();
    return !(set.count(Null) == 0);
}

bool check_zero(Grammar &grammar, Token_Set &visited, Token token) {
    std::vector<Token> has_zero;
    Token Null = Token();

    if (token.isTerminal)
        return false;
    
    for (auto item : grammar[token]) {
        if (visited.find(item.get_first_tail()) != visited.end())
            continue;

        if (item.get_first_tail() == Null)
            return true;

        if (!(item.get_first_tail().isTerminal)) {
            visited.insert(token);
            return check_zero(grammar, visited, item.get_first_tail());
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

Lookahead get_first_set(Grammar &grammar, const Token token, int idx) {
    Lookahead first_set;

    // Terminating condition in recursion
    if (token.isTerminal) {
        first_set.insert(token);
        return first_set;   
    }

    std::vector<Rule> rules = grammar[token];
    Token_Set zero_set;
    Token null = Token();

    // Check if the current token contains the null token
    if (check_zero(grammar, zero_set, token)) first_set.insert(null);

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

        // if (next_token == token) {
        //     if (!visited.count(next_token)) {
        //         visited.insert(token);
        //         Lookahead temp = get_first_set(grammar, visited, next_token);

        //         if (temp.count(null) == 0)
        //             first_set.insert(temp.begin(), temp.end());

        //         else {
        //             if (!left_token_null)
        //                 first_set.insert(null);
        //         }
        //     }
        
        if (idx < prod_rule.get_tail().size() && next_token != token) {
            Lookahead temp = get_first_set(grammar, next_token, idx);
            
            if (left_token_null)
                temp.erase(null);

            first_set.insert(temp.begin(), temp.end());

            // else {
            //     // std::cout << "Test" << std::endl;
            //     if (!left_token_null)
            //         first_set.insert(null);
                   
            //     // temp.erase(Token());
            //     // Token next_next_token = prod_rule.get_tail()[i + 1];
            //     // // std::cout << next_next_token << std::endl;
            //     // temp = get_first_set(grammar, visited, next_next_token);
            // }
        }

        if (left_token_null && idx + 1 < prod_rule.get_tail().size() && next_token != token) {
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

