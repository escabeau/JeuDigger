#pragma once

#include "utils.hpp"
#include "texture.hpp"


void loosePiege(GameState& gameState);
void looseEnnemi(GameState& gameState);
void update_player_position(double const deltaTime, GameState& gameState);
bool handle_collision(Vector3D posPerso, double const deltaTime);
void drawPerso();
void detruireBloc(GameState& gameState);
void resetGame();


struct Direction {
    float dx;
    float dy;
};

struct Ennemi{
    Vector3D position;
    float speed;
};



// Tableau de directions pour le flow field
extern std::vector<std::vector<Direction>> flowField;
// Liste des ennemis
extern std::vector<Ennemi> enemies;
// Tableau pour marquer les cases visitées pendant la génération du flow field
extern std::vector<std::vector<bool>> visited;


void initEnnemy(int nbEnnemi);
void initFlowField();
void generateFlowField();
void updateEnemies(double deltaTime);
void drawEnemies();
void spawnEnemy(const Vector3D& position, float speed);
Vector3D getRandomEmptyPosition();


void drawScore();

void drawBoum(float x, float y, float taille);
struct Boum {
    bool isExploding;
    int row;
    int col;
    double startTime;
    int frame;
};
extern Boum explodingMine;