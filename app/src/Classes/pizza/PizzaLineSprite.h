//
//  PizzaLineSprite.hpp
//  Pizza
//
//  Created by LiXiaofei on 4/5/21.
//

#ifndef PizzaLineSprite_h
#define PizzaLineSprite_h

#include <stdio.h>

#include "cocos2d.h"

using namespace cocos2d;

class PizzaLineSprite : public CCSprite{
public:
    
    void draw();
    void drawLine();
//    virtual void draw(void);
//
//    static float degree(CCPoint vect);
    std::list<CCPoint>pointList;
    CREATE_FUNC(PizzaLineSprite);
public:
    CCPoint start;
    CCPoint end;
    
    int R = arc4random()%255;
    int G = arc4random()%255;
    int B = arc4random()%255;
    
    int s;
};

#endif /* PizzaLineSprite_hpp */
