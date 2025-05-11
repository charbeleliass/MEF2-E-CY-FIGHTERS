#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "computer.h"

void choix_ordi_persos(int *equipe, int nbr_joueur) {
    int dispo[12] = {0};
    for (int i = 0; i <= nbr_joueur; i++) {
        int r;
        do {
            r = rand() % 12;
        } while (dispo[r]);
        dispo[r] = 1;
        equipe[i] = r + 1;
        printf("🤖 Ordi a choisi le perso %d\n", equipe[i]);
    }
}

void choix_ordi_assets(int *equipe, int nbr_joueur, Player *eq_stats, AffichagePerso *affichage) {
    for (int i = 0; i <= nbr_joueur; i++) {
        int choix = rand() % 6 + 1;
        printf("🤖 Ordi donne arme %d à %s\n", choix, eq_stats[i].name);
        atout(&affichage[equipe[i] - 1], choix);
        vraiatout(&eq_stats[i], choix);
    }
}

int trouver_cible_plus_faible(Player *ennemis, int nbr_joueur) {
    int min_index = -1;
    float min_pv = 100000;
    for (int i = 0; i <= nbr_joueur; i++) {
        if (ennemis[i].stats_temp.pv > 0 && ennemis[i].stats_temp.pv < min_pv) {
            min_pv = ennemis[i].stats_temp.pv;
            min_index = i;
        }
    }
    return min_index;
}

void tour_ordinateur(Player *ordi, Player *ennemis, Player *alliés, int nbr_joueur, int difficulte) {
    printf("🤖 Tour de %s (ordi - difficulté %d)\n", ordi->name, difficulte);

    switch (difficulte) {
        case 1: { // Noob : attaque aléatoire
            int cible;
            do {
                cible = rand() % (nbr_joueur + 1);
            } while (ennemis[cible].stats_temp.pv <= 0);
            printf("🤖 Ordi attaque un ennemi aléatoire : %s\n", ennemis[cible].name);
            attaque_classique_direct(ordi, &ennemis[cible]);
            break;
        }
        case 2: { // Facile : attaque le plus faible
            int cible = trouver_cible_plus_faible(ennemis, nbr_joueur);
            if (cible != -1) {
                printf("🤖 Ordi attaque le plus faible : %s\n", ennemis[cible].name);
                attaque_classique_direct(ordi, &ennemis[cible]);
            }
            break;
        }
        case 3: { // Moyen : utilise compétences si possible
            if (ordi->atk_spe.recharge == 0) {
                printf("🤖 Ordi utilise sa compétence : %s\n", ordi->atk_spe.name);
                printf("⌀ %s\n", ordi->atk_spe.description);
                appliquer_effet(ordi, alliés, ennemis, nbr_joueur, 1);
                ordi->atk_spe.recharge = ordi->atk_spe.recharge_max;
                attendreEntree();
            } else {
                int cible = trouver_cible_plus_faible(ennemis, nbr_joueur);
                if (cible != -1) {
                    printf("🤖 Ordi attaque %s\n", ennemis[cible].name);
                    attaque_classique_direct(ordi, &ennemis[cible]);
                }
            }
            break;
        }
    }
}
