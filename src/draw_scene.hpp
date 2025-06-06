#pragma once

#include "utils.hpp"
#include "texture.hpp"
#include "ennemies.hpp"


void loosePiege(GameState& gameState);
void looseEnnemi(GameState& gameState);
void update_player_position(double const deltaTime, GameState& gameState);
bool handle_collision(Vector3D posPerso, double const deltaTime);
void drawPerso();
void detruireBloc(GameState& gameState);
void resetGame();


extern std::vector<Ennemi> enemies;

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