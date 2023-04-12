#include "parser.hpp"

Rule::Rule(Token head, Tail tail) {
    this->head = head;
    this->tail = tail;
    this->pos = 0;
    this->num_tail = tail.size();
    this->lookahead_token = Token();
}

Rule::Rule(Token head, Tail tail, Token lookahead_token) {
    this->head = head;
    this->tail = tail;
    this->pos = 0;
    this->num_tail = tail.size();
    this->lookahead_token = lookahead_token;
}

Rule::Rule(Token head, Tail tail, int pos, Token lookahead_token) {
    this->head = head;
    this->tail = tail;
    this->pos = pos;
    this->num_tail = tail.size();
    this->lookahead_token = lookahead_token;
}

void Rule::print_rule(void) {

    for (size_t i = 0; i < num_tail; i++) {
        if (i == pos) std::cout << ". ";
        std::cout << this->tail[i] << " ";
    }

    std::cout << "{ " << this->lookahead_token << " }" << std::endl;
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

Lookahead get_first_set(const Grammar &grammar, Token token, int idx) {
    Lookahead first_set;
    Token null = Token();

    // Terminating condition in recursion
    if (token.isTerminal || token == null) {
        first_set.insert(token);
        return first_set;   
    }

    Rules rules = grammar.at(token);
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

Lookahead_Set get_first_set_table(const Grammar &grammar) {
    Lookahead_Set first_set_table;
    for (const auto &pair : grammar) {
        Lookahead first_set = get_first_set(grammar, pair.first, 0);
        first_set_table.emplace(pair.first, first_set);
    }

    return first_set_table;
}


bool in(const Rule &source_rule, const State &rules) {
    for (const auto &item : rules) {
        if (item == source_rule)
            return true;
    }
    return false;
}

State closure(Rule &rule, const Lookahead_Set &first_set_table, const Grammar &grammar) {
    // head and rule are should be tied together in grammar
    Token null = Token();
    State state;

    state.push_back(rule);

    if (rule.get_next_token().isTerminal ||
        rule.get_next_token() == null ||
        rule.get_next_token().token_type == _EOF
    ) 
        return state;

    Lookahead lookahead_set;


    for (size_t i = rule.get_current_pos() + 1; i < rule.get_length(); i++) {
        if (rule[i].isTerminal ||
            rule[i] == null ||
            rule[i].token_type == _EOF
        ) {
            lookahead_set.emplace(rule[i]);
            break;

        } else {
            lookahead_set.insert(first_set_table.at(rule[i]).begin(), first_set_table.at(rule[i]).end());
            
            if (first_set_table.at(rule[i]).find(null) == first_set_table.at(rule[i]).end()) {
                break;
            }
        }
    }

    if (lookahead_set.find(null) != lookahead_set.end())
        lookahead_set.insert(rule.get_lookahead());

    lookahead_set.erase(null);
    
    if (lookahead_set.empty())
        lookahead_set.insert(rule.get_lookahead());


    Rules rules_of_next_closure = grammar.at(rule.get_next_token());

    for (auto &next_rule : rules_of_next_closure) {
        for (auto &lookahead : lookahead_set) {
            
            Rule new_rule_copy = Rule(next_rule.get_head(), next_rule.get_tail(), lookahead);

            State child_states = closure(new_rule_copy, first_set_table, grammar);

            for (const auto &elem : child_states) {
                if (!in(elem, state))
                    state.push_back(elem);
            }
        }
    }

    return state;
}

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

void print_first_set_table(Lookahead_Set &first_set_table) {
    for (auto const &pair : first_set_table) {
        std::cout << pair.first << "\t: ";

        for (auto const &elem : pair.second)
            std::cout << elem << ",  ";

        std::cout << std::endl;
    }
}


Parser::Parser() {

}

