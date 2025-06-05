#include "utils.hpp"
#include "draw_scene.hpp"
#include "draw_map.hpp"
#include "menu.hpp"
#include "texture.hpp"

/* Window size */
int winWidth{800};
int winHeight{800};

float winHaut;
float winBas;
float winDroite;
float winGauche;

enum class GameState {
    MENU,
    PLAYING,
    WIN,
    GAMEOVER,
};

//initialise l'état du jeu sur menu
GameState gameState{GameState::MENU};

using namespace glbasimac;

const float GL_VIEW_SIZE = 40.0f;

/* Minimal time wanted between two images */
static const double FRAMERATE_IN_SECONDS = 1. / 30.;
static float aspectRatio = 1.0f;

/* Error handling function */
void onError(int error, const char *description)
{
    std::cout << "GLFW Error (" << error << ") : " << description << std::endl;
}



void onWindowResized(GLFWwindow *, int width, int height)
{
    aspectRatio = width / (float)height;
    glViewport(0, 0, width, height);
	if( aspectRatio > 1.0)
	{
		myEngine.set2DProjection(-GL_VIEW_SIZE * aspectRatio/ 2.,
		GL_VIEW_SIZE * aspectRatio / 2. ,
		-GL_VIEW_SIZE / 2., GL_VIEW_SIZE / 2.);

        winGauche = (-GL_VIEW_SIZE * aspectRatio/ 2.)+0.5;
        winDroite = (GL_VIEW_SIZE * aspectRatio / 2.)-0.5;
        winHaut = (GL_VIEW_SIZE / 2.)-0.5;
        winBas = (-GL_VIEW_SIZE / 2.)+0.5;
	}
	else
	{
		myEngine.set2DProjection(-GL_VIEW_SIZE / 2., GL_VIEW_SIZE / 2.,
		-GL_VIEW_SIZE / (2. * aspectRatio),
		GL_VIEW_SIZE / (2. * aspectRatio));

        winGauche = (-GL_VIEW_SIZE / 2.)+0.5;
        winDroite = (GL_VIEW_SIZE / 2.)-0.5;
        winHaut = (GL_VIEW_SIZE / (2. * aspectRatio))-0.5;
        winBas = (-GL_VIEW_SIZE / (2. * aspectRatio))+0.5;
	}
};


void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods){
    // update keysState
    if (key >= 0 && key < keysState.size()) {
        keysState[key] = action == GLFW_PRESS || action == GLFW_REPEAT;
    }
}

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	float r = xpos/ winWidth; 
	float g = ypos / winHeight;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
        double xpos, ypos;
        //getting cursor position
        glfwGetCursorPos(window, &xpos, &ypos);
        if ((xpos>150 && xpos<650 )&& (ypos>330 && ypos >470) ){
            std::cout << "quitter le jeu" << std::endl;
            glfwSetWindowShouldClose(window, 1);
        }
        else if (xpos>150 && xpos<650 && ypos>200 && ypos >350 ){
            std::cout << "lancer le jeu" << std::endl;
            gameState = GameState::PLAYING;
            
        }
    }
}

int main()
{
    srand(time(NULL)); // pour le rand() dans initMap();


    // Initialize the library
    if (!glfwInit())
    {
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    /* Callback to a function if an error is rised by GLFW */
    glfwSetErrorCallback(onError);

    // Create a windowed mode window and its OpenGL context
    GLFWwindow *window = glfwCreateWindow(winWidth, winHeight, "OpenGLTemplate", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    // -- Callbacks --
    glfwSetFramebufferSizeCallback(window, onWindowResized);

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Intialize glad (loads the OpenGL functions)
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        return -1;
    }

    // Initialize Rendering Engine

    myEngine.mode2D = true;

    myEngine.initGL();
    //gltInit();
    myEngine.activateTexturing(true);

    {
    // RESIZE WINDOW SUR MAC
        int w, h;
        glfwGetFramebufferSize(window, &w, &h);
        onWindowResized(window, w, h);
    }

    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    
    // Initialize objects and textures
    initTexturePerso();
    initTextureBlocs();
    initTextureBoutons();
    initTextureMenu();
    initTexturesHerbe();
    initMap();

    initFlowField();
    initEnnemy(3);


    

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Get time (in second) at loop beginning */
        double startTime = glfwGetTime();
        /* Render here */
        glClearColor(1, 1, 1, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);
        myEngine.mvMatrixStack.loadIdentity();
        //drawScore();
        
        if (gameState==GameState::MENU){
            // std::cout << "en mode menu"<< std::endl;
            drawBoutons();
            drawMenu();
        }
        else if (gameState==GameState::PLAYING){
            // std::cout << "en mode playing"<< std::endl;
            drawPerso();
            drawEnemies();
            drawMap();
        }     
        
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();

        /* Elapsed time computation from loop begining */
        double elapsedTime = glfwGetTime() - startTime;
        /* If to few time is spend vs our wanted FPS, we wait */
        // while (elapsedTime < FRAMERATE_IN_SECONDS)
        // {
        //     glfwWaitEventsTimeout(FRAMERATE_IN_SECONDS - elapsedTime);
        //     elapsedTime = glfwGetTime() - startTime;
        // }
        update_player_position(elapsedTime);
        updateEnemies(elapsedTime);
        
    }

    gltTerminate();
    glfwTerminate();
    return 0;
}