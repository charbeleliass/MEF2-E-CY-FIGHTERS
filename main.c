#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "structure.h"
#include "choix.h"
#include "combat.h"

int main() {
    int mode = 0, nbr_joueur = 0;
    int equipe1[3], equipe2[3];

    afficherTitre();
    afficherMenu(&mode, &nbr_joueur);
    afficherTousLesPersos();
    choix_joueur(equipe1, equipe2, nbr_joueur, mode);
    Player eq1_stats[nbr_joueur + 1];
    Player eq2_stats[nbr_joueur + 1];

    switch (nbr_joueur) {
        case 1: 
            eq1_stats[0] = p[equipe1[0] - 1];
            eq1_stats[1] = p[equipe1[1] - 1];
            eq2_stats[0] = p[equipe2[0] - 1];
            eq2_stats[1] = p[equipe2[1] - 1];
            break;

        case 2:
            eq1_stats[0] = p[equipe1[0] - 1];
            eq1_stats[1] = p[equipe1[1] - 1];
            eq1_stats[2] = p[equipe1[2] - 1];
            eq2_stats[0] = p[equipe2[0] - 1];
            eq2_stats[1] = p[equipe2[1] - 1];
            eq2_stats[2] = p[equipe2[2] - 1];
            break;

        default:
            printf("Erreur dans la sélection du nombre de joueurs.\n");
            exit(1);
    }

    choix_assets_E(equipe1, equipe2, nbr_joueur, eq1_stats, eq2_stats);

    combat(eq1_stats, eq2_stats, nbr_joueur);
    
    return 0;
}

