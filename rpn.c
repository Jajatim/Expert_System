#include "exp_sys.h"


//WARNING : pas de gestion d'erreur dans ces fonctions ! Envoyer uniquement des chaines bien formatées !!


static void strip_ending(char *expr) {
    for (int i = 0 ; expr[i] != '\0' ; i++) {
        if (expr[i] == '=') {
            expr[i] = '\0';
            break;
        }
    }
}

static void replace_with_val(char *expr, _Bool *values) {
    for (int i = 0 ; expr[i] != '\0' ; i++) {
        if (expr[i] >= 'A' && expr[i] <= 'Z')
            expr[i] = values[expr[i] - 'A'] + '0';
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

static int solve_op(char op, char *expr, int start, int end) {
    for (int i = start ; i < end ; i++) {
        if (expr[i] == op) {
            int j;
            int left;
            int right;
            //Adding the left operand
            j = i - 1;
            while (expr[j] != '0' && expr[j] != '1')
                j--;
            left = expr[j];
            expr[j] = ' ';

            //Adding the right operand
            j = i + 1;
            while (expr[j] != '0' && expr[j] != '1')
                j++;
            right = expr[j];
            expr[j] = ' ';

            //Solves the operation and writes the answer on the operation
            if (op == '^')
                expr[i] = ((left - '0') ^ (right - '0')) + '0';
            else if (op == '+')
                expr[i] = ((left - '0') & (right - '0')) + '0';
            else if (op == '|')
                expr[i] = ((left - '0') | (right - '0')) + '0';

            return 1;
        }
    }
    return 0;
}

static void solve_expr(char *expr, int start, int end) {
    printf("Solving : ");
    for (int i = start ; i < end ; i++)
        printf("%c", expr[i]);
    printf("\n");
    
    //Adding NOTs to queue
    for (int i = start ; i < end ; i++) {
        if (expr[i] == '!') {
            expr[i] = ' ';
            int j = i + 1;
            while (expr[j] != '0' && expr[j] != '1')
                j++;
            if (expr[j] == '0')
                expr[j] = '1';
            else if (expr[j] == '1')
                expr[j] = '0';
        }
    }
    
    //Finding and solving operations
    while (solve_op('^', expr, start, end))
        ;
    while (solve_op('+', expr, start, end))
        ;
    while (solve_op('|', expr, start, end))
        ;
}

_Bool rpn(char *expr, _Bool* values) {
    printf("Received : |%s|\n",expr);

    strip_ending(expr);
    printf("Ending stripped : |%s|\n",expr);

    replace_with_val(expr, values);
    printf("Letters changed to vals : |%s|\n",expr);

    int start, end;
    find_innermost_paren(expr, &start, &end);
    while (start != -1 && end != -1) {
        solve_expr(expr, start + 1, end);

        expr[start] = ' ';
        expr[end] = ' ';
        find_innermost_paren(expr, &start, &end);

        printf("Intermediate solving : |%s|\n", expr);
    }
    printf("Solved parenthesis : |%s|\n",expr);
    
    solve_expr(expr, 0, (int)strlen(expr));
    printf("Solved last expr : |%s|\n",expr);

    for (int i = 0 ; expr[i] != '\0' ; i++)
        if (expr[i] == '0' || expr[i] == '1')
            return expr[i] - '0';

    return -1;
}