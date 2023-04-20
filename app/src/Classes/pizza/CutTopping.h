//
//  CutTopping.hpp
//  Pizza
//
//  Created by LiXiaofei on 4/2/21.
//

#ifndef CutTopping_h
#define CutTopping_h

#include "stdio.h"
#include "cocos2d.h"
#include "PizzaLineSprite.h"

using namespace cocos2d;

class CutTopping : public CCLayer{
public:
    static CCScene* scene();
    virtual void onEnter();
    virtual void onExit();
    CCLabelTTF *curallscores;
    bool init();
    CutTopping();
    virtual ~CutTopping();
    
    virtual void ccTouchesBegan(CCSet *pTouches,CCEvent *pEvent);
    virtual void ccTouchesMoved(CCSet *pTouches,CCEvent *pEvent);
    virtual void ccTouchesEnded(CCSet *pTouches,CCEvent *pEvent);
    
    PizzaLineSprite* pizzaLineSprite;
    
    CCPoint center;
    CCPoint newPoint;
    //更多芝士披萨
    void cheeseTopping();
    //意大利辣香肠披萨
    void pepperoniTopping();
    //夏威夷披萨
    void showBoluo();
    
    //蔬菜披萨
    void showMogu();
    void showBocai();
    void showXiLanHua();
//    void showGanlanye();
    
    //至尊披萨
    void showRouwan();
//    void showJirou();
    void showPeigen();
    void showLajiao();
    void showTomato();
    
    void isCancut();
    void CannotCut();
    void goNext();
    void sausageAction(int index);
    void moguAction(int index);
    void bocaiAction(int index);
    void xilanhuaAction(int index);
    void boluoAction(int index);
    void tomatoAction(int index);
    void rouwanAction(int index);
//    void jirouAction();
    void peigenAction(int index);
    void lajiaoAction(int index);
//    CCRect createRectByPoint(CCPoint point,float width,float height);
    
    void noPotato();
    void noXilanhua();
    void noMogu();
    void noPepper();
    void noBoluo();
    void noBocai();
    void noChang();
    void noRouwan();
    void noPengen();
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
    bool xilanhuas=false;
    bool mushroom = false;
    bool pepper = false;
    bool pineapple = false;
    bool spinach = false;
    bool chang = false;
    bool rouwans  =false;
    bool pengens = false;
    
    void resetCutNum();
    
    
//    CCSetIterator it;
//    CCTouch* touch;
//    CCSprite* potato = NULL;
//    CCSprite* rouwan = NULL;
//    CCSprite* peigen = NULL;
    int cutNum=1;
    
    bool backClick;
    
    bool clickNext;
    
    void clickBack();
    CREATE_FUNC(CutTopping);
};


#endif /* CutTopping_hpp */
