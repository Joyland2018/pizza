//
// Created by LiXiaofei on 5/28/22.
//

#ifndef PIZZA_FIRSTSCENE_H
#define PIZZA_FIRSTSCENE_H


#include <stdio.h>
#include "cocos2d.h"

using namespace cocos2d;

class FirstScene : public CCLayer{
public:
    static CCScene* scene();
    virtual void onEnter();
    virtual void onExit();

    bool init();
    FirstScene();
    virtual ~FirstScene();
    virtual void ccTouchesBegan(CCSet *pTouches,CCEvent *pEvent);
    virtual void ccTouchesMoved(CCSet *pTouches,CCEvent *pEvent);
    virtual void ccTouchesEnded(CCSet *pTouches,CCEvent *pEvent);
    void goToNext();

    int x_x=0;
    int x_y=0;

    void fireAction();
    void fireActions();
    void steamAction();
    void steamActions();
    bool touchStart;

    CCSprite *bt_wordblock;
    CCSprite *bt_wordbreak;
    CCSprite *bt_shapepuzzle;
    CCSprite *bt_firstword;
    CCSprite *bt_background;
    CCSprite *bt_Jorland;
    CCSprite *bt_Match;
    CCSprite *bt_ad;

    CREATE_FUNC(FirstScene);
};


#endif //PIZZA_FIRSTSCENE_H
