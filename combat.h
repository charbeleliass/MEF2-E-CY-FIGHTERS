#ifndef COMBAT_H
#define COMBAT_H

#include "structure.h"
#include "choix.h"
#include "menu.h"

void afficher_stats();
void atout(AffichagePerso *p, int a);
void vraiatout(Player* p, int a);
void choix_assets(int equipe[], int nbr_joueur);
void choix_assets_E(int equipe1[], int equipe2[], int nbr_joueur);

#endif
