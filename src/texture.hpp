#pragma once

#include "tools/stb_image.h"
#include "glbasimac/glbi_texture.hpp"
#include "utils.hpp"


using namespace glbasimac;

extern StandardMesh carre;
extern StandardMesh tileShape;

// Coordonnées UV (u, v)
static float uvs[] = {0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f};

// Coordonnées des sommets (x, y) du Perso
static float coordCoins[] =  {-0.5,-0.5, -0.5,0.5, 0.5,0.5, 0.5,-0.5};

// Coordonnées des sommets (x, y) des cubes de la map
static float tileCoords[] =  {-0.5,-0.5, -0.5,0.5, 0.5,0.5, 0.5,-0.5};

// extern GLBI_Texture texturePerso;
// extern GLBI_Texture textureFond;


void initTexturePerso();
void initTextureBackground();


void loadTexture(const char* filename,GLBI_Texture& texture);
void loadTexturePerso(GLBI_Texture& texture);
void loadTextureFond(GLBI_Texture& texture);
void loadTextureObjet(GLBI_Texture& texture);
void loadTexturePiege(GLBI_Texture& texture);
