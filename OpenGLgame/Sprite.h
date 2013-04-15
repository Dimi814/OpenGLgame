//
//  Sprite.h
//  OpenGLgame
//
//  Created by Dimitriy Dounaev on 12/04/13.
//  Copyright (c) 2013 Dimitriy Dounaev. All rights reserved.
//

#ifndef __OpenGLgame__Sprite__
#define __OpenGLgame__Sprite__

#include <iostream>
#include <GL/glfw.h>

#define GAME_SPRITE_SIZE 100.0f

typedef struct {
    float left;
    float right;
    float top;
    float bottom;
} Rect;


typedef struct {
    
    float x;
    float y;
    
} Vector2;

class Sprite
{
private:
    
    GLuint _textureBufferID;
    Vector2 _position;
    Vector2 _moveVelocity;
    int _locationInArray;
    Rect _rect;
    
    void setRect();

public:
    
    
    Rect getRect();
    
    void setLocationInArray(int locationInArray);
    int getLocationInArray();
    
    void setTextureBufferID(GLuint textureBufferID);
    GLuint getTextureBufferID();
    
    void setPosition(Vector2 position);
    Vector2 getPosition();
    
    void setMoveVelocity(Vector2 moveVelocity);
    Vector2 getMoveVelocity();
    
    Sprite(GLuint textureBufferID);
    ~Sprite();
    void drawSprite();
    void updateSprite();

};

#endif 
