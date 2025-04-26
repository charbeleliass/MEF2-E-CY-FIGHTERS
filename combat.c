#include <stdio.h>
#include <stdlib.h>
#include "combat.h"
#include "structure.h"
#include "choix.h"
#include "menu.h"

void afficher_stats() {
    system("clear");
    const char* noms_assets[] = {
        "1 - Bouclier     ",
        "2 - Épée         ",
        "3 - Mitraillette ",
        "4 - Bâton        ",
        "5 - Medkit       ",
        "6 - Éclair       "
    };
    const char *stats_pos[] = { "DEF", "ATT", "CRIT", "DODGE", "PV", "SPEED" };
    const char *stats_neg[] = { "DODGE", "DEF", "PV", "CRIT", "ATT", "ATT" };

    for (int i = 0; i < 6; i++) {
        printf("[ %s]", noms_assets[i]);
    }
    printf("\n\n");

    for (int i = 0; i < 6; i++) {
        printf(VERT"[+] %-16s", stats_pos[i]);
    }
    printf("\n\n");

    for (int i = 0; i < 6; i++) {
        printf(ROUGE"[-] %-16s" RESET, stats_neg[i]);
    }
    printf("\n\n\n");
}

void atout(AffichagePerso *p, int a) {
    switch (a) {
        case 1: p->def++; p->dodge--; break;
        case 2: p->att++; p->def--; break;
        case 3: p->crit++; p->pv--; break;
        case 4: p->dodge++; p->crit--; break;
        case 5: p->pv++; p->att--; break;
        case 6: p->speed++; p->att--; break;
        case 0: break;
        default:
            printf("Erreur : atout non reconnu\n");
            exit(1);
    }
}

void vraiatout(Player* p, int a) {
    switch(a) {
        case 1:
            p->stats_temp.def += 0.1;
            p->stats_temp.dodge -= 0.1;
            break;
        case 2:
            p->stats_temp.att += 0.1;
            p->stats_temp.def -= 0.1;
            break;
        case 3:
            p->stats_temp.pv -= 10;
            break;
        case 4:
            p->stats_temp.dodge += 0.1;
            break;
        case 5:
            p->stats_temp.pv += 10;
            p->stats_temp.att -= 0.1;
            break;
        case 6:
            p->stats_temp.speed += 1;
            p->stats_temp.att -= 0.1;
            break;
        case 0:
            break;
        default:
            printf("Erreur : atout non reconnu\n");
            exit(1);
    }

    if (p->stats_temp.pv > p->stats.pv_max) {
        p->stats_temp.pv = p->stats.pv_max;
    }
}

void choix_assets(int equipe[], int nbr_joueur, Player eq_stats[]) {
    int arme = 0;
    for (int i = 0; i <= nbr_joueur; i++) {
        arme = demanderChoixDansIntervalle("choisir arme : ", 0, 6, VERT);

        AffichagePerso *paff = &persos_affichage[equipe[i] - 1];
        atout(paff, arme);                 // Modifier l'affichage
        afficherPersonnage(equipe[i] - 1);  // Afficher les nouvelles stats
        vraiatout(&eq_stats[i], arme);      // Modifier les vraies stats
    }
}

void choix_assets_E(int equipe1[], int equipe2[], int nbr_joueur, Player eq1_stats[], Player eq2_stats[]) {
    afficher_stats();
    printf("Au tour de l'équipe 1 :\n");
    choix_assets(equipe1, nbr_joueur, eq1_stats);

    printf("\nAppuie sur Entrée pour continuer...\n");
    while (getchar() != '\n');

    afficher_stats();
    printf("Au tour de l'équipe 2 :\n");
    choix_assets(equipe2, nbr_joueur, eq2_stats);
}

/*
void stats_combat_E(Player eq_stats[], int nbr_joueur){
    for (int i = 0; i <= nbr_joueur; i++) {
        printf("[ %-20s ]", eq_stats[i].name);
    }
    printf("\n");

    for (int j = 0; j <= nbr_joueur; j++) {
        printf("[ ");
        for (int k = 0; k < eq_stats[j].stats_temp.pv; k++) {
            printf(">");
        }
        for (int x = 0; x < (eq_stats[j].stats_temp.pv_max - eq_stats[j].stats_temp.pv); x++) {
            printf(" ");
        }
        printf(" ] ");
    }
}

void debut_combat(Player eq1_stats[], Player eq2_stats[], int nbr_joueur) {
    stats_combat_E(eq1_stats, nbr_joueur);
    printf("\n\n_________________________________________________________________________________________\n\n");
    stats_combat_E(eq2_stats, nbr_joueur);
}
*/
