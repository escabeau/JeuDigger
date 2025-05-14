#include "draw_scene.hpp"
#include <tuple>

GLBI_Engine myEngine;
static GLBI_Convex_2D_Shape carre {};
static float deplacement {0.2};


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
void initScene(){
	// INIT PERSONNAGE
	std::vector<float> const carreCoord {-0.5,-0.5, -0.5,0.5, 0.5,0.5, 0.5,-0.5}; //coordonnées des 4 coins
	carre.initShape(carreCoord);
	carre.changeNature(GL_TRIANGLE_FAN);
}
void movePersoHaut(){
	std::vector<float> prevCoord {carre.coord_pts};
	std::vector<float> newCoord{prevCoord[0],prevCoord[1]+deplacement, prevCoord[2],prevCoord[3]+deplacement, prevCoord[4],prevCoord[5]+deplacement, prevCoord[6],prevCoord[7]+deplacement};
	carre.initShape(newCoord);
}
void movePersoBas(){
	std::vector<float> prevCoord {carre.coord_pts};
	std::vector<float> newCoord{prevCoord[0],prevCoord[1]-deplacement, prevCoord[2],prevCoord[3]-deplacement, prevCoord[4],prevCoord[5]-deplacement, prevCoord[6],prevCoord[7]-deplacement};
	carre.initShape(newCoord);
}
void movePersoDroite(){
	std::vector<float> prevCoord {carre.coord_pts};
	std::vector<float> newCoord{prevCoord[0]+deplacement,prevCoord[1], prevCoord[2]+deplacement,prevCoord[3], prevCoord[4]+deplacement,prevCoord[5], prevCoord[6]+deplacement,prevCoord[7]};
	carre.initShape(newCoord);
}
void movePersoGauche(){
	std::vector<float> prevCoord {carre.coord_pts};
	std::vector<float> newCoord{prevCoord[0]-deplacement,prevCoord[1], prevCoord[2]-deplacement,prevCoord[3], prevCoord[4]-deplacement,prevCoord[5], prevCoord[6]-deplacement,prevCoord[7]};
	carre.initShape(newCoord);
}

void drawPerso(){
	myEngine.setFlatColor (0,1,0);
	carre.drawShape();
}


void drawScene()
{
	glPointSize(1.0);
	drawPerso();

}
