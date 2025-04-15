#include <stdio.h>
#include <stdlib.h>
#include "structure.h"

Player p[12] = {
  {"luffy", {70, PVMAX, 0.3, 7, 2, 0.4}, {70, PVMAX, 0.3, 7, 2, 0.4}, {"Gum Gum no Gum Gum", 1.4, "", 2, 0, {0, 0, 0, 0, 0}}, 0},
  {"sanji", {60, PVMAX, 0.4, 8, 3, 0.2}, {60, PVMAX, 0.4, 8, 3, 0.2}, {"diabolo jumbo", 1.2, "", 2, 0, {0, 0, 0, 0, 0}}, 0},
  {"zoro", {80, PVMAX, 0.1, 7, 4, 0.3}, {80, PVMAX, 0.1, 7, 4, 0.3}, {"tiger slash", 1.1, "", 2, 0, {0, 0, 0, 0, 0}}, 0},
  {"ace", {90, PVMAX, 0.3, 5, 1, 0.5}, {90, PVMAX, 0.3, 5, 1, 0.5}, {"Flame fence", 1.2, "", 1, 0, {0, 0, 0, 0, 0}}, 0},
  {"brook", {70, PVMAX, 0.4, 5, 4, 0.3}, {70, PVMAX, 0.4, 5, 4, 0.3}, {"Song slash", 1.2, "", 3, 0, {0, 0, 0, 0, 0}}, 0},
  {"ussop", {80, PVMAX, 0.3, 5, 3, 0.4}, {80, PVMAX, 0.3, 5, 3, 0.4}, {"Skull bomb blast", 1.1, "", 1, 0, {0, 0, 0, 0, 0}}, 0},
  {"do flamingo", {60, PVMAX, 0.4, 5, 5, 0.3}, {60, PVMAX, 0.4, 5, 5, 0.3}, {"Fallbright", 1.2, "", 2, 0, {0, 0, 0, 0, 0}}, 0},
  {"big mom", {80, PVMAX, 0.3, 6, 1, 0.5}, {80, PVMAX, 0.3, 6, 1, 0.5}, {"Master cannon", 1.3, "", 1, 0, {0, 0, 0, 0, 0}}, 0},
  {"katakuri", {80, PVMAX, 0.4, 8, 1, 0.2}, {80, PVMAX, 0.4, 8, 1, 0.2}, {"Mochi hadan", 1.3, "", 3, 0, {0, 0, 0, 0, 0}}, 0},
  {"black beard", {80, PVMAX, 0.1, 7, 4, 0.3}, {80, PVMAX, 0.1, 7, 4, 0.3}, {"Black hole", 1.4, "", 2, 0, {0, 0, 0, 0, 0}}, 0},
  {"crocodile", {60, PVMAX, 0.5, 4, 5, 0.3}, {60, PVMAX, 0.5, 4, 5, 0.3}, {"Desert spada", 1.2, "", 3, 0, {0, 0, 0, 0, 0}}, 0},
  {"Kaido", {90, PVMAX, 0.3, 8, 4, 0.2}, {90, PVMAX, 0.3, 8, 4, 0.2}, {"Thunder", 1.4, "", 2, 0, {0, 0, 0, 0, 0}}, 0}
};

AffichagePerso persos_affichage[12] = {
    {"(1)  Luffy", 2, 4, 3, 2, 4, 4},
    {"(2)  Sanji", 1, 5, 4, 3, 2, 2},
    {"(3)  Zoro", 3, 4, 1, 4, 3, 1},
    {"(4)  Ace", 4, 2, 3, 1, 5, 2},
    {"(5)  Brook", 2, 2, 4, 4, 3, 2},
    {"(6)  Ussop", 3, 2, 3, 3, 4, 1},
    {"(7)  Do Flamingo", 1, 2, 4, 5, 3, 2},
    {"(8)  Big Mom", 3, 3, 3, 1, 5, 3},
    {"(9)  Katakuri", 3, 5, 4, 1, 2, 3},
    {"(10) Black Beard", 3, 4, 1, 4, 3, 4},
    {"(11) Crocodile", 1, 1, 5, 5, 3, 2},
    {"(12) Kaido", 4, 5, 3, 4, 2, 4}
};
