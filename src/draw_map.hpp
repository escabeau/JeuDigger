#pragma once

#include "utils.hpp"

void fillGrille(std::vector<std::vector<int>> &grille, int pourcentPlein);
std::vector<std::vector<int>> majGrille(std::vector<std::vector<int>> &grille);
void initMap();
void drawTile(int x, int y, float taille);
void drawMap();