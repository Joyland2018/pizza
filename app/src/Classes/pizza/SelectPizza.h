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
    int x_y=0;
    bool backClick;
    CCSprite *bt_wordblock;
    CCSprite *bt_wordbreak;
    CCSprite *bt_shapepuzzle;
    CCSprite *bt_firstword;
    CCSprite *bt_background;
    CCSprite *bt_Jorland;
    CCSprite *bt_Match;
    CCSprite *bt_ad;
    int select;

    void clickBuy();
    void clickBack();
    CREATE_FUNC(SelectPizza);
};

#endif /* SelectPizza_h */
