//
//  SelectPizza.cpp
//  Pizza
//
//  Created by LiXiaofei on 3/24/21.
//

#include "SelectPizza.h"
#include "GameManager.h"
#include "MakeDough.h"
#include "SimpleAudioEngine.h"
#include "PizzaManager.h"
//#include "DeviceManager.h"
//#include "DinoTownScene.h"
#include "FirstScene.h"
#include "BuyPage.h"
#include "MakeSauce.h"
#include "MakePizza.h"
#include "AddTopping.h"
using namespace cocos2d;
using namespace CocosDenshion;

enum{
    kBackground = 0,
    kBack = 1,
    kTaste=5,
    kLockTag=10,
    kBuylayerTag = 900,
};

CCScene* SelectPizza::scene(){
    CCScene* scene = CCScene::create();
    SelectPizza* layer = SelectPizza::create();
    scene->addChild(layer);
    return  scene;
}

void SelectPizza::onEnter(){
    CCLayer::onEnter();
}

void SelectPizza::onExit(){
    CCLayer::onExit();
}

SelectPizza::SelectPizza(){
    
}

SelectPizza::~SelectPizza(){
}


bool SelectPizza::init(){
    if (!CCLayer::init()) {
        return false;
    }
    
    backClick = false;
    selectedPizza = false;
    CCPoint center = GameManager::sharedManager()->getCenter();
    CCPoint leftTop = GameManager::sharedManager()->getLeftTopPos();
    CCPoint rightTop = GameManager::sharedManager()->getRightTopPos();
    
    //返回按钮
    CCSprite* back=CCSprite::create("background/back.png");
    back->setPosition(ccp(leftTop.x+50,leftTop.y-50));
    back->setTag(kBack);
    this->addChild(back,1);
    
    CCSprite* bg = CCSprite::create("background/background.png");
    bg->setPosition(center);
    bg->setTag(kBackground);
    this->addChild(bg);
    
    if (GameManager::sharedManager()->isIphoneX()) {
        bg->setScale(1.3);
        x_x=-100;
    }
    
    if (GameManager::sharedManager()->isAndroidPad()) {
        x_x = 40;
    }
    
    this->setTouchEnabled(true);
    this->showPizzaTaste();
    return true;
}

void SelectPizza::addLock(cocos2d::CCSprite *pSprite, cocos2d::CCSize spriteSize){
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    CCSprite* lock = CCSprite::create("iap/lock.png");
    lock->setPosition(ccp(spriteSize.width*0.5, spriteSize.height*0.5));
    lock->setScale(0.7);
    lock->setTag(kLockTag);
    pSprite->addChild(lock);
//    pSprite->setColor(ccc3(200, 200, 200)) ;
//#endif
}

void SelectPizza::showPizzaTaste(){
    int index=0;
    tasteNameArr = CCArray::create();
    char taste[][20] = {"pepperoni","cheese","candy","cheeses","halloween","Hawaii","christmas","vegetables","Supreme"};
    int count = 0;
    while (count < 9) {
        CCString* strName = CCString::create(taste[count]);
        tasteNameArr->addObject(strName);
        count++;
    }
    CC_SAFE_RETAIN(tasteNameArr);
    for (int i =0; i<9; i++) {
        CCString* tasteStr = CCString::createWithFormat("background/%s.png",((CCString*)tasteNameArr->objectAtIndex(i))->getCString());
        CCSprite* taste = CCSprite::create(tasteStr->getCString());
        taste->setScale(0.7);
        
        //万圣节
//        if (i==4) {
//            index=0;
//        }else if(i>4){
//            index=i;
//        }else{
//            index=i+1;
//        }
        //万圣节
//        if (i<3) {
        //圣诞节
//        if (i==6) {
//            index=0;
//        }else if(i>6){
//            index=i;
//        }else{
//            index=i+1;
//        }
            taste->setPosition(ccp(300+(i%3)*(305-x_x), 510-(i/3)*190));
//        }else if(i>=3){
//            taste->setPosition(ccp(280+(i-3)*(320-x_x), 190));
//        }
        if (GameManager::sharedManager()->isAndroidPad()) {
            taste->setScale(0.7);
        }
        taste->setTag(kTaste+i);
        this->addChild(taste);
        CCLog("---%d---",PizzaManager::sharedManager()->havePlay);
        if (CCUserDefault::sharedUserDefault()->getBoolForKey("UnlockAll") == false && !CCUserDefault::sharedUserDefault()->getBoolForKey("purchased")){
//            if (PizzaManager::sharedManager()->havePlay) {
                if (i>0) {
                    this->addLock(taste, taste->getContentSize());
                }
//            }else if(!PizzaManager::sharedManager()->havePlay){
//                this->addLock(taste, taste->getContentSize());
//            }
        }
    }
}

void SelectPizza::openIAPPage(){
    
    this->showIAPPage(2);
}

void SelectPizza::showIAPPage(int _index){
    CCPoint center = GameManager::getCenter();
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCLayer* buyLayer = (CCLayer*)this->getChildByTag(kBuylayerTag);
    if (buyLayer == NULL) {
        SimpleAudioEngine::sharedEngine()->playEffect("universal/pressBt.mp3");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        buyLayer = (CCLayer*)BuyLayer::nodeWithID(_index);
#else
        buyLayer = (CCLayer*)BuyPage::nodeWithID(_index);
#endif
        buyLayer->setTag(kBuylayerTag);
        this->addChild(buyLayer, 999);
        CCLayerColor *blacklayer = CCLayerColor::create(ccc4(0, 0, 0, 180), winSize.width, winSize.height);
        blacklayer->ignoreAnchorPointForPosition(false);
        blacklayer->setPosition(center);
        buyLayer->addChild(blacklayer,-1);
    }
}

void SelectPizza::clickBack(){
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, FirstScene::scene(), ccBLACK));
}

void SelectPizza::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent){
    CCTouch *pTouch = (CCTouch*)(pTouches->anyObject());
    CCPoint location = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
    CCSprite* back = (CCSprite*)this->getChildByTag(kBack);
    if (back!=NULL && back->boundingBox().containsPoint(location) && backClick==false) {
        backClick = true;
        CCScaleBy* scaleBy = CCScaleBy::create(0.1, 1.2);
        //            homeBtn->setScale(1.2);
        //            touchSprite = homeBtn;
        SimpleAudioEngine::sharedEngine()->playEffect("mp3/touchItem.mp3");
        back->runAction(CCSequence::createWithTwoActions(CCSequence::createWithTwoActions(scaleBy, scaleBy->reverse()), CCCallFunc::create(this, callfunc_selector(SelectPizza::clickBack))));
    }else{
        for (int i = 0; i<9; i++) {
            CCSprite* pizzaTaste = (CCSprite*)this->getChildByTag(kTaste+i);
            if (pizzaTaste!=NULL && pizzaTaste->boundingBox().containsPoint(location) && selectedPizza==false) {
                
                if ((i==0 || CCUserDefault::sharedUserDefault()->getBoolForKey("UnlockAll") == true || CCUserDefault::sharedUserDefault()->getBoolForKey("purchased"))) {
                    SimpleAudioEngine::sharedEngine()->playEffect("mp3/touchItem.mp3");
                    pizzaTaste->runAction(CCSequence::create(CCScaleTo::create(0.2, 0.9),
                                                             CCScaleTo::create(0.2, 0.7),
                                                             CCCallFunc::create(this, callfunc_selector(SelectPizza::goToNext)),
                                                             NULL));
//                    if (i==0) {
//                        PizzaManager::sharedManager()->whichPizza = 6;
//                    }else if(i>6){
                        PizzaManager::sharedManager()->whichPizza = i;
//                    }else{
//                        PizzaManager::sharedManager()->whichPizza = i-1;
//                    }
                    selectedPizza = true;
                }else{
                    this->openIAPPage();
                }
                
            }
        }
    }
    
    
}

void SelectPizza::goToNext(){
    selectedPizza = false;
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.0, MakeDough::scene(), ccBLACK));
//    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.0, AddTopping::scene(), ccBLACK));
}

void SelectPizza::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent){
    
}

void SelectPizza::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent){}
