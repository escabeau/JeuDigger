#include "draw_scene.hpp"
#include "draw_map.hpp"
#include <tuple>
#include <queue>

GLBI_Engine myEngine;
static float deplacement {5};
Vector3D posPerso {0.0f, 0.0f, 0.0f};

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

    // collision fenetre
	if(next_position.y > winHaut || next_position.y< winBas || next_position.x > winDroite || next_position.x < winGauche){
		return true;
	}

    int col = (next_position.x + GL_VIEW_SIZE/2) / (GL_VIEW_SIZE/grilleMap[0].size());
    int row = (next_position.y + GL_VIEW_SIZE/2) / (GL_VIEW_SIZE/grilleMap.size());
    // collision rochers
    if (row >= 0 && row < grilleMap.size() && col >= 0 && col < grilleMap[0].size()) {
        if (grilleMap[row][col] == 5) {
            return true;
        }
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
            score += 1; // Incrémenter le score
            std::cout<< "oh un donut"<< score << std::endl;
            grilleMap[row][col] = 0;
            if(score == 15) {
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
    const float taille = 1.2f; // Ajustez selon la taille de vos sprites
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