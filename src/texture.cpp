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


void TexturePerso(int width, int height, int nbChan){
    unsigned char *data = stbi_load("/src/homer.png", &width, &height, &nbChan, 0);
    if(!data){
        std::cout<<"image non chargée!!!"<< std::endl;
    }
    
    

    GLBI_Texture texture;
    texture.createTexture();
    texture.attachTexture();
    texture.setParameters(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    texture.loadImage(width, height, nbChan, data);
    
    stbi_image_free(data);
    texture.detachTexture();
}
