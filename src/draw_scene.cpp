#include "draw_scene.hpp"
#include "draw_map.hpp"
#include <tuple>
#include <queue>

GLBI_Engine myEngine;
static float deplacement {5};
static Vector3D posPerso {0.0f, 0.0f, 0.0f};

std::array<int, GLFW_KEY_LAST> keysState;

StandardMesh perso(4, GL_TRIANGLE_FAN);
std::array<GLBI_Texture, 4> texturesPerso;

int score = 0;

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

static int directionTexture = 0;
void update_player_position(double const deltaTime, GameState& gameState) {
    
	if (!handle_collision(posPerso, deltaTime)){
		if (keysState[GLFW_KEY_W]) {
			posPerso.y += deltaTime * deplacement;
            directionTexture = 1;
		}
		if (keysState[GLFW_KEY_S]) {
		   posPerso.y -= deltaTime * deplacement;
           directionTexture = 0;
		}
		if (keysState[GLFW_KEY_A]) {
		   posPerso.x -= deltaTime * deplacement;
           directionTexture = 3;
		}
		if (keysState[GLFW_KEY_D]) {
		   posPerso.x += deltaTime * deplacement;
           directionTexture = 2;
		}
	}
	detruireBloc();
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

void drawPerso(){
	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.addTranslation(posPerso);
	myEngine.updateMvMatrix();

	texturesPerso[directionTexture].attachTexture();
	perso.draw();
	texturesPerso[directionTexture].detachTexture();

	myEngine.mvMatrixStack.popMatrix();
	myEngine.updateMvMatrix();
}

bool ObjCollectes() {
    for(size_t i = 0; i < grilleMap.size(); i++) {
        for(size_t j = 0; j < grilleMap[0].size(); j++) {
            if(grilleMap[i][j] == 2) { // Si on trouve encore un objet
                return false;
            }
        }
    }
    return true;
}

void detruireBloc(){
    // conversion de la position du personnage en indices de la grille
    int col = (posPerso.x + GL_VIEW_SIZE/2) / (GL_VIEW_SIZE/grilleMap[0].size());
    int row = (posPerso.y + GL_VIEW_SIZE/2) / (GL_VIEW_SIZE/grilleMap.size());
    
    // Vérifier si les indices sont valides
    if (row >= 0 && row < grilleMap.size() && col >= 0 && col < grilleMap[0].size()){
        // si c'est un objet
        if (grilleMap[row][col] == 2) {
            score += 1; // Incrémenter le score
        }
        // detruire si bloc donut
        if (grilleMap[row][col]==2){
            grilleMap[row][col] = 0;
        }
		// changer en fleurEcrases si c'est un bloc plein
        if (grilleMap[row][col]==1){
            grilleMap[row][col] = 4;
            if(ObjCollectes()) {
                resetGame();
            }
        }
    }
}

void resetGame(){
    initMap();
    posPerso.x = 0;
    posPerso.y = 0;
    enemies.clear();
    score = 0;
    int nbEnnemis = 3; // ou le nombre que vous souhaitez
    initEnnemy(nbEnnemis);
}

void loosePiege(GameState& gameState){
    // conversion de la position du personnage en indices de la grille
    int col = (posPerso.x + GL_VIEW_SIZE/2) / (GL_VIEW_SIZE/grilleMap[0].size());
    int row = (posPerso.y + GL_VIEW_SIZE/2) / (GL_VIEW_SIZE/grilleMap.size());
    
    // Vérifier si les indices sont valides
    if (row >= 0 && row < grilleMap.size() && col >= 0 && col < grilleMap[0].size()){
		// détruire si c'est un bloc plein ou un objet
        if (grilleMap[row][col] == 3){
            gameState = GameState::GAMEOVER; 
        }
    }
}

void looseEnnemi(GameState& gameState) {
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

void updateEnemies(double deltaTime) {
    generateFlowField();
    
    for(auto& enemy : enemies) {
        int col = (enemy.position.x + GL_VIEW_SIZE/2) / (GL_VIEW_SIZE/grilleMap[0].size());
        int row = (enemy.position.y + GL_VIEW_SIZE/2) / (GL_VIEW_SIZE/grilleMap.size());
        
        if(row >= 0 && row < grilleMap.size() && col >= 0 && col < grilleMap[0].size()) {
            Direction dir = flowField[row][col];
            
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

void drawEnemies() {
    for(const auto& enemy : enemies) {
        myEngine.mvMatrixStack.pushMatrix();
        myEngine.mvMatrixStack.addTranslation(enemy.position);
        myEngine.updateMvMatrix();
        
        perso.draw();
        
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

void drawScore() {
    // Creating text
    GLTtext *text = gltCreateText();
    char scoreText[32];
    snprintf(scoreText, sizeof(scoreText), "Score: %d", score);
    gltSetText(text, scoreText);

    // Begin text drawing (this for instance calls glUseProgram)
    gltBeginDraw();

    // Draw any amount of text between begin and end
    gltColor(1.0f, 1.0f, 1.0f, 1.0f);
    gltDrawText2D(text, 20, 20, 2);

    // Finish drawing text
    gltEndDraw();
    gltDeleteText(text);
}