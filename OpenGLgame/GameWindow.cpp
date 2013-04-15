//
//  GameWindow.cpp
//  OpenGLgame
//
//  Created by Dimitriy Dounaev on 12/04/13.
//  Copyright (c) 2013 Dimitriy Dounaev. All rights reserved.
//

#include "GameWindow.h"

typedef struct {
    
    GLfloat positionCoordinates[3];
    GLfloat textureCoordinates[2];
    
} VertexData;


VertexData vertices[] = {
    {{0.0f, 0.0f, 0.0f},{0.0f,0.0f}},
    {{GAME_SPRITE_SIZE, 0.0f, 0.0f},{1.0f,0.0f}},
    {{GAME_SPRITE_SIZE, GAME_SPRITE_SIZE, 0.0f},{1.0f,1.0f}},
    {{0.0f, GAME_SPRITE_SIZE, 0.0f},{0.0f,1.0f}}
};

void GameWindow::setRunning(bool running)
{
    _running = running;
}

bool GameWindow::getRunning()
{
    return _running;
}

GLuint GameWindow::loadTexture(const char *fileName)
{
    GLFWimage ufoImage;
    GLuint textureBufferID;
    
    if(glfwReadImage(fileName, &ufoImage, NULL)) {
        std::cout << "fsfe" << std::endl;
    }
    glGenTextures(1, &textureBufferID);
    glBindTexture(GL_TEXTURE_2D, textureBufferID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, ufoImage.Width, ufoImage.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, ufoImage.Data);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    
    glfwFreeImage(&ufoImage);
    
    return textureBufferID;
}

void GameWindow::setupGL()
{
    glClearColor(0.9f, 0.9f, 1.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glViewport(0, 0, _width, _height);
    gluOrtho2D(0, _width, 0, _height);
    glMatrixMode(GL_MODELVIEW);
    
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glGenBuffers(1, &_vertexBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, sizeof(VertexData),(GLvoid *) offsetof(VertexData, positionCoordinates));
    
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glTexCoordPointer(2, GL_FLOAT, sizeof(VertexData), (GLvoid *)offsetof(VertexData, textureCoordinates));

}

GameWindow::GameWindow(): _running(true), _width(800*16/9), _height(800), _playerUFO(0)
{
    setupGL();
    
    _ghostArray = new TowerArray();
    _starArray = new TowerArray();
    
    _textureBufferIDghost = loadTexture("/Users/dimdon23/GHOST.tga");
    _textureBufferIDufo = loadTexture("/Users/dimdon23/UFO.tga");
    _textureBufferIDstar = loadTexture("/Users/dimdon23/star.tga");

    _playerUFO.setTextureBufferID(_textureBufferIDufo);
    Vector2 position;
    position.x = _width/2;
    position.y = _height/2;
    _playerUFO.setPosition(position);
    
    spawnGhost();
}

GameWindow::~GameWindow()
{
    delete _ghostArray;
    delete _starArray;
}

void GameWindow::keyPressed(int key, int action)
{
 //spawnGhost();
}

void GameWindow::mouseButtonPressed(int button, int action)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        int x;
        int y;
        glfwGetMousePos(&x, &y);
        y = 800-y;
        
        //std::cout << x << " " << y << std::endl;
        
        Sprite *newStar = new Sprite(_textureBufferIDstar);
        newStar->setPosition(_playerUFO.getPosition());
        Vector2 velocity;
        velocity.x = -((_playerUFO.getPosition()).x - x);
        velocity.y = -((_playerUFO.getPosition()).y - y);
        
        float length = sqrtf((velocity.x*velocity.x) + (velocity.y*velocity.y));
        velocity.x = (velocity.x / length)*8;
        velocity.y = (velocity.y / length)*8;
        
        newStar->setMoveVelocity(velocity);
        _starArray->addSprite(newStar);
    }
}

void GameWindow::drawSprites(TowerArray *array)
{
    for (int iii = 0; iii < array->getCount(); iii++) {
        if (array->getSpriteAt(iii) != NULL) {
            (array->getSpriteAt(iii))->drawSprite();
        }
    }
}

void GameWindow::draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    glLoadIdentity();
   
    _playerUFO.drawSprite();
    drawSprites(_ghostArray);
    drawSprites(_starArray);
    
    glfwSwapBuffers();
}

#pragma mark - Game Logic


void GameWindow::spawnGhost()
{
    Sprite *newGhost = new Sprite(_textureBufferIDghost);
    int randomSide = arc4random()%4;
    if (randomSide == 0) {
        int maxY = _height - GAME_SPRITE_SIZE/2;
        int minY = GAME_SPRITE_SIZE/2;
        int range = maxY - minY;
        int spawnLocationY = (arc4random()%range) + minY;
        Vector2 vector;
        vector.x = -GAME_SPRITE_SIZE;
        vector.y = spawnLocationY;
        newGhost->setPosition(vector);
        vector.x = 5;
        vector.y = 0;
        newGhost->setMoveVelocity(vector);
        //newGhost->setLocationInArray(_currentGhostArrayIndex);
    } else if (randomSide == 1) {
        int maxY = _height - GAME_SPRITE_SIZE/2;
        int minY = GAME_SPRITE_SIZE/2;
        int range = maxY - minY;
        int spawnLocationY = (arc4random()%range) + minY;
        Vector2 vector;
        vector.x = _width+GAME_SPRITE_SIZE;
        vector.y = spawnLocationY;
        newGhost->setPosition(vector);
        vector.x = -5;
        vector.y = 0;
        newGhost->setMoveVelocity(vector);
        //newGhost->setLocationInArray(_currentGhostArrayIndex);
    } else if (randomSide == 2) {
        int maxX = _width - GAME_SPRITE_SIZE/2;
        int minX = GAME_SPRITE_SIZE/2;
        int range = maxX - minX;
        int spawnLocationX= (arc4random()%range) + minX;
        Vector2 vector;
        vector.x = spawnLocationX;
        vector.y = -GAME_SPRITE_SIZE;
        newGhost->setPosition(vector);
        vector.x = 0;
        vector.y = 5;
        newGhost->setMoveVelocity(vector);
        //newGhost->setLocationInArray(_currentGhostArrayIndex);
    } else if (randomSide == 3) {
        int maxX = _width - GAME_SPRITE_SIZE/2;
        int minX = GAME_SPRITE_SIZE/2;
        int range = maxX - minX;
        int spawnLocationX = (arc4random()%range) + minX;
        Vector2 vector;
        vector.x = spawnLocationX;
        vector.y = _height+GAME_SPRITE_SIZE;
        newGhost->setPosition(vector);
        vector.x = 0;
        vector.y = -5;
        newGhost->setMoveVelocity(vector);
        //newGhost->setLocationInArray(_currentGhostArrayIndex);
    }
    
    _ghostArray->addSprite(newGhost);
    
}

void GameWindow::checkForOutOfBoundsSprites(TowerArray *array)
{
    for (int iii = 0; iii < array->getCount(); iii++) {
        if ( array->getSpriteAt(iii) != NULL) {
            Sprite *sprite = array->getSpriteAt(iii);
            if (((sprite->getPosition()).x >= _width + GAME_SPRITE_SIZE)&&((sprite->getMoveVelocity()).x > 0)) {
                array->deleteSpriteAt(iii);
                sprite = NULL;
                
            } else if (((sprite->getPosition()).x <= -GAME_SPRITE_SIZE)&&((sprite->getMoveVelocity()).x < 0)) {
                array->deleteSpriteAt(iii);
                sprite = NULL;
                
            } else if (((sprite->getPosition()).y >= _height+GAME_SPRITE_SIZE)&&((sprite->getMoveVelocity()).y > 0)) {
                array->deleteSpriteAt(iii);
                sprite = NULL;
                
                //std::cout <<"fsfes" << std::endl;
            } else if (((sprite->getPosition()).y < -GAME_SPRITE_SIZE)&&((sprite->getMoveVelocity()).y < 0)) {
                array->deleteSpriteAt(iii);
                sprite = NULL;
                
                //std::cout <<"fsfes" << std::endl;
            }
        }
    }

}


bool GameWindow::checkForRectangleCollision(Rect a, Rect b)
{
    return !(a.right <= b.left ||
             a.left >= b.right ||
             a.top <= b.bottom ||
             a.bottom >= b.top);
}


void GameWindow::updateSprites(TowerArray *array)
{
    for (int iii = 0; iii < array->getCount(); iii++) {
        if ( array->getSpriteAt(iii) != NULL) ( array->getSpriteAt(iii))->updateSprite();
    }
}

void GameWindow::update()
{
    
    for (int iii = 0; iii < _ghostArray->getCount(); iii++) {
        Sprite *ghostSprite = _ghostArray->getSpriteAt(iii);
        for (int jjj = 0; jjj <_starArray->getCount(); jjj++) {
            Sprite *starSprite = _starArray->getSpriteAt(jjj);
            if (checkForRectangleCollision(starSprite->getRect(), ghostSprite->getRect())) {
                _ghostArray->deleteSpriteAt(iii);
                _starArray->deleteSpriteAt(jjj);
            }
        }
        
    }
    
    checkForOutOfBoundsSprites(_starArray);
    checkForOutOfBoundsSprites(_ghostArray);
    
    if (glfwGetTime() >= 1.0f) {
        glfwSetTime(0);
        spawnGhost();
        std::cout <<  _starArray->getCount() << std::endl;
    }
    
    _playerUFO.updateSprite();
    updateSprites(_ghostArray);
    updateSprites(_starArray);
    
    
    if (glfwGetKey(GLFW_KEY_UP)) {
        Vector2 vector = _playerUFO.getPosition();
        if (vector.y <= _height-GAME_SPRITE_SIZE/1.7) vector.y += 5;
        _playerUFO.setPosition(vector);
    }
    if (glfwGetKey(GLFW_KEY_LEFT)) {
        Vector2 vector = _playerUFO.getPosition();
        if (vector.x >= GAME_SPRITE_SIZE/1.7) vector.x -= 5;
        _playerUFO.setPosition(vector);
    }
    if (glfwGetKey(GLFW_KEY_RIGHT)) {
        Vector2 vector = _playerUFO.getPosition();
        if (vector.x <= _width-GAME_SPRITE_SIZE/2) vector.x += 5;
        _playerUFO.setPosition(vector);
    }
    if (glfwGetKey(GLFW_KEY_DOWN)) {
        Vector2 vector = _playerUFO.getPosition();
        if (vector.y >= 0)vector.y -= 5;
        _playerUFO.setPosition(vector);
    }

}