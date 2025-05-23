#pragma once

#include "utils.hpp"

void initPerso();

void movePersoHaut();
void movePersoBas();
void movePersoDroite();
void movePersoGauche();
void update_player_position(double const deltaTime);
void drawPerso();

