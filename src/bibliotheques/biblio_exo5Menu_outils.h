// -------------------------------------------------------------------------------------------
// Seance 2 - 02 fev. 2022
// Kantane Pritam Charles
// 3PSC - groupe 1
// Bibliotheque pour le 'Menu - ETUDIANTS' - version 1.0
// -------------------------------------------------------------------------------------------
#define nbmax 20
#define nbmax_char 40

// ---------------------------------------------------------------------------------------------------------------------
// Definition des structures
// ---------------------------------------------------------------------------------------------------------------------
// --- La structure date ---
typedef struct {
    int jour, mois, annee;
} date;

// --- La structure etudiant ---
typedef struct {
    char nom[nbmax_char], prenom[nbmax_char];
    date ddn;
    int nb_notes;
    float note[nbmax], coeff[nbmax], moyenne;      // tableaux note et coeff : contiennent 20 emplacements
} etudiant;

// ---------------------------------------------------------------------------------------------------------------------
// Definition des fonctions et des procedures
// ---------------------------------------------------------------------------------------------------------------------
void verification_date_de_naissance (int *jour, int *mois, int *annee) {
    bool etat_gen, etat_annee, etat_mois, etat_jour;

    do {
        if ((*jour <= 0) || (*jour > 31)) {
            printf("\nLe jour doit etre compris 1 et 31. Veuillez corriger cette information.");     // si des le debut, jour > 31, on avertit l'utilisateur
            etat_jour = FALSE;
        }
        else {
            etat_jour = TRUE;
        }
        if ((*annee < 1990) || (*annee > 2010)) {     // annee comprise entre 1990 et 2010
            printf("\nL'annee doit etre comprise entre 1990 (inclus) et 2010 (inclus). Veuillez corriger cette information.");
            etat_annee = FALSE;
        }
        else {
            etat_annee = TRUE;
        }

        if ((*mois < 0) || (*mois > 12)) {
            printf("\nLe mois doit etre compris entre 1 et 12.");
            etat_mois = FALSE;
        }
        else {
            etat_mois = TRUE;
            if (etat_jour == TRUE) {
                if (((*mois > 0) && (*mois < 8)) && (*mois % 2 == 0)) {     // les mois pairs compris entre 1 et 7 ont 30 jours
                    if ((*jour <= 0) || (*jour > 30)) {
                        printf("\nIl y a 30 jours dans ce mois. Veuillez corriger cette information.");
                        etat_jour = FALSE;
                    }
                    else {
                        etat_jour = TRUE;
                    }
                }
                else if (((*mois > 0) && (*mois < 8)) && (*mois % 2 != 0)) {     // les mois impairs compris entre 1 et 7 ont 31 jours
                    if ((*jour <= 0) || (*jour > 31)) {
                        printf("\nIl y a 31 jours dans ce mois. Veuillez corriger cette information.");
                        etat_jour = FALSE;
                    }
                    else {
                        etat_jour = TRUE;
                    }
                }

                if (((*mois >= 8) && (*mois < 13)) && (*mois % 2 == 0)) {     // les mois pairs compris entre 8 et 12 ont 31 jours
                    if ((*jour <= 0) || (*jour > 31)) {
                        printf("\nIl y a 30 jours dans ce mois. Veuillez corriger cette information.");
                        etat_jour = FALSE;
                    }
                    else {
                        etat_jour = TRUE;
                    }
                }
                else if (((*mois >= 8) && (*mois < 13)) && (*mois % 2 != 0)) {     // les mois impairs compris entre 8 et 12 ont 30 jours
                    if ((*jour <= 0) || (*jour > 30)) {
                        printf("\nIl y a 31 jours dans ce mois. Veuillez corriger cette information.");
                        etat_jour = FALSE;
                    }
                    else {
                        etat_jour = TRUE;
                    }
                }
            }
            if (etat_annee == TRUE) {
                if (*mois == 2) {
                    if ((*annee % 4 == 0) && (*jour <= 0) || (*jour >= 30)) {     // verification d l'annee bissextile ou non
                        printf("\n%d est une annee bissextile. Il y a 29 jours dans ce mois.", *annee);
                        etat_jour = FALSE;
                    }
                    else if ((*annee % 4 != 0) && (*jour <= 0) || (*jour >= 29)) {
                        printf("\n%d n'est pas une annee bissextile. Il y a 28 jours dans ce mois.", *annee);
                        etat_jour = FALSE;
                    }
                    else {
                        etat_jour = TRUE;
                    }
                }
            }
        }
        if ((etat_jour == FALSE) || (etat_mois == FALSE) || (etat_annee == FALSE)) {     // on demande la date de naissance tant qu'une condition est vérifiée
            printf("\n\nEntrez votre date de naissance (jj/mm/aaaa) :");
            scanf("%d/%d/%d", jour, mois, annee);
            etat_gen = FALSE;     // on attribue FALSE a l'etat general pour refaire une verification du input qui vient d'etre fait
        }
        else {
            etat_gen = TRUE;     // sinon on retourne TRUE et on quitte le do.
        }
    } while (etat_gen == FALSE);
    system("pause");
}

etudiant saisir_1_etudiant () {
    etudiant e;     // declaration d'un etudiant
    int i;
    float somme_note = 0, somme_coeff = 0;

    do {
        printf("\nCombien de notes voulez-vous entrer (entre 1 et 20 inclus)?");     // on demande a l'utilisateur combien de notes il veut entrer
        scanf("%d", &e.nb_notes);
    } while (e.nb_notes < 1 || e.nb_notes > 20);     // le nombre de notes est compris entre 1 et 20 = taille des tableaux notes et coefficients

    titre("Fiche Etudiant", 0);

    // on entre ses coordonnees
    printf("\nNom :");
    scanf("%s",&e.nom);

    printf("\nPrenom :");
    scanf("%s",&e.prenom);

    printf("\nEntrez la date de naissance (jj/mm/aaaa) :");
    scanf("%d/%d/%d", &e.ddn.jour ,&e.ddn.mois, &e.ddn.annee);
    verification_date_de_naissance(&e.ddn.jour, &e.ddn.mois, &e.ddn.annee);     // appel de la fonction verifier la date de naissance

    for (i = 0; i < e.nb_notes; i++) {                      // on boucle autant de fois que l'utilisateur veut entrer de notes
        do {
            printf("\nNote %d :", i + 1);
            scanf("%f", &e.note[i]);
        } while (e.note[i] < 0 || e.note[i] > 20);          // note comprise entre 0 (inclus) et 20 (inclus)

        do {
            printf("\nCoefficient de la note %d (entre 1 inclus et 5 inclus) :", i + 1);
            scanf("%f", &e.coeff[i]);
        } while(e.coeff[i] < 1 || e.coeff[i] > 5);          // et coeff compris entre 1 (inclus) et 5 (inclus)
    }

    for (i = 0; i < e.nb_notes; i++) {
        somme_note += e.note[i] * e.coeff[i];
        somme_coeff += e.coeff[i];
    }
    e.moyenne = somme_note / somme_coeff;                   // calcul de la moyenne en prenant en compte les coeff.

    return e;
}

void afficher_1_etudiant(etudiant e) {
    int i;

    // affiche des coordonnees de l'etudiant
    printf("\nNom : %s", e.nom );
    printf("\nPrenom : %s", e.prenom );
    printf("\n%s %s est ne(e) le %d/%d/%d.", e.prenom, e.nom, e.ddn.jour, e.ddn.mois, e.ddn.annee);

    // on affiche toutes les notes ainsi que les coefficients correspondants
    for (i = 0; i < e.nb_notes; i++) {
        printf("\n\nNote %d : %.2f", i + 1, e.note[i]);
        printf("\nCoeffcient de la note %d : %.2f", i + 1, e.coeff[i]);
    }

    tiret();
    printf("\nMoyenne : %.2f", e.moyenne);
    tiret();
}

bool effacer_1_etudiant (etudiant *e, int *compteur, int *n_save) {
    int i, j, k, l, etat_etu_a_eff;
    char choix_eff[nbmax_char];

    system("cls");
    printf("\nListe des noms du/des etudiant(e)s enregistre(e)s");
    for (k = 0; k < *compteur; k++) {
        printf("\n%d - %s", k + 1, (e + k)->nom);          // on affiche la liste des etudiants enregistres pour plus de confort
    }

    do {
        printf("\n\nQuel est l'etudiant dont vous voulez effacer les coordonnees (entrer son nom) ?");     // on demande a l'utilisateur d'entrer le nom de l'etudiant a effacer
        scanf("%s", choix_eff);

        for (l = 0; l < *compteur; l++) {
            if (strcmp(choix_eff, (e + l)->nom) == 0) {
                printf("\nEffacement des coordonnees de l'etudiant(e) ...");
                Sleep(500);
                etat_etu_a_eff = 1;                  // on incremente etat_etu_a_eff pour sortir du do
            }
            else {
                printf("Vous n'avez pas entre le bon numero. Veuillez reessayer.");
            }
        }
    } while (etat_etu_a_eff == 0);                       // tant que etat_etu_a_eff == 0, on execute ce qu'il y a dans le do

    for (i = 0; i < *compteur; i++) {                    // on parcourt le tableau d'etudiants enregistres
        if (strcmp((e + i)->nom, choix_eff) == 0) {      // on compare si la recherche de l'utilisateur correspond a un nom d'etudiant
            for (j = i; j < *n_save; j++) {              // on parcourt le tableau d'etudiants a partir de l'indice i jusqu'a la taille max du tableau
                if (j < *n_save - 1) {                   // si j < max du tableau
                    *(e + j) = *(e + j + 1);             // on decale d'un rang vers la gauche tous les etudiants qui sont apres l'etudiant a effacer
                }
                else {                                                                              // si le tableau contient qu'un seul element
                    e = (etudiant *) calloc(0, sizeof(etudiant));     // on donne au tableau la taille 0 en appelant la methode calloc qui attribue l'espace apres avoir assigne des 0 aux espaces a allouer
                }                                                                                   // donc (etudiant *) calloc(0, sizeof(etudiant)) => le tableau n'existe pas
            }
        }
    }
}

void afficher_n_etudiant_dynamic (etudiant *e, int n) {
    int i;

    system("cls");
    for (i = 0; i < n; i++) {
        titre("\nFiche Etudiant", i + 1);
        afficher_1_etudiant(*(e + i)); // pour i allant de 0 jusqu'a n (exclus), on affiche les coordonnees de l'etudiant
        printf("\n");
    }
    system("pause");
}

void nombre_etudiant (int *n, int *n_save) {
    do {
        printf("\nSaisir un nombre entre 1 et %d (exclus) d'etudiants:", nbmax);
        scanf("%d", n);
    } while (*n <= 0 || *n > nbmax);
    *n_save += *n;     // on ajoute la valeur du input n a une variable n_save pour le realloc
}
