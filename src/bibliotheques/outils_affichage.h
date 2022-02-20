// -------------------------------------------------------------------------------------------
// Seance 2 - 02 fev. 2022
// Kantane Pritam Charles
// 3PSC - groupe 1
// Bibliotheque de fonctions et de procedures pour un affichage esthetique
// -------------------------------------------------------------------------------------------
#include <string.h>

void tiret () {
    printf("\n---------------------------------------------------------------------");
}

void exercice (int num) {
    tiret();
    printf("\nExercice %d", num);
    tiret();
}

void titre (char un_titre[50], int i) { // deuxieme argument : si i != 0, alors on affiche un entier dans le titre, sinon il n'y a que le %s
    tiret();
    if (i == 0) {
        printf("%s", un_titre);
    }
    else if (i != 0) {
        printf("%s %d", un_titre, i);
    }
    tiret();
}

int choix_recommencer () {
    int choix;

    do {
        printf("\nVoulez-vous recommencer ? (1- Oui ; 0- Non)");
        scanf("%d", &choix);
    } while (choix != 0 && choix != 1); // tant que choix != de 0 ou 1, on execute le bloc d'instruction dans le do

    return choix;
}
