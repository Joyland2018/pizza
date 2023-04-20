//
//  SelectPizza.hpp
//  Pizza
//
//  Created by LiXiaofei on 3/24/21.
//

#ifndef SelectPizza_h
#define SelectPizza_h

#include <stdio.h>
#include "cocos2d.h"

using namespace cocos2d;

class SelectPizza : public CCLayer{
public:
    static CCScene* scene();
    virtual void onEnter();
    virtual void onExit();
    
    bool init();
    SelectPizza();
    virtual ~SelectPizza();
    void openIAPPage();
    virtual void ccTouchesBegan(CCSet *pTouches,CCEvent *pEvent);
    virtual void ccTouchesMoved(CCSet *pTouches,CCEvent *pEvent);
    virtual void ccTouchesEnded(CCSet *pTouches,CCEvent *pEvent);
    void showIAPPage(int _index);
    void showPizzaTaste();
    void goToNext();
    CCArray* tasteNameArr;
    
    void addLock(CCSprite* pSprite,CCSize spriteSize);
    
    int x_x=0;
    
    bool backClick;
    
    void clickBack();
    
    bool selectedPizza;
    CREATE_FUNC(SelectPizza);
};

#endif /* SelectPizza_h */
