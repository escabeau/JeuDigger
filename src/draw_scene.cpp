#include "draw_scene.hpp"
#include <tuple>

GLBI_Engine myEngine;
static float deplacement {5};
Vector3D posPerso {0.0f, 0.0f, 0.0f};
Vector3D posIA {10.0f, 10.0f, 0.0f};
Graph::WeightedGraph grapheEnnemis;

std::array<int, GLFW_KEY_LAST> keysState;


std::unordered_map<Graph::Position, Graph::Position, Graph::PositionHash> flow_field {};

StandardMesh carre(4, GL_TRIANGLE_FAN);


GLBI_Texture texturePerso;

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


void update_player_position(double const deltaTime) {
	if (!handle_collision(posPerso, deltaTime)){
		if (keysState[GLFW_KEY_W]) {
			posPerso.y += deltaTime * deplacement;
		}
		if (keysState[GLFW_KEY_S]) {
			posPerso.y -= deltaTime * deplacement;
		}
		if (keysState[GLFW_KEY_A]) {
			posPerso.x -= deltaTime * deplacement;
		}
		if (keysState[GLFW_KEY_D]) {
			posPerso.x += deltaTime * deplacement;
		}
	}
	detruireBloc();
}

void update_IA_position(double const deltaTime) {
	float xIA {(posIA.x + GL_VIEW_SIZE/2) / (GL_VIEW_SIZE/grilleMap[0].size())};
    float yIA {(posIA.y + GL_VIEW_SIZE/2) / (GL_VIEW_SIZE/grilleMap.size())};

	Graph::Position posiIA {static_cast<int>(xIA),static_cast<int>(yIA)};
	Graph::Position direction{};
	if (flow_field.contains(posiIA)) {
		direction = flow_field[posiIA];
		direction.x -= xIA; 
		direction.y -= yIA; 
		std::cout << direction.x << ", " << direction.y << std::endl;
		if (direction.x==0 && direction.y==1) {
			std::cout << "go up"<< std::endl;
			posIA.y += deltaTime * deplacement;
		}
		else if (direction.x==0 && direction.y==-1) {
			std::cout << "go up"<< std::endl;
			posIA.y -= deltaTime * deplacement;
		}
		else if (direction.x==-1 && direction.y==0) {
			std::cout << "go up"<< std::endl;
			posIA.x -= deltaTime * deplacement;
		}
		else if (direction.x==1 && direction.y==0) {
			std::cout << "go up"<< std::endl;
			posIA.x += deltaTime * deplacement;
		}
	}
}

void updateGraphe(Vector3D posPerso){
	Graph::Position posHomer {static_cast<int>(posPerso.x),static_cast<int>(posPerso.y)};
	flow_field = Graph::updateFlowField(grapheEnnemis,posHomer);
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

	texturePerso.attachTexture();
	carre.draw();
	texturePerso.detachTexture();

	myEngine.mvMatrixStack.popMatrix();
	myEngine.updateMvMatrix();
}

void drawIA(){

	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.addTranslation(posIA);
	myEngine.updateMvMatrix();

	texturePerso.attachTexture();
	carre.draw();
	texturePerso.detachTexture();

	myEngine.mvMatrixStack.popMatrix();
	myEngine.updateMvMatrix();
}


void detruireBloc(){
    // conversion de la position du personnage en indices de la grille
    int col = (posPerso.x + GL_VIEW_SIZE/2) / (GL_VIEW_SIZE/grilleMap[0].size());
    int row = (posPerso.y + GL_VIEW_SIZE/2) / (GL_VIEW_SIZE/grilleMap.size());
    
    // Vérifier si les indices sont valides
    if (row >= 0 && row < grilleMap.size() && col >= 0 && col < grilleMap[0].size()){
		// détruire si c'est un bloc plein ou un objet
        if (grilleMap[row][col] == 1 || grilleMap[row][col]==2){
            grilleMap[row][col] = 0;
			updateGraphe(posPerso);
        }
    }
}