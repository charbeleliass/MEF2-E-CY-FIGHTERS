#ifndef MENU_H
#define MENU_H

#include "structure.h"
#include "choix.h"
#include "combat.h"

void afficherTitre();
void afficherMenu(int *mode , int *nbr_joueur);
void afficherTousLesPersos();
void afficherBarre(int valeur);
void afficherPersonnage(int x);

#endif
