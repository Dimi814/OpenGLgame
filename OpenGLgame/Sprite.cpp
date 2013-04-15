//
//  Sprite.cpp
//  OpenGLgame
//
//  Created by Dimitriy Dounaev on 12/04/13.
//  Copyright (c) 2013 Dimitriy Dounaev. All rights reserved.
//

#include "Sprite.h"



////////////////////////////////////////////////
//TEXTURE_BUFFER_ID
///////////////////////////////////////////////

void Sprite::setTextureBufferID(GLuint textureBufferID)
{
    _textureBufferID = textureBufferID;
}

GLuint Sprite::getTextureBufferID()
{
    return _textureBufferID;
}

////////////////////////////////////////////////
//POSITION
///////////////////////////////////////////////

void Sprite::setPosition(Vector2 position)
{
    _position = position;
}

Vector2 Sprite::getPosition()
{
    return _position;
}

////////////////////////////////////////////////
//MOVE_VELOCITY
///////////////////////////////////////////////
void Sprite::setMoveVelocity(Vector2 moveVelocity)
{
    _moveVelocity = moveVelocity;
}

Vector2 Sprite::getMoveVelocity()
{
    return _moveVelocity;
}

////////////////////////////////////////////////
//SET_LOCATION_IN_ARRAY
///////////////////////////////////////////////
void Sprite::setLocationInArray(int locationInArray)
{
    _locationInArray = locationInArray;
}

int Sprite::getLocationInArray()
{
    return _locationInArray;
}

Rect Sprite::getRect()
{
    return _rect;
}

void Sprite::setRect()
{
    Rect rect;
    rect.left = _position.x -GAME_SPRITE_SIZE/3;
    rect.right = _position.x+GAME_SPRITE_SIZE/3;
    rect.top = _position.y + GAME_SPRITE_SIZE/3;
    rect.bottom = _position.y -GAME_SPRITE_SIZE/3;
    _rect = rect;
}



Sprite::Sprite(GLuint textureBufferID):_locationInArray(0)
{
    _textureBufferID = textureBufferID;
}

Sprite::~Sprite()
{
    //std::cout <<"destroyed" << std::endl;
}

void Sprite::drawSprite()
{
    glLoadIdentity();
    
    glTranslatef(_position.x, _position.y, 0.0f);
    glTranslatef(-GAME_SPRITE_SIZE/2, -GAME_SPRITE_SIZE/2, 0.0f);
    
    glBindTexture(GL_TEXTURE_2D, _textureBufferID);
    glDrawArrays(GL_QUADS, 0, 4);
}

void Sprite::updateSprite()
{   
    _position.x += _moveVelocity.x;
    _position.y += _moveVelocity.y;
    
    setRect();
}