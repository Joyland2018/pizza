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
    CCSprite* pizzaTop=NULL;
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
    int x_x=0;
    
    int x_y=0;
    int rect_x=0;
    int yuan_x=0;
    int heart_x=0;
    
    int topXdis=0;
    
    CCSprite* board = NULL;
    
    bool backClick;
    
    void clickBack();
    
    
    CREATE_FUNC(CutPizza);
};

#endif /* CutPizza_hpp */
