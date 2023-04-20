//
//  SelectTopping.hpp
//  Pizza
//
//  Created by LiXiaofei on 4/1/21.
//

#ifndef SelectTopping_h
#define SelectTopping_h

#include "stdio.h"
#include "cocos2d.h"

using namespace cocos2d;

class SelectTopping : public CCLayer{
public:
    static CCScene* scene();
    virtual void onEnter();
    virtual void onExit();
    CCLabelTTF *curallscores;
    bool init();
    SelectTopping();
    virtual ~SelectTopping();
    
    virtual void ccTouchesBegan(CCSet *pTouches,CCEvent *pEvent);
    virtual void ccTouchesMoved(CCSet *pTouches,CCEvent *pEvent);
    virtual void ccTouchesEnded(CCSet *pTouches,CCEvent *pEvent);
    
    CCPoint center;
    
    int selectTopping[10]={0};
    int selectNum=0;
    bool submit=false;
    bool haveSelect=false;
    
    void showTopping();
    void showVegTopping();
    void showDone();
    
    void goNext();
    
    CCSprite* select = NULL;
    int selectTopNum=0;
    int selectedTop=99;
    int x_x=0;
    bool clickBack;
    bool clickNext;
    
    void clickToBack();
    CREATE_FUNC(SelectTopping);
};


#endif /* SelectTopping_hpp */
