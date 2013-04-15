//
//  TowerArray.cpp
//  OpenGLgame
//
//  Created by Dimitriy Dounaev on 12/04/13.
//  Copyright (c) 2013 Dimitriy Dounaev. All rights reserved.
//

#include "TowerArray.h"

int TowerArray::getCount()
{
    return _count;
}

TowerArray::TowerArray():_count(0)
{
    
}

TowerArray::~TowerArray()
{
    for (int iii = 0; iii < _count; iii++) {
        delete _spriteArray[iii];
    }
}

void TowerArray::addSprite(Sprite *newElement)
{
    _spriteArray[_count] = newElement;
    ++_count;
}

void TowerArray::deleteSpriteAt(int index)
{
    --_count;
    delete _spriteArray[index];
    _spriteArray[index] = NULL;
    for (int iii = index; iii < _count; iii++) {
        _spriteArray[iii] = _spriteArray[iii+1];
    }
}

Sprite* TowerArray::getSpriteAt(int index)
{
    return _spriteArray[index];
}