#include "draw_scene.hpp"
#include <tuple>

GLBI_Engine myEngine;
static float deplacement {10};
static Vector3D posPerso {0.0f, 0.0f, 0.0f};

std::array<int, GLFW_KEY_LAST> keysState;

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

