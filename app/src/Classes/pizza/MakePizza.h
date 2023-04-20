//
//  MakePizza.hpp
//  Pizza
//
//  Created by LiXiaofei on 3/30/21.
//

#ifndef MakePizza_h
#define MakePizza_h

#include "stdio.h"
#include "cocos2d.h"

using namespace cocos2d;

class MakePizza : public CCLayer{
public:
    static CCScene* scene();
    virtual void onEnter();
    virtual void onExit();
    
    bool init();
    MakePizza();
    virtual ~MakePizza();
    CCLabelTTF *curallscores;
    virtual void ccTouchesBegan(CCSet *pTouches,CCEvent *pEvent);
    virtual void ccTouchesMoved(CCSet *pTouches,CCEvent *pEvent);
    virtual void ccTouchesEnded(CCSet *pTouches,CCEvent *pEvent);
    CCRect createRectByPoint(CCPoint point,float width,float height);
    CCPoint center;
    
    void selectNough();
    void rollNough();
    void noughSteam();
    
    
    void showRollingPin();
    void rollingAction(int index);
    
    void moJiang();
    void cheese();
    void cheeseAction(CCObject *pSender,int index);
    void noughAction();
    void removeNough();
    void removePin();
    void removeSpoon();
    void removeCheeserub();
    void sauce();
    void sauceNum();
    void cheeseNum();
    void sprinkleCheese();
    void goNext();
    
    void goMaterial();
    void cannotRoll();
    
    void noughDropMusic();
    void noughActionMp3();
    
    void showNough();
    CCSprite* saucer = NULL;
    CCSprite* cheeser = NULL ;
    CCSprite* touchSprite = NULL;
    CCSprite* touchSpoonSprite = NULL;
    CCSprite* touchCheeseSprite = NULL;
//    CCSprite* cheeserub = NULL;
    
    
//    int noughShape=0;
    int time=0;
    int showSauce=0;
    int showCheese=0;
    int sauceCount=0;
    bool noughComplate=false;
    int sauceArray[50]={0};
    int cheeseArray[50]={0};
    
    int rollingIndex=0;
    int rollPinIndex=1;
    int cheeseRubNum=1;
    
    
    bool canRolling=false;
    bool isRolled=false;
    
    
    float beginY=0.0;
    float endY=0.0;
    bool selectedNough=false;
    
    bool canRubPizza=false;
    bool canSpoonPizza = false;
    bool cannotSpoon = false;
    int x_x=0;
    int y_x=0;
    int sauce_x=0;
    bool backClick;
    
    bool clickNext;
    
    void clickBack();
    void clickToBack();
    CREATE_FUNC(MakePizza);
    
};


#endif /* MakePizza_hpp */
