//
//  BakedPizza.cpp
//  Pizza
//
//  Created by LiXiaofei on 4/7/21.
//

#include "BakedPizza.h"
#include "GameManager.h"
#include "PizzaManager.h"
#include "AddTopping.h"
#include "SimpleAudioEngine.h"
#include "CutPizza.h"
#include "MakePizza.h"

using namespace CocosDenshion;

enum{
    kBack = 0,
    kPizza=1,
    kMachine=2,
    kTimebgTag=3,
    kPrograssTag=4,
    kClockTag=5,
    kPrograss1Tag=6,
    kClock1Tag=7,
    kBakeMachine = 10,
    kGuard=11,
    kFireTag = 99,
};

CCScene* BakedPizza::scene(){
    CCScene* scene = CCScene::create();
    BakedPizza* layer = BakedPizza::create();
    scene->addChild(layer);
    return scene;
}

BakedPizza::BakedPizza(){}
BakedPizza::~BakedPizza(){};


void BakedPizza::onEnter(){
    CCLayer::onEnter();
}

void BakedPizza::onExit(){
    CCLayer::onExit();
}


bool BakedPizza::init(){
    if (!CCLayer::init()) {
        return false;
    }
    
    backClick = false;
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("pizza/animate/pick.plist");
    center = GameManager::sharedManager()->getCenter();
    CCPoint visibleOrigin=CCDirector::sharedDirector()->getVisibleOrigin();
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint leftTop = GameManager::sharedManager()->getLeftTopPos();
    //背景
    center = GameManager::sharedManager()->getCenter();
    CCSprite* bg = CCSprite::create("background/bakedbg.png");
    bg->setPosition(center);
    this->addChild(bg);
    
    
    
    if (GameManager::sharedManager()->isIphoneX()) {
        bg->setScale(1.3);
        x_x=80;
    }else if (GameManager::sharedManager()->isAndroidPad()){
        x_x=-55;
    }
    
    CCSprite* machine = CCSprite::create("background/bakedmachine.png");
    machine->setPosition(center);
    machine->setTag(kBakeMachine);
    this->addChild(machine);
    
    //返回按钮
    CCSprite* back=CCSprite::create("background/back.png");
    back->setPosition(ccp(leftTop.x+50,leftTop.y-50));
    back->setTag(kBack);
    this->addChild(back,1);
    
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
    
//    this->addChild(table);
    
//    if(GameManager::sharedManager()->firstPlayPizza){
//        this->playGuaid();
//    }
    if (!CCUserDefault::sharedUserDefault()->getBoolForKey("purchased")){
        GameManager::sharedManager()->showBanner();
    }

    this->scheduleOnce(schedule_selector(BakedPizza::playGuaid), 0.5);
//    this->showPizza();
    this->fireAction();
    this->setTouchEnabled(true);
    return true;
}


void BakedPizza::playGuaid(){
    //手势
    CCSprite* bakeMachine = (CCSprite*)this->getChildByTag(kBakeMachine);
    CCSprite* finger = CCSprite::createWithSpriteFrameName("touch0.png");
    finger->setPosition(ccp(bakeMachine->getPosition().x+200, bakeMachine->getPosition().y-180));
    finger->setTag(kGuard);
    finger->setScale(0.6);
    finger->runAction(CCFadeIn::create(0.3));
    this->addChild(finger,10);
    this->schedule(schedule_selector(BakedPizza::guardAction),1.0f);
}

void BakedPizza::guardAction(){
    CCSprite* finger=(CCSprite*)this->getChildByTag(kGuard);
    CCArray* frame = CCArray::create();
    for (int m =0; m<2; m++) {
        CCString *name = CCString::createWithFormat("touch%d.png",m);
        frame->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString()));
    }
        CCAnimation *animation = CCAnimation::createWithSpriteFrames(frame);
        animation->setDelayPerUnit(0.3f);
        CCAnimate *animate = CCAnimate::create(animation);
//    if(!GameManager::sharedManager()->firstPlay){
        finger->runAction(animate);
//    }
        
}


void BakedPizza::fireAction(){
    CCSprite* bakeMachine = (CCSprite*)this->getChildByTag(kBakeMachine);
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("pizza/animate/fire.plist");
    CCSprite* fire = CCSprite::createWithSpriteFrameName("fire1.png");
    fire->setScale(1.15);
    fire->setTag(kFireTag);
    fire->setPosition(ccp(bakeMachine->getPosition().x-x_x, bakeMachine->getPosition().y-70));
    CCArray* frame = CCArray::create();
    for (int i =1; i<4; i++) {
        CCString *name = CCString::createWithFormat("fire%d.png",i);
        frame->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString()));
    }
    CCAnimation *animation = CCAnimation::createWithSpriteFrames(frame);
    animation->setDelayPerUnit(0.2f);
    CCAnimate *animate = CCAnimate::create(animation);
//    CCRepeatForever::create(animate);
    fire->runAction(CCRepeatForever::create(animate));
    bakeMachine->addChild(fire);
    this->showPizza();
//    this->playFireBakeMp3();
}

void BakedPizza::playFireBakeMp3(){
//    SimpleAudioEngine::sharedEngine()->playBackgroundMusic("mp3/fire.m4a",true);
    SimpleAudioEngine::sharedEngine()->playEffect("mp3/fire.m4a",true);
}

void BakedPizza::showPizza(){
    CCSprite* bakeMachine = (CCSprite*)this->getChildByTag(kBakeMachine);
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("pizza/animate/baked_pizza.plist");
    pizza = CCSprite::createWithSpriteFrameName("baked_pizza1.png");
    pizza->setScale(2);
    pizza->setTag(kPizza);
    pizza->setPosition(ccp(bakeMachine->getPosition().x-x_x, bakeMachine->getPosition().y-162));
    bakeMachine->addChild(pizza,1);
    
    CCSprite* pizzaPlate = CCSprite::create("background/bakeboard.png");
    pizzaPlate->setPosition(ccp(pizza->getContentSize().width/2,-3));
    pizza->addChild(pizzaPlate,1);
}

void BakedPizza::pizzaAction(){
    CCSprite* bakeMachine = (CCSprite*)this->getChildByTag(kBakeMachine);
    pizza = (CCSprite*)bakeMachine->getChildByTag(kPizza);
    if (pizza!=NULL) {
        CCArray* frame = CCArray::create();
        for (int i =1; i<4; i++) {
            CCString *name = CCString::createWithFormat("baked_pizza%d.png",i);
            frame->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString()));
        }
        CCAnimation *animation = CCAnimation::createWithSpriteFrames(frame);
        animation->setDelayPerUnit(1.5f);
        CCAnimate *animate = CCAnimate::create(animation);
        CCFiniteTimeAction *action = CCSpawn::create(CCCallFunc::create(this, callfunc_selector(BakedPizza::playFireBakeMp3)),
                                                      NULL);
        CCRepeat* repeat = CCRepeat::create(action, 2);
        
        CCFiniteTimeAction *action1 = CCSpawn::create(CCCallFunc::create(this, callfunc_selector(BakedPizza::showTime)),
                                                      repeat,
                                                      NULL);
        
        CCFiniteTimeAction *action2 = CCSpawn::create(CCScaleTo::create(0.4, 1.3),
                                                      CCCallFunc::create(this, callfunc_selector(BakedPizza::bakeMp3)),
                                                      NULL);
        pizza->runAction(CCSequence::create(action2,
                                            action1,
                                            CCDelayTime::create(0.5),
                                            CCCallFunc::create(this, callfunc_selector(BakedPizza::showSteam)),
                                            animate,
                                            NULL));
        
    }
}

void BakedPizza::bakeMp3(){
    SimpleAudioEngine::sharedEngine()->playEffect("mp3/bakepizza.mp3");
}

void BakedPizza::showSteam(){
    CCSprite* bakeMachine = (CCSprite*)this->getChildByTag(kBakeMachine);
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("pizza/animate/baked_pizza.plist");
    CCSprite* steams = CCSprite::create("pizza/element/steam.png");
    steams->setScale(0.5);
//    steams->setTag(kPizza);
//    steams->setOpacity(0.9);
    steams->setPosition(ccp(bakeMachine->getPosition().x-x_x, bakeMachine->getPosition().y-10));
//    CCFiniteTimeAction *action1 = CCSequence::create(CCScaleTo::create(0.5, 0.5),
//                                                     CCCallFunc::create(this, callfunc_selector(BakedPizza::showSteam1)),
//                                                     CCScaleTo::create(0.8, 0.6),
//                                                     CCScaleTo::create(0.5, 0.5),
//                                                     CCCallFuncN::create(this, callfuncN_selector(BakedPizza::removeSteam)),
//                                                     NULL);
    CCRepeat* repeat = CCRepeat::create(CCSequence::create(CCCallFuncN::create(this, callfuncN_selector(BakedPizza::canShowSteam)),
                                                           CCScaleTo::create(0.4, 0.5),
//                                                           CCCallFunc::create(this, callfunc_selector(BakedPizza::showSteam1)),
                                                           CCScaleTo::create(0.5, 0.6),
                                                           CCScaleTo::create(0.4, 0.5),
                                                           CCCallFuncN::create(this, callfuncN_selector(BakedPizza::removeSteam)),
                                                           NULL),3);
    steams->runAction(CCSpawn::create(repeat,
                                      CCCallFunc::create(this, callfunc_selector(BakedPizza::showSteam1)),
                                      NULL));
    bakeMachine->addChild(steams,1);
}

void BakedPizza::showSteam1(){
    CCSprite* bakeMachine = (CCSprite*)this->getChildByTag(kBakeMachine);
    CCSprite* steams1 = CCSprite::create("pizza/element/steam.png");
    steams1->setScale(0.5);
//    steams->setTag(kPizza);
//    steams1->setScale(0.3);
//    steams1->setOpacity(0.9);
    steams1->setPosition(ccp(bakeMachine->getPosition().x-50-x_x, bakeMachine->getPosition().y-70));
//    CCFiniteTimeAction *action2 = CCSequence::create(CCScaleTo::create(0.5, 0.5),
//                                                     CCCallFunc::create(this, callfunc_selector(BakedPizza::showSteam2)),
//                                                     CCScaleTo::create(0.8, 0.6),
//                                                     CCScaleTo::create(0.5, 0.5),
//                                                     CCCallFuncN::create(this, callfuncN_selector(BakedPizza::removeSteam)),
//                                                     NULL);
    CCRepeat* repeat1 = CCRepeat::create(CCSequence::create(CCCallFuncN::create(this, callfuncN_selector(BakedPizza::canShowSteam)),
                                                            CCScaleTo::create(0.4, 0.5),
                                                            CCScaleTo::create(0.5, 0.6),
                                                            CCScaleTo::create(0.4, 0.5),
                                                            CCCallFuncN::create(this, callfuncN_selector(BakedPizza::removeSteam)),
                                                            NULL),3);
    steams1->runAction(CCSpawn::create(repeat1,
                                       CCCallFunc::create(this, callfunc_selector(BakedPizza::showSteam2)),
                                       NULL));
    bakeMachine->addChild(steams1,1);
}

void BakedPizza::showSteam2(){
    CCSprite* bakeMachine = (CCSprite*)this->getChildByTag(kBakeMachine);
    CCSprite* steams2 = CCSprite::create("pizza/element/steam.png");
    steams2->setScale(0.5);
//    steams->setTag(kPizza);
//    steams2->setScale(0.3);
//    steams2->setOpacity(0.9);
    steams2->setPosition(ccp(bakeMachine->getPosition().x+50-x_x, bakeMachine->getPosition().y-70));
//    CCFiniteTimeAction *action3 = CCSequence::create(CCScaleTo::create(0.5, 0.5),
//                                                     CCScaleTo::create(0.8, 0.6),
//                                                     CCScaleTo::create(0.5, 0.5),
//                                                     CCCallFuncN::create(this, callfuncN_selector(BakedPizza::removeSteam)),
//                                                     NULL);
    CCRepeat* repeat2 = CCRepeat::create(CCSequence::create(CCCallFuncN::create(this, callfuncN_selector(BakedPizza::canShowSteam)),
                                                            CCScaleTo::create(0.4, 0.5),
                                                            CCScaleTo::create(0.5, 0.6),
                                                            CCScaleTo::create(0.4, 0.5),
                                                            CCCallFuncN::create(this, callfuncN_selector(BakedPizza::removeSteam)),
                                                           NULL),3);
    steams2->runAction(repeat2);
    bakeMachine->addChild(steams2,1);
}

void BakedPizza::removeSteam(CCObject *pSender){
    CCSprite* sprite = (CCSprite*)pSender;
    if (sprite) {
        sprite->setVisible(false);
    }
}

void BakedPizza::canShowSteam(CCObject *pSender){
    CCSprite* sprite = (CCSprite*)pSender;
    if (sprite) {
        sprite->setVisible(true);
    }
}

void BakedPizza::showTime(){
    time_bg = CCSprite::create("pizza/element/circle_black.png");
    time_bg->setPosition(ccp(center.x+150, center.y+100));
    time_bg->setTag(kTimebgTag);
    this->addChild(time_bg,99);
    
    CCSprite* pSprite = CCSprite::create("pizza/element/circle_green.png");
    progress = CCProgressTimer::create(pSprite);
    progress->setPosition(ccp(center.x+150, center.y+100));
    progress->setTag(kPrograss1Tag);
    progress->setType(kCCProgressTimerTypeRadial);
    progress->setPercentage(0);
    progress->setReverseProgress(false);
    
    CCProgressFromTo* time1 = CCProgressFromTo::create(5.0f, 0, 100);
    progress->runAction(CCSequence::create(time1,
                                           CCCallFunc::create(this, callfunc_selector(BakedPizza::bakeDone)),
//                                           CCCallFunc::create(this, callfunc_selector(BakedPizza::showTime1)),
                                           NULL));
    this->addChild(progress,100);
//    this->scheduleOnce(schedule_selector(BakedPizza::bakeDone), 5.0);
    clock = CCSprite::create("pizza/element/circle_clock.png");
    clock->setPosition(ccp(center.x+150, center.y+100));
    clock->setTag(kClock1Tag);
    this->addChild(clock,100);
}

void BakedPizza::showTime1(){
    CCSprite* pSprite = CCSprite::create("pizza/element/circle_red.png");
    progress = CCProgressTimer::create(pSprite);
    progress->setPosition(ccp(center.x+150, center.y+100));
    progress->setType(kCCProgressTimerTypeRadial);
    progress->setPercentage(0);
    progress->setTag(kPrograssTag);
    progress->setReverseProgress(false);
    
    CCProgressFromTo* time1 = CCProgressFromTo::create(5.0f, 0, 100);
    progress->runAction(CCSequence::create(time1,
                                           NULL));
    this->addChild(progress,110);
    clock = CCSprite::create("pizza/element/circle_clock.png");
    clock->setPosition(ccp(center.x+150, center.y+100));
    clock->setTag(kClockTag);
    this->addChild(clock,110);
}



void BakedPizza::removeTime(){
    this->removeChildByTag(kTimebgTag);
    this->removeChildByTag(kPrograssTag);
    this->removeChildByTag(kClockTag);
    this->removeChildByTag(kPrograss1Tag);
    this->removeChildByTag(kClock1Tag);
//    this->removeFromParent();
}

void BakedPizza::bakeDone(){
    SimpleAudioEngine::sharedEngine()->playEffect("mp3/done.mp3");
    bakeFinish=true;
    this->goNext();
}

void BakedPizza::goNext(){
//    SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->stopAllEffects();
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, CutPizza::scene(), ccBLACK));
}

void BakedPizza::clickBack(){
    if (PizzaManager::sharedManager()->whichPizza != 1) {
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, AddTopping::scene(), ccBLACK));
    }else{
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, MakePizza::scene(), ccBLACK));
    }
}

void BakedPizza::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent){
    CCTouch *pTouch = (CCTouch*)(pTouches->anyObject());
    CCPoint location = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
    CCSprite* bakeMachine = (CCSprite*)this->getChildByTag(kBakeMachine);
    CCSprite* fire = (CCSprite*)bakeMachine->getChildByTag(kFireTag);
    CCSprite* pizza = (CCSprite*)bakeMachine->getChildByTag(kPizza);
    CCPoint pizzaPos =bakeMachine->convertToNodeSpace(location);
    CCSprite* back = (CCSprite*)this->getChildByTag(kBack);
    this->unschedule(schedule_selector(BakedPizza::guardAction));
    this->removeChildByTag(kGuard);
    if (((pizza && pizza->boundingBox().containsPoint(pizzaPos)) || (fire && fire->boundingBox().containsPoint(pizzaPos))) && !touchPizza) {
        touchPizza=true;
        this->pizzaAction();
        
        CCUserDefault::sharedUserDefault()->setBoolForKey("isFirstPizza", false);
        GameManager::sharedManager()->firstPlayPizza=false;
    }
    
    if (back!=NULL && back->boundingBox().containsPoint(location) && backClick == false) {
        backClick = true;
        SimpleAudioEngine::sharedEngine()->stopAllEffects();
//        SimpleAudioEngine::sharedEngine()->playEffect("mp3/done.mp3");
//        PizzaManager::sharedManager()->cleanAllSprite();
        CCScaleBy* scaleBy = CCScaleBy::create(0.1, 1.2);
        //            homeBtn->setScale(1.2);
        //            touchSprite = homeBtn;
        SimpleAudioEngine::sharedEngine()->playEffect("mp3/touchItem.mp3");
        back->runAction(CCSequence::createWithTwoActions(CCSequence::createWithTwoActions(scaleBy, scaleBy->reverse()), CCCallFunc::create(this, callfunc_selector(BakedPizza::clickBack))));
//        PizzaManager::sharedManager()->cleanAllSprite();
    }
//    if (machine!=NULL && machine->boundingBox().containsPoint(location) && bakeComplate && bakeFinish) {
//        CCFiniteTimeAction *action = CCSpawn::create(CCMoveTo::create(0.3, ccp(center.x-250,center.y-100)),
//                                                     CCCallFunc::create(this, callfunc_selector(BakedPizza::removeTime)),
//                                                     NULL);
//        pizza->runAction(CCSequence::create(action,
//                                            CCDelayTime::create(0.5),
//                                            CCCallFunc::create(this, callfunc_selector(BakedPizza::goNext)),
//                                            NULL));
//        bakeFinish=false;
////        this->removeTime();
//    }
}

void BakedPizza::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent){
    CCTouch *pTouch = (CCTouch*)(pTouches->anyObject());
    CCPoint location = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
    CCSprite* pizza = (CCSprite*)this->getChildByTag(kPizza);
    if (pizza!=NULL && pizza->boundingBox().containsPoint(location) && !bakeComplate) {
        if (originalPosition.x <location.x) {
            pizza->setPositionX(location.x);
            originalPosition = location;
        }
        
    }
}

void BakedPizza::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent){
    CCTouch *pTouch = (CCTouch*)(pTouches->anyObject());
    CCPoint location = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
    CCSprite* machine = (CCSprite*)this->getChildByTag(kMachine);
    CCSprite* pizza = (CCSprite*)this->getChildByTag(kPizza);
//    float rectWidth = 40;
//    float rectHeight = 40;
//    float storeWidth = 400;
//    float storeHeight = 200;
//    CCRect rect1 = this->createRectByPoint(pizza->getPosition(), rectWidth, rectHeight);
//    CCRect rect2 = this->createRectByPoint(machine->getPosition(), storeWidth, storeHeight);
//    if (rect1.intersectsRect(rect2) && !bakeComplate) {
//        bakeComplate=true;
////        this->removeChildByTag(kPizza);
//        this->runAction(CCSequence::create(CCFadeIn::create(0.1),
//                                           CCCallFunc::create(this, callfunc_selector(BakedPizza::showTime)),
//                                           NULL));
//    }else if(!bakeComplate){
//        pizza->runAction(CCMoveTo::create(0.3, ccp(center.x-250,center.y-100)));
//    }
    
}


CCRect BakedPizza::createRectByPoint(CCPoint point, float width, float height){
    return CCRectMake(point.x-width/2,point.y-height/2,width,height);       //CCRectMake(x,y,width,height)；x,矩形左下角x坐标；y，矩形左下角y坐标；width，矩形宽度；height，矩形高度
}
