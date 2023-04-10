#include "util/parser.hpp"
#include <unordered_set>

int main(int argc, char const *argv[]) {

    /* Rules for grammar 1 */
    Rules S_rules = {
        Rule({Token(A), Token(C), Token(B)}),
        Rule({Token(C), Token(b, "b"), Token(b,"b")}),
        Rule({Token(B), Token(a, "a")})
    };

    Rules A_rules = {
        Rule({Token(d, "d"), Token(a, "a")}),
        Rule({Token(B), Token(C)})
    };

    Rules B_rules = {
        Rule({Token(g, "g")}),
        Rule({Token()})
    };

    Rules C_rules = {
        Rule({Token(h, "h")}),
        Rule({Token()})
    };
    

    /* Rules for grammar 2 */
    Rules E_rules = {
        Rule({Token(T), Token(EE)})
    };

    Rules EE_rules = {
        Rule({Token(PLUS, "+"), Token(T), Token(EE)}),
        Rule({Token()})
    };

    Rules T_rules = {
        Rule({Token(F), Token(TT)})
    };

    Rules TT_rules = {
        Rule({Token(MUL_OP, "*"), Token(F), Token(TT)}),
        Rule({Token()})
    };

    Rules F_rules = {
        Rule({Token(LPAR, "("), Token(E), Token(RPAR, ")")}),
        Rule({Token(ID, "token", "token")})
    };


    /* Rules for grammar 3 */
    Rules S_rules_3 = {
        Rule({Token(E), Token(_EOF)})
    };

    Rules E_rules_3 = {
        Rule({Token(E), Token(PLUS, "+"), Token(T)}),
        Rule({Token(T)})
    };

    Rules T_rules_3 = {
        Rule({Token(ID, "token_2", "token_2")}),
        Rule({Token(LPAR, "("), Token(E), Token(RPAR, ")")})
    };
    
    /* Grammar 1 */
    Grammar grammar {
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

    for (const auto &pair : grammar) {
        std::cout << pair.first << '\t' << "= ";
        std::cout << "{";
        for (const auto& items : get_first_set(grammar, pair.first, 0))
            std::cout << items << " ";
        std::cout << "}";
        std::cout << std::endl;
    }

    return 0;
}
