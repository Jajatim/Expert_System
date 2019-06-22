#include "exp_sys.h"


//WARNING : pas de gestion d'erreur dans ces fonctions !
// -> Envoyer uniquement des chaines bien formatées !!


static void strip_ending(char *expr) {
    for (int i = 0 ; expr[i] != '\0' ; i++) {
        if (expr[i] == '=') {
            expr[i] = '\0';
            break;
        }
    }
}

static void replace_with_val(char *expr, _Bool *facts) {
    for (int i = 0 ; expr[i] != '\0' ; i++) {
        if (expr[i] >= 'A' && expr[i] <= 'Z')
            expr[i] = facts[expr[i] - 'A'] + '0';
    }
}

static void find_innermost_paren(char *expr, int *start, int *end) {
    *start = -1;
    *end = -1;
    for (int i = 0 ; expr[i] != '\0' ; i++) {
        if (expr[i] == '(')
            *start = i;
        else if (expr[i] == ')') {
            *end = i;
            break;
        }
    }
}

static int get_operand_pos(char *expr, int i, int step) {
    int j = i + step;
    while (expr[j] != '0' && expr[j] != '1')
        j = j + step;

    return j;
}

static void solve_expr(char *expr, int start, int end) {
    //solving NOTs
    for (int i = start ; i < end ; i++) {
        if (expr[i] == '!') {
            expr[i] = ' ';
            while (expr[i] != '0' && expr[i] != '1')
                i++;
            expr[i] = (expr[i] == '0') ? '1' : '0';
        }
    }
    
    //Solving XORs
    for (int i = start ; i < end ; i++) {
        if (expr[i] == '^') {
            int last_nb = get_operand_pos(expr, i, -1);
            int next_nb = get_operand_pos(expr, i, +1);
            expr[i] = ((expr[last_nb] - '0') ^ (expr[next_nb] - '0')) + '0';
            expr[last_nb] = ' ';
            expr[next_nb] = ' ';
            i = next_nb;
        }
    }

    //Solving ANDs
    for (int i = start ; i < end ; i++) {
        if (expr[i] == '+') {
            int last_nb = get_operand_pos(expr, i, -1);
            int next_nb = get_operand_pos(expr, i, +1);
            expr[i] = ((expr[last_nb] - '0') & (expr[next_nb] - '0')) + '0';
            expr[last_nb] = ' ';
            expr[next_nb] = ' ';
            i = next_nb;
        }
    }

    //Solving ORs
    for (int i = start ; i < end ; i++) {
        if (expr[i] == '|') {
            int last_nb = get_operand_pos(expr, i, -1);
            int next_nb = get_operand_pos(expr, i, +1);
            expr[i] = ((expr[last_nb] - '0') | (expr[next_nb] - '0')) + '0';
            expr[last_nb] = ' ';
            expr[next_nb] = ' ';
            i = next_nb;
        }
    }
}

int solver(char *expr, _Bool* facts) {
    if (DEBUG_SOLVER) printf("|%s| Received\n",expr);

    strip_ending(expr);
    if (DEBUG_SOLVER) printf("|%s| Ending stripped\n",expr);

    replace_with_val(expr, facts);
    if (DEBUG_SOLVER) printf("|%s| Letters changed to vals\n",expr);

    //Solving parenthesis first
    int start, end;
    find_innermost_paren(expr, &start, &end);
    while (start != -1 && end != -1) {
        //Solving the expression between the parenthesis
        solve_expr(expr, start + 1, end);

        //Erasing parenthesis
        expr[start] = ' ';
        expr[end] = ' ';

        //Finding next parenthesis
        find_innermost_paren(expr, &start, &end);

        if (DEBUG_SOLVER) printf("|%s| Intermediate solving\n", expr);
    }
    if (DEBUG_SOLVER) printf("|%s| Solved parenthesis\n",expr);
    
    solve_expr(expr, 0, (int)strlen(expr));
    if (DEBUG_SOLVER) printf("|%s| Solved last expr\n",expr);

    //Returns -1 if more than one bool left in the char, else returns 0 or 1
    int res = -1;
    for (int i = 0 ; expr[i] != '\0' ; i++) {
        if (expr[i] == '0' || expr[i] == '1') {
            if (res != -1)
                return -1;
            res = expr[i] - '0';
        }
    }
    return res;
}