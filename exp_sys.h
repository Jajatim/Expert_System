#ifndef EXP_SYS_H
#define EXP_SYS_H


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


#define DEBUG_MAIN 1
#define DEBUG_SOLVER 1

typedef struct s_queue {
    char data;
    struct s_queue *next;
} s_queue;

enum {
    A=0,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z
};

int solver(char *expr, _Bool* facts);

#endif //EXP_SYS_H