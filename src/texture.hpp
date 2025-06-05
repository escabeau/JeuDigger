#pragma once

#include "tools/stb_image.h"
#include "glbasimac/glbi_texture.hpp"
#include "utils.hpp"


using namespace glbasimac;

extern StandardMesh perso;
extern StandardMesh tileShape;
extern StandardMesh fondMenu;
extern StandardMesh bouton;

extern std::array<GLBI_Texture, 4> texturesPerso;
extern GLBI_Texture textureObjet;
extern GLBI_Texture texturePiege;
extern GLBI_Texture textureMenu;
extern GLBI_Texture textureJouer;
extern GLBI_Texture textureQuitter;
extern GLBI_Texture textureFleurEcrase;

extern std::array<GLBI_Texture, 7> texturesHerbe;
extern std::vector<std::vector<int>> variationHerbe;

extern std::array<GLBI_Texture, 2> texturesFleur;
extern std::vector<std::vector<int>> variationFleur;





// Coordonnées UV (u, v)
static float uvs[] = {0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f};

// Coordonnées des sommets (x, y) du Perso
static float persoCoords[] =  {-0.5,-1, -0.5,1, 0.5,1, 0.5,-1};

// Coordonnées des sommets (x, y) des cubes de la map
static float tileCoords[] =  {-0.5,-0.5, -0.5,0.5, 0.5,0.5, 0.5,-0.5};

// Coordonnées des sommets (x, y) du menu
static float menuCoords[] =  {-20,-20, -20,20, 20,20, 20,-20};

// Coordonnées des sommets (x, y) des boutons du menu
static float boutonCoords[] =  {-12.5,-3.5, -12.5,3.5, 12.5,3.5, 12.5,-3.5};


// extern GLBI_Texture texturePerso;
// extern GLBI_Texture textureFleur;

void initTexture(StandardMesh& mesh,  float coords[]);
void loadTexture(const char* filename,GLBI_Texture& texture);

void initTexturePerso();
void initTextureBlocs();
void initTextureMenu();
void initTextureBoutons();
void initTexturesHerbe();

void applyTexture(GLBI_Texture& texture, float x, float y, float taille);