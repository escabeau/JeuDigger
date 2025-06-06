#include "draw_scene.hpp"
#include "draw_map.hpp"
#include <tuple>
#include <queue>

GLBI_Engine myEngine;
static float deplacement {5};
static Vector3D posPerso {0.0f, 0.0f, 0.0f};

std::array<int, GLFW_KEY_LAST> keysState;

StandardMesh perso(4, GL_TRIANGLE_FAN);


int score {0};

float degToRad(float const &angle)
{
	return (angle * M_PI / 2) / 90;
}

std::tuple<float, float, float> colorConvertor(int const &r, int const &g, int const &b)
{
	return {static_cast<float>(r) / 255.0f,
			static_cast<float>(g) / 255.0f,
			static_cast<float>(b) / 255.0f};
}

std::tuple<float, float, float> colorConvertor(int const &color)
{
	return {static_cast<float>(color) / 255.0f,
			static_cast<float>(color) / 255.0f,
			static_cast<float>(color) / 255.0f};
}

static int directionTexturePerso = 0;
static int directionTexture = 0;
void update_player_position(double const deltaTime, GameState& gameState){
    if (explodingMine.isExploding) {
        // Si la mine explose, on ne met pas à jour la position du joueur
        loosePiege(gameState);
        return;
    }
	if (!handle_collision(posPerso, deltaTime)){
		if (keysState[GLFW_KEY_W]) {
			posPerso.y += deltaTime * deplacement;
            directionTexturePerso = 1;
		}
		if (keysState[GLFW_KEY_S]) {
		   posPerso.y -= deltaTime * deplacement;
           directionTexturePerso = 0;
		}
		if (keysState[GLFW_KEY_A]) {
		   posPerso.x -= deltaTime * deplacement;
           directionTexturePerso = 3;
		}
		if (keysState[GLFW_KEY_D]) {
		   posPerso.x += deltaTime * deplacement;
           directionTexturePerso = 2;
		}
	}
	detruireBloc(gameState);
    loosePiege(gameState);
    looseEnnemi(gameState);
}

bool handle_collision(Vector3D posPerso, double const deltaTime){
	Vector3D next_position = posPerso;
	if (keysState[GLFW_KEY_W]) {
    	next_position.y += deltaTime * deplacement;
    }
    if (keysState[GLFW_KEY_S]) {
       next_position.y -= deltaTime * deplacement;
    }
    if (keysState[GLFW_KEY_A]) {
       next_position.x -= deltaTime * deplacement;
    }
    if (keysState[GLFW_KEY_D]) {
       next_position.x += deltaTime * deplacement;
    }

	if(next_position.y > winHaut || next_position.y< winBas || next_position.x > winDroite || next_position.x < winGauche){
		return true;
	}
	return false;
}

std::array<GLBI_Texture, 4> texturesPerso;
void drawPerso(){
	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.addTranslation(posPerso);
	myEngine.updateMvMatrix();

	texturesPerso[directionTexturePerso].attachTexture();
	perso.draw();
	texturesPerso[directionTexturePerso].detachTexture();

	myEngine.mvMatrixStack.popMatrix();
	myEngine.updateMvMatrix();
}



void detruireBloc(GameState& gameState){
    // conversion de la position du personnage en indices de la grille
    int col = (posPerso.x + GL_VIEW_SIZE/2) / (GL_VIEW_SIZE/grilleMap[0].size());
    int row = (posPerso.y + GL_VIEW_SIZE/2) / (GL_VIEW_SIZE/grilleMap.size());
    
    // Vérifier si les indices sont valides
    if (row >= 0 && row < grilleMap.size() && col >= 0 && col < grilleMap[0].size()){
        // detruire si bloc donut
        if (grilleMap[row][col]==2){
            std::cout<< "oh un donut"<< score << std::endl;
            score += 1; // Incrémenter le score
            grilleMap[row][col] = 0;
            if(score > 13) {
                gameState=GameState::WIN;
            }
        }
		// changer en fleurEcrases si c'est un bloc plein
        if (grilleMap[row][col]==1){
            grilleMap[row][col] = 4;
        }
    }
}

void resetGame(){
    initMap();
    posPerso.x = 0;
    posPerso.y = 0;
    enemies.clear();
    score = 0;
    explodingMine = {false, -1, -1, 0.0, 0};
    int nbEnnemis = 3; // ou le nombre que vous souhaitez
    initEnnemy(nbEnnemis);
}

std::array<GLBI_Texture, 3> texturesBoum;
Boum explodingMine = {false, -1, -1, 0.0, 0};
void loosePiege(GameState& gameState) {
    int col = (posPerso.x + GL_VIEW_SIZE/2) / (GL_VIEW_SIZE/grilleMap[0].size());
    int row = (posPerso.y + GL_VIEW_SIZE/2) / (GL_VIEW_SIZE/grilleMap.size());
    
    if (row >= 0 && row < grilleMap.size() && col >= 0 && col < grilleMap[0].size()) {
        if (grilleMap[row][col] == 3) {
            if (!explodingMine.isExploding) {
                explodingMine = {true, row, col, glfwGetTime(), 0};
            } else {
                double currentTime = glfwGetTime();
                double elapsedTime = currentTime - explodingMine.startTime;
                
                if (elapsedTime >= 2.0) { // 2 secondes d'animation
                    gameState = GameState::GAMEOVER;
                } else {
                    // Mettre à jour la frame de l'animation (3 frames sur 2 secondes)
                    explodingMine.frame = static_cast<int>((elapsedTime / 2.0) * 3);
                    if (explodingMine.frame >= 3) explodingMine.frame = 2;
                }
            }
        }
    }
}

bool explosionActive = false;
Vector3D explosionPos;
double explosionStartTime = 0.0;
const double explosionDuration = 1.0;

void drawBoum(float x, float y, float taille) {
    if (!explodingMine.isExploding) return;

    applyTexture(texturesBoum[explodingMine.frame], x, y, taille);
}


void looseEnnemi(GameState& gameState){
    const float taille = 0.5f; // Ajustez selon la taille de vos sprites
    for(const auto& enemy : enemies) {
        // Calculer la distance entre le joueur et l'ennemi
        float dx = posPerso.x - enemy.position.x;
        float dy = posPerso.y - enemy.position.y;
        float distance = std::sqrt(dx*dx + dy*dy);
        
        // Si collision
        if(distance < taille) {
            gameState = GameState::GAMEOVER; 
            return;
        }
    }
}

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
    
    const int dx[] = {-1, 1, 0, 0, -1, -1, 1, 1};
    const int dy[] = {0, 0, -1, 1, -1, 1, -1, 1};
    
    while(!toExplore.empty()) {
        auto [currentRow, currentCol] = toExplore.front();
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


static int directionTextureEnnemi = 0;
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

StandardMesh scoreMesh(4, GL_TRIANGLE_FAN);
std::array<GLBI_Texture, 16> texturesScore;
void drawScore() {
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation({15,16,0});
    myEngine.updateMvMatrix();
    
    texturesScore[score].attachTexture();
    scoreMesh.draw();
    texturesScore[score].detachTexture();
    
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();
    
}