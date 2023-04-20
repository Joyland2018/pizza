//
//  MakeSauce.hpp
//  DrDino
//
//  Created by LiXiaofei on 9/1/21.
//

#ifndef MakeSauce_h
#define MakeSauce_h

#include <stdio.h>
#include "cocos2d.h"

#include "PizzaLineSprite.h"

using namespace cocos2d;

class MakeSauce : public CCLayer{
public:
    static CCScene* scene();
    virtual void onEnter();
    virtual void onExit();
    CCLabelTTF *curallscores;
    bool init();
    MakeSauce();
    virtual ~MakeSauce();
    
    virtual void ccTouchesBegan(CCSet *pTouches,CCEvent *pEvent);
    virtual void ccTouchesMoved(CCSet *pTouches,CCEvent *pEvent);
    virtual void ccTouchesEnded(CCSet *pTouches,CCEvent *pEvent);
    
    void candyMaterial();
    void halloweenMaterial();
    void christmasMaterial();
    void showMilk();
    void milkAction();
    void potMilk();
    void moveToCenter();
    bool canTouchSpoon = false;
    void showSpoon();
    void showSpoon1();
    
    void removeNewsprite();
    
    void showSauce();
    void sauceAction(int index);
    
    void oliMp3();
    
    void goNext();
    void canTouchOther();
    
    void cannotStir();
    void stirMp3();
    
    void showFinger();
    void canTouchedSpoon();
    void showPot();
    void potActoion();
    
    
    bool touchedMilk;
    bool fireOn;
    
    bool canStri;
    
    
    int newSpriteIndex;
    int rotation;
    int originRotation;
    int sauceIndex;
    
    int newSpriteTag;
    
    int beginPos;
    int endPos;
    
    CCRect createRectByPoint(CCPoint point,float width,float height);
    CCPoint originPos;
    int milkIndex;
    
    int MaterialIndex;
    
    CCSprite* touchSprite;
    
    CCSprite* touchSpoon;
    
    bool subStir;
    bool addStir;
    bool stirNum ;
    bool touchOther;
    
    int whichMaterial;
    
    CCPoint center;
    int touchIndex;
    bool touchMilk;
//    bool addAllMaterial = false;
    const char* fileName;
    
    int cutNum;
    
    bool backClick;
    
    bool clickNext;
    
    void clickBack();
    CREATE_FUNC(MakeSauce);
};

#endif /* MakeSauce_hpp */
