#include "exp_sys.h"

void queue_tester() {
    s_queue *q1 = NULL;
    s_queue *q2 = NULL;
    
    char res;
    res = queue_pop(&q1);
    printf("popped %c\n",res);
    queue_add(&q1, 'A');
    queue_add(&q1, 'B');
    queue_add(&q1, 'C');
    res = queue_pop(&q1); printf("popped %c\n",res);
    res = queue_pop(&q1); printf("popped %c\n",res);
    res = queue_pop(&q1); printf("popped %c\n",res);
    res = queue_pop(&q1); printf("popped %c\n",res);

    queue_pop(&q2);
    queue_add(&q2, 'X');
    queue_add(&q2, 'Y');
    queue_add(&q2, 'Z');
    res = queue_pop(&q2); printf("popped %c\n",res);
    res = queue_pop(&q2); printf("popped %c\n",res);
    res = queue_pop(&q2); printf("popped %c\n",res);
    res = queue_pop(&q2); printf("popped %c\n",res);
}

int main(int argc, char **argv) {
    _Bool values[26] = {0};

    //Test data
    char s[99] = "A+!B+(C+!(D+!E)+F)+(G+H) => D";
    values[A] = 1;
    values[C] = 1;
    values[E] = 1;
    values[G] = 1;
    values[H] = 1;


    printf("Initial values : \n");
    for (int i = 0 ; i < 26 ; i++)
        printf("%s%c=%d", i?", ":"", i+'A', values[i]);
    printf("\n");

    int res = rpn((char *)s, (_Bool *)values);
    if (res == -1)
        printf("Something has gone wrong...\n");
    else
        values[D] = res;

    printf("\nFinal values : \n");
    for (int i = 0 ; i < 26 ; i++)
        printf("%s%c=%d", i?", ":"", i+'A', values[i]);
    printf("\n");

    return 0;
}