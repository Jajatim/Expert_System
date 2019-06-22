#include "exp_sys.h"

int main(int argc, char **argv) {
    
    /* DEBUT INIT */
    
    //TODO : Tableau des règles en fonction des faits
    // ex : rules[A] contiendra toutes les règles qui définissent A
    //  (sera à remplir dans le parser)
    char rules[26][10][99]; //Rappel : la 3eme dimension correspond à la taille de la chaine
    for (int fact = 0 ; fact < 26 ; fact++)
        for (int rule = 0 ; rule < 10 ; rule++)
            for (int c = 0 ; c < 99 ; c++)
                rules[fact][rule][c] = '\0'; //Init des chaines à vide
    strcpy(rules[E][0], "A | B + C => E");
    strcpy(rules[E][1], "(F | G) + H => E");

    //TODO : Faits initiaux
    // (sera à remplir dans le parser)
    _Bool facts[26] = {0};
    facts[A] = 1;
    //facts[C] = 1;

    //TODO : Faits demandés
    // (sera à remplir dans le parser)
    //  Note : Facilement optimisable, mais bon, c'est juste 26 checks... donc pas très utile...
    _Bool requests[26] = {0};
    requests[E] = 1;

    /* FIN INIT */
    /* DEBUT SOLVER */

    //NOTE : Est-ce que les faits gardent leur nouvelle valeur d'un check à l'autre ?
    // Ex : 
    // Init : A = vrai
    // Règles : A => B et B => C
    // Demandés : B et C
    // En cherchant B, on trouve qu'il est vrai (car A est vrai)
    // Si on garde l'info précédente, en cherchant C il sera vrai
    //     mais si on repart de l'état initial, il sera faux...


    if (DEBUG_MAIN) {
        printf("Initial facts : \n");
        for (int i = 0 ; i < 26 ; i++)
            printf("%s%c=%d", i?", ":"", i+'A', facts[i]);
        printf("\n");
    }

    for (int req = 0 ; req < 26 ; req++) {
        //Ignoring the unrequested data
        if (!requests[req])
            continue;
        
        for (int rule = 0 ; rules[req][rule][0] != '\0' ; rule++) {
            int res = solver((char *)rules[req][rule], (_Bool *)facts);
            if (res == -1)
                printf("Something has gone wrong...\n");
            else if (res == 1)
                facts[req] = res;
        }
    }

    if (DEBUG_MAIN) {
        printf("\nFinal facts : \n");
        for (int i = 0 ; i < 26 ; i++)
            printf("%s%c=%d", i?", ":"", i+'A', facts[i]);
        printf("\n");
    }

    /* FIN SOLVER */

    //Answering the user
    for (int req = 0 ; req < 26 ; req++) {
        if (!requests[req])
            continue;
        
        printf("%c is %s\n", req + 'A', facts[req] ? "true" : "false");
    }

    return 0;
}