#pragma once

#include "glbasimac/glbi_engine.hpp"
#include "glbasimac/glbi_set_of_points.hpp"
#include "glbasimac/glbi_convex_2D_shape.hpp"
#include "tools/basic_mesh.hpp"
#include "texture.hpp"

using namespace glbasimac;


/* OpenGL Engine */
extern GLBI_Engine myEngine;

extern float winHaut;
extern float winBas;
extern float winDroite;
extern float winGauche;



void initScene();

void movePersoHaut();
void movePersoBas();
void movePersoDroite();
void movePersoGauche();

void drawScene();

