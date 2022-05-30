//
//  makeDough.cpp
//  Pizza
//
//  Created by LiXiaofei on 3/25/21.
//

#include "MakeDough.h"
#include "SimpleAudioEngine.h"
#include "GameManager.h"
#include "SelectPizza.h"
#include "MakePizza.h"
#include "PizzaManager.h"

using namespace cocos2d;
using namespace CocosDenshion;

enum{
    kBackTouch = 9,
    kIphone = 10,
    kSpoon=11,
    kWater=15,
    kSugar=16,
    kYeast=17,
    kOlive=18,
    kSalt=19,
    kFlour=20,
    kBowl=21,
    kAddFlour=70,
    kAddWater=71,
    kAddSugar=72,
    kAddOli=73,
    kAddSalt=74,
};


CCScene* MakeDough::scene(){
    CCScene* scene = CCScene::create();
    MakeDough* layer = MakeDough::create();
    scene->addChild(layer);
    return  scene;
}

void MakeDough::onEnter(){
    CCLayer::onEnter();
}

void MakeDough::onExit(){
    CCLayer::onExit();
}

MakeDough::MakeDough(){}

MakeDough::~MakeDough(){
    
}

bool MakeDough::init(){
    if (!CCLayer::init()) {
        return false;
    }
    clickBack =false;
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("pizza/animate/pour_water.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("pizza/animate/sugar.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("pizza/animate/oli.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("pizza/animate/salt.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("pizza/animate/pour_flour.plist");
    CCPoint leftTop = GameManager::sharedManager()->getLeftTopPos();
    CCPoint rightTop = GameManager::sharedManager()->getRightTopPos();
    CCPoint visibleOrigin=CCDirector::sharedDirector()->getVisibleOrigin();
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    //背景
    center = GameManager::sharedManager()->getCenter();
    CCSprite* bg = CCSprite::create("background/background.png");
    bg->setPosition(center);
    this->addChild(bg);
    
    //返回按钮
    CCSprite* back=CCSprite::create("background/back.png");
    back->setPosition(ccp(leftTop.x+50,leftTop.y-50));
    back->setTag(kBackTouch);
    this->addChild(back,1);
    
    //桌子
    CCSprite* table = CCSprite::create("background/table.png");
    table->setPosition(ccp(center.x, center.y-260));
    this->addChild(table);
    
    //桌子
    CCSprite* table_side = CCSprite::create("background/table_side.png");
    table_side->setPosition(ccp(center.x, center.y-300));
    this->addChild(table_side);
    
    //面盆
    CCSprite* bowl = CCSprite::create("pizza/element/bowl.png");
    bowl->setPosition(ccp(center.x, center.y-115));
    bowl->setTag(kBowl);
    this->addChild(bowl,5);
    
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
    
    this->showIphone();

    if (!CCUserDefault::sharedUserDefault()->getBoolForKey("purchased")){
        GameManager::sharedManager()->showBanner();
    }
    
//    this->scheduleOnce(schedule_selector(MakeDough::showWater), 0.5f);
    this->scheduleOnce(schedule_selector(MakeDough::showFlour), 0.5f);
    this->setAccelerometerEnabled(true);
    this->setTouchEnabled(true);
    
    return true;
}

void MakeDough::showIphone(){
    if(GameManager::sharedManager()->firstPlayPizza){
//        CCUserDefault::sharedUserDefault()->setBoolForKey("isFirstPizza", false);
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("pizza/animate/iphone.plist");
        CCSprite* iphone = CCSprite::createWithSpriteFrameName("iPhone1.png");
        iphone->setPosition(ccp(center.x+80,center.y+230));
        iphone->setTag(kIphone);
    //    iphone->setScale(1.2);
        iphone->runAction(CCFadeIn::create(0.3));
        this->addChild(iphone,6);
        this->schedule(schedule_selector(MakeDough::showIphoneAction), 1.0f);
    }
}

void MakeDough::showIphoneAction(){
    CCSprite* iphone=(CCSprite*)this->getChildByTag(kIphone);
    CCArray* frame = CCArray::create();
    for (int m =1; m<3; m++) {
        CCString *name = CCString::createWithFormat("iPhone%d.png",m);
        frame->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString()));
    }
        CCAnimation *animation = CCAnimation::createWithSpriteFrames(frame);
        animation->setDelayPerUnit(0.3f);
        CCAnimate *animate = CCAnimate::create(animation);
        iphone->runAction(animate);
}

void MakeDough::canPourWater(){
    isCanPourWater=true;
}

void MakeDough::canPourSugar(){
    isCanPourSugar=true;
}

//void MakeDough::canPourYeast(){
//    isCanPourYeast=true;
//}

void MakeDough::canPourOlive(){
    isCanPourOlive=true;
}

void MakeDough::canPourSalt(){
    isCanPourSalt=true;
}

void MakeDough::canPourFlour(){
    isCanPourFlour=true;
}

void MakeDough::cannotPourWater(){
    isCanPourWater=false;
}

void MakeDough::cannotPourSugar(){
    isCanPourSugar=false;
}

//void MakeDough::cannotPourYeast(){
//    isCanPourYeast=false;
//}

void MakeDough::cannotPourOlive(){
    isCanPourOlive=false;
}

void MakeDough::cannotPourSalt(){
    isCanPourSalt=false;
}

void MakeDough::cannotPourFlour(){
    isCanPourFlour=false;
}

void MakeDough::showWater(){
    
    
        water =CCSprite::createWithSpriteFrameName("pour_water1.png");
        water->setPosition(ccp(center.x-1000,center.y+50));
//        sugar->runAction(CCEaseIn::create(CCMoveTo::create(1.0, ccp(center.x-115,center.y+80)), 0.3f));
        water->runAction(CCSequence::create(CCEaseIn::create(CCMoveTo::create(1.0, ccp(center.x-170,center.y+60)), 0.3f),
                                            CCCallFunc::create(this, callfunc_selector(MakeDough::canPourWater)),
                                            NULL));
        water->setTag(kWater);
        this->addChild(water,9);
}

void MakeDough::showSugar(){
    
    //糖罐
    CCSprite* sugar =CCSprite::createWithSpriteFrameName("sugar1.png");
        sugar->setPosition(ccp(center.x-1000,center.y+50));
//        sugar->runAction(CCEaseIn::create(CCMoveTo::create(1.0, ccp(center.x-115,center.y+80)), 0.3f));
        sugar->runAction(CCSequence::create(CCEaseIn::create(CCMoveTo::create(1.0, ccp(center.x-175,center.y+75)), 0.3f),
                                            CCCallFunc::create(this, callfunc_selector(MakeDough::canPourSugar)),
                                            NULL));
        sugar->setTag(kSugar);
        this->addChild(sugar,9);
}



void MakeDough::showOlive(){
    
  
    CCSprite* olive =CCSprite::createWithSpriteFrameName("oil1.png");
        olive->setPosition(ccp(center.x-1000,center.y+50));
//        sugar->runAction(CCEaseIn::create(CCMoveTo::create(1.0, ccp(center.x-115,center.y+80)), 0.3f));
        olive->runAction(CCSequence::create(CCEaseIn::create(CCMoveTo::create(1.0, ccp(center.x-140,center.y+120)), 0.3f),
                                            CCCallFunc::create(this, callfunc_selector(MakeDough::canPourOlive)),
                                            NULL));
        olive->setTag(kOlive);
        this->addChild(olive,9);
}

void MakeDough::showSalt(){
    
   
    CCSprite* salt =CCSprite::createWithSpriteFrameName("salt1.png");
    salt->setPosition(ccp(center.x-1000,center.y+50));
//        sugar->runAction(CCEaseIn::create(CCMoveTo::create(1.0, ccp(center.x-115,center.y+80)), 0.3f));
    salt->runAction(CCSequence::create(CCEaseIn::create(CCMoveTo::create(1.0, ccp(center.x-160,center.y+80)), 0.3f),
                                            CCCallFunc::create(this, callfunc_selector(MakeDough::canPourSalt)),
                                            NULL));
    salt->setTag(kSalt);
        this->addChild(salt,9);
}

void MakeDough::showFlour(){
    
   
    flourers =CCSprite::createWithSpriteFrameName("pour_flour1.png");
        flourers->setPosition(ccp(center.x-1000,center.y+50));
//        sugar->runAction(CCEaseIn::create(CCMoveTo::create(1.0, ccp(center.x-115,center.y+80)), 0.3f));
        flourers->runAction(CCSequence::create(CCEaseIn::create(CCMoveTo::create(1.0, ccp(center.x-160,center.y+50)), 0.3f),
                                            CCCallFunc::create(this, callfunc_selector(MakeDough::canPourFlour)),
                                            NULL));
        flourers->setTag(kFlour);
        this->addChild(flourers,9);
}

void MakeDough::showSpoon(){
    
    CCSprite* bowl = (CCSprite*)this->getChildByTag(kBowl);
    CCSprite* spoon =CCSprite::create("pizza/element/spoon.png");
    CCPoint pos = bowl->getPosition();
    spoon->setPosition(ccp(bowl->getContentSize().width/1.3,pos.y+800));
    CCFiniteTimeAction *action1=CCSpawn::create(CCRemoveSelf::create(),
                                                CCCallFunc::create(this, callfunc_selector(MakeDough::showSpoon1)),
                                                NULL);
//    spoon->runAction(CCEaseIn::create(CCMoveTo::create(1.0, ccp(bowl->getContentSize().width/2,pos.y+30)), 0.3f));
    
//    CCActionInterval *forwardBy = CCJumpBy::create(0.3, ccp(0,0), 50, 1);
//    CCActionInterval *backBy = forwardBy->reverse();
    
    spoon->runAction(CCSequence::create(CCEaseOut::create(CCMoveTo::create(1.0, ccp(bowl->getContentSize().width/1.3,pos.y+150)), 0.3f),
//                                        CCEaseOut::create(CCMoveTo::create(1.0, ccp(bowl->getContentSize().width/2,pos.y+40)), 0.1f),
//                                        forwardBy,
//                                        CCDelayTime::create(0.5),
//                                        backBy,
//                                        CCMoveTo::create(1.0, ccp(bowl->getContentSize().width/2,pos.y+30)),
                                        action1,
                                        NULL));
//    spoon->setTag(kSpoon);
    bowl->addChild(spoon);
//    spoon->setAnchorPoint(ccp(0.5,0.5));
    spoon->setRotation(20);
}

void MakeDough::showSpoon1(){
    rotation = 20;
    CCSprite* bowl = (CCSprite*)this->getChildByTag(kBowl);
    CCSprite* spoon =CCSprite::create("pizza/element/spoon1.png");
    CCPoint pos = bowl->getPosition();
    spoon->setPosition(ccp(bowl->getContentSize().width/1.3,pos.y+150));
    spoon->setTag(kSpoon);
    bowl->addChild(spoon);
//    bowl->setAnchorPoint(ccp(0.5,0.5));
    spoon->setRotation(20);
    
    CCActionInterval *forwardBy = CCJumpBy::create(0.4, ccp(0,0), 10, 1);
    CCActionInterval *backBy = forwardBy->reverse();
    
    spoon->runAction(CCSequence::create(
//                                        CCEaseOut::create(CCMoveTo::create(1.0, ccp(bowl->getContentSize().width/2,pos.y+40)), 0.1f),
                                        forwardBy,
                                        CCCallFunc::create(this, callfunc_selector(MakeDough::spoonMp3)),
//                                        CCDelayTime::create(0.5),
                                        backBy,
//                                        CCMoveTo::create(1.0, ccp(bowl->getContentSize().width/2,pos.y+30)),
                                        NULL));
}

void MakeDough::spoonMp3(){
    SimpleAudioEngine::sharedEngine()->playEffect("mp3/spoon.mp3");
}

void MakeDough::addFlours(){
    CCSprite* container =(CCSprite*)this->getChildByTag(kBowl);
    CCPoint pos = container->getPosition();
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("pizza/animate/flour.plist");
    //糖罐
    flourers =CCSprite::createWithSpriteFrameName("flour1.png");
    flourers->setPosition(ccp(container->getContentSize().width/2,pos.y-50));
    flourers->setTag(kAddFlour);
    container->addChild(flourers,-5);

    CCArray* frame = CCArray::create();
    for (int i =1; i<4; i++) {
        CCString *name = CCString::createWithFormat("flour%d.png",i);
        frame->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString()));
    }
   
    CCAnimation *animation = CCAnimation::createWithSpriteFrames(frame);
    animation->setDelayPerUnit(0.2f);
    CCAnimate *animate = CCAnimate::create(animation);
    flourers->runAction(animate);
//    SimpleAudioEngine::sharedEngine()->playBackgroundMusic("mp3/poursugar.mp3");
}

void MakeDough::addWater(){
    flourers->removeFromParentAndCleanup(true);
    CCSprite* container =(CCSprite*)this->getChildByTag(kBowl);
    CCPoint pos = container->getPosition();
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("pizza/animate/flour.plist");
    //糖罐
//    CCSprite* water =CCSprite::createWithSpriteFrameName("flour3.png");
//    water->setPosition(ccp(container->getContentSize().width/2,pos.y-50));
//    water->setTag(kAddWater);
//    container->addChild(water,-5);
    
    flourers =CCSprite::createWithSpriteFrameName("flour3.png");
    flourers->setPosition(ccp(container->getContentSize().width/2,pos.y-50));
    flourers->setTag(kAddWater);
    container->addChild(flourers,-5);
//    flourers = CCSprite

    CCArray* frame = CCArray::create();
    for (int i =3; i<5; i++) {
        CCString *name = CCString::createWithFormat("flour%d.png",i);
        frame->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString()));
    }
    CCAnimation *animation = CCAnimation::createWithSpriteFrames(frame);
    animation->setDelayPerUnit(0.2f);
    CCAnimate *animate = CCAnimate::create(animation);
//    water->setTag(kAddWater);
    flourers->runAction(animate);
//    this->removeChildByTag(kAddFlour);
//    SimpleAudioEngine::sharedEngine()->playBackgroundMusic("mp3/pourjuice.mp3");
}

void MakeDough::addSugar(){
    flourers->removeFromParentAndCleanup(true);
    CCSprite* container =(CCSprite*)this->getChildByTag(kBowl);
    CCPoint pos = container->getPosition();
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("pizza/animate/flour.plist");
    //糖罐
//    CCSprite* sugar =CCSprite::createWithSpriteFrameName("flour4.png");
//    sugar->setPosition(ccp(container->getContentSize().width/2,pos.y-50));
//    sugar->setTag(kAddSugar);
//    container->addChild(sugar,-5);
    
    flourers =CCSprite::createWithSpriteFrameName("flour4.png");
    flourers->setPosition(ccp(container->getContentSize().width/2,pos.y-50));
    flourers->setTag(kAddSugar);
    container->addChild(flourers,-5);

    CCArray* frame = CCArray::create();
    for (int i =4; i<6; i++) {
        CCString *name = CCString::createWithFormat("flour%d.png",i);
        frame->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString()));
    }
    CCAnimation *animation = CCAnimation::createWithSpriteFrames(frame);
    animation->setDelayPerUnit(0.2f);
    CCAnimate *animate = CCAnimate::create(animation);
    flourers->runAction(animate);
//    this->removeChildByTag(kAddWater);
//    SimpleAudioEngine::sharedEngine()->playBackgroundMusic("mp3/poursugar.mp3");
}

void MakeDough::addOil(){
    flourers->removeFromParentAndCleanup(true);
    CCSprite* container =(CCSprite*)this->getChildByTag(kBowl);
    CCPoint pos = container->getPosition();
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("pizza/animate/flour.plist");
    //糖罐
//    CCSprite* oil =CCSprite::createWithSpriteFrameName("flour5.png");
//    oil->setPosition(ccp(container->getContentSize().width/2,pos.y-50));
//    oil->setTag(kAddOli);
//    container->addChild(oil,-5);
    
    flourers =CCSprite::createWithSpriteFrameName("flour5.png");
    flourers->setPosition(ccp(container->getContentSize().width/2,pos.y-50));
    flourers->setTag(kAddOli);
    container->addChild(flourers,-5);

    CCArray* frame = CCArray::create();
    for (int i =5; i<7; i++) {
        CCString *name = CCString::createWithFormat("flour%d.png",i);
        frame->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString()));
    }
    CCAnimation *animation = CCAnimation::createWithSpriteFrames(frame);
    animation->setDelayPerUnit(0.2f);
    CCAnimate *animate = CCAnimate::create(animation);
    flourers->runAction(animate);
//    this->removeChildByTag(kAddSugar);
//    SimpleAudioEngine::sharedEngine()->playBackgroundMusic("mp3/poursugar.mp3");
}

void MakeDough::addSalt(){
    flourers->removeFromParentAndCleanup(true);
    CCSprite* container =(CCSprite*)this->getChildByTag(kBowl);
    CCPoint pos = container->getPosition();
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("pizza/animate/flour.plist");
    //糖罐
//    CCSprite* salt =CCSprite::createWithSpriteFrameName("flour6.png");
//    salt->setPosition(ccp(container->getContentSize().width/2,pos.y-50));
//    salt->setTag(kAddSalt);
//    container->addChild(salt,-5);
    flourers =CCSprite::createWithSpriteFrameName("flour6.png");
    flourers->setPosition(ccp(container->getContentSize().width/2,pos.y-50));
    flourers->setTag(kAddSalt);
    container->addChild(flourers,-5);

    CCArray* frame = CCArray::create();
    for (int i =6; i<8; i++) {
        CCString *name = CCString::createWithFormat("flour%d.png",i);
        frame->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString()));
    }
    CCAnimation *animation = CCAnimation::createWithSpriteFrames(frame);
    animation->setDelayPerUnit(0.2f);
    CCAnimate *animate = CCAnimate::create(animation);
//    this->removeChildByTag(kAddOli);
    flourers->runAction(animate);
//    SimpleAudioEngine::sharedEngine()->playBackgroundMusic("mp3/poursugar.mp3");
}

void MakeDough::striMp3(){
    SimpleAudioEngine::sharedEngine()->playEffect("mp3/stir.mp3");
}

void MakeDough::showBowlFlour(){
    CCSprite* container =(CCSprite*)this->getChildByTag(kBowl);
    CCPoint pos = container->getPosition();
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("pizza/animate/flour.plist");
    if(flourers){
        flourers->removeFromParentAndCleanup(true);
        flourers=NULL;
    }
    flours=CCSprite::createWithSpriteFrameName("flour7.png");
    flours->setPosition(ccp(container->getContentSize().width/2,pos.y-50));
    container->addChild(flours,-5);
}

void MakeDough::cannotStirFlour(){
    cannotStir = true;
    stirTimes=0;
}

void MakeDough::striFlour(int index){
//    CCSprite* container =(CCSprite*)this->getChildByTag(kBowl);
//    CCPoint pos = container->getPosition();
//    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("pizza/animate/flour.plist");
//    if(flourers){
//        flourers->removeFromParentAndCleanup(true);
//        flourers=NULL;
//    }
    if (index >=10) {
        index =10;
    }
     
    CCString *name = CCString::createWithFormat("flour%d.png",index);
    CCSpriteFrame*  tomatoAction= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString());
    flours->setDisplayFrame(tomatoAction);
    if (stirTimes%2==0) {
//        flours->runAction(CCCallFunc::create(this, callfunc_selector(MakeDough::striMp3)));
        this->striMp3();
    }
//    this->scheduleOnce(schedule_selector(MakeDough::striMp3), 0.3);
//    if (stirTimes ==5) {
//        flours->runAction(CCSpawn::create(CCCallFunc::create(this, callfunc_selector(MakeDough::goNext)),
//                                             CCCallFunc::create(this, callfunc_selector(MakeDough::cannotStirFlour)),
//                                             NULL));
//    }
//    if (stirTimes <=3 && stirTimes!=0) {
//    //糖罐
//        if (stirTimes==1 && flourIndex==9) {
//            flours =CCSprite::createWithSpriteFrameName("flour7.png");
//        }else if ((stirTimes==2) && flourIndex==10){
//            flours =CCSprite::createWithSpriteFrameName("flour8.png");
//        }else if (stirTimes==3){
//            flours=CCSprite::createWithSpriteFrameName("flour9.png");
//        }
//
//            flours->setPosition(ccp(container->getContentSize().width/2,pos.y-50));
//            container->addChild(flours,-5);
//
//
//            CCArray* frame = CCArray::create();
//            for (int i =flourIndex-2; i<flourIndex; i++) {
//                CCString *name = CCString::createWithFormat("flour%d.png",i);
//                frame->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString()));
//            }
//            CCAnimation *animation = CCAnimation::createWithSpriteFrames(frame);
//            animation->setDelayPerUnit(0.5f);
//            CCAnimate *animate = CCAnimate::create(animation);
//            flours->runAction(CCSpawn::create(animate,
//                                              CCCallFunc::create(this, callfunc_selector(MakeDough::striMp3)),
//                                              NULL));
////        SimpleAudioEngine::sharedEngine()->stopEffect(<#unsigned int nSoundId#>)
//    }else if(stirTimes>3){
//        CCString *name = CCString::createWithFormat("flour%d.png",10);
//        CCSpriteFrame*  tomatoAction= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString());
//        flours->setDisplayFrame(tomatoAction);
//    }
       
   
}

void MakeDough::pourLiquidMp3(){
    SimpleAudioEngine::sharedEngine()->playEffect("mp3/pourjuice.mp3");
}

void MakeDough::pourSolidMp3(){
    SimpleAudioEngine::sharedEngine()->playEffect("mp3/poursugar.mp3");
}


void MakeDough::pourWater(){
    water = (CCSprite*)this->getChildByTag(kWater);
    if (water!=NULL) {
                  CCArray* frame = CCArray::create();
                  for (int i =1; i<7; i++) {
                      CCString *name = CCString::createWithFormat("pour_water%d.png",i);
                      frame->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString()));
                  }
                  CCAnimation *animation = CCAnimation::createWithSpriteFrames(frame);
                  animation->setDelayPerUnit(0.2f);
                  CCAnimate *animate = CCAnimate::create(animation);
        
        
                CCArray* frame1 = CCArray::create();
                for (int i =7; i<12; i++) {
                    CCString *name1 = CCString::createWithFormat("pour_water%d.png",i);
                    frame1->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name1->getCString()));
                }
                CCAnimation *animation1 = CCAnimation::createWithSpriteFrames(frame1);
                animation1->setDelayPerUnit(0.2f);
                CCAnimate *animate1 = CCAnimate::create(animation1);
                  CCFiniteTimeAction *action1=CCSpawn::create(animate,
                                                              CCCallFunc::create(this, callfunc_selector(MakeDough::pourLiquidMp3)),
                                                              CCCallFunc::create(this, callfunc_selector(MakeDough::cannotPourWater)),
//                                                              CCDelayTime::create(1.5),
//                                                              CCCallFunc::create(this, callfunc_selector(MakeDough::addWater)),
                                                              NULL);
        
                water->runAction(CCSequence::create(action1,
                                                    CCCallFunc::create(this, callfunc_selector(MakeDough::addWater)),
                                                    animate1,
    //                                                  CCDelayTime::create(0.3),
                                                      CCEaseOut::create(CCMoveTo::create(1.0, ccp(center.x-800,center.y+50)), 0.3f),
                                                       CCCallFunc::create(this, callfunc_selector(MakeDough::showSugar)),
                                                      NULL));
        isPourWater=true;
        }
}

void MakeDough::pourSugar(){
    sugar = (CCSprite*)this->getChildByTag(kSugar);
    if (sugar!=NULL) {
                  CCArray* frame = CCArray::create();
                  for (int i =1; i<5; i++) {
                      CCString *name = CCString::createWithFormat("sugar%d.png",i);
                      frame->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString()));
                  }
                  CCAnimation *animation = CCAnimation::createWithSpriteFrames(frame);
                  animation->setDelayPerUnit(0.2f);
                  CCAnimate *animate = CCAnimate::create(animation);
        
                CCArray* frame1 = CCArray::create();
                for (int i =5; i<8; i++) {
                    CCString *name1 = CCString::createWithFormat("sugar%d.png",i);
                    frame1->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name1->getCString()));
                }
                CCAnimation *animation1 = CCAnimation::createWithSpriteFrames(frame1);
                animation1->setDelayPerUnit(0.2f);
                CCAnimate *animate1 = CCAnimate::create(animation1);
                  CCFiniteTimeAction *action1=CCSpawn::create(animate,
                                                              CCCallFunc::create(this, callfunc_selector(MakeDough::pourSolidMp3)),
                                                              CCCallFunc::create(this, callfunc_selector(MakeDough::cannotPourSugar)),
                                                              NULL);
                  sugar->runAction(CCSequence::create(action1,
                                                      CCCallFunc::create(this, callfunc_selector(MakeDough::addSugar)),
                                                      animate1,
    //                                                  CCDelayTime::create(0.3),
                                                      CCEaseOut::create(CCMoveTo::create(1.0, ccp(center.x-800,center.y+50)), 0.3f),
//                                                       CCCallFunc::create(this, callfunc_selector(MakeDough::showYeast)),
                                                      CCCallFunc::create(this, callfunc_selector(MakeDough::showOlive)),
                                                      NULL));
        isPourSugar=true;
        }
}


//void MakeDough::pourYeast(){
//    yeast = (CCSprite*)this->getChildByTag(kYeast);
//    if (yeast!=NULL) {
//                  CCArray* frame = CCArray::create();
//                  for (int i =1; i<4; i++) {
//                      CCString *name = CCString::createWithFormat("sugar%d.png",i);
//                      frame->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString()));
//                  }
//                  CCAnimation *animation = CCAnimation::createWithSpriteFrames(frame);
//                  animation->setDelayPerUnit(0.3f);
//                  CCAnimate *animate = CCAnimate::create(animation);
//                  CCFiniteTimeAction *action1=CCSpawn::create(animate,
//                                                              CCCallFunc::create(this, callfunc_selector(MakeDough::pourSolidMp3)),
//                                                              CCCallFunc::create(this, callfunc_selector(MakeDough::cannotPourYeast)),
//                                                              NULL);
//                  yeast->runAction(CCSequence::create(action1,
//    //                                                  CCDelayTime::create(0.3),
//                                                      CCEaseOut::create(CCMoveTo::create(1.0, ccp(center.x-800,center.y+50)), 0.3f),
//                                                       CCCallFunc::create(this, callfunc_selector(MakeDough::showOlive)),
//                                                      NULL));
//        isPourYeast=true;
//           
//        }
//}

void MakeDough::pourOlive(){
    olive = (CCSprite*)this->getChildByTag(kOlive);
    if (olive!=NULL) {
                  CCArray* frame = CCArray::create();
                  for (int i =1; i<3; i++) {
                      CCString *name = CCString::createWithFormat("oil%d.png",i);
                      frame->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString()));
                  }
                  CCAnimation *animation = CCAnimation::createWithSpriteFrames(frame);
                  animation->setDelayPerUnit(0.2f);
                  CCAnimate *animate = CCAnimate::create(animation);
        
                CCArray* frame2 = CCArray::create();
                for (int i =3; i<7; i++) {
                    CCString *name = CCString::createWithFormat("oil%d.png",i);
                    frame2->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString()));
                }
                CCAnimation *animation2 = CCAnimation::createWithSpriteFrames(frame2);
                animation2->setDelayPerUnit(0.2f);
                CCAnimate *animate2 = CCAnimate::create(animation2);
        
                CCArray* frame1 = CCArray::create();
                for (int i =7; i<12; i++) {
                    CCString *name1 = CCString::createWithFormat("oil%d.png",i);
                    frame1->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name1->getCString()));
                }
                CCAnimation *animation1 = CCAnimation::createWithSpriteFrames(frame1);
                animation1->setDelayPerUnit(0.2f);
                CCAnimate *animate1 = CCAnimate::create(animation1);
                  CCFiniteTimeAction *action1=CCSpawn::create(animate2,
                                                              CCCallFunc::create(this, callfunc_selector(MakeDough::pourOliMp3)),
                                                              CCCallFunc::create(this, callfunc_selector(MakeDough::cannotPourOlive)),
                                                              NULL);
        
                  olive->runAction(CCSequence::create(animate,
                                                      action1,
                                                      CCCallFunc::create(this, callfunc_selector(MakeDough::addOil)),
                                                      animate1,
    //                                                  CCDelayTime::create(0.3),
                                                      CCEaseOut::create(CCMoveTo::create(1.0, ccp(center.x-800,center.y+50)), 0.3f),
                                                       CCCallFunc::create(this, callfunc_selector(MakeDough::showSalt)),
                                                      NULL));
        isPourOlive=true;
        }
}

void MakeDough::pourOliMp3(){
    SimpleAudioEngine::sharedEngine()->playEffect("mp3/oli.m4a");
}

void MakeDough::pourSalt(){
    CCSprite* salt = (CCSprite*)this->getChildByTag(kSalt);
    if (salt!=NULL) {
        CCArray* frame = CCArray::create();
        for (int i =1; i<6; i++) {
            CCString *name = CCString::createWithFormat("salt%d.png",i);
            frame->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString()));
        }
        CCAnimation *animation = CCAnimation::createWithSpriteFrames(frame);
        animation->setDelayPerUnit(0.2f);
        CCAnimate *animate = CCAnimate::create(animation);
        
        CCRepeat* repeat = CCRepeat::create(CCSequence::create(animate,
                                                               CCCallFunc::create(this, callfunc_selector(MakeDough::pourSolidMp3)),
//                                                               CCCallFunc::create(this, callfunc_selector(MakeDough::addSalt)),
                                                               NULL),3);
        
        CCFiniteTimeAction *action1=CCSpawn::create(repeat,
                                                    CCCallFunc::create(this, callfunc_selector(MakeDough::cannotPourSalt)),
//                                                    CCDelayTime::create(0.7),
                                                    CCCallFunc::create(this, callfunc_selector(MakeDough::addSalt)),
                                                    NULL);
        salt->runAction(CCSequence::create(action1,
                                           CCCallFunc::create(this, callfunc_selector(MakeDough::showBowlFlour)),
    //                                                  CCDelayTime::create(0.3),
                                           CCEaseOut::create(CCMoveTo::create(1.0, ccp(center.x-800,center.y+50)), 0.3f),
//                                                       CCCallFunc::create(this, callfunc_selector(MakeDough::showFlour)),
                                           CCCallFunc::create(this, callfunc_selector(MakeDough::showSpoon)),
                                                    NULL));
        isPourSalt=true;
           
        }
}

void MakeDough::pourFlour(){
    flour = (CCSprite*)this->getChildByTag(kFlour);
    if (flour!=NULL) {
                  CCArray* frame = CCArray::create();
                  for (int i =1; i<7; i++) {
                      CCString *name = CCString::createWithFormat("pour_flour%d.png",i);
                      frame->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString()));
                  }
                  CCAnimation *animation = CCAnimation::createWithSpriteFrames(frame);
                  animation->setDelayPerUnit(0.2f);
                  CCAnimate *animate = CCAnimate::create(animation);
                CCArray* frame1 = CCArray::create();
                for (int i =7; i<12; i++) {
                    CCString *name1 = CCString::createWithFormat("pour_flour%d.png",i);
                    frame1->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name1->getCString()));
                }
                CCAnimation *animation1 = CCAnimation::createWithSpriteFrames(frame1);
                animation1->setDelayPerUnit(0.2f);
                CCAnimate *animate1 = CCAnimate::create(animation1);
                  CCFiniteTimeAction *action1=CCSpawn::create(animate,
                                                              CCCallFunc::create(this, callfunc_selector(MakeDough::pourSolidMp3)),
                                                              CCCallFunc::create(this, callfunc_selector(MakeDough::cannotPourFlour)),
                                                              
                                                              NULL);
                  flour->runAction(CCSequence::create(action1,
                                                      CCCallFunc::create(this, callfunc_selector(MakeDough::addFlours)),
                                                      animate1,
    //                                                  CCDelayTime::create(0.3),
                                                      CCEaseOut::create(CCMoveTo::create(1.0, ccp(center.x-800,center.y+50)), 0.3f),
                                                      CCDelayTime::create(0.3),
//                                                       CCCallFunc::create(this, callfunc_selector(MakeDough::showSpoon)),
                                                      CCCallFunc::create(this, callfunc_selector(MakeDough::showWater)),
                                                      NULL));
        isPourFlour=true;
           
        }
}



    
void MakeDough::didAccelerate(cocos2d::CCAcceleration *pAccelerationValu){
    gracityX=pAccelerationValu->x;
    if(gracityX>0.25){
        this->unschedule(schedule_selector(MakeDough::showIphoneAction));
        this->removeChildByTag(kIphone);
        if (!isPourWater && isCanPourWater) {
            pourWater();
        }else if (!isPourSugar && isCanPourSugar){
            pourSugar();
        }else if (!isPourOlive && isCanPourOlive){
            pourOlive();
        }else if (!isPourSalt && isCanPourSalt){
            pourSalt();
        }else if (!isPourFlour && isCanPourFlour){
            pourFlour();
        }
    }
}


void MakeDough::clickToBack(){
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.0, SelectPizza::scene(), ccBLACK));
}


void MakeDough::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent){
    CCTouch *pTouch = (CCTouch*)(pTouches->anyObject());
    CCPoint location=CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
    CCSprite* back = (CCSprite*)this->getChildByTag(kBackTouch);
//    CCSprite* originflavor = (CCSprite*)this->getChildByTag(kOriginflavor);
//    beginX = location.x;
    CCSprite* water = (CCSprite*)this->getChildByTag(kWater);
    CCSprite* sugers = (CCSprite*)this->getChildByTag(kSugar);
//    CCSprite* yeast = (CCSprite*)this->getChildByTag(kYeast);
    CCSprite* oliver = (CCSprite*)this->getChildByTag(kOlive);
    CCSprite* salt = (CCSprite*)this->getChildByTag(kSalt);
    CCSprite* flour = (CCSprite*)this->getChildByTag(kFlour);
    CCSprite* bowl = (CCSprite*)this->getChildByTag(kBowl);
    CCSprite* spoon = (CCSprite*)bowl->getChildByTag(kSpoon);
    CCPoint spoonPos =bowl->convertToNodeSpace(location);
    lastPos = spoonPos.x;
    
    
    if (back!=NULL && back->boundingBox().containsPoint(location) && clickBack == false) {
        clickBack=true;
        CCScaleBy* scaleBy = CCScaleBy::create(0.1, 1.2);
        //            homeBtn->setScale(1.2);
        //            touchSprite = homeBtn;
        SimpleAudioEngine::sharedEngine()->playEffect("mp3/touchItem.mp3");
        back->runAction(CCSequence::createWithTwoActions(CCSequence::createWithTwoActions(scaleBy, scaleBy->reverse()), CCCallFunc::create(this, callfunc_selector(MakeDough::clickToBack))));
    }
    if (water!=NULL && water->boundingBox().containsPoint(location) && isCanPourWater) {
        this->cannotPourWater();
        pourWater();
    }else if (sugers!=NULL && sugers->boundingBox().containsPoint(location) && isCanPourSugar){
        this->cannotPourSugar();
        pourSugar();
    }else if (oliver!=NULL && oliver->boundingBox().containsPoint(location) && isCanPourOlive){
        this->cannotPourOlive();
        pourOlive();
    }else if (salt!=NULL && salt->boundingBox().containsPoint(location) && isCanPourSalt){
        this->cannotPourSalt();
        pourSalt();
    }else if (flour!=NULL && flour->boundingBox().containsPoint(location) && isCanPourFlour){
        this->cannotPourFlour();
        pourFlour();
    }
    if(GameManager::sharedManager()->firstPlayPizza){
        this->unschedule(schedule_selector(MakeDough::showIphoneAction));
        this->removeChildByTag(kIphone);
    }

    
    if (spoon != NULL && spoon->boundingBox().containsPoint(spoonPos)) {
        touchSprite = spoon;
    }
    
//    CCLOG("---%f---",spoon->getPosition().x);
}


void MakeDough::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent){
    CCTouch *pTouch = (CCTouch*)(pTouches->anyObject());
    CCPoint location=CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
    CCSprite* bowl = (CCSprite*)this->getChildByTag(kBowl);
    CCSprite* spoon = (CCSprite*)bowl->getChildByTag(kSpoon);
    CCPoint spoonPos =bowl->convertToNodeSpace(location);
//    lastPos = spoonPos.x;
//    CCLOG("---%f---",spoonPos.x);
//    CCLOG("---%f---",location.x);
//    CCLOG("---%f---",bowl->getPosition().x);
//    CCLOG("---%f---",touchSprite->getPosition().x);
//    if (spoon != NULL && spoon->boundingBox().containsPoint(spoonPos)) {
//
        if(touchSprite){
            
//            if ((spoonPos.x < lastPos) ) {
                if (rotation<=15  && rotation!=-15 && rotation>-15 && !subStir) {
//                    if ((lastPos - spoonPos.x)>10) {
                        rotation--;
//                    }
                }else if(rotation<=-15){
//                    stirTimes++;
                    subStir=true;
                    addStir=true;
                    rotation=-15;
                }
//            }else if ((spoonPos.x > lastPos)){
                if (rotation>=-15 && rotation!=15 && rotation<15 &&  addStir) {
//                    if ((spoonPos.x - lastPos)>10) {
                        rotation++;
//                    }
                }else if(rotation>=15){
//                    stirTimes++;
                    addStir=false;
                    subStir = false;
                    rotation=15;
                }
//            }
            
//            if (rotation!=-15) {
//                if ((spoonPos.x < lastPos) ) {
//                    if ((lastPos - spoonPos.x)>=13) {
//                        rotation--;
//                    }
//
//                }
//            }
//

            if (spoonPos.x <= bowl->getContentSize().width/1.9 && spoonPos.x >= bowl->getContentSize().width/2.05 && !stirNum) {
                stirTimes++;
                flourIndex++;
                stirNum =true;
                this->striFlour(flourIndex);
            }else if((spoonPos.x >= bowl->getContentSize().width/1.9 || spoonPos.x <= bowl->getContentSize().width/2.1) && !cannotStir){
                stirNum=false;
            }
            if(spoonPos.x<=bowl->getContentSize().width/1.5 && spoonPos.x >=bowl->getContentSize().width/3.5){
                touchSprite->setPositionX(spoonPos.x);
            }
            touchSprite->setRotation(rotation);
            if (stirTimes ==5) {
                    this->runAction(CCSequence::create(CCCallFunc::create(this, callfunc_selector(MakeDough::cannotStirFlour)),
                                                       CCCallFunc::create(this, callfunc_selector(MakeDough::goNext)),
                                                         NULL));
//                this->scheduleOnce(schedule_selector(MakeDough::cannotStirFlour), 0.3);
            }
//            this->striMp3();
//            this->striFlour(flourIndex);
//            if (stirTimes==1 && flourIndex!=9) {
//                flourIndex=9;
//                this->runAction(CCSequence::create(CCCallFunc::create(this, callfunc_selector(MakeDough::striFlour)),
//                                                   NULL));
//            }else if ((stirTimes==2) && flourIndex!=10) {
//                flourIndex=10;
//                this->runAction(CCSequence::create(CCCallFunc::create(this, callfunc_selector(MakeDough::striFlour)),
//                                                   NULL));
//            }else if (stirTimes>=3) {
////                flourIndex=11;
////                stirTimes=0;
//                this->runAction(CCSequence::create(CCCallFunc::create(this, callfunc_selector(MakeDough::striFlour)),
////                                                   CCDelayTime::create(1.0),
////                                                   CCCallFunc::create(this, callfunc_selector(MakeDough::goNext)),
//                                                   NULL));
//            }
//            if (stirTimes == 5) {
//                stirTimes=0;
//                cannotStir = true;
//                this->goNext();
//            }
        }
//
////        SimpleAudioEngine::sharedEngine()->playEffect("mp3/poursugar.mp3");
//    }
}

void MakeDough::goNext(){
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.5, MakePizza::scene(), ccBLACK));
    SimpleAudioEngine::sharedEngine()->stopAllEffects();
    water = NULL;
    sugar = NULL;
    olive = NULL;
    flours = NULL;
    flour = NULL;
    flourers = NULL;
}


void MakeDough::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent){
    CCTouch *pTouch = (CCTouch*)(pTouches->anyObject());
    CCPoint location=CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
    CCSprite* bowl = (CCSprite*)this->getChildByTag(kBowl);
    CCSprite* spoon = (CCSprite*)bowl->getChildByTag(kSpoon);
    CCPoint spoonPos =bowl->convertToNodeSpace(location);
    if (touchSprite!=NULL) {
        touchSprite=NULL;
        flourIndex=8;
    }
}
