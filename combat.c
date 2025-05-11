#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "combat.h"
#include "structure.h"
#include "choix.h"
#include "menu.h"
#include "computer.h"

// Pause le programme en attente d’un appui sur Entrée
void attendreEntree() {
    printf("\nAppuie sur Entrée pour continuer...\n");
    while (getchar() != '\n');
}

// Affiche les effets des assets disponibles pour chaque personnage
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

// Applique les effets des assets côté affichage uniquement
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

// Applique les effets réels des assets sur les stats temporaires des personnages
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
    if (p->stats_temp.pv < 0)
        p->stats_temp.pv = 0;
}

// Choix d'armes pour chaque combattant d'une équipe
void choix_assets(int equipe[], int nbr_joueur, Player eq_stats[], AffichagePerso persos_affichage[]) {
    int arme = 0;
    for (int i = 0; i <= nbr_joueur; i++) {
        arme = demanderChoixDansIntervalle("choisir arme : ", 0, 6, VERT);
        AffichagePerso *paff = &persos_affichage[equipe[i] - 1];
        atout(paff, arme); // modifie l’affichage
        afficherPersonnage(equipe[i] - 1, persos_affichage);
        vraiatout(&eq_stats[i], arme); // modifie les vraies stats
    }
}

// Choix d’armes pour les deux équipes (interface utilisateur)
void choix_assets_E(int equipe1[], int equipe2[], int nbr_joueur, Player eq1_stats[], Player eq2_stats[], AffichagePerso persos_affichage[]) {
    afficher_stats();
    printf("Au tour de l'équipe 1 :\n");
    choix_assets(equipe1, nbr_joueur, eq1_stats, persos_affichage);
    attendreEntree();
    afficher_stats();
    printf("Au tour de l'équipe 2 :\n");
    choix_assets(equipe2, nbr_joueur, eq2_stats, persos_affichage);
}
// Affiche les effets visuels (emojis) des buffs/debuffs actifs
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
        else if (strcmp(effet, "debuff_hit") == 0) printf("☠️ ");
        else printf("✨ ");
    }
}

// Affiche l'état complet du combat avec les deux équipes (barres de PV, effets, progression)
void afficher_etat_combat(Player eq1[], Player eq2[], int joueur_actuel, int equipe_joueur, int nbr_joueur) {
    system("clear");

    // --- Affichage de l'équipe 1 ---
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

    // Barres de vie
    for (int i = 0; i <= nbr_joueur; i++) {
        printf("[");
        int pv_ratio = (int)((eq1[i].stats_temp.pv / eq1[i].stats.pv_max) * 20);
        for (int j = 0; j < pv_ratio; j++) printf("#");
        for (int j = pv_ratio; j < 20; j++) printf(" ");
        printf("]");
    }
    printf("\n");

    // Affichage des effets
    for (int i = 0; i <= nbr_joueur; i++) {
        printf("[ ");
        afficher_emojis_effets(eq1[i]);
        printf(" ]");
    }
    printf("\n");

    // Progression de la barre de vitesse
    for (int i = 0; i <= nbr_joueur; i++) {
        if (eq1[i].stats_temp.pv > 0) {
            int pct = (eq1[i].barre_vitesse * 100) / 1000;
            printf("Progression : %3d%%   ", pct);
        } else {
            printf("                ");
        }
    }
    printf("\n");

    // --- Affichage de l'équipe 2 ---
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

    // Barres de vie
    for (int i = 0; i <= nbr_joueur; i++) {
        printf("[");
        int pv_ratio = (int)((eq2[i].stats_temp.pv / eq2[i].stats.pv_max) * 20);
        for (int j = 0; j < pv_ratio; j++) printf("#");
        for (int j = pv_ratio; j < 20; j++) printf(" ");
        printf("]");
    }
    printf("\n");

    // Effets spéciaux
    for (int i = 0; i <= nbr_joueur; i++) {
        printf("[ ");
        afficher_emojis_effets(eq2[i]);
        printf(" ]");
    }
    printf("\n");

    // Progression de la barre de vitesse
    for (int i = 0; i <= nbr_joueur; i++) {
        if (eq2[i].stats_temp.pv > 0) {
            int pct = (eq2[i].barre_vitesse * 100) / 1000;
            printf("Progression : %3d%%   ", pct);
        } else {
            printf("                ");
        }
    }
    printf("\n\n");
}

// Vérifie si toute une équipe est K.O. (PV <= 0 pour tous)
int equipe_KO(Player equipe[], int nbr_joueur) {
    for (int i = 0; i <= nbr_joueur; i++)
        if (equipe[i].stats_temp.pv > 0)
            return 0;
    return 1;
}

// Réduction de la recharge des compétences spéciales
void update_competence(Player* p) {
    if (p->atk_spe.recharge > 0)
        p->atk_spe.recharge--;
}

// Met à jour les effets temporaires (fin des buffs/debuffs)
void update_effets(Player* p) {
    if (p->tour_buff_restant > 0) {
        p->tour_buff_restant--;

        if (p->tour_buff_restant == 0) {
            // Réinitialisation des stats à la fin des effets temporaires
            p->stats_temp.att = p->stats.att;
            p->stats_temp.def = p->stats.def;
            p->stats_temp.dodge = p->stats.dodge;
            p->stats_temp.speed = p->stats.speed;

            // Sécurité sur les PV
            if (p->stats_temp.pv > p->stats.pv_max)
                p->stats_temp.pv = p->stats.pv_max;
            if (p->stats_temp.pv < 0)
                p->stats_temp.pv = 0;
        }
    }
    // Détermine quel joueur est prêt à jouer (barre de vitesse pleine)
int trouver_suivant_joueur(Player eq1[], Player eq2[], int taille) {
    int total = 2 * (taille + 1); // Nombre total de combattants
    int index = -1;
    int max = -1;

    for (int i = 0; i < total; i++) {
        Player* p = (i < taille + 1) ? &eq1[i] : &eq2[i - (taille + 1)];
        if (p->stats_temp.pv <= 0) continue;

        p->barre_vitesse += p->stats_temp.speed;
        if (p->barre_vitesse >= 1000 && p->barre_vitesse > max) {
            max = p->barre_vitesse;
            index = i;
        }
    }
    return index;
}

// Réinitialise la barre de vitesse d’un joueur après son tour
void reset_barre(Player* p) {
    p->barre_vitesse = 0;
}

// Gère l'attaque classique d'un joueur avec sélection manuelle de la cible
void attaque_classique(Player* attaquant, Player ennemis[], int nbr_joueur) {
    int cible = demanderChoixDansIntervalle("Choisir la cible :", 1, nbr_joueur + 1, BLEU) - 1;
    attaque_classique_direct(attaquant, &ennemis[cible]);
}

// Variante directe de l'attaque classique (utile pour l'IA)
void attaque_classique_direct(Player* attaquant, Player* cible) {
    // Vérifie si la cible est déjà K.O.
    if (cible->stats_temp.pv <= 0) {
        printf("Cible déjà K.O. !\n");
        attendreEntree();
        return;
    }

    // Vérifie si la cible est en esquive automatique (buff dodge++)
    if (cible->tour_buff_restant > 0 && strcmp(cible->atk_spe.effet_type, "dodge++") == 0) {
        printf(JAUNE "%s esquive automatiquement grâce à sa technique spéciale !\n" RESET, cible->name);
        attendreEntree();
        return;
    }

    // Calcul des dégâts infligés
    float degats = attaquant->stats_temp.att * 5;
    degats *= (1 - cible->stats_temp.def);

    // Test d'esquive
    if (((float)rand() / RAND_MAX) < cible->stats_temp.dodge) {
        printf(JAUNE "Ce combattant a esquivé l'attaque !\n" RESET);
        attendreEntree();
        return;
    }

    // Applique les dégâts
    cible->stats_temp.pv -= degats;
    if (cible->stats_temp.pv < 0) cible->stats_temp.pv = 0;

    printf("%s inflige %.1f dégâts à %s !\n", attaquant->name, degats, cible->name);
    if (cible->stats_temp.pv <= 0)
        printf(ROUGE "%s est K.O. !\n" RESET, cible->name);
    attendreEntree();
}
}
// Applique les effets d'une compétence spéciale, en tenant compte du contexte (ordi ou joueur humain)
void appliquer_effet(Player* lanceur, Player equipe[], Player ennemis[], int nbr_joueur, int is_ordi) {
    char* effet = lanceur->atk_spe.effet_type;
    float val = lanceur->atk_spe.valeur;
    int duree = lanceur->atk_spe.tour_actif;

    if (strcmp(effet, "aoe") == 0) {
        // Dégâts à toute l’équipe ennemie
        for (int i = 0; i <= nbr_joueur; i++) {
            if (ennemis[i].stats_temp.pv > 0) {
                ennemis[i].stats_temp.pv -= lanceur->stats_temp.att * val * 5;
                if (ennemis[i].stats_temp.pv < 0)
                    ennemis[i].stats_temp.pv = 0;
            }
        }
    } else if (strcmp(effet, "pv+") == 0) {
        // Soigne le lanceur en pourcentage de ses PV
        lanceur->stats_temp.pv += lanceur->stats_temp.pv * val;
        if (lanceur->stats_temp.pv > lanceur->stats.pv_max)
            lanceur->stats_temp.pv = lanceur->stats.pv_max;
    } else if (strcmp(effet, "pv_max_temp") == 0) {
        // Soigne à fond une seule fois
        lanceur->stats_temp.pv = lanceur->stats.pv_max;
    } else if (strcmp(effet, "team_pv+") == 0) {
        // Soin en AOE + réanimation
        for (int i = 0; i <= nbr_joueur; i++) {
            if (equipe[i].stats_temp.pv <= 0) {
                equipe[i].stats_temp.pv = 10; // Réanimation
            } else {
                equipe[i].stats_temp.pv += equipe[i].stats.pv_max * val;
                if (equipe[i].stats_temp.pv > equipe[i].stats.pv_max)
                    equipe[i].stats_temp.pv = equipe[i].stats.pv_max;
            }
        }
    } else if (strcmp(effet, "team_def+") == 0) {
        // Buff défense pour l’équipe
        for (int i = 0; i <= nbr_joueur; i++)
            equipe[i].stats_temp.def += val;
        lanceur->tour_buff_restant = duree;
    } else if (strcmp(effet, "def--") == 0) {
        // Debuff défense pour ennemis
        for (int i = 0; i <= nbr_joueur; i++) {
            ennemis[i].stats_temp.def -= val;
            if (ennemis[i].stats_temp.def < 0) ennemis[i].stats_temp.def = 0;
        }
        lanceur->tour_buff_restant = duree;
    } else if (strcmp(effet, "att+") == 0) {
        // Buff attaque personnel
        lanceur->stats_temp.att += lanceur->stats.att * val;
        lanceur->tour_buff_restant = duree;
    } else if (strcmp(effet, "dodge++") == 0) {
        // Esquive automatique
        lanceur->tour_buff_restant = duree;
    } else if (strcmp(effet, "debuff_hit") == 0) {
        // Frappe + réduction défense
        int cible = -1;
        if (is_ordi)
            cible = trouver_cible_plus_faible(ennemis, nbr_joueur);
        else
            cible = demanderChoixDansIntervalle("Choisir la cible :", 1, nbr_joueur + 1, BLEU) - 1;

        if (cible >= 0 && ennemis[cible].stats_temp.pv > 0) {
            ennemis[cible].stats_temp.pv -= lanceur->stats_temp.att * val * 5;
            ennemis[cible].stats_temp.def -= 0.25;
            if (ennemis[cible].stats_temp.def < 0) ennemis[cible].stats_temp.def = 0;
            if (ennemis[cible].stats_temp.pv < 0) ennemis[cible].stats_temp.pv = 0;
            lanceur->tour_buff_restant = duree;
        }
    }
}

// Gère l'utilisation d'une compétence par un joueur humain
void utiliser_competence(Player* lanceur, Player equipe[], Player ennemis[], int nbr_joueur) {
    if (lanceur->atk_spe.recharge > 0) {
        printf(ROUGE "✖ Compétence non rechargée (%d tour(s) restant)\n" RESET, lanceur->atk_spe.recharge);
        attendreEntree();
        return;
    }

    printf("%s utilise %s !\n", lanceur->name, lanceur->atk_spe.name);
    printf("⌀ %s\n", lanceur->atk_spe.description);
    appliquer_effet(lanceur, equipe, ennemis, nbr_joueur, 0);
    lanceur->atk_spe.recharge = lanceur->atk_spe.recharge_max;
    attendreEntree();
}

// Fonction principale de déroulement du combat (PvP ou PvC)
void combat(Player eq1[], Player eq2[], int nbr_joueur, AffichagePerso affichage[], int mode, int difficulte) {
    srand(time(NULL)); // Initialise l'aléatoire

    // Initialisation des barres de vitesse
    for (int i = 0; i <= nbr_joueur; i++) {
        eq1[i].barre_vitesse = 0;
        eq2[i].barre_vitesse = 0;
    }

    // Boucle principale du combat
    while (1) {
        // Vérifie si une des équipes a perdu
        if (equipe_KO(eq1, nbr_joueur)) {
            printf(ROUGE "\n=== L'ÉQUIPE 1 EST K.O. ===\nÉQUIPE 2 GAGNE !\n" RESET);
            break;
        }
        if (equipe_KO(eq2, nbr_joueur)) {
            printf(ROUGE "\n=== L'ÉQUIPE 2 EST K.O. ===\nÉQUIPE 1 GAGNE !\n" RESET);
            break;
        }

        // Trouve le prochain joueur à jouer
        int index = trouver_suivant_joueur(eq1, eq2, nbr_joueur);
        if (index == -1) continue;

        Player* joueur = (index <= nbr_joueur) ? &eq1[index] : &eq2[index - nbr_joueur - 1];
        Player* equipe = (index <= nbr_joueur) ? eq1 : eq2;
        Player* ennemis = (index <= nbr_joueur) ? eq2 : eq1;
        int equipe_num = (index <= nbr_joueur) ? 0 : 1;
        int joueur_index = (index <= nbr_joueur) ? index : index - nbr_joueur - 1;

        reset_barre(joueur);
        update_competence(joueur);
        update_effets(joueur);

        afficher_etat_combat(eq1, eq2, joueur_index, equipe_num, nbr_joueur);
        printf("\nC'est au tour de %s\n", joueur->name);

        // Si c'est l'ordinateur, on lance son tour automatiquement
        if ((equipe_num == 1) && (mode == 2)) {
            tour_ordinateur(joueur, ennemis, equipe, nbr_joueur, difficulte);
            continue;
        }

        // Sinon, choix pour le joueur humain
        printf("1 - Attaque classique\n");
        printf("2 - %s ", joueur->atk_spe.name);
        if (joueur->atk_spe.recharge > 0)
            printf("(Recharge: %d tour(s) restant)\n", joueur->atk_spe.recharge);
        else
            printf("(Disponible)\n");

        printf("   ⌀ %s\n", joueur->atk_spe.description);

        int choix = demanderChoixDansIntervalle("Que veux-tu faire ?", 1, 2, JAUNE);
        if (choix == 1)
            attaque_classique(joueur, ennemis, nbr_joueur);
        else
            utiliser_competence(joueur, equipe, ennemis, nbr_joueur);
    }
}
