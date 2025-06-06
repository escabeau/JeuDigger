#include "menu.hpp"

// GLBI_Texture textureMenu;
std::array<GLBI_Texture,3> texturesMenu;
void drawMenu(int state){
    myEngine.mvMatrixStack.pushMatrix();
    texturesMenu[state].attachTexture();
    fondMenu.draw();
    texturesMenu[state].detachTexture();

    myEngine.mvMatrixStack.popMatrix();
}


GLBI_Texture textureJouer;
GLBI_Texture textureQuitter;
void drawBoutons(){
    myEngine.mvMatrixStack.pushMatrix();
    textureJouer.attachTexture();
    bouton.draw();
    textureJouer.detachTexture();
    
    Vector3D posBouton {0,-10,0};
    myEngine.mvMatrixStack.addTranslation(posBouton);
    myEngine.updateMvMatrix();

    textureQuitter.attachTexture();
    bouton.draw();
    textureQuitter.detachTexture();

    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();
}