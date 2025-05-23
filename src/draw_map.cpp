#include "draw_map.hpp"

std::vector<std::vector<int>> grilleMap(80, std::vector<int>(80));

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
                        voisinsPleins += 1;
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

void initMap(){
    fillGrille(grilleMap, 45);

    for (int rep {0}; rep < 4; rep++){
        grilleMap = majGrille(grilleMap);
    }
    // for(int i{0}; i<grilleMap.size(); i++){
    //     for(int j{0}; j<grilleMap[0].size(); j++){
    //         std::cout<<grilleMap[i][j];
    //     }
    // }


}

void drawTile(int x, int y, float taille){
    GLBI_Convex_2D_Shape tile {};
    // coordonnées des 4 coins :
    std::vector<float> coordBasGauche{x-taille, y-taille};
    std::vector<float> coordHautGauche{x-taille, y+taille};
    std::vector<float> coordHautDroit{x+taille, y+taille};
    std::vector<float> coordBasDroit{x+taille, y-taille};

    std::vector<float> const tileCoord {coordBasGauche[0],coordBasGauche[1],
                                        coordHautGauche[0],coordHautGauche[1],
                                        coordHautDroit[0],coordHautDroit[1],
                                        coordBasDroit[0],coordBasDroit[1]};
	
    glPointSize(1.0);
	myEngine.setFlatColor (1,1,1);
    tile.initShape(tileCoord);
	tile.changeNature(GL_TRIANGLE_FAN);

	tile.drawShape();
}


void drawMap() {
    int lignes = grilleMap.size();
    int cols = grilleMap[0].size();

    // on ajuste la taille du carreau en fonction de la taille de la grilleMap et la taille de la fenêtre virtuelle :
    float tileSize = GL_VIEW_SIZE / cols;

    for (int i = 0; i < lignes; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (grilleMap[i][j] == 1) {
                // conversion des coordonnées en coordonnées OpenGL :
                float x = -GL_VIEW_SIZE / 2 + j * tileSize + tileSize / 2;
                float y = -GL_VIEW_SIZE / 2 + i * tileSize + tileSize / 2;

                drawTile(x, y, tileSize);
            }
        }
    }
}

