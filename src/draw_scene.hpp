#pragma once

#include "utils.hpp"
#include "texture.hpp"



void update_player_position(double const deltaTime);
bool handle_collision(Vector3D posPerso, double const deltaTime);
void drawPerso();

