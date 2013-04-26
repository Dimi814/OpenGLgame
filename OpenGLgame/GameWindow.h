//
//  GameWindow.h
//  OpenGLgame
//
//  Created by Dimitriy Dounaev on 12/04/13.
//  Copyright (c) 2013 Dimitriy Dounaev. All rights reserved.
//

#ifndef __OpenGLgame__GameWindow__
#define __OpenGLgame__GameWindow__

#include <iostream>
#include <GL/glfw.h>
#include "Sprite.h"
#include "TowerArray.h"
#include "math.h"

class GameWindow
{
private:
    
    bool _running;
    int _height;
    int _width;
    double _delta;
    GLuint _vertexBufferID;
    GLuint _textureBufferIDufo;
    GLuint _textureBufferIDghost;
    GLuint _textureBufferIDstar;
    Sprite _playerUFO;
    TowerArray *_ghostArray;
    TowerArray *_starArray;
    
    GLuint loadTexture(const char *fileName);
    void setupGL();
    void spawnGhost();
    void updateSprites(TowerArray *array);
    void drawSprites(TowerArray *array);
    void checkForOutOfBoundsSprites(TowerArray *array);
    bool checkForRectangleCollision(Rect a, Rect b);
        
public:
    
    void setRunning(bool running);
    bool getRunning();
    
    GameWindow();
    ~GameWindow();
    void draw();
    void update();
    void keyPressed(int key, int action);
    void mouseButtonPressed(int button, int action);
};

#endif /* defined(__OpenGLgame__GameWindow__) */
