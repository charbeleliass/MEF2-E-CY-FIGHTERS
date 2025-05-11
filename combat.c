#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "combat.h"
#include "structure.h"
#include "choix.h"
#include "menu.h"

void attendreEntree() {
    printf("\nAppuie sur Entrée pour continuer...\n");
    while (getchar() != '\n');
}

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

    for (int i = 0; i < 6; i++) printf("[ %s]", noms_assets[i]);
    printf("\n\n");
    for (int i = 0; i < 6; i++) printf(VERT"[+] %-16s", stats_pos[i]);
    printf("\n\n");
    for (int i = 0; i < 6; i++) printf(ROUGE"[-] %-16s" RESET, stats_neg[i]);
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
    attendreEntree();
    afficher_stats();
    printf("Au tour de l'équipe 2 :\n");
    choix_assets(equipe2, nbr_joueur, eq2_stats, persos_affichage);
}

void afficher_emojis_effets(Player p) {
    if (p.tour_buff_restant <= 0) return;

    char *effet = p.atk_spe.effet_type;
    for (int i = 0; i < p.tour_buff_restant; i++) {
        if (strcmp(effet, "pv+") == 0) printf("❤️ ");
        else if (strcmp(effet, "team_def+") == 0) printf("🛡️ ");
        else if (strcmp(effet, "def--") == 0) printf("⬇️ ");
        else if (strcmp(effet, "dodge++") == 0) printf("⚡ ");
        else if (strcmp(effet, "att+") == 0) printf("✊ ");
        else if (strcmp(effet, "speed+") == 0) printf("➡️ ");
        else if (strcmp(effet, "pv_max_temp") == 0) printf("🔺 ");
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
        int pv_ratio = (int)((eq1[i].stats_temp.pv / eq1[i].stats.pv_max) * 20);
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
        int pv_ratio = (int)((eq2[i].stats_temp.pv / eq2[i].stats.pv_max) * 20);
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
void update_competence(Player* p) {
    if (p->atk_spe.recharge > 0)
        p->atk_spe.recharge--;
}

void update_effets(Player* p) {
    if (p->tour_buff_restant > 0) {
        p->tour_buff_restant--;

        if (p->tour_buff_restant == 0) {
            if (strcmp(p->atk_spe.effet_type, "att+") == 0)
                p->stats_temp.att = p->stats.att;
            else if (strcmp(p->atk_spe.effet_type, "speed+") == 0)
                p->stats_temp.speed = p->stats.speed;
            else if (strcmp(p->atk_spe.effet_type, "team_def+") == 0 ||
                     strcmp(p->atk_spe.effet_type, "def--") == 0)
                p->stats_temp.def = p->stats.def;
        }
    }
}

int equipe_KO(Player equipe[], int nbr_joueur) {
    for (int i = 0; i <= nbr_joueur; i++)
        if (equipe[i].stats_temp.pv > 0)
            return 0;
    return 1;
}

void appliquer_effet(Player* lanceur, Player equipe[], Player ennemis[], int nbr_joueur) {
    char* effet = lanceur->atk_spe.effet_type;
    float val = lanceur->atk_spe.valeur;
    int duree = lanceur->atk_spe.tour_actif;

    if (strcmp(effet, "aoe") == 0) {
        for (int i = 0; i <= nbr_joueur; i++) {
            if (ennemis[i].stats_temp.pv > 0)
                ennemis[i].stats_temp.pv -= lanceur->stats_temp.att * val * 5;
        }

    } else if (strcmp(effet, "pv+") == 0) {
        lanceur->stats_temp.pv += lanceur->stats_temp.pv * val;
        if (lanceur->stats_temp.pv > lanceur->stats.pv_max)
            lanceur->stats_temp.pv = lanceur->stats.pv_max;

    } else if (strcmp(effet, "team_pv+") == 0) {
        for (int i = 0; i <= nbr_joueur; i++) {
            float heal = equipe[i].stats.pv_max * val;
            equipe[i].stats_temp.pv += heal;
            if (equipe[i].stats_temp.pv > equipe[i].stats.pv_max)
                equipe[i].stats_temp.pv = equipe[i].stats.pv_max;
        }

    } else if (strcmp(effet, "team_def+") == 0) {
        for (int i = 0; i <= nbr_joueur; i++)
            equipe[i].stats_temp.def += val;
        lanceur->tour_buff_restant = duree;

    } else if (strcmp(effet, "def--") == 0) {
        for (int i = 0; i <= nbr_joueur; i++) {
            ennemis[i].stats_temp.def -= val;
            if (ennemis[i].stats_temp.def < 0) ennemis[i].stats_temp.def = 0;
        }
        lanceur->tour_buff_restant = duree;

    } else if (strcmp(effet, "dodge++") == 0) {
        lanceur->tour_buff_restant = duree;

    } else if (strcmp(effet, "att+") == 0) {
        lanceur->stats_temp.att += lanceur->stats.att * val;
        lanceur->tour_buff_restant = duree;

    } else if (strcmp(effet, "speed+") == 0) {
        lanceur->stats_temp.speed += lanceur->stats.speed * val;
        lanceur->tour_buff_restant = duree;

    } else if (strcmp(effet, "pv_max_temp") == 0) {
        lanceur->stats_temp.pv = lanceur->stats.pv_max;
    } else if (strcmp(effet, "debuff_hit") == 0) {
        int cible = demanderChoixDansIntervalle("Choisis une cible :", 1, nbr_joueur + 1, BLEU) - 1;
        float degats = lanceur->stats_temp.att * val * 5;
        ennemis[cible].stats_temp.pv -= degats;
        ennemis[cible].stats_temp.def -= 0.2;
        if (ennemis[cible].stats_temp.def < 0) ennemis[cible].stats_temp.def = 0;
        printf("%s inflige %.1f dégâts à %s et réduit sa défense !\n", lanceur->name, degats, ennemis[cible].name);
        attendreEntree();
    }
}

void attaque_classique(Player* attaquant, Player ennemis[], int nbr_joueur) {
    int cible = demanderChoixDansIntervalle("Choisir la cible :", 1, nbr_joueur + 1, BLEU) - 1;

    if (ennemis[cible].stats_temp.pv <= 0) {
        printf("Cible déjà K.O. !\n");
        attendreEntree();
        return;
    }

    if (ennemis[cible].tour_buff_restant > 0 && strcmp(ennemis[cible].atk_spe.effet_type, "dodge++") == 0) {
        printf(JAUNE "%s esquive automatiquement grâce à sa technique spéciale !\n" RESET, ennemis[cible].name);
        attendreEntree();
        return;
    }

    float degats = attaquant->stats_temp.att * 5;
    degats *= (1 - ennemis[cible].stats_temp.def);

    if (((float)rand() / RAND_MAX) < ennemis[cible].stats_temp.dodge) {
        printf(JAUNE "Ce combattant a esquivé l'attaque !\n" RESET);
        attendreEntree();
        return;
    }

    ennemis[cible].stats_temp.pv -= degats;
    printf("%s inflige %.1f dégâts à %s !\n", attaquant->name, degats, ennemis[cible].name);
    if (ennemis[cible].stats_temp.pv <= 0)
        printf(ROUGE "%s est K.O. !\n" RESET, ennemis[cible].name);
    attendreEntree();
}

void utiliser_competence(Player* lanceur, Player equipe[], Player ennemis[], int nbr_joueur) {
    if (lanceur->atk_spe.recharge > 0) {
        printf(ROUGE "✖ Compétence non rechargée (%d tour(s) restant)\n" RESET, lanceur->atk_spe.recharge);
        attendreEntree();
        return;
    }

    printf("%s utilise %s !\n", lanceur->name, lanceur->atk_spe.name);
    printf("⌀ %s\n", lanceur->atk_spe.description);

    appliquer_effet(lanceur, equipe, ennemis, nbr_joueur);
    lanceur->atk_spe.recharge = lanceur->atk_spe.recharge_max;
}

void combat(Player eq1_stats[], Player eq2_stats[], int nbr_joueur, AffichagePerso affichage[]) {
    srand(time(NULL));
    int tour = 1;
    int arreter = 0;

    while (!arreter) {
        printf("\n========== TOUR %d ==========\n", tour);

        for (int e = 0; e <= 1; e++) {
            Player* equipe = (e == 0) ? eq1_stats : eq2_stats;
            Player* ennemis = (e == 0) ? eq2_stats : eq1_stats;

            for (int i = 0; i <= nbr_joueur; i++) {
                if (equipe[i].stats_temp.pv <= 0) continue;

                if (equipe_KO(ennemis, nbr_joueur)) {
                    printf("\n=== L'équipe %d est K.O. ===\nÉQUIPE %d GAGNE !\n", (e == 0) ? 2 : 1, (e == 0) ? 1 : 2);
                    arreter = 1;
                    break;
                }

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
                int choix = demanderChoixDansIntervalle("Que veux-tu faire ?", 1, 2, JAUNE);

                if (choix == 1)
                    attaque_classique(&equipe[i], ennemis, nbr_joueur);
                else
                    utiliser_competence(&equipe[i], equipe, ennemis, nbr_joueur);

                update_competence(&equipe[i]);
                update_effets(&equipe[i]);
            }

            if (arreter) break;
        }

        tour++;
    }
