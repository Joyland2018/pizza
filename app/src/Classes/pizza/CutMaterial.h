//
//  CutMaterial.hpp
//  DrDino
//
//  Created by LiXiaofei on 8/31/21.
//

#ifndef CutMaterial_h
#define CutMaterial_h

#include <stdio.h>
#include "cocos2d.h"

#include "PizzaLineSprite.h"

using namespace cocos2d;

class CutMaterial : public CCLayer{
public:
    static CCScene* scene();
    virtual void onEnter();
    virtual void onExit();
    CCLabelTTF *curallscores;
    bool init();
    CutMaterial();
    virtual ~CutMaterial();
    
    virtual void ccTouchesBegan(CCSet *pTouches,CCEvent *pEvent);
    virtual void ccTouchesMoved(CCSet *pTouches,CCEvent *pEvent);
    virtual void ccTouchesEnded(CCSet *pTouches,CCEvent *pEvent);
    
    PizzaLineSprite* pizzaLineSprite;
    
    CCPoint center;
    CCPoint newPoint;
    void candyMaterial1();
    void candyMaterial2();
    void candyMaterial3();
    
    void halloween1();
    void halloween2();
    
    void christmas1();
    void christmas2();
    
//    void halloweenMaterial();
//    void christmasMaterial();
    
    
    
    void isCancut();
    void CannotCut();
    void goNext();
    void strawberryAction(int index);
    void bananaAction(int index);
    void beetAction(int index);
    
    void potatoAction(int index);
    void pumpkinAction(int index);
    
    void onionAction(int index);
    void garlicAction(int index);
//    CCRect createRectByPoint(CCPoint point,float width,float height);
    
   
    
    void cutActionMp3();
    void  showTopping();
    void setComplate();
    
    //手指提示
    void showFinger();
    void removeSprite(CCObject* pSender);
    
    
    float beginTouchX;
    float endTouchX;
    
    
    int sausageIndex=0;
    bool canCuttop=false;
    
    bool isMoveComplate=false;
    
    
    int cutNumber=0;
    bool potatos=false;
    bool strawberrys = false;
    bool bananas = false;
    bool beets = false;
    bool pumpkins = false;
    bool onions = false;
    bool garlics = false;
    
    void resetCutNum();
    void noStrawberry();
    void noBanana();
    void noBeet();
    void noPotato();
    void noPumpkins();
    void noOnion();
    void noGarlic();
//    CCSetIterator it;
//    CCTouch* touch;
//    CCSprite* potato = NULL;
//    CCSprite* rouwan = NULL;
//    CCSprite* peigen = NULL;
    int cutNum=1;
    
    bool backClick;
    
    bool clickNext;
    
    void clickBack();
    CREATE_FUNC(CutMaterial);
};

#endif /* CutMaterial_hpp */
