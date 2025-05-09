#include <stdio.h>
#include <stdlib.h>
#include "choix.h"
#include "structure.h"

int demanderChoixDansIntervalle(const char *texte, int min, int max, const char *couleur) {
    int choix = 0;
    char ligne[10];

    do {
        printf("%s%s (%d à %d) : " RESET, couleur, texte, min, max);
        if (fgets(ligne, sizeof(ligne), stdin)) {
            if (sscanf(ligne, "%d", &choix) == 1 && choix >= min && choix <= max) {
                return choix;
            }
        }
        printf(ROUGE "Choix incorrect, rechoisis\n" RESET);
    } while (1);
}

void choix_joueur_E(int *equipe, int nbr_joueur, AffichagePerso persos_affichage[]) {
    int x = -1, y = -1;
    for (int i = 0; i <= nbr_joueur; i++) {
        switch(i) {
            case 0:
                equipe[i] = demanderChoixDansIntervalle("👉 Choisis le premier Personnage",  1,  12 , JAUNE);
                x = equipe[i];
                break;
            case 1:
                equipe[i] = demanderChoixDansIntervalle("👉 Choisis le deuxième Personnage",  1, 12 , JAUNE);
                while(equipe[i] == x){
                    equipe[i] = demanderChoixDansIntervalle(" Vous ne pouvez pas choisir deux fois le même personnage",  1, 12 , ROUGE);
                }
                y = equipe[i];
                break;
            case 2:
                equipe[i] = demanderChoixDansIntervalle("👉 Choisis le troisième Personnage", 1, 12 , JAUNE);
                while(equipe[i] == x || equipe[i] == y){
                    equipe[i] = demanderChoixDansIntervalle(" Vous ne pouvez pas choisir deux fois le même personnage",  1, 12 , ROUGE);
                }
                break;
            default:
                printf("Erreur : nombre de personnages non supporté\n");
                exit(1);
        }

        printf("✅  Vous avez choisi : %s\n", persos_affichage[equipe[i] - 1].nom);
    }
}

void choix_joueur(int *equipe1, int *equipe2, int nbr_joueur , int mode, AffichagePerso persos_affichage[]) {
    switch(mode){
        case 1:
            printf("\n👥  EQUIPE 1, c’est à votre tour :\n");
            choix_joueur_E(equipe1, nbr_joueur, persos_affichage);
            printf("\n👥  EQUIPE 2, c’est à votre tour :\n");
            choix_joueur_E(equipe2, nbr_joueur, persos_affichage);
            break;
        case 2:
            printf("\n👥  EQUIPE 1, c’est à votre tour :\n");
            choix_joueur_E(equipe1, nbr_joueur, persos_affichage);
            break;
        default:
            printf("Erreur : mode non supporté\n");
            exit(1);
    }

    printf("\n Appuie sur Entrée pour continuer... \n");
    while (getchar() != '\n');
}
