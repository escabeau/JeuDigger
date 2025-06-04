#pragma once

#include "utils.hpp"
#include "texture.hpp"



void update_player_position(double const deltaTime);
bool handle_collision(Vector3D posPerso, double const deltaTime);
void drawPerso();
void detruireBloc();

struct Direction {
    float dx;
    float dy;
};

struct Ennemi {
    Vector3D position;
    float speed;
};

// Tableau de directions pour le flow field
extern std::vector<std::vector<Direction>> flowField;
// Liste des ennemis
extern std::vector<Ennemi> enemies;
// Tableau pour marquer les cases visitées pendant la génération du flow field
extern std::vector<std::vector<bool>> visited;

void initFlowField();
void generateFlowField();
void updateEnemies(double deltaTime);
void drawEnemies();
void spawnEnemy(const Vector3D& position, float speed);
Vector3D getRandomEmptyPosition();