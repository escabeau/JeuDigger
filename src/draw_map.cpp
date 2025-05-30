#include "draw_map.hpp"

std::vector<std::vector<int>> grilleMap(40, std::vector<int>(40));

StandardMesh tileShape(4, GL_TRIANGLE_FAN);
Vector3D posTile{};

GLBI_Texture textureFond;

// void initTile() {
//     float tileCoords[] =  {-0.5,-0.5, -0.5,0.5, 0.5,0.5, 0.5,-0.5};
//     tileShape.setNbElt(4);
//     tileShape.addOneBuffer(0, 2, tileCoords, "position", true);
//     tileShape.createVAO();
//     tileShape.changeType(GL_TRIANGLE_FAN);
// }

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
                        voisinsPleins++;
                        
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

void ajoutObj(std::vector<std::vector<int>> &grille){
    int randInt;
    for(int i{0}; i<grille.size(); i++){
        for(int j{0}; j<grille[0].size(); j++){
            randInt = rand()%100;
            if(randInt < 5){
                grille[i][j]=2;
            }
        }
    }
}

void initMap(){
    fillGrille(grilleMap, 50);
    for (int rep = 0; rep < 2; rep++) {
        grilleMap = majGrille(grilleMap);
    }
    ajoutObj(grilleMap);

    for(int i{0}; i<grilleMap.size(); i++){
        for(int j{0}; j<grilleMap[0].size(); j++){
            std::cout << grilleMap[i][j];
        }

    }
}

void drawTile(float x, float y, float taille){
    myEngine.setFlatColor(1, 1, 1); // couleur blanche

    myEngine.mvMatrixStack.pushMatrix();
    posTile = {x, y, 0.0f};
    myEngine.mvMatrixStack.addTranslation(posTile);
    myEngine.mvMatrixStack.addHomothety(taille);
    myEngine.updateMvMatrix();

    textureFond.attachTexture();
    tileShape.draw();
    textureFond.detachTexture();

    myEngine.mvMatrixStack.popMatrix();
}

void drawObjet(float x, float y, float taille){
    myEngine.setFlatColor(1, 0, 1);

    myEngine.mvMatrixStack.pushMatrix();
    posTile = {x, y, 0.0f};
    myEngine.mvMatrixStack.addTranslation(posTile);
    myEngine.mvMatrixStack.addHomothety(taille);
    myEngine.updateMvMatrix();

    // textureFond.attachTexture();
    tileShape.draw();
    // textureFond.detachTexture();

    myEngine.mvMatrixStack.popMatrix();
}

void drawMap() {
    int lignes = grilleMap.size();
    int cols = grilleMap[0].size();
    float tileSize = GL_VIEW_SIZE / cols;

    for (int i = 0; i < lignes; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (grilleMap[i][j] == 1) {
                float x = -GL_VIEW_SIZE / 2 + j * tileSize + tileSize / 2;
                float y = -GL_VIEW_SIZE / 2 + i * tileSize + tileSize / 2;
                drawTile(x, y, tileSize);
            }
            else if(grilleMap[i][j] == 2){
                float x = -GL_VIEW_SIZE / 2 + j * tileSize + tileSize / 2;
                float y = -GL_VIEW_SIZE / 2 + i * tileSize + tileSize / 2;
                drawObjet(x,y,tileSize);
            }
        }
    }
}
