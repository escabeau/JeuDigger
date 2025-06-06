#include "utils.hpp"
#include "initOpenGL.hpp"
#include "draw_scene.hpp"
#include "draw_map.hpp"
#include "menu.hpp"
#include "texture.hpp"
#include "ennemies.hpp"


//initialise l'état du jeu sur menu
GameState gameState{GameState::MENU};

int main()
{
    srand(time(NULL)); // pour le rand() dans initMap();

    // Initialize the library
    if (!glfwInit()){
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
    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

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

    // Initialize objects, textures and ennemies
    initAllTextures();
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
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        myEngine.mvMatrixStack.loadIdentity();
        
        switch (gameState)
        {
        case GameState::MENU :
            drawMenu(0);
            drawBoutons();
            break;
        
        case GameState::PLAYING :
            drawMap();
            if (explodingMine.isExploding) {
                float tileSize = GL_VIEW_SIZE / grilleMap[0].size();
                float x = -GL_VIEW_SIZE/2 + explodingMine.col * tileSize + tileSize/2;
                float y = -GL_VIEW_SIZE/2 + explodingMine.row * tileSize + tileSize/2;
                drawBoum(x, y, tileSize);
            }
            drawPerso();
            drawEnemies();
            drawScore();
            break;
        
        case GameState::WIN :
            drawMenu(1);
            drawBoutons();
            break;
        
        case GameState::GAMEOVER :
            drawMenu(2);
            drawBoutons();
            break;
        
        default:
            break;
        }
       
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();

        /* Elapsed time computation from loop begining */
        double elapsedTime = glfwGetTime() - startTime;

        update_player_position(elapsedTime,gameState);
        updateEnemies(elapsedTime);
        
    }

    glfwTerminate();
    return 0;
}