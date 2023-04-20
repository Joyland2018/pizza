//
//  CutPizza.hpp
//  Pizza
//
//  Created by LiXiaofei on 4/8/21.
//

#ifndef CutPizza_h
#define CutPizza_h

#include <stdio.h>
#include "cocos2d.h"

using namespace cocos2d;

class CutPizza : public CCLayer{
public:
    static CCScene* scene();
    virtual void onEnter();
    virtual void onExit();
    CCPoint visibleOrigin;
    CCSize visibleSize ;
    bool init();
    CCPoint center;
    CutPizza();
    virtual ~CutPizza();
    CCLabelTTF *curallscores;
    virtual void ccTouchesBegan(CCSet *pTouches,CCEvent *pEvent);
    virtual void ccTouchesMoved(CCSet *pTouches,CCEvent *pEvent);
    virtual void ccTouchesEnded(CCSet *pTouches,CCEvent *pEvent);
    CCSprite* pizzaTop;
    void showTopping();
    
    void showFlower();
    void showPizza();
    
    void playSildeMp3();
    void showSlide();
    void showSlide1();
    void showSlide2();
    void showSlide3();
    void visiSlide(CCObject *pSender);
    
    void showDino();
    void dinoEatAction();
    
    void eatMp3();
    void eatFinish();
    void collectCoinMusic();
    void removeNormalSprite(CCObject* pSender);
    void gameComplate();
    int x_x;
    
    int x_y;
    int rect_x;
    int yuan_x;
    int heart_x;
    
    int topXdis;
    
    CCSprite* board;
    
    bool backClick;
    bool clickNext;
    
    void clickBack();
    
    
    CREATE_FUNC(CutPizza);
};

#endif /* CutPizza_hpp */
