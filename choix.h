#ifndef CHOIX_H
#define CHOIX_H

#include "structure.h"
#define ROUGE   "\033[1;31m"
#define VERT    "\033[1;32m"
#define JAUNE   "\033[1;33m"
#define BLEU    "\033[1;36m"
#define RESET   "\033[0m"

int demanderChoixDansIntervalle(const char *texte, int min, int max, const char *couleur);
void choix_joueur_E(int *equipe, int nbr_joueur);
void choix_joueur(int *equipe1, int *equipe2, int nbr_joueur , int mode);

#endif
