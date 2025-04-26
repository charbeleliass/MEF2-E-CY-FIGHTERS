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
void afficher_equipes(Player eq1_stats[], Player eq2_stats[], int nbr_joueur) {
    printf("\nEQUIPE 1 :\n");
    for (int i = 0; i <= nbr_joueur; i++) {
        printf("[ %-15s ] PV : %.0f/%.0f\n", eq1_stats[i].name, eq1_stats[i].stats_temp.pv, eq1_stats[i].stats_temp.pv_max);
    }

    printf("\nEQUIPE 2 :\n");
    for (int i = 0; i <= nbr_joueur; i++) {
        printf("[ %-15s ] PV : %.0f/%.0f\n", eq2_stats[i].name, eq2_stats[i].stats_temp.pv, eq2_stats[i].stats_temp.pv_max);
    }

    printf("\n");
}

int equipe_KO(Player equipe[], int nbr_joueur) {
    for (int i = 0; i <= nbr_joueur; i++) {
        if (equipe[i].stats_temp.pv > 0)
            return 0; // il reste au moins un vivant
    }
    return 1; // toute l'équipe est KO
}

void update_competence(Player* p) {
    if (p->atk_spe.recharge > 0) {
        p->atk_spe.recharge--;
    }
}

void update_effets(Player* p) {
    if (p->tour_buff_restant > 0) {
        p->tour_buff_restant--;

        if (p->tour_buff_restant == 0) {
            // Reset des stats
            p->stats_temp.att = p->stats.att;
            p->stats_temp.def = p->stats.def;
            p->stats_temp.dodge = p->stats.dodge;
            p->stats_temp.speed = p->stats.speed;
        }
    }
}

void attaque_classique(Player* attaquant, Player ennemis[], int nbr_joueur) {
    int cible = demanderChoixDansIntervalle("Choisir la cible :", 1, nbr_joueur + 1, BLEU) - 1;

    if (ennemis[cible].stats_temp.pv <= 0) {
        printf("Cible déjà K.O. !\n");
        return;
    }

    float degats = attaquant->stats_temp.att * 5;

    // Réduction par la défense
    degats *= (1 - ennemis[cible].stats_temp.def);

    // Chance d'esquive
    if (((float)rand() / RAND_MAX) < ennemis[cible].stats_temp.dodge) {
        printf("%s esquive l'attaque !\n", ennemis[cible].name);
        return;
    }

    ennemis[cible].stats_temp.pv -= degats;
    printf("%s inflige %.1f dégâts à %s !\n", attaquant->name, degats, ennemis[cible].name);

    if (ennemis[cible].stats_temp.pv <= 0) {
        printf("%s est K.O. !\n", ennemis[cible].name);
    }
}

void utiliser_competence(Player* lanceur, Player ennemis[], int nbr_joueur) {
    if (lanceur->atk_spe.recharge > 0) {
        printf("Compétence en rechargement !\n");
        return;
    }

    printf("%s utilise %s !\n", lanceur->name, lanceur->atk_spe.name);

    int cible = demanderChoixDansIntervalle("Choisir la cible :", 1, nbr_joueur + 1, BLEU) - 1;

    if (ennemis[cible].stats_temp.pv <= 0) {
        printf("Cible déjà K.O. !\n");
        return;
    }

    ennemis[cible].stats_temp.pv -= (lanceur->stats_temp.att * lanceur->atk_spe.valeur * 5);

    printf("%s subit %.1f dégâts spéciaux !\n", ennemis[cible].name, lanceur->stats_temp.att * lanceur->atk_spe.valeur * 5);

    lanceur->atk_spe.recharge = 3;
}

void combat(Player eq1_stats[], Player eq2_stats[], int nbr_joueur) {
    srand(time(NULL));
    int tour = 1;

    while (1) {
        printf("\n========== TOUR %d ==========\n", tour);
        afficher_equipes(eq1_stats, eq2_stats, nbr_joueur);

        for (int e = 0; e <= 1; e++) {
            Player* equipe = (e == 0) ? eq1_stats : eq2_stats;
            Player* ennemis = (e == 0) ? eq2_stats : eq1_stats;

            for (int i = 0; i <= nbr_joueur; i++) {
                if (equipe[i].stats_temp.pv > 0) {
                    printf("\nC'est au tour de %s\n", equipe[i].name);
                    printf("1 - Attaque classique\n");
                    printf("2 - Utiliser compétence spéciale\n");

                    int choix = demanderChoixDansIntervalle("Que veux-tu faire ?", 1, 2, JAUNE);

                    if (choix == 1) {
                        attaque_classique(&equipe[i], ennemis, nbr_joueur);
                    } else {
                        utiliser_competence(&equipe[i], ennemis, nbr_joueur);
                    }

                    update_competence(&equipe[i]);
                    update_effets(&equipe[i]);
                }
            }
        }

        if (equipe_KO(eq1_stats, nbr_joueur)) {
            printf("\n=== L'équipe 1 est K.O. ===\nÉQUIPE 2 GAGNE !\n");
            break;
        }
        if (equipe_KO(eq2_stats, nbr_joueur)) {
            printf("\n=== L'équipe 2 est K.O. ===\nÉQUIPE 1 GAGNE !\n");
            break;
        }

        tour++;
    }
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
