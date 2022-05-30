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
    
    
    bool touchedMilk=false;
    bool fireOn = false;
    
    bool canStri = false;
    
    
    int newSpriteIndex=0;
    int rotation=0;
    int originRotation=0;
    int sauceIndex=0;
    
    int newSpriteTag=0;
    
    int beginPos=0;
    int endPos=0;
    
    CCRect createRectByPoint(CCPoint point,float width,float height);
    CCPoint originPos;
    int milkIndex=0;
    
    int MaterialIndex=0;
    
    CCSprite* touchSprite= NULL;
    
    CCSprite* touchSpoon = NULL;
    
    bool subStir=false;
    bool addStir = false;
    bool stirNum = false;
    bool touchOther = false;
    
    int whichMaterial=0;
    
    CCPoint center;
    int touchIndex=0;
    bool touchMilk = false;
//    bool addAllMaterial = false;
    const char* fileName="";
    
    int cutNum=1;
    
    bool backClick;
    
    void clickBack();
    CREATE_FUNC(MakeSauce);
};

#endif /* MakeSauce_hpp */
