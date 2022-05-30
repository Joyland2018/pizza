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

using namespace CocosDenshion;

enum{
    kBack=0,
    kTopping=10,
    kDone=1,
    kDone1 = 2,
    kDone2 = 3,
    kSelectTag = 100,
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
    
    clickBack = false;
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
        x_x=100;
    }else if(GameManager::sharedManager()->isAndroidPad()){
        x_x=-40;
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


    if (!CCUserDefault::sharedUserDefault()->getBoolForKey("purchased")){
        GameManager::sharedManager()->showBanner();
    }
    
    
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
    if (back!=NULL && back->boundingBox().containsPoint(location) && clickBack==false) {
//        SimpleAudioEngine::sharedEngine()->playEffect("mp3/done.mp3");
        clickBack = true;
        PizzaManager::sharedManager()->cleanAllSprite();
        CCScaleBy* scaleBy = CCScaleBy::create(0.1, 1.2);
        //            homeBtn->setScale(1.2);
        //            touchSprite = homeBtn;
        SimpleAudioEngine::sharedEngine()->playEffect("mp3/touchItem.mp3");
        back->runAction(CCSequence::createWithTwoActions(CCSequence::createWithTwoActions(scaleBy, scaleBy->reverse()), CCCallFunc::create(this, callfunc_selector(SelectTopping::clickToBack))));
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
                        done->setOpacity(1);
                        
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

