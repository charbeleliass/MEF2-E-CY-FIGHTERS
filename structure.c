#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structure.h"

#define MAX_LIGNE 256

// Chargement des personnages depuis personnages.txt
void chargerPersonnages(Player persos[], int taille) {
    FILE *f = fopen("personnages.txt", "r");
    if (!f) {
        perror("Erreur ouverture personnages.txt");
        exit(1);
    }

    char ligne[MAX_LIGNE];
    fgets(ligne, MAX_LIGNE, f); // Ignore l'en-tête

    for (int i = 0; i < taille; i++) {
        if (fgets(ligne, MAX_LIGNE, f)) {
            char nom[50];
            int pv, att, speed, crit;
            float def, dodge;

            sscanf(ligne, "%[^;];%d;%d;%f;%d;%f;%d", nom, &pv, &att, &def, &speed, &dodge, &crit);

            persos[i].name = strdup(nom);
            persos[i].stats.pv = pv;
            persos[i].stats.pv_max = PVMAX;
            persos[i].stats.att = att;
            persos[i].stats.def = def;
            persos[i].stats.speed = speed;
            persos[i].stats.dodge = dodge;
            persos[i].stats_temp = persos[i].stats;
            persos[i].tour_buff_restant = 0;
        }
    }

    fclose(f);
}

// Chargement des techniques depuis techniques.txt
void chargerTechniques(Player persos[], int taille) {
    FILE *f = fopen("techniques.txt", "r");
    if (!f) {
        perror("Erreur ouverture techniques.txt");
        exit(1);
    }

    char ligne[MAX_LIGNE];
    fgets(ligne, MAX_LIGNE, f); // Ignore l'en-tête

    for (int i = 0; i < taille; i++) {
        if (fgets(ligne, MAX_LIGNE, f)) {
            char nom[50], effet[20], description[200];
            float valeur;
            int tours, recharge;

            sscanf(ligne, "%[^;];%f;%[^;];\"%[^\"]\";%d;%d", nom, &valeur, effet, description, &tours, &recharge);

            persos[i].atk_spe.name = strdup(nom);
            persos[i].atk_spe.valeur = valeur;
            strncpy(persos[i].atk_spe.description, description, sizeof(persos[i].atk_spe.description));
            persos[i].atk_spe.tour_actif = tours;
            persos[i].atk_spe.recharge = recharge;

            // Stocke le type d'effet sous forme de chaîne (ex: "pv+", "aoe", etc.)
            strncpy(persos[i].atk_spe.effet_type, effet, sizeof(persos[i].atk_spe.effet_type));
        }
    }

    fclose(f);
}

// Chargement des infos visuelles pour l'affichage (statistiques simplifiées)
void chargerAffichage(AffichagePerso aff[], Player persos[], int taille) {
    for (int i = 0; i < taille; i++) {
        char buffer[32];
        snprintf(buffer, sizeof(buffer), "(%d)  %s", i + 1, persos[i].name);
        aff[i].nom = strdup(buffer);

        // Simplifie l'affichage à base d'échelles de 1 à 5
        aff[i].pv = persos[i].stats.pv / 20;
        aff[i].att = persos[i].stats.att;
        aff[i].def = (int)(persos[i].stats.def * 10);
        aff[i].speed = persos[i].stats.speed;
        aff[i].dodge = (int)(persos[i].stats.dodge * 10);
        aff[i].crit = 3; // Valeur par défaut
    }
}
