#include "exp_sys.h"


void queue_add(s_queue **q, char data) {
    s_queue *new = NULL;

    new = malloc(sizeof(s_queue));
    if (new == NULL) {
        printf("Malloc err\nErr management TODO\nExiting...\n");
        exit(1);
    }
    new->data = data;
    new->next = NULL;
    
    if (*q == NULL)
        *q = new;
    else {
        s_queue *crawler = *q;
        while (crawler->next != NULL)
            crawler = crawler->next;
        crawler->next = new;
    }
}

char queue_pop(s_queue **q) {
    if (*q == NULL) {
        printf("This queue is empty mate... Go pop yourself.\n");
        return -1;
    }

    s_queue *crawler = *q;
    char res = crawler->data;
    *q = crawler->next;
    free(crawler);
    return res;
}

void queue_print(s_queue **q) {
    int i = 1;
    s_queue *crawler = *q;

    while (crawler) {
        printf("Queue %d : %c\n", i++, crawler->data);
        crawler = crawler->next;
    }
}