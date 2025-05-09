#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "structure.h"
#include "choix.h"
#include "combat.h"

#define NB_PERSOS 12

int main() {
    int mode = 0, nbr_joueur = 0;
    int equipe1[3], equipe2[3];

    Player persos[NB_PERSOS];
    AffichagePerso affichage[NB_PERSOS];

    // Chargement des données depuis fichiers
    chargerPersonnages(persos, NB_PERSOS);
    chargerTechniques(persos, NB_PERSOS);
    chargerAffichage(affichage, persos, NB_PERSOS);

    // Interface de jeu
    afficherTitre();
    afficherMenu(&mode, &nbr_joueur);
    afficherTousLesPersos(affichage);
    choix_joueur(equipe1, equipe2, nbr_joueur, mode, affichage);

    // Préparation des équipes
    Player eq1_stats[nbr_joueur + 1];
    Player eq2_stats[nbr_joueur + 1];
    for (int i = 0; i <= nbr_joueur; i++) {
        eq1_stats[i] = persos[equipe1[i] - 1];
        eq2_stats[i] = persos[equipe2[i] - 1];
    }

    // Choix d’assets (armes) + Combat
    choix_assets_E(equipe1, equipe2, nbr_joueur, eq1_stats, eq2_stats, affichage);
    combat(eq1_stats, eq2_stats, nbr_joueur, affichage);

    return 0;
}
