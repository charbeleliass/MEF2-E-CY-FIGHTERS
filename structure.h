#ifndef STRUCTURE_H
#define STRUCTURE_H

#define ROUGE   "\033[1;31m"
#define VERT    "\033[1;32m"
#define JAUNE   "\033[1;33m"
#define BLEU    "\033[1;36m"
#define RESET   "\033[0m"

#define PVMAX 120
#define ENNERGIE 10

typedef struct {
    char* nom;  
    int pv;
    int att;
    int def;
    int speed;
    int dodge;
    int crit;
} AffichagePerso;

typedef struct {
    float pv;
    float pv_max;
    float def;
    float att;
    int speed;
    float dodge;
} Stats;

typedef struct {
    int pv;
    int att;
    int def;
    int speed;
    int dodge;
} Effect;

typedef struct {
    char* name;
    float valeur;
    char description[200];
    int tour_actif;
    int recharge;
    int recharge_max;
    Effect buff;
    char effet_type[20]; 
} Special;

typedef struct {
    char* name;
    Stats stats;
    Stats stats_temp;
    Special atk_spe;
    int tour_buff_restant;
    int barre_vitesse;
} Player;

Player initialiserJoueur(int index);
AffichagePerso getAffichagePerso(int index);

void chargerPersonnages(Player persos[], int taille);
void chargerTechniques(Player persos[], int taille);
void chargerAffichage(AffichagePerso aff[], Player persos[], int taille);

#endif
