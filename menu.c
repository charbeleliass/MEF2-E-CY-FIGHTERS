#include <stdio.h>
#include <stdlib.h> 
#include "menu.h"
#include "structure.h"
#include "choix.h"
#include "combat.h"

// Définition des codes couleurs ANSI pour la mise en forme console
#define ROUGE   "\033[1;31m"
#define VERT    "\033[1;32m"
#define JAUNE   "\033[1;33m"
#define BLEU    "\033[1;36m"
#define RESET   "\033[0m"

void afficherTitre() {
    system("clear");
    printf(ROUGE);
    printf(" ░▒▓██████▓▒░░▒▓███████▓▒░░▒▓████████▓▒░      ░▒▓███████▓▒░░▒▓█▓▒░▒▓████████▓▒░▒▓██████▓▒░░▒▓████████▓▒░      ░▒▓████████▓▒░▒▓█▓▒░░▒▓██████▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓████████▓▒░▒▓████████▓▒░▒▓███████▓▒░  \n");
    printf("░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░             ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░     ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░             ░▒▓█▓▒░      ░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░  ░▒▓█▓▒░   ░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░ \n");
    printf("░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░             ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░     ░▒▓█▓▒░      ░▒▓█▓▒░             ░▒▓█▓▒░      ░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░  ░▒▓█▓▒░   ░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░ \n");
    printf("░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓██████▓▒░        ░▒▓███████▓▒░░▒▓█▓▒░▒▓██████▓▒░░▒▓█▓▒░      ░▒▓██████▓▒░        ░▒▓██████▓▒░ ░▒▓█▓▒░▒▓█▓▒▒▓███▓▒░▒▓████████▓▒░  ░▒▓█▓▒░   ░▒▓██████▓▒░ ░▒▓███████▓▒░  \n");
    printf("░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░             ░▒▓█▓▒░      ░▒▓█▓▒░▒▓█▓▒░     ░▒▓█▓▒░      ░▒▓█▓▒░             ░▒▓█▓▒░      ░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░  ░▒▓█▓▒░   ░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░ \n");
    printf("░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░             ░▒▓█▓▒░      ░▒▓█▓▒░▒▓█▓▒░     ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░             ░▒▓█▓▒░      ░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░  ░▒▓█▓▒░   ░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░ \n");
    printf(" ░▒▓██████▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓████████▓▒░      ░▒▓█▓▒░      ░▒▓█▓▒░▒▓████████▓▒░▒▓██████▓▒░░▒▓████████▓▒░      ░▒▓█▓▒░      ░▒▓█▓▒░░▒▓██████▓▒░░▒▓█▓▒░░▒▓█▓▒░  ░▒▓█▓▒░   ░▒▓████████▓▒░▒▓█▓▒░░▒▓█▓▒░ \n");
    printf("                                           \n");
    printf(RESET);
    printf("\nAppuyer sur Enter pour ouvrir le jeu");
    while (getchar() != '\n');
}

// Affiche le menu principal permettant de choisir le mode (PVP ou PVC) et la taille de l’équipe
void afficherMenu(int *mode , int *nbr_joueur) {
    system("clear");

    // Sélection du mode de jeu
    printf(BLEU "+========================================+\n");
    printf("║            🌟  MODE DE JEU 🌟           ║\n");
    printf("+========================================+\n" RESET);
    printf(" 1. 🎮  Joueur vs Joueur (PVP)\n");
    printf(" 2. 🤖 Joueur vs Ordinateur (PVC)\n\n");

    *mode = demanderChoixDansIntervalle("👉 Choisis ton mode", 1, 2 , JAUNE);  // Entrée utilisateur

    system("clear");

    // Sélection de la taille de l’équipe
    printf(BLEU "\n+========================================+  \n");
    printf("║       🛡️  TAILLE DE L'ÉQUIPE 🛡️        ║\n");
    printf("+========================================+\n" RESET);
    printf(" 1. 👥  2 contre 2\n");
    printf(" 2. 👥  3 contre 3\n\n");

    *nbr_joueur = demanderChoixDansIntervalle("👉 Choisis la taille de ton équipe", 1, 2 , JAUNE);

    // Confirmation du choix
    printf(VERT "\n✅  Tu as choisi : %s\n", (*mode== 1) ? "PVP" : "PVC");
    printf("👥  Taille : %s\n\n" RESET, (*nbr_joueur == 1) ? "2v2" : "3v3");

    printf("\nAppuyer sur Enter pour choisir vos Personnages ");
    while (getchar() != '\n');  // Pause avant d'afficher la sélection des personnages
}

// Affiche une barre de statistiques sous forme de # sur 8 unités
void afficherBarre(int valeur) {
    for (int i = 0; i < valeur; i++) {
        printf(VERT "#" RESET);
    }
    for (int j = 0; j < 8 - valeur; j++) {
        printf(" ");
    }
    printf(" ");
}

// Affiche les statistiques visuelles d’un seul personnage
void afficherPersonnage(int x, AffichagePerso persos_affichage[]) {
    AffichagePerso p = persos_affichage[x];

    printf(ROUGE"[%-17s]"RESET, p.nom );  // Nom avec couleur
    printf("PV    : "); afficherBarre(p.pv);
    printf("Att   : "); afficherBarre(p.att);
    printf("Def   : "); afficherBarre(p.def);
    printf("Spd   : "); afficherBarre(p.speed);
    printf("Dodge : "); afficherBarre(p.dodge);
    printf("Crit  : "); afficherBarre(p.crit);
    printf("\n");
}

// Affiche la liste complète des personnages disponibles avec leurs statistiques
void afficherTousLesPersos(AffichagePerso persos_affichage[]) {
    system("clear");
    printf(BLEU "+=====================================================================================================================+\n");
    printf("║                                            👥  PERSONNAGES DISPONIBLES 👥                                             ║\n");
    printf("+=====================================================================================================================+\n\n" RESET);

    for (int i = 0; i < 12; i++) {
        afficherPersonnage(i, persos_affichage);
    }

    printf("Appuie sur Entrée pour continuer...");
    while (getchar() != '\n');  // Pause après affichage
}
