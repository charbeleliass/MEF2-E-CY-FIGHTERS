#ifndef COMBAT_H
#define COMBAT_H

#include "structure.h"
#include "choix.h"
#include "menu.h"

void afficher_stats();
void atout(AffichagePerso *p, int a);
void vraiatout(Player* p, int a);
void choix_assets(int equipe[], int nbr_joueur, Player eq_stats[]);
void choix_assets_E(int equipe1[], int equipe2[], int nbr_joueur,Player eq1_stats[], Player eq2_stats[]);
void afficher_etat_combat(Player eq1[], Player eq2[], int joueur_actuel, int equipe_joueur, int nbr_joueur);
void combat(Player eq1_stats[], Player eq2_stats[], int nbr_joueur);

void attaque_classique(Player* attaquant, Player ennemis[], int nbr_joueur);
void utiliser_competence(Player* lanceur, Player ennemis[], int nbr_joueur);

void update_competence(Player* p);
void update_effets(Player* p);
int equipe_KO(Player equipe[], int nbr_joueur);

#endif
