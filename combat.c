#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
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
        default: break;
    }
}

void vraiatout(Player* p, int a) {
    switch(a) {
        case 1: p->stats_temp.def += 0.1; p->stats_temp.dodge -= 0.1; break;
        case 2: p->stats_temp.att += 0.1; p->stats_temp.def -= 0.1; break;
        case 3: p->stats_temp.pv -= 10; break;
        case 4: p->stats_temp.dodge += 0.1; break;
        case 5: p->stats_temp.pv += 10; p->stats_temp.att -= 0.1; break;
        case 6: p->stats_temp.speed += 1; p->stats_temp.att -= 0.1; break;
        default: break;
    }

    if (p->stats_temp.pv > p->stats.pv_max)
        p->stats_temp.pv = p->stats.pv_max;
}

void choix_assets(int equipe[], int nbr_joueur, Player eq_stats[], AffichagePerso persos_affichage[]) {
    int arme = 0;
    for (int i = 0; i <= nbr_joueur; i++) {
        arme = demanderChoixDansIntervalle("choisir arme : ", 0, 6, VERT);
        AffichagePerso *paff = &persos_affichage[equipe[i] - 1];
        atout(paff, arme);
        afficherPersonnage(equipe[i] - 1, persos_affichage);
        vraiatout(&eq_stats[i], arme);
    }
}

void choix_assets_E(int equipe1[], int equipe2[], int nbr_joueur, Player eq1_stats[], Player eq2_stats[], AffichagePerso persos_affichage[]) {
    afficher_stats();
    printf("Au tour de l'équipe 1 :\n");
    choix_assets(equipe1, nbr_joueur, eq1_stats, persos_affichage);

    printf("\nAppuie sur Entrée pour continuer...\n");
    while (getchar() != '\n');

    afficher_stats();
    printf("Au tour de l'équipe 2 :\n");
    choix_assets(equipe2, nbr_joueur, eq2_stats, persos_affichage);
}

void afficher_emojis_effets(Player p) {
    char *effet = p.atk_spe.effet_type;
    for (int i = 0; i < p.tour_buff_restant; i++) {
        if (strcmp(effet, "pv+") == 0) printf("❤️ ");
        else if (strcmp(effet, "team_def+") == 0) printf("🛡️ ");
        else if (strcmp(effet, "dodge++") == 0) printf("⚡ ");
        else if (strcmp(effet, "skip_enemy") == 0) printf("❌ ");
        else if (strcmp(effet, "dot") == 0) printf("☠️ ");
        else if (strcmp(effet, "def--") == 0) printf("⬇️ ");
        else if (strcmp(effet, "crit+") == 0) printf("🔥 ");
        else printf("✨ ");
    }
}

void afficher_etat_combat(Player eq1[], Player eq2[], int joueur_actuel, int equipe_joueur, int nbr_joueur) {
    system("clear");

    printf(BLEU "_[EQUIPE 1]_____________________________________________________________\n" RESET);
    for (int i = 0; i <= nbr_joueur; i++) {
        if (eq1[i].stats_temp.pv <= 0)
            printf("[ " ROUGE "%-10s |✠|" RESET "]", eq1[i].name);
        else if (equipe_joueur == 0 && i == joueur_actuel)
            printf("[ " JAUNE ")>%s<(" RESET "]", eq1[i].name);
        else
            printf("[ " VERT "%-10s |%d|" RESET "]", eq1[i].name, i+1);
    }
    printf("\n");

    for (int i = 0; i <= nbr_joueur; i++) {
        printf("[");
        int pv_ratio = (int)((eq1[i].stats_temp.pv / eq1[i].stats_temp.pv_max) * 20);
        for (int j = 0; j < pv_ratio; j++) printf("#");
        for (int j = pv_ratio; j < 20; j++) printf(" ");
        printf("]");
    }
    printf("\n");

    for (int i = 0; i <= nbr_joueur; i++) {
        printf("[ ");
        afficher_emojis_effets(eq1[i]);
        printf(" ]");
    }
    printf("\n");

    printf(BLEU "_[EQUIPE 2]_____________________________________________________________\n" RESET);
    for (int i = 0; i <= nbr_joueur; i++) {
        if (eq2[i].stats_temp.pv <= 0)
            printf("[ " ROUGE "%-10s |✠|" RESET "]", eq2[i].name);
        else if (equipe_joueur == 1 && i == joueur_actuel)
            printf("[ " JAUNE ")>%s<(" RESET "]", eq2[i].name);
        else
            printf("[ " VERT "%-10s |%d|" RESET "]", eq2[i].name, i+1);
    }
    printf("\n");

    for (int i = 0; i <= nbr_joueur; i++) {
        printf("[");
        int pv_ratio = (int)((eq2[i].stats_temp.pv / eq2[i].stats_temp.pv_max) * 20);
        for (int j = 0; j < pv_ratio; j++) printf("#");
        for (int j = pv_ratio; j < 20; j++) printf(" ");
        printf("]");
    }
    printf("\n");

    for (int i = 0; i <= nbr_joueur; i++) {
        printf("[ ");
        afficher_emojis_effets(eq2[i]);
        printf(" ]");
    }
    printf("\n\n");
}

int equipe_KO(Player equipe[], int nbr_joueur) {
    for (int i = 0; i <= nbr_joueur; i++)
        if (equipe[i].stats_temp.pv > 0)
            return 0;
    return 1;
}

void update_competence(Player* p) {
    if (p->atk_spe.recharge > 0)
        p->atk_spe.recharge--;
}

void update_effets(Player* p) {
    if (p->tour_buff_restant > 0) {
        p->tour_buff_restant--;
        if (p->tour_buff_restant == 0) {
            p->stats_temp = p->stats;
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
    degats *= (1 - ennemis[cible].stats_temp.def);

    if (((float)rand() / RAND_MAX) < ennemis[cible].stats_temp.dodge) {
        printf(JAUNE "%s esquive l'attaque !\n" RESET, ennemis[cible].name);
        return;
    }

    ennemis[cible].stats_temp.pv -= degats;
    printf("%s inflige %.1f dégâts à %s !\n", attaquant->name, degats, ennemis[cible].name);

    if (ennemis[cible].stats_temp.pv <= 0)
        printf(ROUGE "%s est K.O. !\n" RESET, ennemis[cible].name);
}

void utiliser_competence(Player* lanceur, Player ennemis[], int nbr_joueur) {
    if (lanceur->atk_spe.recharge > 0) {
        printf(ROUGE "✖ Compétence en rechargement (%d tour(s) restant)\n" RESET, lanceur->atk_spe.recharge);
        return;
    }

    printf("%s utilise %s !\n", lanceur->name, lanceur->atk_spe.name);
    printf("⌀ %s\n", lanceur->atk_spe.description);

    char *effet = lanceur->atk_spe.effet_type;

    if (strcmp(effet, "aoe") == 0) {
        for (int i = 0; i <= nbr_joueur; i++) {
            if (ennemis[i].stats_temp.pv > 0)
                ennemis[i].stats_temp.pv -= lanceur->stats_temp.att * lanceur->atk_spe.valeur * 5;
        }
    } else if (strcmp(effet, "pv+") == 0) {
        lanceur->stats_temp.pv += lanceur->stats_temp.pv * lanceur->atk_spe.valeur;
        if (lanceur->stats_temp.pv > lanceur->stats.pv_max)
            lanceur->stats_temp.pv = lanceur->stats.pv_max;
    } else {
        lanceur->tour_buff_restant = lanceur->atk_spe.tour_actif;
    }

    lanceur->atk_spe.recharge = lanceur->atk_spe.recharge;
}

void combat(Player eq1_stats[], Player eq2_stats[], int nbr_joueur, AffichagePerso affichage[]) {
    srand(time(NULL));
    int tour = 1;

    while (1) {
        printf("\n========== TOUR %d ==========\n", tour);

        for (int e = 0; e <= 1; e++) {
            Player* equipe = (e == 0) ? eq1_stats : eq2_stats;
            Player* ennemis = (e == 0) ? eq2_stats : eq1_stats;

            for (int i = 0; i <= nbr_joueur; i++) {
                if (equipe[i].stats_temp.pv > 0) {
                    afficher_etat_combat(eq1_stats, eq2_stats, i, e, nbr_joueur);
                    printf("\nC'est au tour de %s\n", equipe[i].name);

                    printf("1 - Attaque classique\n");

                    Special spe = equipe[i].atk_spe;
                    printf("2 - %s ", spe.name);
                    if (spe.recharge > 0)
                        printf("(Recharge: %d tour(s) restant)\n", spe.recharge);
                    else
                        printf("(Disponible)\n");

                    printf("   ⌀ %s\n", spe.description);
                    if (spe.tour_actif > 0)
                        printf("   ⌀ Effet actif pendant %d tour(s)\n", spe.tour_actif);

                    int choix = demanderChoixDansIntervalle("Que veux-tu faire ?", 1, 2, JAUNE);

                    if (choix == 1)
                        attaque_classique(&equipe[i], ennemis, nbr_joueur);
                    else
                        utiliser_competence(&equipe[i], ennemis, nbr_joueur);

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
