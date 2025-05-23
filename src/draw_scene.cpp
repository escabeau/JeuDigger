#include "draw_scene.hpp"
#include <tuple>

GLBI_Engine myEngine;
// static GLBI_Convex_2D_Shape carre {};
static	StandardMesh carre(4, GL_TRIANGLE_FAN);
static float deplacement {0.2};
static Vector3D posPerso {0.0f, 0.0f, 0.0f};


// Coordonnées des sommets (x, y)
static float positions[] =  {-0.5,-0.5, -0.5,0.5, 0.5,0.5, 0.5,-0.5};
// Coordonnées UV (u, v)
static float uvs[] = {0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f};


static GLBI_Texture texture;


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



void initPerso(){
    carre.setNbElt(4);
    // Attrib location 0 pour position, 2 floats
    carre.addOneBuffer(0, 2, positions, "position", true);
    // Attrib location 2 pour UV, 2 floats
    carre.addOneBuffer(2, 2, uvs, "uvs", true);
    carre.createVAO();

	// INIT PERSONNAGE
	carre.changeType(GL_TRIANGLE_FAN);

	// TEXTURE 
	int width{};
	int height{};
	int nbChan{3};
	stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load("./assets/images/homer1.png", &width, &height, &nbChan, 0);
    if(data){
		
		myEngine.activateTexturing(true);
        texture.createTexture();
		texture.attachTexture();
		texture.setParameters(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		texture.loadImage(width, height, nbChan, data);
    }
	else{
		std::cout<<"image non chargée!!!"<< std::endl;
	}
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

	// myEngine.setFlatColor (0,1,0);
	texture.attachTexture();

	myEngine.mvMatrixStack.addTranslation(posPerso);
	myEngine.updateMvMatrix();
	carre.draw();
	// texture.detachTexture();

}

