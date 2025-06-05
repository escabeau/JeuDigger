#pragma once

#include "glbasimac/glbi_engine.hpp"
#include "glbasimac/glbi_set_of_points.hpp"
#include "glbasimac/glbi_convex_2D_shape.hpp"
#include "tools/basic_mesh.hpp"
#include "texture.hpp"

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include "tools/matrix_stack.hpp"
#include <iostream>
#include <cmath>
#include <array>

#define GLT_IMPLEMENTATION
#include "easyfont/gltext.h"

using namespace glbasimac;

extern const float GL_VIEW_SIZE;

extern std::array<int, GLFW_KEY_LAST> keysState;

/* OpenGL Engine */
extern GLBI_Engine myEngine;

extern int winWidth;
extern int winHeight;

extern float winHaut;
extern float winBas;
extern float winDroite;
extern float winGauche;

extern GLBI_Texture texturePerso;
extern GLBI_Texture textureFond;
extern GLBI_Texture textureObjet;
extern GLBI_Texture texturePiege;
extern GLBI_Texture textureMenu;
extern GLBI_Texture textureJouer;
extern GLBI_Texture textureQuitter;

extern std::vector<GLBI_Texture> texturesHerbe;
extern std::vector<std::vector<int>> variationHerbe;

extern std::vector<std::vector<int>> grilleMap;