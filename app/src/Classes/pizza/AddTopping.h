//
//  AddTopping.hpp
//  Pizza
//
//  Created by LiXiaofei on 4/5/21.
//

#ifndef AddTopping_h
#define AddTopping_h

#include "iostream"
#include "cocos2d.h"
#include "cocos-ext.h"

using namespace cocos2d;
using namespace extension;

class AddTopping : public cocos2d::CCLayer,public extension::CCScrollViewDelegate{
    extension::CCScrollView *scrollView;
    CCLayer *containerLayer;
public:
    static CCScene* scene();
    virtual void onEnter();
    virtual void onExit();
    
    bool init();
    
    AddTopping();
    virtual ~AddTopping();
    virtual void scrollViewDidScroll(extension::CCScrollView *view);
    virtual void scrollViewDidZoom(extension::CCScrollView *view);
    
//    virtual void ccTouchesBegan(CCSet *pTouches,CCEvent *pEvent);
//    virtual void ccTouchesMoved(CCSet *pTouches,CCEvent *pEvent);
//    virtual void ccTouchesEnded(CCSet *pTouches,CCEvent *pEvent);
    virtual void registerWithTouchDispatcher();
    virtual bool ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
    virtual void ccTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
    virtual void ccTouchMoved(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    
    CCPoint center;
    CCRect createRectByPoint(CCPoint point,float width,float height);
    void showTopping();
    
    void showPepperTopping();
    
    void showHawaiiTopping();
    
    void showMoreCheeseTopping();
    
    void showVegTopping();
    void goNext();
    
    void showPizza();
    
    void candyTopping();
    void halloweenTopping();
    void christmasTopping();
    
    
    int whichTopping=0;
    
    CCSprite* pizzaShape=NULL;
    
    CCSprite* newTop =  NULL;
    CCPoint originalPosition;
    
    float beginTouchX;
    float endTouchX;
    float beginPosY;
    float endPosY;
    float beginPosX;
    float endPosX;
    int xDis=0;
    
    bool selectTop=false;
    bool selected=false;
    bool showTop = false;
    bool haveMovedScroll = false;
    
    CCScale9Sprite* board=NULL;
    
//    int selectedTop=99;
    int touchTopping=0;
    int x_x=0;
    
    float iphoneXoffsetX;
    
    float storeWidth = 0.0;
    float storeHeight = 0.0;
    
    float storeWidth1 = 0.0;
    float storeHeight1 = 0.0;
    
    float storeWidth2 = 0.0;
    float storeHeight2 = 0.0;
    
    float storeWidth3 = 0.0;
    float storeHeight3 = 0.0;
    
    float storeWidth4 = 0.0;
    float storeHeight4 = 0.0;
    
    int topDis=0;
//    CCRect rect2;
    void playGuaid();
    void guardAction();
    
    int ipadX=0;
    
    bool backClick;
    
    bool selectedTop = false;
    
    bool clickNext;
    
    bool addTopping;
    
    void clickBack();
    
//    int curPizza;
    CREATE_FUNC(AddTopping);
};
#endif /* AddTopping_hpp */
