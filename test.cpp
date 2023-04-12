#include "util/parser.hpp"
#include <unordered_set>

int main(int argc, char const *argv[]) {

    /* Rules for grammar 1 */

    Rule starting_F_rule = Rule(Token(F), {Token(S), Token(_EOF)}, {Token(_EOF)});

    Rules F_rules_start = {
        starting_F_rule
    };

    Rules S_rules = {
        Rule(Token(S), {Token(A), Token(C), Token(B)}),
        Rule(Token(S), {Token(C), Token(b, "b"), Token(b,"b")}),
        Rule(Token(S), {Token(B), Token(a, "a")})
    };

    Rules A_rules = {
        Rule(Token(A), {Token(d, "d"), Token(a, "a")}),
        Rule(Token(A), {Token(B), Token(C)})
    };

    Rules B_rules = {
        Rule(Token(B), {Token(g, "g")}),
        Rule(Token(B), {Token()})
    };

    Rules C_rules = {
        Rule(Token(C), {Token(h, "h")}),
        Rule(Token(C), {Token()})
    };
    

    /* Rules for grammar 2 */
    Rules E_rules = {
        Rule(Token(E), {Token(T), Token(EE)})
    };

    Rules EE_rules = {
        Rule(Token(EE), {Token(PLUS, "+"), Token(T), Token(EE)}),
        Rule(Token(EE), {Token()})
    };

    Rules T_rules = {
        Rule(Token(T), {Token(F), Token(TT)})
    };

    Rules TT_rules = {
        Rule(Token(TT), {Token(MUL_OP, "*"), Token(F), Token(TT)}),
        Rule(Token(TT), {Token()})
    };

    Rules F_rules = {
        Rule(Token(F), {Token(LPAR, "("), Token(E), Token(RPAR, ")")}),
        Rule(Token(F), {Token(ID, "token", "token")})
    };

    /* Rules for grammar 3 */
    Rules S_rules_3 = {
        Rule(Token(S), {Token(E), Token(_EOF)})
    };

    Rules E_rules_3 = {
        Rule(Token(E), {Token(E), Token(PLUS, "+"), Token(T)}),
        Rule(Token(E), {Token(T)})
    };

    Rules T_rules_3 = {
        Rule(Token(T), {Token(ID, "token_2", "token_2")}),
        Rule(Token(T), {Token(LPAR, "("), Token(E), Token(RPAR, ")")})
    };
    
    /* Grammar 1 */
    Grammar grammar {
        {Token(F), F_rules_start},
        {Token(S), S_rules},
        {Token(A), A_rules},
        {Token(B), B_rules},
        {Token(C), C_rules}
    };

    /* Grammar 2 */
    Grammar grammar2 {
        {Token(E), E_rules},
        {Token(EE), EE_rules},
        {Token(T), T_rules},
        {Token(TT), TT_rules},
        {Token(F), F_rules}
    };

    /* Grammar 3 */
    Grammar grammar3 {
        {Token(S), S_rules_3},
        {Token(E), E_rules_3},
        {Token(T), T_rules_3}
    };


    print_grammar(grammar);
    std::cout << std::endl;

    std::cout << std::endl;

    Lookahead_Set first_set_table = get_first_set_table(grammar);

    // print_first_set_table(first_set_table);
    // Lookahead lookahead_F({_EOF});

    State state_0 = closure(starting_F_rule, first_set_table, grammar);

    State state_1 = go_to(state_0, Token(S), first_set_table, grammar);

    print_state(state_1);

    State state_2 = go_to(state_1, Token(_EOF), first_set_table, grammar);

    print_state(state_2);

    State state_3 = go_to(state_0, Token(B), first_set_table, grammar);

    print_state(state_3);

    return 0;
}
