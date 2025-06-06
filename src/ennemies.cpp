#include "ennemies.hpp"
#include <queue>


std::vector<std::vector<Direction>> flowField;
std::vector<Ennemi> enemies;
std::vector<std::vector<bool>> visited;

void initEnnemy(int nbEnnemi){
    for(int i = 0; i < nbEnnemi; i++) {
        Vector3D randomPos = getRandomEmptyPosition();
        spawnEnemy(randomPos, 3.0f);
    }
}

void initFlowField() {
    flowField.resize(grilleMap.size(), std::vector<Direction>(grilleMap[0].size()));
    visited.resize(grilleMap.size(), std::vector<bool>(grilleMap[0].size()));
}

void generateFlowField() {
    // Réinitialiser les tableaux
    for(size_t i = 0; i < grilleMap.size(); i++) {
        for(size_t j = 0; j < grilleMap[0].size(); j++) {
            flowField[i][j] = {0.0f, 0.0f};
            visited[i][j] = false;
        }
    }
    
    // Position du joueur en indices de grille
    int playerCol = (posPerso.x + GL_VIEW_SIZE/2) / (GL_VIEW_SIZE/grilleMap[0].size());
    int playerRow = (posPerso.y + GL_VIEW_SIZE/2) / (GL_VIEW_SIZE/grilleMap.size());
    
    std::queue<std::pair<int, int>> toExplore;
    toExplore.push({playerRow, playerCol});
    visited[playerRow][playerCol] = true;
    
    const std::array<int,8> dx{-1, 1, 0, 0, -1, -1, 1, 1};
    const std::array<int,8> dy{0, 0, -1, 1, -1, 1, -1, 1};
    
    while(!toExplore.empty()) {
        int currentRow = toExplore.front().first;
        int currentCol = toExplore.front().second;
        toExplore.pop();
        
        // Pour chaque direction possible
        for(int i = 0; i < 8; i++) {
            int newRow = currentRow + dx[i];
            int newCol = currentCol + dy[i];
            
            if(newRow >= 0 && newRow < grilleMap.size() && 
               newCol >= 0 && newCol < grilleMap[0].size() && 
               !visited[newRow][newCol] && 
               grilleMap[newRow][newCol] != 1) {
                
                visited[newRow][newCol] = true;
                
                // Calculer le vecteur direction vers le joueur
                float dirX = currentCol - newCol;
                float dirY = currentRow - newRow;
                
                // Normaliser le vecteur
                float length = std::sqrt(dirX * dirX + dirY * dirY);
                if(length > 0) {
                    dirX /= length;
                    dirY /= length;
                }
                
                flowField[newRow][newCol] = {dirX, dirY};
                toExplore.push({newRow, newCol});
            }
        }
    }
}


static int directionTextureEnnemi{0};
void updateEnemies(double deltaTime) {
    generateFlowField();
    
    for(auto& enemy : enemies) {
        int col = (enemy.position.x + GL_VIEW_SIZE/2) / (GL_VIEW_SIZE/grilleMap[0].size());
        int row = (enemy.position.y + GL_VIEW_SIZE/2) / (GL_VIEW_SIZE/grilleMap.size());
        if(row >= 0 && row < grilleMap.size() && col >= 0 && col < grilleMap[0].size()) {
            Direction dir = flowField[row][col];
            if(abs(dir.dx) > abs(dir.dy)) {
                // Mouvement horizontal dominant
                directionTextureEnnemi = (dir.dx > 0) ? 2 : 3; // 2 pour droite, 3 pour gauche
            } else {
                // Mouvement vertical dominant
                directionTextureEnnemi = (dir.dy > 0) ? 1 : 0; // 1 pour haut, 0 pour bas
            }

            // Test du mouvement horizontal
            Vector3D newPos = enemy.position;
            float cellWidth = GL_VIEW_SIZE/grilleMap[0].size();
            float cellHeight = GL_VIEW_SIZE/grilleMap.size();
            
            // Mouvement horizontal
            newPos.x = enemy.position.x + dir.dx * enemy.speed * deltaTime;
            int testCol = ((newPos.x + GL_VIEW_SIZE/2) + (dir.dx > 0 ? 0.5f : -0.5f)) / cellWidth;
            
            if(testCol >= 0 && testCol < grilleMap[0].size() && 
               grilleMap[row][testCol] != 1) {
                enemy.position.x = newPos.x;
            }
            
            // Mouvement vertical
            newPos.y = enemy.position.y + dir.dy * enemy.speed * deltaTime;
            int testRow = ((newPos.y + GL_VIEW_SIZE/2) + (dir.dy > 0 ? 0.5f : -0.5f)) / cellHeight;
            
            if(testRow >= 0 && testRow < grilleMap.size() && 
               grilleMap[testRow][col] != 1) {
                enemy.position.y = newPos.y;
            }
        }
    }
}


std::array<GLBI_Texture, 4> texturesMarge;
void drawEnemies() {
    for(const auto& enemy : enemies) {
        myEngine.mvMatrixStack.pushMatrix();
        myEngine.mvMatrixStack.addTranslation(enemy.position);
        myEngine.updateMvMatrix();
        
        texturesMarge[directionTextureEnnemi].attachTexture();
        perso.draw();
        texturesMarge[directionTextureEnnemi].detachTexture();
        
        myEngine.mvMatrixStack.popMatrix();
        myEngine.updateMvMatrix();
    }
}

// Fonction pour ajouter un ennemi
void spawnEnemy(const Vector3D& position, float speed) {
    enemies.push_back({position, speed});
}

Vector3D getRandomEmptyPosition() {
    std::vector<std::pair<int, int>> emptyPositions;
    
    // Collecter toutes les positions vides
    for(size_t i = 0; i < grilleMap.size(); i++) {
        for(size_t j = 0; j < grilleMap[0].size(); j++) {
            if(grilleMap[i][j] == 0) { // bloc vide
                emptyPositions.push_back({i, j});
            }
        }
    }
    
    // Choisir une position aléatoire parmi les positions vides
    if(!emptyPositions.empty()) {
        int randomIndex = rand() % emptyPositions.size();
        auto [row, col] = emptyPositions[randomIndex];
        
        // Convertir les indices de la grille en coordonnées du monde
        float cellWidth = GL_VIEW_SIZE/grilleMap[0].size();
        float cellHeight = GL_VIEW_SIZE/grilleMap.size();
        
        float x = (col * cellWidth) - GL_VIEW_SIZE/2;
        float y = (row * cellHeight) - GL_VIEW_SIZE/2;
        
        return Vector3D(x, y, 0.0f);
    }
    
    // Position par défaut si aucune position vide n'est trouvée
    return Vector3D(0.0f, 0.0f, 0.0f);
}