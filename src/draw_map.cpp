#include "draw_map.hpp"


StandardMesh tileShape(4, GL_TRIANGLE_FAN);
StandardMesh fondMenu(4, GL_TRIANGLE_FAN);
StandardMesh bouton(4, GL_TRIANGLE_FAN);
Vector3D posTile2{};

std::vector<std::vector<int>> grilleMap(25, std::vector<int>(25));
// FONCTION QUI REMPLIT UN TABLEAU 2 DIM
void fillGrille(std::vector<std::vector<int>> &grille, int pourcentPlein){
    int randInt;
    for(int i{0}; i<grille.size(); i++){
        for(int j{0}; j<grille[0].size(); j++){
            randInt = rand()%100;
            if(randInt < pourcentPlein){
                grille[i][j]=1;
            }
            else{
                grille[i][j]=0;
            }
        }
    }
}

std::vector<std::vector<int>> majGrille(std::vector<std::vector<int>> &grille){
    // création de la nouvelle grille améliorée : 
    std::vector<std::vector<int>> grilleMap(grille.size(), std::vector<int>(grille[0].size(), 0));

    // on parcourt la grille initiale :
    for(int i{0}; i<grille.size(); i++){
        for(int j{0}; j<grille[0].size(); j++){

            // le nombre de voisins pleins :
            int voisinsPleins{0};
            int randInt{};

            // on parcourt les voisins de la case, décalage i et j de -1 à 1 :
            for (int decal_i = -1; decal_i <= 1; ++decal_i) {
                for (int decal_j = -1; decal_j <= 1; ++decal_j) {

                    // coordonnées i, j des cases voisines : 
                    int voisin_i = i + decal_i;
                    int voisin_j = j + decal_j;

                    // on vérifie que la case voisine est dans la grille :
                    if (voisin_i >= 0 && voisin_i < grille.size() && voisin_j >= 0 && voisin_j < grille[0].size()){
                        voisinsPleins += grille[voisin_i][voisin_j];
                    }
                    else{
                        // si la case voisine n'est pas dans la grille, on considère qu'elle est pleine
                        //voisinsPleins++;
                    }
                }
            }
            // si la case a + de 4 voisins pleins alors elle devient pleine
            if(voisinsPleins >= 5){
                grilleMap[i][j]=1;
            }
            //sinon elle devient vide
            else{
                grilleMap[i][j]=0;
            }
        }
    }
    return grilleMap;
}

// FONCTION AJOUT DE CASE OBJET DANS NOTRE GRILLEMAP
void ajoutObj_piege(std::vector<std::vector<int>> &grille){
    for (int count{0}; count<15; count++){
        bool placed {false};
        while (!placed)
        {
            int x = rand()%25;
            int y = rand()%25;
            if (grille[x][y]!=2){
                grille[x][y]=2;
                placed = true;
            }
        }       
    }
    
    for(int i{0}; i<grille.size(); i++){
        for(int j{0}; j<grille[0].size(); j++){
            int randInt = rand()%100;
            if(randInt>96){
                grille[i][j]=3;
            }
        }
    }
}


std::vector<std::vector<int>> variationHerbe;
std::vector<std::vector<int>> variationFleur;
void initMap(){
    fillGrille(grilleMap, 48);
    for (int rep = 0; rep < 2; rep++) {
        grilleMap = majGrille(grilleMap);
    }
    ajoutObj_piege(grilleMap);

    variationHerbe.resize(grilleMap.size(), std::vector<int>(grilleMap[0].size()));
    variationFleur.resize(grilleMap.size(), std::vector<int>(grilleMap[0].size()));
    for(int i = 0; i < grilleMap.size(); i++) {
        for(int j = 0; j < grilleMap[0].size(); j++) {
            variationHerbe[i][j] = rand() % texturesHerbe.size();
            variationFleur[i][j] = rand() % texturesFleur.size();
        }
    }
}



std::array<GLBI_Texture, 7> texturesHerbe;
void drawHerbe(float x, float y, float taille, int variation) {
    applyTexture(texturesHerbe[variation], x, y, taille);
}

std::array<GLBI_Texture, 2> texturesFleur;
void drawFleur(float x, float y, float taille, int variation){
    applyTexture(texturesFleur[variation], x, y, taille);
}

GLBI_Texture textureDonut;
GLBI_Texture textureDonut2;
void drawObjet(float x, float y, float taille) {
    double currentTime = glfwGetTime();
    bool useSecondTexture = static_cast<int>(currentTime * 2) % 2 == 1;

    if (useSecondTexture) {
        applyTexture(textureDonut2, x, y, taille);
    } else {
        applyTexture(textureDonut, x, y, taille);
    }
}


GLBI_Texture texturePiege;
void drawPiege(float x, float y, float taille){
    applyTexture(texturePiege, x, y, taille);
}


GLBI_Texture textureFleurEcrase;
void drawFleurEcrase(float x, float y, float taille){
    applyTexture(textureFleurEcrase, x, y, taille);
}

// DESSIN DES CASES DE LA MAP
void drawMap() {
    int lignes = grilleMap.size();
    int cols = grilleMap[0].size();
    float tileSize = GL_VIEW_SIZE / cols;
    // HERBE SUR TOUTE LA MAP :
    for (int i = 0; i < lignes; ++i) {
        for (int j = 0; j < cols; ++j) {
            float x = -GL_VIEW_SIZE / 2 + j * tileSize + tileSize / 2;
            float y = -GL_VIEW_SIZE / 2 + i * tileSize + tileSize / 2;
            drawHerbe(x, y, tileSize, variationHerbe[i][j]);
        }
    }

    for (int i = 0; i < lignes; ++i) {
        for (int j = 0; j < cols; ++j) {
            float x = -GL_VIEW_SIZE / 2 + j * tileSize + tileSize / 2;
            float y = -GL_VIEW_SIZE / 2 + i * tileSize + tileSize / 2;

            // BLOC FLEUR
            if (grilleMap[i][j] == 1) {
                drawFleur(x, y, tileSize, variationFleur[i][j]);
            }
            // BLOC DONUT
            else if(grilleMap[i][j] == 2) {
                drawObjet(x, y, tileSize);
            }
            // BLOC MINE
            else if(grilleMap[i][j] == 3) {
                drawPiege(x, y, tileSize);
            }
            else if(grilleMap[i][j] == 4) {
                drawFleurEcrase(x, y, tileSize);
            }
        }
    }

    

    
}