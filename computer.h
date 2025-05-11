#ifndef COMPUTER_H
#define COMPUTER_H

#include "structure.h"
#include "combat.h"

void choix_ordi_persos(int *equipe, int nbr_joueur);
void choix_ordi_assets(int *equipe, int nbr_joueur, Player *eq_stats, AffichagePerso *affichage);
int trouver_cible_plus_faible(Player *ennemis, int nbr_joueur);
void tour_ordinateur(Player *ordi, Player *ennemis, Player *alliés, int nbr_joueur, int difficulte);

#endif
