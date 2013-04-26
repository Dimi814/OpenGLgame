#include <GL/glfw.h>
#include "GameWindow.h"

GameWindow *gameWindow;

void GLFWCALL keyPressed(int key,int action)
{
    gameWindow->keyPressed(key, action);
}

void GLFWCALL mouseButtonPressed(int button, int action)
{
    gameWindow->mouseButtonPressed(button, action);
}

int main(int argc, char **argv)
{
    glfwInit();
    glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_TRUE);
    glfwOpenWindow(800*16/9, 800, 8, 8, 8, 8, 0, 0, GLFW_WINDOW);
    glfwSetWindowTitle("OpenGL game");
    glfwEnable(GLFW_KEY_REPEAT);
    glfwSetKeyCallback(keyPressed);
    glfwSetMouseButtonCallback(mouseButtonPressed);
    
    gameWindow = new GameWindow();
    
    double currentTime = 0.0f;
    
    while (gameWindow->getRunning()) {
        
        gameWindow->draw();
        
        currentTime += (glfwGetTime()-currentTime);
        
        if (currentTime >= 0.01f) {
            currentTime = 0.0f;
            gameWindow->update();
        }
        
        gameWindow->setRunning(glfwGetWindowParam(GLFW_OPENED)&&!glfwGetKey(GLFW_KEY_ESC));
    }
    
    delete gameWindow;
    glfwTerminate();
    
}

