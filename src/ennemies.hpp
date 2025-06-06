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

void initEnnemy(int nbEnnemi);
void initFlowField();
void generateFlowField();
void updateEnemies(double deltaTime);
void drawEnemies();
void spawnEnemy(const Vector3D& position, float speed);
Vector3D getRandomEmptyPosition();