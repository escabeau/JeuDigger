#pragma once

#include "tools/stb_image.h"
#include "glbasimac/glbi_texture.hpp"
#include "utils.hpp"


using namespace glbasimac;

extern StandardMesh carre;
// Coordonnées des sommets (x, y)
static float coordCoins[] =  {-0.5,-0.5, -0.5,0.5, 0.5,0.5, 0.5,-0.5};
// Coordonnées UV (u, v)
static float uvs[] = {0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f};

extern GLBI_Texture texture;

void initTexture();
void TexturePerso();
void TextureFond();
