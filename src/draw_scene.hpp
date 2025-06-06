#pragma once

#include "utils.hpp"
#include "texture.hpp"
#include "ennemies.hpp"



void update_player_position(double const deltaTime, GameState& gameState);
bool handle_collision(Vector3D posPerso, double const deltaTime);
void drawPerso();
void detruireBloc(GameState& gameState);
void resetGame();
void loosePiege(GameState& gameState);
void looseEnnemi(GameState& gameState);

extern std::vector<Ennemi> enemies;

void drawScore();