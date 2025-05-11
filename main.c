#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "structure.h"
#include "choix.h"
#include "combat.h"
#include "computer.h"

#define NB_PERSOS 12

int main() {
    int mode = 0, nbr_joueur = 0, difficulte = 1;
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

    if (mode == 1) {
        choix_joueur(equipe1, equipe2, nbr_joueur, mode, affichage);
    } else {
        choix_joueur_E(equipe1, nbr_joueur, affichage);
        choix_ordi_persos(equipe2, nbr_joueur);
    }

    // Préparation des équipes
    Player eq1_stats[nbr_joueur + 1];
    Player eq2_stats[nbr_joueur + 1];
    for (int i = 0; i <= nbr_joueur; i++) {
        eq1_stats[i] = persos[equipe1[i] - 1];
        eq2_stats[i] = persos[equipe2[i] - 1];
    }

    // Choix d’assets (armes) + Combat
    if (mode == 1)
        choix_assets_E(equipe1, equipe2, nbr_joueur, eq1_stats, eq2_stats, affichage);
    else {
        afficher_stats();
        choix_assets(equipe1, nbr_joueur, eq1_stats, affichage);
        attendreEntree();
        choix_ordi_assets(equipe2, nbr_joueur, eq2_stats, affichage);
        attendreEntree();

        printf("\n+================ DIFFICULTÉ ================+\n");
        printf("1. Noob    (attaque aléatoire)\n");
        printf("2. Facile  (attaque le plus faible)\n");
        printf("3. Moyen   (utilise les compétences intelligemment)\n\n");
        difficulte = demanderChoixDansIntervalle("Choisis la difficulté", 1, 3, JAUNE);
    }

    combat(eq1_stats, eq2_stats, nbr_joueur, affichage, mode, difficulte);
    return 0;
}
