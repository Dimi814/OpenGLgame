//
//  TowerArray.h
//  OpenGLgame
//
//  Created by Dimitriy Dounaev on 12/04/13.
//  Copyright (c) 2013 Dimitriy Dounaev. All rights reserved.
//

#ifndef __OpenGLgame__TowerArray__
#define __OpenGLgame__TowerArray__

#include <iostream>
#include "Sprite.h"
#include <vector>

class TowerArray
{
    
private:
    
    Sprite *_spriteArray[42];
    int _count;
    
public:
    
    int getCount();
    
    TowerArray();
    ~TowerArray();
    void addSprite(Sprite *newElement);
    void deleteSpriteAt(int index);
    Sprite* getSpriteAt(int index);
    
};

#endif /* defined(__OpenGLgame__TowerArray__) */
