#ifndef EXP_SYS_H
#define EXP_SYS_H


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

//Operator precedence : NOT > XOR > AND > OR
#define NOT_WEIGHT 3
#define XOR_WEIGHT 2
#define AND_WEIGHT 1
#define OR_WEIGHT 0

typedef struct s_queue {
    char data;
    struct s_queue *next;
} s_queue;

enum {
    A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z
};

_Bool rpn(char *expr, _Bool* values);

void queue_add(s_queue **s, char c);
char queue_pop(s_queue **s);
void queue_print(s_queue **s);

#endif //EXP_SYS_H