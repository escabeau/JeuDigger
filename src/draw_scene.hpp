#pragma once

#include "utils.hpp"
#include "texture.hpp"
#include "graphe.hpp"



void update_player_position(double const deltaTime);
void update_IA_position(double const deltaTime);
bool handle_collision(Vector3D posPerso, double const deltaTime);
void drawPerso();
void drawIA();
void detruireBloc();
void loosePiege();
void updateGraphe();

