#define STB_IMAGE_IMPLEMENTATION
#include "texture.hpp"

// Initialisation des buffers et VAO du perso
void initTexturePerso(){
    carre.setNbElt(4);
    // Attrib location 0 pour position, 2 floats
    carre.addOneBuffer(0, 2, coordCoins, "position", true);
    // Attrib location 2 pour UV, 2 floats
    carre.addOneBuffer(2, 2, uvs, "uvs", true);
    carre.createVAO();
	carre.changeType(GL_TRIANGLE_FAN);

    loadTexture("./assets/images/homer1.png", texturePerso);
}

// Initialisation des buffers et VAO des blocs 
void initTextureBackground(){
    tileShape.setNbElt(4);
    // Attrib location 0 pour position, 2 floats
    tileShape.addOneBuffer(0, 2, tileCoords, "position", true);
    // Attrib location 2 pour UV, 2 floats
    tileShape.addOneBuffer(2, 2, uvs, "uvs", true);
    tileShape.createVAO();
	tileShape.changeType(GL_TRIANGLE_FAN);

    loadTexture("./assets/images/poisson.png", textureFond);
    loadTexture("./assets/images/donut.jpg", textureObjet);
    loadTexture("./assets/images/piege.jpg", texturePiege);
}

// Initialisation des buffers et VAO des blocs 
void initTextureMenu(){
    fondMenu.setNbElt(4);
    // Attrib location 0 pour position, 2 floats
    fondMenu.addOneBuffer(0, 2, menuCoords, "position", true);
    // Attrib location 2 pour UV, 2 floats
    fondMenu.addOneBuffer(2, 2, uvs, "uvs", true);
    fondMenu.createVAO();
	fondMenu.changeType(GL_TRIANGLE_FAN);

    loadTexture("./assets/images/ecranTitre.png", textureMenu);
}
// Initialisation des buffers et VAO des blocs 
void initTextureBoutons(){
    bouton.setNbElt(4);
    // Attrib location 0 pour position, 2 floats
    bouton.addOneBuffer(0, 2, boutonCoords, "position", true);
    // Attrib location 2 pour UV, 2 floats
    bouton.addOneBuffer(2, 2, uvs, "uvs", true);
    bouton.createVAO();
	bouton.changeType(GL_TRIANGLE_FAN);

    loadTexture("./assets/images/jouer.png", textureJouer);
    loadTexture("./assets/images/quitter.png", textureQuitter);
}

void initTexturesHerbe() {
    tileShape.setNbElt(4);
    // Attrib location 0 pour position, 2 floats
    tileShape.addOneBuffer(0, 2, tileCoords, "position", true);
    // Attrib location 2 pour UV, 2 floats
    tileShape.addOneBuffer(2, 2, uvs, "uvs", true);
    tileShape.createVAO();
	tileShape.changeType(GL_TRIANGLE_FAN);

    texturesHerbe.resize(7);
    for(int i = 0; i < 7; i++) {
        texturesHerbe[i].createTexture();
    }

    loadTexture("./assets/images/herbe1.png", texturesHerbe[0]);
    loadTexture("./assets/images/herbe2.png", texturesHerbe[1]);
    loadTexture("./assets/images/herbe3.png", texturesHerbe[2]);
    loadTexture("./assets/images/herbe4.png", texturesHerbe[3]);
    loadTexture("./assets/images/herbe5.png", texturesHerbe[4]);
    loadTexture("./assets/images/herbe6.png", texturesHerbe[5]);
    loadTexture("./assets/images/herbe7.png", texturesHerbe[6]);

}

// Fonction générique de chargement de texture à partir d'un fichier
void loadTexture(const char* filename, GLBI_Texture& texture){
	int width{};
	int height{};
	int nbChan{3};
	stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load(filename, &width, &height, &nbChan, 0);
    if(data){
		
		myEngine.activateTexturing(true);
        texture.createTexture();
		texture.attachTexture();
		texture.setParameters(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		texture.loadImage(width, height, nbChan, data);
		stbi_image_free(data);
        texture.detachTexture();
		
    }
	else{
		std::cout<<"image non chargée!!!"<< std::endl;
	}
}

Vector3D posTile{};
void applyTexture(GLBI_Texture& texture, float x, float y, float taille){
    myEngine.mvMatrixStack.pushMatrix();
    posTile = {x, y, 0.0f};
    myEngine.mvMatrixStack.addTranslation(posTile);
    myEngine.mvMatrixStack.addHomothety(taille);
    myEngine.updateMvMatrix();

    texture.attachTexture();
    tileShape.draw();
    texture.detachTexture();

    myEngine.mvMatrixStack.popMatrix();
}