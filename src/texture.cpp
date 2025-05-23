#define STB_IMAGE_IMPLEMENTATION
#include "texture.hpp"

// Basic usage (see HDR discussion below for HDR usage):
//    int x,y,n;
//    unsigned char *data = stbi_load(filename, &x, &y, &n, 0);
//    // ... process data if not NULL ...
//    // ... x = width, y = height, n = # 8-bit components per pixel ...
//    // ... replace '0' with '1'..'4' to force that many components per pixel
//    // ... but 'n' will always be the number that it would have been if you said 0
//    stbi_image_free(data)

void initTexture(){
    carre.setNbElt(4);
    // Attrib location 0 pour position, 2 floats
    carre.addOneBuffer(0, 2, coordCoins, "position", true);
    // Attrib location 2 pour UV, 2 floats
    carre.addOneBuffer(2, 2, uvs, "uvs", true);
    carre.createVAO();
	carre.changeType(GL_TRIANGLE_FAN);
}

void TexturePerso(){
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
