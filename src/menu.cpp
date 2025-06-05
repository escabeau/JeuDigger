#include "menu.hpp"

GLBI_Texture textureMenu;
void drawMenu(){
    myEngine.setFlatColor(0, 0, 1);

    myEngine.mvMatrixStack.pushMatrix();
    textureMenu.attachTexture();
    fondMenu.draw();
    textureMenu.detachTexture();

    myEngine.mvMatrixStack.popMatrix();
}


GLBI_Texture textureJouer;
GLBI_Texture textureQuitter;
void drawBoutons(){
    myEngine.setFlatColor(0, 0, 1);

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