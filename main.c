// -------------------------------------------------------------------------------------------
// Seance 3 - 02 fev. 2022
//
// 3PSC - groupe 1
// Menu - ETUDIANTS - version 1.0
// -------------------------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
#include "src/bibliotheques/outils_affichage.h"
#include "src/bibliotheques/biblio_exo5Menu_outils.h"
#include "src/bibliotheques/biblio_menu.h"

int main () {
    // declaration des variables
    bool etat;
    int compteur = 0, ntab = 0, n_save = 0;

    // boucle le menu tant que etat == TRUE
    do {
        etat = affichage_menu(&compteur, &ntab, &n_save);     // affichage_menu renvoie un booleen
    } while (etat == TRUE);
}