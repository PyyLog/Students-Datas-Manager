// -------------------------------------------------------------------------------------------
// Seance 2 - 02 fev. 2022
// Kantane Pritam Charles
// 3PSC - groupe 1
// Bibliotheque pour le 'Menu - ETUDIANTS' - version 1.0
// -------------------------------------------------------------------------------------------
#define nbmax 20
#define nbmax_char 40

// ---------------------------------------------------------------------------------------------------------------------
// Definition des fonctions et procedures qui vont etre utilises dans le menu
// ---------------------------------------------------------------------------------------------------------------------
// ------------------ Fonctions d'ecriture et de lecture d'un fichier .txt ------------------
void ecrire_fichier (FILE *fp, char nom_fic[], char mode[5], char type[nbmax_char], etudiant *e, int *compteur, int *n_save) {
    int j;

    if (strcmp(type, "Saisie etudiant(e)") == 0) {         // si le type == "saisie etudiant(e)", on ecrit dans le fichier "etudiants.txt"
        fp = fopen(nom_fic, mode);          // ouverture du fichier en mode "a": on ecrit a la suite sans effacer le contenu du fichier (s'il y en a)
        if (fp == NULL) {
            printf("Erreur dans l'ouverture du fichier.");
        }
        else {
            // toutes les informations qu'on ecrit dans le fichier
            fprintf(fp, "-----------------------------------------------------------------------");
            fprintf(fp, "\nFiche Etudiant %d", *compteur);
            fprintf(fp, "\n-----------------------------------------------------------------------");
            fprintf(fp, "\nNom : %s", (e + *compteur - 1)->nom);
            fprintf(fp, "\nPrenom : %s", (e + *compteur - 1)->prenom);
            fprintf(fp, "\nDate de naissance : %d/%d/%d", (e + *compteur - 1)->ddn.jour, (e + *compteur - 1)->ddn.mois, (e + *compteur - 1)->ddn.annee);
            for (j = 0; j < e->nb_notes; j++) {
                fprintf(fp, "\n\nNote %d : %.2f", j + 1, (e + *compteur - 1)->note[j]);
                fprintf(fp, "\nCoefficient de la note %d : %.2f", j + 1, (e + *compteur - 1)->coeff[j]);
            }
            fprintf(fp, "\n-----------------------------------------------------------------------");
            fprintf(fp, "\nMoyenne : %.2f", (e + *compteur - 1)->moyenne);
            fprintf(fp, "\n-----------------------------------------------------------------------");
            fprintf(fp, "\n");
        }
        fclose(fp);                                         // on ferme le fichier pour dire que tout c'est bien passe et securiser le document
    }
    else if (strcmp(type, "Suivi compteur et ntab") == 0) {      // si le type == "Suivi compteur et ntab", on ecrit dans le fichier "suivi_compteur_tab.txt
        fp = fopen(nom_fic, mode);                // ouverture en mode ecriture
        if (fp == NULL) {
            printf("Erreur dans l'ouverture du fichier.");
        }

        // on ecrit les informations sur la longueur du tableau, le compteur d'etudiants enregistres et la place restante dans le tableau
        fprintf(fp, "n total : %d", *n_save);
        fprintf(fp, "\ncompteur : %d", *compteur);
        fprintf(fp, "\nntab (place(s) restante(s)) : %d", *n_save - *compteur);
        fclose(fp);                                      // on ferme le fichier pour dire que tout c'est bien passe et securiser le document
    }
}

void lire_fichier (FILE *f, char nom_fic[nbmax]) {
    char str[500];

    f = fopen("etudiants.txt", "r");          // on ouvre le fichier en mode lecture
    if (f == NULL) {
        printf("\nErreur d'ouverture du fichier.");
    }

    while (!feof(f)) {                                   // tant que ce n'est pas la fin du fichier
        if (fgets(str, 500, f)) {        // on lit chaque ligne du fichier
            printf("%s", str);                        // on affiche le contenu de chaque ligne
        }
    }
    fclose(f);
}

void recuperer_donnees_compteur (int *n, int *compteur, int *ntab) {
    char str[500], c[256], arr[10], *endPtr;;
    int i = 0;
    FILE *f;

    f = fopen("suivi_compteur_tab.txt", "r");
    if (f == NULL) {
        printf("\nErreur d'ouverture du fichier.");
        printf("\n");
    }

    while ((*c = fgetc(f)) != EOF) {
        if (strcmp(c, ":") == 0) {
            if (fgets(str, 500, f) != NULL) {
                arr[i] = strtod(str, &endPtr);
                i ++;
            }
        }
    }

    *n = arr[0];
    *compteur = arr[1];
    *ntab = arr[2];

    fclose(f);
}

// ------------------ Fonctions pour le choix recherche d'un etudiant ------------------
bool recherche_ddn_jma (etudiant *e, int *compteur) {
    int choix_recherche_ddn, recherche_ddn, i, etat_recherche;

    do {
        printf("\nVoulez-vous rechercher par :\n1 - Jour\n2 - Mois\n3 - Annee");     // on demande a l'utilisateur s'il veut rechercher par jour; mois; annee
        printf("\n");
        scanf("\n%d", &choix_recherche_ddn);

        switch(choix_recherche_ddn) {
            case 1:
                do {
                    printf("\nJour :");
                    scanf("\n%d", &recherche_ddn);
                    system("cls");
                } while ((recherche_ddn < 0) || (recherche_ddn > 31));

                for (i = 0; i < *compteur; i++) {                            // pour i allant de 0 au nb du compteur
                    if ((e + i)->ddn.jour == recherche_ddn) {                // si la case ddn.jour a la position i == recherche de l'utilisateur
                        titre("\nFiche Etudiant", i + 1);          // mise en page - affichage Fiche etudiant i
                        afficher_1_etudiant(*(e + i));                    // on affiche l'etudiant
                    }
                }
                printf("\n");
                system("pause");
                return TRUE;     // on retourne TRUE pour continuer la boucle du menu

            case 2:
                // meme demarche pour le mois
                do {
                    printf("\nMois :");
                    scanf("\n%d", &recherche_ddn);
                    system("cls");
                } while ((recherche_ddn <= 0) || (recherche_ddn > 12));

                for (i = 0; i < *compteur; i++) {
                    if ((e + i)->ddn.mois == recherche_ddn) {
                        titre("\nFiche Etudiant", i + 1);
                        afficher_1_etudiant(*(e + i));
                    }
                }
                printf("\n");
                system("pause");
                return TRUE;

            case 3:
                // meme demarche pour l'annee
                do {
                    printf("\nAnnee (comprise entre 1990 (inclus) et 2010 (inclus)) :");
                    scanf("\n%d", &recherche_ddn);
                    system("cls");
                } while ((recherche_ddn < 1990) || (recherche_ddn > 2010));

                for (i = 0; i < *compteur; i++) {
                    if ((e + i)->ddn.annee == recherche_ddn) {
                        titre("\nFiche Etudiant", i + 1);
                        afficher_1_etudiant(*(e + i));
                    }
                }
                printf("\n");
                system("pause");
                return TRUE;

            default:
                printf("\nVous n'avez pas entre le bon numero. Veuillez reessayer.");     // si le nombre entre n'est pas bon, on redemande a rentrer le choix
        }
    } while(etat_recherche == 0);
}

void recherche_nom_prenom (etudiant *e, char type[nbmax_char], int *compteur) {
    char recherche_np[nbmax_char];
    int i;

    if (strcmp(type, "Prenom") == 0) {                                     // on compare si le type == "Prenom" alors cette fonction cherchera en fonction du prenom
        printf("\nPrenom :");
        scanf("%s", recherche_np);
        system("cls");

        for (i = 0; i < *compteur; i++) {                                  // pour i allant de 0 au nb du compteur
            if (strcmp((e + i)->prenom, recherche_np) == 0) {              // on compare si l'element de la case du tableau == recherche de l'utilisateur
                titre("\nFiche Etudiant", i + 1);                // mise en page - affichage Fiche Etudiant i
                afficher_1_etudiant(*(e + i));                          // on affiche l'etudiant
                printf("\n");
            }
        }
        system("pause");
    }
    else if (strcmp(type, "Nom") == 0) {      // on compare si le type == "Nom" alors cette fonction cherchera en fonction du nom
        printf("\nNom :");
        scanf("%s", recherche_np);
        system("cls");

        // meme demarche que pour la recherche par le prenom
        for (i = 0; i < *compteur; i++) {
            if (strcmp((e + i)->nom, recherche_np) == 0) {
                titre("\nFiche Etudiant", i + 1);
                afficher_1_etudiant(*(e + i));
                printf("\n");
            }
        }
        system("pause");
    }
}

// fonction pour la recherche d'etudiant
bool recherche_etudiant (etudiant *e, int *compteur) {
    int choix_recherche, etat_recherche_etudiant;

    do {
        system("cls");
        printf("\nVoulez-vous rechercher un etudiant :\n1 - Par nom\n2 - Par prenom\n3 - Par date de naissance\n4 - Revenir au menu");
        printf("\n");
        scanf("%d", &choix_recherche);

        switch (choix_recherche){
            case 1:
                recherche_nom_prenom(e, "Nom", compteur);
                break;

            case 2:
                recherche_nom_prenom(e, "Prenom", compteur);
                break;

            case 3:
                recherche_ddn_jma(e, compteur);
                break;

            case 4:
                return TRUE;

            default:
                printf("\nVous n'avez pas entre le bon numero veuillez reessayer.");
        }
    } while(etat_recherche_etudiant == 0);
}

// ------------------ Fonction pour quitter le menu  ------------------
void quitter_menu () {
    system("cls");
    printf("Merci et a bientot !");
    Sleep(1000);
}

// ------------------ Initialisation des donnees (si enregistrees dans des fichiers txt) ------------------
void initialisation_donnees (etudiant *e, int *n, int *compteur, int *ntab) {
    char c[256];
    FILE *f1;

    f1 = fopen("suivi_compteur_tab.txt", "r");
    if ((*c = fgetc(f1)) == EOF) {
        printf("Absence de donnees dans le fichier.");
        printf("Initialisation");
        Sleep(500);
    }
    else {
        printf("Initialisation des donnees");
        Sleep(500);
        recuperer_donnees_compteur(n, compteur, ntab);

        if (*compteur != 0) {
            printf("\nAllocation de la memoire ...");
            Sleep(500);
            e = (etudiant *) malloc(*n * sizeof(etudiant));
        }
    }
}

// ------------------ Fonction affichage menu ------------------
bool affichage_menu (int *compteur, int *ntab, int *n_save) {
    // definition des variables
    etudiant *e;
    FILE *fp;
    char nom_fic1[] = "etudiants.txt", nom_fic2[] = "suivi_compteur_tab.txt";
    int choix, n, n2, choix_realloc, choix_consult_etu, etat_realloc = 0, etat_choix_consult = 0;

    // affichage  du menu de navigation
    system("cls");
    titre ("\n------------- Gestionnaire d'enregistrement d'etudiants -------------", 0);
    printf("\n");
    titre("\n\t------------- Menu de navigation -------------", 0);

    printf("\n1 - Saisir un(e) etudiant(e)\n2 - Afficher la liste des etudiant(e)s\n3 - Effacer un(e) etudiant(e)\n4 - Rechercher un(e) etudiant(e)\n5 - Informations sur le tableau d'etudiants\n6 - Quitter l'application");
    printf("\n\nQue souhaitez-vous faire ?");
    scanf("\n%d", &choix);

    switch (choix) {
        // Saisie d'un(e) etudiant(e)
        case 1:
            system("cls");
            if (*compteur == 0) {                                                                      // si le compteur == 0, on alloue pour la premiere fois de la memoire
                nombre_etudiant(&n, n_save);                                                        // on demande le nombre d'etudiants dans le tableau
                printf("\nAllocation de la memoire ...");
                Sleep(500);
                system("cls");
                e = (etudiant *) malloc(n * sizeof(etudiant));                                    // malloc : allocation de la memoire
                *(e + *compteur) = saisir_1_etudiant();                                                // on saisit un etudiant
                *compteur += 1;                                                                        // on augmente le compteur d'etudiants enregistres
                *ntab += 1;                                                                            // on augmente le compteur de l'espace pris dans le tableau
                ecrire_fichier(fp, nom_fic1, "a", "Saisie etudiant(e)", e, compteur, n_save); // on ecrit les coordonnees de l'etudiant dans un fichier .txt
                ecrire_fichier(fp, nom_fic2, "w", "Suivi compteur et ntab", e, compteur, n_save);     // on ecrit les infos sur les compteurs et la longueur du tableau dans le fichier .txt correspondant
            }
            else if (*compteur == *n_save){       // si nb compteur == nb de place max dans le tableau
                do {
                    printf("\nIl n'y a pas assez d'espace pour entrer un nouvel etudiant.");
                    printf("\nVoulez-vous continuer (1 - Oui / 0 - Non)");          // on demande si l'utilisateur veut continuer a saisir l'etudiant ou non
                    scanf("%d", &choix_realloc);

                    switch (choix_realloc) {
                        case 1:
                            // on realloue de la memoire et on saisit les coordonnees de l'etudiant ensuite, on augmente les compteurs et on ecrit dans le fichier .txt
                            nombre_etudiant(&n2, n_save);
                            printf("\nReallocation de la memoire ...");
                            Sleep(500);
                            system("cls");
                            e = (etudiant *) realloc(e, (*n_save + n2) * sizeof(etudiant));
                            *(e + *compteur) = saisir_1_etudiant();         // pour i allant de 0 jusqu'a n (exclus), on affiche saisit les coordonnees de l'etudiant
                            *compteur += 1;
                            *ntab += 1;
                            ecrire_fichier(fp, nom_fic1, "a", "Saisie etudiant(e)", e, compteur, n_save);
                            ecrire_fichier(fp, nom_fic2, "w", "Suivi compteur et ntab", e, compteur, n_save);     // on ecrit les infos sur les compteurs et la longueur du tableau dans le fichier .txt correspondant
                            etat_realloc = 1;

                        case 0:
                            etat_realloc = 1;
                            return TRUE;     // on retourne TRUE pour revenir au menu de depart

                        default:
                            printf("Vous n'avez pas entre le bon numero. Veuillez reessayer.");
                            Sleep(300);
                            system("cls");
                    }
                } while (etat_realloc == 0);
            }
            else {
                *(e + *compteur) = saisir_1_etudiant();     // on saisit les coordonnees de l'etudiant si il y a des cases disponibles dans le tableau
                *compteur += 1;
                *ntab += 1;
                ecrire_fichier(fp, nom_fic1, "a", "Saisie etudiant(e)", e, compteur, n_save);
                ecrire_fichier(fp, nom_fic2, "w", "Suivi compteur et ntab", e, compteur, n_save);     // on ecrit les infos sur les compteurs et la longueur du tableau dans le fichier .txt correspondant
            }
            return TRUE;

            // Afficher la liste des etudiants
        case 2:
            if (*compteur == 0) {                          // si le compteur est nul, alors il n'y a pas d'etudiant a afficher
                system("cls");
                printf("\nIl n'y a pas d'etudiant a afficher.\n");
                system("pause");
            } else {
                do {
                    system("cls");
                    printf("\nVoulez-vous consulter les etudiants enregistres sur cette session ou l'integralite de la liste (via un fichier .txt) ?");
                    printf("\n1 - Consulter sur cette session\n2 - Consulter en general");
                    scanf("%d", &choix_consult_etu);

                    switch(choix_consult_etu) {
                        case 1:
                            afficher_n_etudiant_dynamic(e, *compteur);
                            etat_choix_consult = 1;

                        case 2:
                            system("cls");
                            lire_fichier(fp, nom_fic1);     // on lit le fichier .txt et affiche les coordonnees de tous les etudiants
                            etat_choix_consult = 1;
                            system("pause");

                        default:
                            printf("Vous n'avez pas entre le bon numero. Veuillez reessayer.");
                            Sleep(300);
                            system("cls");
                    }
                } while (etat_choix_consult == 0);
            }
            return TRUE;     // retourne TRUE pour revenir au menu principal

            // Effacer un etudiant
        case 3:
            if (*compteur == 0) {                          // si le compteur est nul, alors il n'y a pas d'etudiant a afficher
                system("cls");
                printf("\nVous ne pouvez pas effacer d'etudiant. Le tableau d'etudiants est vide.\n");
                system("pause");
            }
            else {
                effacer_1_etudiant(e, compteur, n_save);
                *compteur -= 1;
                *ntab -= 1;
                ecrire_fichier(fp, nom_fic1, "w", "Saisie etudiant(e)", e, compteur, n_save);
                ecrire_fichier(fp, nom_fic2, "w", "Suivi compteur et ntab", e, compteur, n_save);
            }
            return TRUE;

            // Rechercher des etudiants
        case 4:
            if (*compteur == 0) {                   // Si compteur == 0, on ne peut pas rechercher d'etudiant
                system("cls");
                printf("\nPour pouvoir effectuer des recherches, veuillez entrer des etudiants.\n");
                system("pause");
            } else {
                recherche_etudiant(e, compteur);     // appel de la fonction recherche_etudiant
            }
            return TRUE;

            // Affichage d'informations a propos du tableau d'etudiants
        case 5:
            system("cls");
            titre("\nInformations sur le tableau d'etudiants", 0);
            printf("\nNombre d'etudiants rentres : %d", *compteur);     // on affiche le nombre d'etudiants enregistres
            if (*ntab == 0) {
                printf("\nLe tableau etudiant n'existe pas.");
            } else {
                printf("\nTaille du tableau d'etudiant : %d", *n_save);     // on affiche la longueur totale du tableau
                printf("\nPlace(s) restante(s) dans le tableau : %d", *n_save - *compteur);     // on affiche le nombre d'emplacements restants dans le tableau
            }
            printf("\n");
            system("pause");
            return TRUE;

            // Quitter le menu
        case 6:
            quitter_menu();     // appel de la fonction quitter_menu
            free(e);     // liberer l'espace memoire utilise pour l'etudiant
            return FALSE;

        default:
            printf("\nVous n'avez pas entre le bon numero. Veuillez reessayer.");
            Sleep(1000);
            return TRUE;     // on reaffiche le menu si le nombre entre n'est pas correct
    }
}
