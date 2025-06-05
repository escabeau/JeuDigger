#define STB_IMAGE_IMPLEMENTATION
#include "texture.hpp"


void initTexture(StandardMesh& mesh,  float coords[]){
    // Initialisation des buffers et VAO du mesh
    mesh.setNbElt(4);
    // Attrib location 0 pour position, 2 floats
    mesh.addOneBuffer(0, 2, coords, "position", true);
    // Attrib location 2 pour UV, 2 floats
    mesh.addOneBuffer(2, 2, uvs, "uvs", true);
    mesh.createVAO();
	mesh.changeType(GL_TRIANGLE_FAN);
}

// Fonction générique de chargement de texture à partir d'un fichier
void loadTexture(const char* filename, GLBI_Texture& texture){
	int width{};
	int height{};
	static int nbChan{4};
	stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load(filename, &width, &height, &nbChan, 4);
    if(data){
		myEngine.activateTexturing(true);
        texture.createTexture();
		texture.attachTexture();
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		texture.setParameters(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        texture.setParameters(GL_PIXEL_MODE_BIT, GL_RGBA);
		texture.loadImage(width, height, 4, data);
		stbi_image_free(data);
        texture.detachTexture();
    }
	else{
		std::cout<<"image non chargée!!!"<< std::endl;
	}
}


void initTexturePerso(){
    initTexture(perso,persoCoords);
    for(int i = 0; i < texturesPerso.size(); i++){
        texturesPerso[i].createTexture();
    }
    loadTexture("./assets/images/homerB1.png", texturesPerso[0]);
    loadTexture("./assets/images/homerH1.png", texturesPerso[1]);
    loadTexture("./assets/images/homerD.png", texturesPerso[2]);
    loadTexture("./assets/images/homerG1.png", texturesPerso[3]);
}

void initTexturesHerbe(){
    initTexture(tileShape,tileCoords);


    for(int i = 0; i < texturesHerbe.size(); i++){
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


void initTextureBlocs(){
    initTexture(tileShape,tileCoords);

    loadTexture("./assets/images/donut1.png", textureObjet);
    loadTexture("./assets/images/mine.png", texturePiege);
    loadTexture("./assets/images/fleurecrase2.png", textureFleurEcrase);

    for(int i = 0; i < texturesFleur.size(); i++){
        texturesFleur[i].createTexture();
    }
    loadTexture("./assets/images/fleur1.png", texturesFleur[0]);
    loadTexture("./assets/images/fleur2.png", texturesFleur[1]);
}


void initTextureMenu(){
    initTexture(fondMenu,menuCoords);
    loadTexture("./assets/images/ecranTitre.png", textureMenu);
}


void initTextureBoutons(){
    initTexture(bouton,boutonCoords);
    loadTexture("./assets/images/jouer.png", textureJouer);
    loadTexture("./assets/images/quitter.png", textureQuitter);
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