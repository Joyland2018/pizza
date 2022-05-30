//
//  BakedPizza.hpp
//  Pizza
//
//  Created by LiXiaofei on 4/7/21.
//

#ifndef BakedPizza_h
#define BakedPizza_h

#include "stdio.h"
#include "cocos2d.h"

using namespace cocos2d;

class BakedPizza : public CCLayer{
public:
    static CCScene* scene();
    virtual void onEnter();
    virtual void onExit();
    
    bool init();
    
    BakedPizza();
    virtual ~BakedPizza();
    CCLabelTTF *curallscores;
    virtual void ccTouchesBegan(CCSet *pTouches,CCEvent *pEvent);
    virtual void ccTouchesMoved(CCSet *pTouches,CCEvent *pEvent);
    virtual void ccTouchesEnded(CCSet *pTouches,CCEvent *pEvent);
    
    CCRect createRectByPoint(CCPoint point,float width,float height);
    CCPoint center;
    CCPoint originalPosition;
    
    //计时器
    CCSprite* time_bg;
    CCSprite* state;
    CCProgressTimer *progress;
    CCSprite* clock;
    bool bakeComplate=false;
    bool bakeFinish=false;
    
//    void showPizza();
    CCSprite* bakePizza=NULL;
    CCSprite* pizza = NULL;
//    CCSprite* steams = NULL;
    void showTime();
    void showTime1();
    void bakeDone();
    
    void removeTime();
    void goNext();
    
    void fireAction();
    void showPizza();
    void pizzaAction();
    void removeSteam(CCObject *pSender);
    void canShowSteam(CCObject *pSender);
    void showSteam();
    void showSteam1();
    void showSteam2();
    
    void bakeMp3();
    
    void playGuaid();
    void guardAction();
    
    void playFireBakeMp3();
    
    bool touchPizza= false;
    
    int x_x=0;
    
    bool backClick;
    
    void clickBack();
    CREATE_FUNC(BakedPizza);
};


#endif /* BakedPizza_hpp */
