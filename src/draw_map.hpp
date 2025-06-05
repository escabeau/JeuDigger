#pragma once

#include "utils.hpp"
#include "texture.hpp"

void fillGrille(std::vector<std::vector<int>> &grille, int pourcentPlein);
std::vector<std::vector<int>> majGrille(std::vector<std::vector<int>> &grille);
void ajoutObj_piege(std::vector<std::vector<int>> &grille);
void initMap();
void drawTile(float x, float y, float taille);
void drawObjet(float x, float y, float taille);
void drawPiege(float x, float y, float taille);
void drawMap();

void drawMenu();
void drawBoutons();