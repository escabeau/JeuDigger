#include "draw_scene.hpp"
#include <tuple>

GLBI_Engine myEngine;
// static GLBI_Convex_2D_Shape carre {};
static float deplacement {0.2};
static Vector3D posPerso {0.0f, 0.0f, 0.0f};

StandardMesh carre(4, GL_TRIANGLE_FAN);

// static	StandardMesh carre(4, GL_TRIANGLE_FAN);
// // Coordonnées des sommets (x, y)
// static float positions[] =  {-0.5,-0.5, -0.5,0.5, 0.5,0.5, 0.5,-0.5};
// // Coordonnées UV (u, v)
// static float uvs[] = {0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f};


// static GLBI_Texture texture;

GLBI_Texture texture;

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






void movePersoHaut(){
	posPerso.y+=deplacement;
}
void movePersoBas(){
	posPerso.y-=deplacement;
}
void movePersoDroite(){
	posPerso.x+=deplacement;
}
void movePersoGauche(){
	posPerso.x-=deplacement;
}

void drawPerso(){

	texture.attachTexture();

	myEngine.mvMatrixStack.addTranslation(posPerso);
	myEngine.updateMvMatrix();
	carre.draw();
	// texture.detachTexture();

}

