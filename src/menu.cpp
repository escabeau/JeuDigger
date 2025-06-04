
#include "menu.hpp"


static bool isInMenu = true;
GLBI_Texture texturePlay;
GLBI_Texture textureQuit;
static Vector3D posPlay {0.0f, 0.5f, 0.0f};
static Vector3D posQuit {0.0f, -0.5f, 0.0f};

void initTextureMenu() {
    // texturePlay.loadImage("assets/textures/play.png");
    // textureQuit.loadImage("assets/textures/quit.png");
}

bool isMouseOverButton(GLFWwindow* window, Vector3D buttonPos) {
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    
    // Conversion des coordonnées de la souris en coordonnées OpenGL
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    float normalizedX = (2.0f * xpos) / width - 1.0f;
    float normalizedY = 1.0f - (2.0f * ypos) / height;
    
    // Vérification si la souris est sur le bouton
    return (normalizedX >= buttonPos.x - 0.2f && normalizedX <= buttonPos.x + 0.2f &&
            normalizedY >= buttonPos.y - 0.1f && normalizedY <= buttonPos.y + 0.1f);
}

void drawButton(Vector3D pos, GLBI_Texture& texture) {
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(pos);
    myEngine.mvMatrixStack.addHomothety(0.2f); // Taille du bouton
    myEngine.updateMvMatrix();
    
    texture.attachTexture();
    carre.draw();
    texture.detachTexture();
    
    myEngine.mvMatrixStack.popMatrix();
}

void drawMenu(GLFWwindow* window) {
    if (!isInMenu) return;
    
    drawButton(posPlay, texturePlay);
    drawButton(posQuit, textureQuit);
    
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        if (isMouseOverButton(window, posPlay)) {
            isInMenu = false; // Commencer le jeu
        }
        else if (isMouseOverButton(window, posQuit)) {
            glfwSetWindowShouldClose(window, true); // Quitter le jeu
        }
    }
}

bool isMenuActive() {
    return isInMenu;
}