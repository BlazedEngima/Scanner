#include "util/parser.hpp"
#include <unordered_set>

int main(int argc, char const *argv[]) {
    Token S_1(S);
    Token E_1(E);
    Token E_2(EE);
    Token T_1(T);
    Token T_2(TT);
    Token F_1(F);

    Token S_token(S);
    Token A_token(A);
    Token B_token(B);
    Token C_token(C);

    Token _null_token = Token();
    Lookahead null_token {_null_token};
    
    Token plus(PLUS, "+");
    Token mul(MUL_OP, "*");
    Token lpar(LPAR, "(");
    Token rpar(RPAR, ")");
    Token id_token(ID, "char_buffer", "char_buffer");
    Token end(_EOF);

    Token small_a_token(a, "a");
    Token small_b_token(b, "a");
    Token small_d_token(d, "a");
    Token small_g_token(g, "a");
    Token small_h_token(h, "a");

    Tail S_rule {E_1, end};
    Tail E_rule {E_1, plus, T_1};
    Tail E_rule_2 {T_1};
    Tail T_rule {id_token};
    Tail T_rule_2 {lpar, E, rpar};

    Tail E_1_tail {T_1, E_2};
    Tail E_2_tail {plus, T_1, E_2};
    Tail E_2_tail_2 {_null_token};
    Tail T_1_tail {F_1, T_2};
    Tail T_2_tail {mul, F_1, T_2};
    Tail T_2_tail_2 {_null_token};
    Tail F_tail {lpar, E_1, rpar};
    Tail F_tail_2 {id_token};

    Tail S_token_tail_1 {A_token, C_token, B_token};
    Tail S_token_tail_2 {C_token, small_b_token, small_b_token};
    Tail S_token_tail_3 {B_token, small_a_token};
    Tail A_token_tail_1 {small_d_token, small_a_token};
    Tail A_token_tail_2 {B_token, C_token};
    Tail B_token_tail_1 {small_g_token};
    Tail B_token_tail_2 {_null_token};
    Tail C_token_tail_1 {small_h_token};
    Tail C_token_tail_2 {_null_token};

    Rules S;
    Rules E;
    Rules T;

    Rules E_1_rule;
    Rules E_2_rule;
    Rules T_1_rule;
    Rules T_2_rule;
    Rules F_rule;

    Rules S_rules;
    Rules A_rules;
    Rules B_rules;
    Rules C_rules;

    // State grammar;
    Grammar _grammar;
    // Grammar _grammar2;
    // Grammar _grammar3;

    Rule _S(S_1, S_rule, null_token);
    Rule _E(E_1, E_rule, null_token);
    Rule _E2(E_1, E_rule_2, null_token);
    Rule _T(T_1, T_rule, null_token);
    Rule _T2(T_1, T_rule_2, null_token);

    S.push_back(_S);
    E.push_back(_E);
    E.push_back(_E2);
    T.push_back(_T);
    T.push_back(_T2);
    // Rule _E(E_1, E_1_tail, null_token);
    // E_1_rule.push_back(_E);

    // Rule _E_2(E_2, E_2_tail, null_token);
    // Rule _E_2_2(E_2, E_2_tail_2, null_token);
    // E_2_rule.push_back(_E_2);
    // E_2_rule.push_back(_E_2_2);

    // Rule _T(T_1, T_1_tail, null_token);
    // T_1_rule.push_back(_T);

    // Rule _T_2(T_2, T_2_tail, null_token);
    // Rule _T_2_2(T_2, T_2_tail_2, null_token);
    // T_2_rule.push_back(_T_2);
    // T_2_rule.push_back(_T_2_2);

    // Rule _F(F, F_tail, null_token);
    // Rule _F_2(F, F_tail_2, null_token);
    // F_rule.push_back(_F);
    // F_rule.push_back(_F_2);

    // Rule S_rule_1(S_token, S_token_tail_1, null_token);
    // Rule S_rule_2(S_token, S_token_tail_2, null_token);
    // Rule S_rule_3(S_token, S_token_tail_3, null_token);
    // S_rules.push_back(S_rule_1);
    // S_rules.push_back(S_rule_2);
    // S_rules.push_back(S_rule_3);

    // Rule A_rule_1(A_token, A_token_tail_1, null_token);
    // Rule A_rule_2(A_token, A_token_tail_2, null_token);
    // A_rules.push_back(A_rule_1);
    // A_rules.push_back(A_rule_2);

    // Rule B_rule_1(B_token, B_token_tail_1, null_token);
    // Rule B_rule_2(B_token, B_token_tail_2, null_token);
    // B_rules.push_back(B_rule_1);
    // B_rules.push_back(B_rule_2);

    // Rule C_rule_1(C_token, C_token_tail_1, null_token);
    // Rule C_rule_2(C_token, C_token_tail_2, null_token);
    // C_rules.push_back(C_rule_1);
    // C_rules.push_back(C_rule_2);

    _grammar[S_1] = S;
    _grammar[E_1] = E;
    _grammar[T_1] = T;

    // _grammar2[E_1] = E_1_rule;
    // _grammar2[E_2] = E_2_rule;
    // _grammar2[T_1] = T_1_rule;
    // _grammar2[T_2] = T_2_rule;
    // _grammar2[F_1] = F_rule;

    // _grammar[S_token] = S_rules;
    // _grammar[A_token] = A_rules;
    // _grammar[B_token] = B_rules;
    // _grammar[C_token] = C_rules;

    for (auto const &pair : _grammar) {
        for (auto elem : pair.second)
            elem.print_rule();
    }

    // for (auto elem : grammar)
    //     elem.print_rule();

    std::cout << std::endl;
    
    Token_Set visited;
    // std::vector<Token> first_set;

    // for (auto items : _grammar) {
    //     std::cout << items.first << '\t';

    //     std::set<Token> first_set = get_first_set(_grammar, items.first, 0);
    //     for (auto elem : first_set) 
    //         std::cout << elem << std::endl;
    // }

    std::set<Token> first_set = get_first_set(_grammar, T_1, 0);

    for (auto elem : first_set)
        std::cout << elem << ' ';

    std::cout << std::endl;

    // std::vector<Rule> closure_set = closure(_S, grammar);

    // for (auto elem : closure_set)
    //     elem.print_rule();
    
    // std::cout << std::endl;

    return 0;
}
