#include "initOpenGL.hpp"


/* Window size */
int winWidth{800};
int winHeight{800};

float winHaut;
float winBas;
float winDroite;
float winGauche;

extern GameState gameState;

using namespace glbasimac;

const float GL_VIEW_SIZE = 40.0f;

/* Minimal time wanted between two images */
static const double FRAMERATE_IN_SECONDS = 1. / 30.;
static float aspectRatio = 1.0f;

/* Error handling function */
void onError(int error, const char *description){
    std::cout << "GLFW Error (" << error << ") : " << description << std::endl;
}

void onWindowResized(GLFWwindow *, int width, int height){
    aspectRatio = width / (float)height;
    glViewport(0, 0, width, height);
	if( aspectRatio > 1.0)
	{
		myEngine.set2DProjection(-GL_VIEW_SIZE * aspectRatio/ 2.,
		GL_VIEW_SIZE * aspectRatio / 2. ,
		-GL_VIEW_SIZE / 2., GL_VIEW_SIZE / 2.);

        winGauche = (-GL_VIEW_SIZE * aspectRatio/ 2.)+0.5;
        winDroite = (GL_VIEW_SIZE * aspectRatio / 2.)-0.5;
        winHaut = (GL_VIEW_SIZE / 2.)-1;
        winBas = (-GL_VIEW_SIZE / 2.)+1;
	}
	else
	{
		myEngine.set2DProjection(-GL_VIEW_SIZE / 2., GL_VIEW_SIZE / 2.,
		-GL_VIEW_SIZE / (2. * aspectRatio),
		GL_VIEW_SIZE / (2. * aspectRatio));

        winGauche = (-GL_VIEW_SIZE / 2.)+0.5;
        winDroite = (GL_VIEW_SIZE / 2.)-0.5;
        winHaut = (GL_VIEW_SIZE / (2. * aspectRatio))-1;
        winBas = (-GL_VIEW_SIZE / (2. * aspectRatio))+1;
	}
};


void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods){
    // update keysState
    if (key >= 0 && key < keysState.size()) {
        keysState[key] = action == GLFW_PRESS || action == GLFW_REPEAT;
    }
}


void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && gameState!=GameState::PLAYING){
        double xpos, ypos;
        //getting cursor position
        glfwGetCursorPos(window, &xpos, &ypos);
        if ((xpos>200 && xpos<600 )&& (ypos>545 && ypos <655) ){
            std::cout << "quitter le jeu" << std::endl;
            glfwSetWindowShouldClose(window, 1);
        }
        else if (xpos>200 && xpos<600 && ypos>340 && ypos <465){
            std::cout << "lancer le jeu" << std::endl;
            resetGame();
            gameState = GameState::PLAYING;
        }
    }
}