//
//  SelectTopping.cpp
//  Pizza
//
//  Created by LiXiaofei on 4/1/21.
//

#include "SelectTopping.h"
#include "GameManager.h"
#include "SimpleAudioEngine.h"
#include "MakePizza.h"
#include "CutTopping.h"
#include "PizzaManager.h"
#include "AddTopping.h"
#include "BakedPizza.h"

using namespace CocosDenshion;

enum{
    kBack=0,
    kTopping=10,
    kDone=1,
    kDone1 = 2,
    kDone2 = 3,
    kSelectTag = 100,
    kNextTag = 199,
};

CCScene* SelectTopping::scene(){
    CCScene* scene = CCScene::create();
    SelectTopping* layer = SelectTopping::create();
    scene->addChild(layer);
    return scene;
}

void SelectTopping::onEnter(){
    CCLayer::onEnter();
}

void SelectTopping::onExit(){
    CCLayer::onExit();
}

SelectTopping::SelectTopping(){}
SelectTopping::~SelectTopping(){}

bool SelectTopping::init(){
    if (!CCLayer::init()) {
        return false;
    }
    selectTopNum=0;
    clickBack = false;
    clickNext = false;
    center = GameManager::sharedManager()->getCenter();
    CCPoint leftTop = GameManager::sharedManager()->getLeftTopPos();
    CCPoint rightTop = GameManager::sharedManager()->getRightTopPos();
    CCPoint visibleOrigin=CCDirector::sharedDirector()->getVisibleOrigin();
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCSprite* bg = CCSprite::create("background/tablecloth.png");
    bg->setPosition(center);
    this->addChild(bg);
    
    CCSprite* back = CCSprite::create("background/back.png");
    back->setPosition(ccp(leftTop.x+50,leftTop.y-50));
    back->setTag(kBack);
    this->addChild(back);
    
    CCSprite* done = CCSprite::create("pizza/element/submit0.png");
    done->setPosition(ccp(center.x, center.y-160));
    done->setTag(kDone);
    this->addChild(done);
    if (GameManager::sharedManager()->isIphoneX()) {
        x_x=120;
    }
    
    if (PizzaManager::sharedManager()->whichPizza==7) {
        this->showVegTopping();
    }else if (PizzaManager::sharedManager()->whichPizza==8) {
        this->showTopping();
    }
    CCSprite* money = CCSprite::create("background/money.png");
    money->setPosition(ccp(visibleOrigin.x+visibleSize.width-100, visibleSize.height-50));
//    money->setTag(kMoney);
    this->addChild(money,10);
    
    CCString* curscore = CCString::createWithFormat("%d",GameManager::sharedManager()->getCurrentCoin());
    const char* curscores = curscore->getCString();
    curallscores = CCLabelTTF::create(curscores, "Arial", 28);
    curallscores->setColor(ccWHITE);
//    curallscores->setTag(100);
    curallscores->setPosition(ccp(visibleOrigin.x+visibleSize.width-70, visibleSize.height-50));
    this->addChild(curallscores,11);
    
    CCSprite* next = CCSprite::create("background/next.png");
    next->setPosition(ccp(rightTop.x-50,rightTop.y-50));
    next->setTag(kNextTag);
//    this->addChild(next);
    
    
    this->setTouchEnabled(true);
    return true;
}

void SelectTopping::showTopping(){
    for (int i =0; i<10; i++) {
//        CCSprite* top = CCSprite::create(CCString::createWithFormat("topping/topping_1.png")); 
//        CCSprite* top = CCSprite::create("topping/topping_1.png");
        char nmName[100] = {0};
        sprintf(nmName, "pizza/element/topping%d.png",i);     //随机加载数字
        CCLog("----%s----",nmName);                 //
        CCSprite* top = CCSprite::create(nmName);
        if(i<=4){
            top->setPosition(ccp(210+i*180+x_x, center.y+150));
        }else if(i>4){
            top->setPosition(ccp(210+(i-5)*180+x_x, center.y));
        }
        top->setTag(kTopping+i);
        this->addChild(top);
    }
}

void SelectTopping::showVegTopping(){
    for (int i =0; i<7; i++) {
//        CCSprite* top = CCSprite::create(CCString::createWithFormat("topping/topping_1.png"));
//        CCSprite* top = CCSprite::create("topping/topping_1.png");
        char nmName[100] = {0};
        sprintf(nmName, "pizza/element/topping%d.png",i);     //随机加载数字
        CCLog("----%s----",nmName);                 //
        CCSprite* top = CCSprite::create(nmName);
        if(i<=3){
            top->setPosition(ccp(300+i*180+x_x, center.y+150));
        }else if(i>3){
            top->setPosition(ccp(570+(i-5)*180+x_x, center.y));
        }
        
        top->setTag(kTopping+i);
        this->addChild(top);
    }
}

void SelectTopping::clickToBack(){
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, MakePizza::scene(), ccBLACK));
}

void SelectTopping::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent){
    CCTouch *pTouch = (CCTouch*)(pTouches->anyObject());
    CCPoint location=CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
    CCSprite* back = (CCSprite*)this->getChildByTag(kBack);
    CCSprite* next = (CCSprite*)this->getChildByTag(kNextTag);
    if (back!=NULL && back->boundingBox().containsPoint(location) && clickBack==false) {
//        SimpleAudioEngine::sharedEngine()->playEffect("mp3/done.mp3");
        clickBack = true;
        PizzaManager::sharedManager()->cleanAllSprite();
        CCScaleBy* scaleBy = CCScaleBy::create(0.1, 1.2);
        //            homeBtn->setScale(1.2);
        //            touchSprite = homeBtn;
        SimpleAudioEngine::sharedEngine()->playEffect("mp3/touchItem.mp3");
        back->runAction(CCSequence::createWithTwoActions(CCSequence::createWithTwoActions(scaleBy, scaleBy->reverse()), CCCallFunc::create(this, callfunc_selector(SelectTopping::clickToBack))));
//    }else if (next !=NULL && next->boundingBox().containsPoint(location) && clickNext == false) {
////        submit=true;
//        clickNext=true;
//        CCScaleBy* scaleBy = CCScaleBy::create(0.1, 1.2);
//        SimpleAudioEngine::sharedEngine()->playEffect("mp3/touchItem.mp3");
//        next->runAction(CCSequence::createWithTwoActions(CCSequence::createWithTwoActions(scaleBy, scaleBy->reverse()), CCCallFunc::create(this, callfunc_selector(SelectTopping::goNext))));
    }
    for (int i = 0; i < 10; i++) {
            CCSprite* topping = (CCSprite*)this->getChildByTag(kTopping+i);
            if(((topping !=NULL && topping->boundingBox().containsPoint(location)))){
                if(selectTopping[i]==0){
                    if (i==0) {
                        PizzaManager::sharedManager()->tomatoSelected=true;
                    }else if(i==1){
                        PizzaManager::sharedManager()->xilanhuaSelected=true;
                    }else if(i==2){
                        PizzaManager::sharedManager()->ganlanyeSelected=true;
                    }else if(i==3){
                        PizzaManager::sharedManager()->moguSelected=true;
                    }else if(i==4){
                        PizzaManager::sharedManager()->pepperSelected=true;
                    }else if(i==5){
                        PizzaManager::sharedManager()->boluoSelected=true;
                    }else if(i==6){
                        PizzaManager::sharedManager()->bocaiSelected=true;
                    }else if(i==7){
                        PizzaManager::sharedManager()->baconsSelected=true;
                    }else if(i==8){
                        PizzaManager::sharedManager()->meatSelected=true;
                    }else if(i==9){
                        PizzaManager::sharedManager()->changSelected=true;
                    }
                    
                    selectTopping[i]=1;
                    PizzaManager::sharedManager()->selectPizzaTopping(i);
                    PizzaManager::sharedManager()->selectedNum++;
                    SimpleAudioEngine::sharedEngine()->playEffect("mp3/touchItem.mp3");
                    CCPoint pos = topping->getPosition();
    //                this->removeChildByTag(kTopping+i);
                    select = CCSprite::create("pizza/topping/selected.png");
                    select->setPosition(pos);
                    select->setTag(kSelectTag+i);
                    this->addChild(select);
                    submit=true;
                    selectTopNum++;
                    selectedTop=i;
                }else if(selectTopping[i]==1){
                    SimpleAudioEngine::sharedEngine()->playEffect("mp3/touchItem.mp3");
                    if (i==0) {
                        PizzaManager::sharedManager()->tomatoSelected=false;
                    }else if(i==1){
                        PizzaManager::sharedManager()->xilanhuaSelected=false;
                    }else if(i==2){
                        PizzaManager::sharedManager()->ganlanyeSelected=false;
                    }else if(i==3){
                        PizzaManager::sharedManager()->moguSelected=false;
                    }else if(i==4){
                        PizzaManager::sharedManager()->pepperSelected=false;
                    }else if(i==5){
                        PizzaManager::sharedManager()->boluoSelected=false;
                    }else if(i==6){
                        PizzaManager::sharedManager()->bocaiSelected=false;
                    }else if(i==7){
                        PizzaManager::sharedManager()->baconsSelected=false;
                    }else if(i==8){
                        PizzaManager::sharedManager()->meatSelected=false;
                    }else if(i==9){
                        PizzaManager::sharedManager()->changSelected=false;
                    }
//                    CCLog("---%d---",PizzaManager::sharedManager()->selectedNum);
                    selectTopping[i]=0;
                    this->removeChildByTag(kSelectTag+i);
                    for (int j =0; j<PizzaManager::sharedManager()->selectedNum; j++) {
                        if (PizzaManager::sharedManager()->topping[j] == i) {
                            PizzaManager::sharedManager()->topping[j] = 99;
                            for (int m = j; m<PizzaManager::sharedManager()->selectedNum-1; m++) {
                                PizzaManager::sharedManager()->topping[m] = PizzaManager::sharedManager()->topping[m+1];
                            }
                        }
                    }
                    selectTopNum--;
                    PizzaManager::sharedManager()->selectedNum--;
                    if (PizzaManager::sharedManager()->selectedNum==0) {
                        submit=false;
                        this->showDone();
                        CCSprite* done = (CCSprite*)this->getChildByTag(kDone);
                        if(done!=NULL){
                            done->setOpacity(1);
                        }
                    }else{
                        submit=true;
                    }
                }
                
            }
        }
//    CCLog("---%d---",PizzaManager::sharedManager()->selectNum);
//    for (int i=0; i<10; i++) {
//        if (selectTopping[i]==0) {
//            PizzaManager::sharedManager()->selectNum++;
//        }
//    }
//    if (PizzaManager::sharedManager()->selectNum==10) {
//        submit=false;
//        PizzaManager::sharedManager()->selectNum=0;
//    }else{
//        submit=true;
//    }
    
//    for (int i=0; i<10; i++) {
//        CCLog("---%d---",PizzaManager::sharedManager()->topping[i]);
////        PizzaManager::sharedManager()->topping[i]
//    }
        if(submit){
            CCSprite* done = (CCSprite*)this->getChildByTag(kDone);
            CCSprite* done2 = (CCSprite*)this->getChildByTag(kDone2);
            CCPoint pos = done->getPosition();
            CCSprite* done1 = CCSprite::create("pizza/element/submit.png");
            done1->setPosition(pos);
            done1->setTag(kDone1);
            if (done2) {
                done2->removeFromParentAndCleanup(true);
            }
            this->addChild(done1,2);
            done->setOpacity(0);
            if (done1!=NULL && done1->boundingBox().containsPoint(location) && selectTopNum==1 && selectedTop==2){
                selectTopNum=0;
                submit=false;
                CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, AddTopping::scene(), ccBLACK));
            }else if (done1!=NULL && done1->boundingBox().containsPoint(location)){
                selectTopNum=0;
                submit=false;
                CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, CutTopping::scene(), ccBLACK));
            }
        }
}

void SelectTopping::goNext(){
//    if (selectTopNum==0) {
////        if(PizzaManager::sharedManager()->whichPizza==7){
////            PizzaManager::sharedManager()->tomatoSelected=true;
////            PizzaManager::sharedManager()->xilanhuaSelected=true;
////            PizzaManager::sharedManager()->ganlanyeSelected=true;
////            PizzaManager::sharedManager()->moguSelected=true;
////            PizzaManager::sharedManager()->pepperSelected=true;
////            PizzaManager::sharedManager()->boluoSelected=true;
////            PizzaManager::sharedManager()->bocaiSelected=true;
////            PizzaManager::sharedManager()->selectedNum = 7;
////            for (int i=0; i<7; i++) {
////                PizzaManager::sharedManager()->topping[i] = i;
////            }
////        }else{
////            PizzaManager::sharedManager()->tomatoSelected=true;
////            PizzaManager::sharedManager()->xilanhuaSelected=true;
////            PizzaManager::sharedManager()->ganlanyeSelected=true;
////            PizzaManager::sharedManager()->moguSelected=true;
////            PizzaManager::sharedManager()->pepperSelected=true;
////            PizzaManager::sharedManager()->boluoSelected=true;
////            PizzaManager::sharedManager()->bocaiSelected=true;
////            PizzaManager::sharedManager()->baconsSelected=true;
////            PizzaManager::sharedManager()->meatSelected=true;
////            PizzaManager::sharedManager()->changSelected=true;
////            PizzaManager::sharedManager()->selectedNum = 10;
////            for (int i=0; i<10; i++) {
////                PizzaManager::sharedManager()->topping[i] = i;
////            }
////        }
//        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, BakedPizza::scene(), ccBLACK));
//    }else{
//        CCSprite* done = (CCSprite*)this->getChildByTag(kDone);
//        CCSprite* done2 = (CCSprite*)this->getChildByTag(kDone2);
//        CCPoint pos = done->getPosition();
//        CCSprite* done1 = CCSprite::create("pizza/element/submit.png");
//        done1->setPosition(pos);
//        done1->setTag(kDone1);
//        if (done2) {
//            done2->removeFromParentAndCleanup(true);
//        }
//        this->addChild(done1,2);
//        done->setOpacity(0);
//        if (selectTopNum==1 && selectedTop==2){
//            selectTopNum=0;
//            submit=false;
//            CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, AddTopping::scene(), ccBLACK));
//        }else{
//            selectTopNum=0;
//            submit=false;
//            CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, CutTopping::scene(), ccBLACK));
//        }
//    }
//
//    
////    if(submit){
////        CCSprite* done = (CCSprite*)this->getChildByTag(kDone);
////        CCSprite* done2 = (CCSprite*)this->getChildByTag(kDone2);
////        CCPoint pos = done->getPosition();
////        CCSprite* done1 = CCSprite::create("pizza/element/submit.png");
////        done1->setPosition(pos);
////        done1->setTag(kDone1);
////        if (done2) {
////            done2->removeFromParentAndCleanup(true);
////        }
////        this->addChild(done1,2);
////        done->setOpacity(0);
////        if (selectTopNum==1 && selectedTop==2){
////            selectTopNum=0;
////            submit=false;
////            CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, AddTopping::scene(), ccBLACK));
////        }else{
////            selectTopNum=0;
////            submit=false;
////            CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, CutTopping::scene(), ccBLACK));
////        }
////    }
}

void SelectTopping::showDone(){
    CCSprite* done = CCSprite::create("pizza/element/submit0.png");
    done->setPosition(ccp(center.x, center.y-160));
    done->setTag(kDone2);
    this->addChild(done,3);
}

void SelectTopping::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent){
    
}

void SelectTopping::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent){
    
}

