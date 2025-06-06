#pragma once

#include "tools/stb_image.h"
#include "glbasimac/glbi_texture.hpp"
#include "utils.hpp"


using namespace glbasimac;

extern StandardMesh perso;
extern StandardMesh tileShape;
extern StandardMesh fondMenu;
extern StandardMesh bouton;
extern StandardMesh scoreMesh;

extern std::array<GLBI_Texture, 4> texturesPerso;
extern std::array<GLBI_Texture, 4> texturesMarge;
extern GLBI_Texture textureDonut;
extern GLBI_Texture textureDonut2;
extern GLBI_Texture texturePiege;
extern std::array<GLBI_Texture, 3> texturesBoum;
extern GLBI_Texture textureFleurEcrase;

extern std::array<GLBI_Texture, 7> texturesHerbe;
extern std::vector<std::vector<int>> variationHerbe;

extern std::array<GLBI_Texture, 2> texturesFleur;
extern std::vector<std::vector<int>> variationFleur;

extern std::array<GLBI_Texture, 3> texturesMenu;
extern GLBI_Texture textureJouer;
extern GLBI_Texture textureQuitter;

extern std::array<GLBI_Texture, 16> texturesScore;




// Coordonnées UV (u, v)
static float uvs[] = {0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f};

// Coordonnées des sommets (x, y) du Perso
static float persoCoords[] =  {-0.5,-1, -0.5,1, 0.5,1, 0.5,-1};

// Coordonnées des sommets (x, y) des cubes de la map
static float tileCoords[] =  {-0.5,-0.5, -0.5,0.5, 0.5,0.5, 0.5,-0.5};

// Coordonnées des sommets (x, y) du menu
static float menuCoords[] =  {-20,-20, -20,20, 20,20, 20,-20};

// Coordonnées des sommets (x, y) des boutons du menu
static float boutonCoords[] =  {-7.89,-2.34, -7.89,2.34, 7.89,2.34, 7.89,-2.34};

// Coordonnées des sommets (x, y) des boutons du menu
static float scoreCoords[] =  {-3.28,-1.95, -3.28,1.95, 3.28,1.95, 3.28,-1.95};


// extern GLBI_Texture texturePerso;
// extern GLBI_Texture textureFleur;

void initTexture(StandardMesh& mesh,  float coords[]);
void loadTexture(const char* filename,GLBI_Texture& texture);

void initTexturePerso();
void initTextureMarge();
void initTextureBlocs();
void initTextureMenu();
void initTextureBoutons();
void initTexturesHerbe();
void initTexturesScore();

void applyTexture(GLBI_Texture& texture, float x, float y, float taille);