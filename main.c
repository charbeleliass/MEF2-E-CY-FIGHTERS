#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "structure.h"
#include "choix.h"
#include "combat.h"

int main() {
    int mode = 0, nbr_joueur = 0;
    int equipe1[3], equipe2[3];

    afficherTitre();
    afficherMenu(&mode, &nbr_joueur);
    afficherTousLesPersos();
    choix_joueur(equipe1, equipe2, nbr_joueur, mode);
    choix_assets_E(equipe1, equipe2, nbr_joueur);

    return 0;
}
