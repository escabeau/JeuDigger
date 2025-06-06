#pragma once

#include "utils.hpp"
#include "texture.hpp"

struct Direction {
    float dx;
    float dy;
};

struct Ennemi{
    Vector3D position;
    float speed;
};

// // Tableau de directions pour le flow field
// extern std::vector<std::vector<Direction>> flowField;
// // Liste des ennemis
// extern std::vector<Ennemi> enemies;
// // Tableau pour marquer les cases visitées pendant la génération du flow field
// extern std::vector<std::vector<bool>> visited;

void initEnnemy(int nbEnnemi);
void initFlowField();
void generateFlowField();
void updateEnemies(double deltaTime);
void drawEnemies();
void spawnEnemy(const Vector3D& position, float speed);
Vector3D getRandomEmptyPosition();