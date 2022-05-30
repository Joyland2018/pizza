//
//  makeDough.hpp
//  Pizza
//
//  Created by LiXiaofei on 3/25/21.
//

#ifndef MakeDough_h
#define MakeDough_h

#include <stdio.h>
#include "cocos2d.h"

using namespace cocos2d;

class MakeDough : public CCLayer{
public:
    static CCScene* scene();
    virtual void onEnter();
    virtual void onExit();
    CCLabelTTF *curallscores;
    bool init();
    MakeDough();
    virtual ~MakeDough();
    
    virtual void ccTouchesBegan(CCSet *pTouches,CCEvent *pEvent);
    virtual void ccTouchesMoved(CCSet *pTouches,CCEvent *pEvent);
    virtual void ccTouchesEnded(CCSet *pTouches,CCEvent *pEvent);
    
    CCPoint center;
    
    //重力感应
    virtual void didAccelerate(cocos2d::CCAcceleration* pAccelerationValu);
    double gracityX=0;                      //重力加速度
    CCArray* tasteNameArr;
    
    void showIphoneAction();
    void showIphone();
    
    //显示原料
    void showWater();
    void showSugar();
//    void showYeast();
    void showOlive();
    void showSalt();
    void showFlour();
    
    
    //在面团上显示添加的原料
    void addFlours();
    void addWater();
    void addSugar();
    void addOil();
    void addSalt();
    
    void goNext();
    
    //搅拌后面团变化
    void striFlour(int index);
    int flourIndex=7;
    void striMp3();
    void showBowlFlour();
    
    //倒原料
    void pourWater();
    void pourSugar();
//    void pourYeast();
    void pourOlive();
    void pourSalt();
    void pourFlour();
    
    void showSpoon();
    void showSpoon1();
//    void spoonAction();
    
    
    //可以倒原料
    void canPourWater();
    void canPourSugar();
//    void canPourYeast();
    void canPourOlive();
    void canPourSalt();
    void canPourFlour();
    
    //不可以倒原料
    void cannotPourWater();
    void cannotPourSugar();
//    void cannotPourYeast();
    void cannotPourOlive();
    void cannotPourSalt();
    void cannotPourFlour();
    
    void cannotStirFlour();
    
    void pourLiquidMp3();
    void pourSolidMp3();
    void pourOliMp3();
    
    
    void spoonMp3();
    
    CCSprite* water = NULL;
    CCSprite* sugar = NULL;
//    CCSprite* yeast = NULL;
    CCSprite* olive = NULL;
//    CCSprite* salt = NULL;
    CCSprite* flour = NULL;
    CCSprite* flours = NULL;
//    CCSprite* spoonTouch = NULL;
    CCSprite* flourers = NULL;
    CCSprite* touchSprite = NULL;
    
    float lastPos=0.0;
    
    bool isCanPourWater=false;
    bool isCanPourSugar=false;
//    bool isCanPourYeast=false;
    bool isCanPourOlive=false;
    bool isCanPourSalt=false;
    bool isCanPourFlour=false;
    
    bool isPourWater=false;
    bool isPourSugar=false;
//    bool isPourYeast=false;
    bool isPourOlive=false;
    bool isPourSalt=false;
    bool isPourFlour=false;
    
    int rotation=0;
    bool leftSlide = true;
    int stirTimes=0;
    
    
    bool stirNum=false;
    bool addStir =false;
    bool subStir =false;
    
    bool cannotStir = false;
    bool clickBack;
    
    void clickToBack();
    CREATE_FUNC(MakeDough);
};

#endif /* makeDough_hpp */
