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
    loadTexture("./assets/images/homerD1.png", texturesPerso[2]);
    loadTexture("./assets/images/homerG1.png", texturesPerso[3]);
}

void initTextureMarge(){
    initTexture(perso,persoCoords);
    for(int i = 0; i < texturesMarge.size(); i++){
        texturesMarge[i].createTexture();
    }
    loadTexture("./assets/images/margeB1.png", texturesMarge[0]);
    loadTexture("./assets/images/margeH1.png", texturesMarge[1]);
    loadTexture("./assets/images/margeD1.png", texturesMarge[2]);
    loadTexture("./assets/images/margeG1.png", texturesMarge[3]);
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

    loadTexture("./assets/images/donut1.png", textureDonut);
    loadTexture("./assets/images/donut2.png", textureDonut2);
    
    loadTexture("./assets/images/mine.png", texturePiege);

    loadTexture("./assets/images/boum1.png", texturesBoum[0]);
    loadTexture("./assets/images/boum2.png", texturesBoum[1]);
    loadTexture("./assets/images/boum3.png", texturesBoum[2]);
    

    for(int i = 0; i < texturesFleur.size(); i++){
        texturesFleur[i].createTexture();
    }
    loadTexture("./assets/images/fleur1.png", texturesFleur[0]);
    loadTexture("./assets/images/fleur2.png", texturesFleur[1]);
    loadTexture("./assets/images/fleurecrase2.png", textureFleurEcrase);
}


void initTextureMenu(){
    initTexture(fondMenu,menuCoords);
    for(int i = 0; i < 3; i++){
        texturesMenu[i].createTexture();
    }
    loadTexture("./assets/images/ecranTitre.png", texturesMenu[0]);
    loadTexture("./assets/images/ecranVictoire.png", texturesMenu[1]);
    loadTexture("./assets/images/ecranDefaite.png", texturesMenu[2]);
}


void initTextureBoutons(){
    initTexture(bouton,boutonCoords);
    loadTexture("./assets/images/jouer.png", textureJouer);
    loadTexture("./assets/images/quitter.png", textureQuitter);
}

void initTexturesScore(){
    initTexture(scoreMesh,scoreCoords);
    for(int i = 0; i < 16; i++){
        texturesScore[i].createTexture();
    }
    loadTexture("./assets/images/0donut.png", texturesScore[0]);
    loadTexture("./assets/images/1donut.png", texturesScore[1]);
    loadTexture("./assets/images/2donut.png", texturesScore[2]);
    loadTexture("./assets/images/3donut.png", texturesScore[3]);
    loadTexture("./assets/images/4donut.png", texturesScore[4]);
    loadTexture("./assets/images/5donut.png", texturesScore[5]);
    loadTexture("./assets/images/6donut.png", texturesScore[6]);
    loadTexture("./assets/images/7donut.png", texturesScore[7]);
    loadTexture("./assets/images/8donut.png", texturesScore[8]);
    loadTexture("./assets/images/9donut.png", texturesScore[9]);
    loadTexture("./assets/images/10donut.png", texturesScore[10]);
    loadTexture("./assets/images/11donut.png", texturesScore[11]);
    loadTexture("./assets/images/12donut.png", texturesScore[12]);
    loadTexture("./assets/images/13donut.png", texturesScore[13]);
    loadTexture("./assets/images/14donut.png", texturesScore[14]);
    loadTexture("./assets/images/15donut.png", texturesScore[15]);
}

void initAllTextures(){
    initTexturePerso();
    initTextureMarge();
    initTextureBlocs();
    initTextureBoutons();
    initTextureMenu();
    initTexturesHerbe();
    initTexturesScore();
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