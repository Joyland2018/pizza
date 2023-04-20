//
//  MakeSauce.cpp
//  DrDino
//
//  Created by LiXiaofei on 9/1/21.
//

#include "MakeSauce.h"
#include "CutTopping.h"
#include "SimpleAudioEngine.h"
#include "GameManager.h"
#include "SelectTopping.h"
#include "MakePizza.h"
#include "PizzaManager.h"
#include "AddTopping.h"
#include "MakePizza.h"
#include "CutMaterial.h"


using namespace CocosDenshion;

enum{
    kBack=0,
    kCandy = 1,
    kHalloweenn = 11,
    kChristmas = 21,
    kMilk = 50,
    kPot =55,
    kPot1 = 56,
    kSauce = 660,
    kSpoon = 99,
    kNewSprite = 70,
    kMilkPot=80,
    kVegBoardTag = 141,
    kNextTag = 199,
};

CCScene* MakeSauce::scene(){
    CCScene* scene = CCScene::create();
    MakeSauce* layer = MakeSauce::create();
    scene->addChild(layer);
    return scene;
}

void MakeSauce::onEnter(){
    CCLayer::onEnter();
}

void MakeSauce::onExit(){
    CCLayer::onExit();
}

MakeSauce::MakeSauce(){}
MakeSauce::~MakeSauce(){}

bool MakeSauce::init(){
    if (!CCLayer::init()) {
        return false;
    }
    clickNext = false;
    backClick=false;
    touchOther = true;
    touchIndex=0;
    newSpriteIndex=0;
    rotation=0;
    originRotation=0;
    sauceIndex=0;
    newSpriteTag=0;
    beginPos=0;
    endPos=0;
    milkIndex=0;
    MaterialIndex=0;
    whichMaterial=0;
    cutNum=1;
    
    touchedMilk=false;
    fireOn = false;
    canStri = false;
    subStir=false;
    addStir = false;
    stirNum = false;
    touchOther = true;
    touchSprite= NULL;
    touchSpoon = NULL;
    touchMilk=false;
    CCPoint visibleOrigin=CCDirector::sharedDirector()->getVisibleOrigin();
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    center = GameManager::sharedManager()->getCenter();
    CCPoint leftTop = GameManager::sharedManager()->getLeftTopPos();
    CCPoint rightTop = GameManager::sharedManager()->getRightTopPos();
    CCPoint leftBottomPos = GameManager::sharedManager()->getLeftBottomPos();
    
    for (int i=1; i<4; i++) {
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(CCString::createWithFormat("pizza/animate/candy/candy%d.plist",i)->getCString());
    }
    
    CCSprite* bg = CCSprite::create("background/bg2.png");
    bg->setPosition(center);
    this->addChild(bg);
    
    if(GameManager::sharedManager()->isIphoneX()){
        bg->setScale(1.3);
    }
    
//    CCSprite* pot = CCSprite::create("pizza/element/pot.png");
//    pot->setPosition(ccp(center.x-200, center.y));
//    pot->setTag(kPot1);
//    this->addChild(pot);
    fileName="";
    
    CCSprite* back = CCSprite::create("background/back.png");
    back->setPosition(ccp(leftTop.x+50,leftTop.y-50));
    back->setTag(kBack);
    this->addChild(back);
    
    this->setTouchEnabled(true);
    
    
    CCSprite* money = CCSprite::create("background/money.png");
    money->setPosition(ccp(visibleOrigin.x+visibleSize.width-100, visibleSize.height-50));
//    money->setTag(kMoney);
//    this->addChild(money,10);
    
    CCString* curscore = CCString::createWithFormat("%d",GameManager::sharedManager()->getCurrentCoin());
    const char* curscores = curscore->getCString();
    curallscores = CCLabelTTF::create(curscores, "Arial", 28);
    curallscores->setColor(ccWHITE);
//    curallscores->setTag(100);
    curallscores->setPosition(ccp(visibleOrigin.x+visibleSize.width-70, visibleSize.height-50));
//    this->addChild(curallscores,11);
    
    CCSprite* next = CCSprite::create("background/next.png");
    next->setPosition(ccp(rightTop.x-50,rightTop.y-50));
    next->setTag(kNextTag);
    this->addChild(next);
    
    if(GameManager::sharedManager()->firstPlayPizza){
//        this->schedule(schedule_selector(MakeSauce::showFinger),1.5f);
    }
    
    if (PizzaManager::sharedManager()->whichPizza==2) {
        candyMaterial();
    }else if (PizzaManager::sharedManager()->whichPizza==4) {
        halloweenMaterial();
    }else if (PizzaManager::sharedManager()->whichPizza==6) {
        christmasMaterial();
    }
    
    if(GameManager::sharedManager()->firstPizzaSauce){
        this->schedule(schedule_selector(MakeSauce::showFinger),1.5f);
//    }else{
//        canTouchOther();
    }
    this->showPot();
    
    CCSprite* vegBoard = CCSprite::create("background/toppings-board.png");
    vegBoard->setPosition(ccp(center.x, leftBottomPos.y+100));
    vegBoard->setScale(1.2);
    vegBoard->setTag(kVegBoardTag);
//    this->addChild(vegBoard);
    
    this->setTouchEnabled(true);
    return true;
}

void MakeSauce::showPot(){
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("pizza/animate/pot.plist");
    CCSprite* pot =CCSprite::createWithSpriteFrameName("pot1.png");
    pot->setPosition(ccp(center.x, center.y+80));
    pot->setTag(kPot);
    this->addChild(pot);
    
}

void MakeSauce::potActoion(){
//    if (index >=2) {
//        index = 2;
//    }
    SimpleAudioEngine::sharedEngine()->playEffect("mp3/foodStart.mp3");
    CCSprite* pot = (CCSprite*)this->getChildByTag(kPot);
    if (pot!=NULL) {
        CCString *name =CCString::createWithFormat("pot2.png");
    //    CCString *name = CCString::createWithFormat("sauce_%d.png",index+2);
        CCSpriteFrame* potAction= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString());
        pot->setDisplayFrame(potAction);
        fireOn=true;
    }

//    fireOnMp3();
}

//void MakeSauce::fireOnMp3(){
//    SimpleAudioEngine::sharedEngine()->playEffect("mp3/foodStart.mp3");
//}

void MakeSauce::showFinger(){
    CCPoint leftBottomPos = GameManager::sharedManager()->getLeftBottomPos();
    float xDis = 0.0;
    if (whichMaterial==2) {
        xDis=-120;
    }else if(whichMaterial==3){
        xDis=0;
    }
    CCSprite* finger = CCSprite::create("background/touch0.png");
//    finger->setPosition(ccp(center.x+150, center.y+150));
    finger->setPosition(ccp(center.x+xDis, leftBottomPos.y+100));
    finger->setScale(0.6);
//    finger->runAction(CCSequence::create(CCMoveTo::create(0.5, ccp(center.x-200, center.y+50)),
//                                         CCFadeOut::create(0.5),
//                                         CCRemoveSelf::create(),
//                                         CCCallFunc::create(this, callfunc_selector(MakeSauce::canTouchOther)),
//                                         NULL));
    finger->runAction(CCSequence::create(
//                                         CCFadeIn::create(0.5),
                                         CCEaseOut::create(CCMoveTo::create(0.8, ccp(center.x, center.y+80)), 1.0f),
                                                           CCFadeOut::create(0.4),
//                                                            CCRemoveSelf::create(),
//                                         CCCallFunc::create(this, callfunc_selector(MakeSauce::canTouchOther)),
                                         NULL));
    this->addChild(finger,999);
}

void MakeSauce::candyMaterial(){
    CCPoint leftBottomPos = GameManager::sharedManager()->getLeftBottomPos();
    
    whichMaterial = 2;
    newSpriteIndex = 3;
    fileName = "candy";
    for (int i=0; i<3; i++) {
        CCSprite* candy = CCSprite::create(CCString::createWithFormat("pizza/element/sauce/candy/candy-%d.png",i+1)->getCString());
//        candy->setPosition(ccp(center.x+150+(i%2)*150, leftBottomPos.y+150-(i/2)*150));
        candy->setPosition(ccp(center.x-50+(i)*150, leftBottomPos.y+110));
        candy->setTag(kCandy+i);
        candy->setScale(0.65);
        this->addChild(candy,99);
    }
    showMilk();
}

void MakeSauce::halloweenMaterial(){
    CCPoint leftBottomPos = GameManager::sharedManager()->getLeftBottomPos();
    
    whichMaterial=3;
    newSpriteIndex = 2;
    fileName = "halloween";
    for (int i=0; i<2; i++) {
        CCSprite* halloween = CCSprite::create(CCString::createWithFormat("pizza/element/sauce/halloween/halloween-%d.png",i+1)->getCString());
//        halloween->setPosition(ccp(center.x+150+(i%2)*150, leftBottomPos.y+150-(i/2)*150));
        halloween->setPosition(ccp(center.x+(i)*200, leftBottomPos.y+110));
        halloween->setTag(kHalloweenn+i);
        halloween->setScale(0.65);
        this->addChild(halloween,99);
    }
    showMilk();
}


void MakeSauce::christmasMaterial(){
    CCPoint leftBottomPos = GameManager::sharedManager()->getLeftBottomPos();
    
    whichMaterial=4;
    newSpriteIndex = 3;
    fileName = "christmas";
    for (int i=0; i<3; i++) {
        CCSprite* christmas = CCSprite::create(CCString::createWithFormat("pizza/element/sauce/christmas/christmas-%d.png",i+1)->getCString());
//        christmas->setPosition(ccp(center.x+150+(i%2)*150, leftBottomPos.y+150-(i/2)*150));
        christmas->setPosition(ccp(center.x-220+(i)*150, leftBottomPos.y+110));
        christmas->setTag(kChristmas+i);
//        if (i==2) {
//            christmas->setScale(0.75);
//        }else{
            christmas->setScale(0.65);
//        }
        
        this->addChild(christmas,99);
    }
    showMilk();
}


void MakeSauce::showMilk(){
    CCPoint leftBottomPos = GameManager::sharedManager()->getLeftBottomPos();
    const char* file = "";
    int index=0;
    int xDis=0;
    milkIndex = 4;
    if (whichMaterial==2) {
        file = "candy";
        index = 4;
        
        xDis=-200;
    }else if(whichMaterial==3){
        file = "halloween";
        index = 4;
//        milkIndex = 4;
        xDis=-200;
    }else if(whichMaterial==4){
        file = "christmas";
        index = 3;
//        milkIndex = 4;
        xDis=270;
    }
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(CCString::createWithFormat("pizza/animate/%s/%s%d.plist",file,file,index)->getCString());
    CCSprite* milk = CCSprite::createWithSpriteFrameName(CCString::createWithFormat("%s4_1.png",file)->getCString());
//    milk->setPosition(ccp(center.x+150, center.y+xDis));
    milk->setPosition(ccp(center.x+xDis, leftBottomPos.y+100));
//    milk->runAction(CCSequence::create(CCEaseIn::create(CCMoveTo::create(1.0, ccp(center.x, center.y)), 0.2f),
////                                            CCCallFunc::create(this, callfunc_selector(CutMaterial::isCancut)),
//                                            NULL));
    milk->setTag(kMilk);
    milk->setScale(0.6);
    this->addChild(milk,99);
}


void MakeSauce::milkAction(){
    CCSprite* milk = (CCSprite*)this->getChildByTag(kMilk);
    if (milk!=NULL) {
        touchMilk = false;
                  CCArray* frame = CCArray::create();
                  for (int i =1; i<4; i++) {
                      CCString *name = CCString::createWithFormat("%s%d_%d.png",fileName,milkIndex,i);
                      frame->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString()));
                  }
                  CCAnimation *animation = CCAnimation::createWithSpriteFrames(frame);
                  animation->setDelayPerUnit(0.4f);
                  CCAnimate *animate = CCAnimate::create(animation);
       
        milk->runAction(CCSequence::create(animate,
                                           CCMoveTo::create(0.3, ccp(milk->getPosition().x, milk->getPosition().y+800)),
                                           CCCallFunc::create(this, callfunc_selector(MakeSauce::potMilk)),
                                           CCCallFunc::create(this, callfunc_selector(MakeSauce::canTouchOther)),
//                                           CCRemoveSelf::create(),
                                           NULL));
        }
    if (newSpriteTag==0 && !fireOn) {
//        if (!fireOn) {
            potActoion();
//        }
    }
}


void MakeSauce::potMilk(){
   
    SimpleAudioEngine::sharedEngine()->playEffect("mp3/water1.mp3");
    CCSprite* pot = (CCSprite*)this->getChildByTag(kPot);
//    CCPoint pos = ccp(pot->getPosition().x, pot->getPosition().y+35);
    if(pot!=NULL && strcmp(fileName, "") != 0){
        CCSprite* newSprite = CCSprite::create(CCString::createWithFormat("pizza/element/sauce/%s/%s%d.png",fileName,fileName,touchIndex)->getCString());
        newSprite->setPosition(ccp(pot->getContentSize().width/2, pot->getContentSize().height/1.7));
        pot->addChild(newSprite,999);
        newSprite->setTag(kMilkPot);
//        touchMilk = false;
    }

}

void MakeSauce::canTouchOther(){
    touchOther = true;
}


void MakeSauce::showSpoon(){
    
    CCSprite* pot = (CCSprite*)this->getChildByTag(kPot);
    if (pot!=NULL) {
        CCSprite* spoon =CCSprite::create("pizza/element/spoon.png");
        CCPoint pos = pot->getPosition();
        spoon->setRotation(90);
        spoon->setScale(0.6);
        spoon->setPosition(ccp(pot->getContentSize().width/1.3,pos.y+800));
        CCFiniteTimeAction *action1=CCSpawn::create(CCRemoveSelf::create(),
                                                    CCCallFunc::create(this, callfunc_selector(MakeSauce::showSpoon1)),
                                                    NULL);
        
        spoon->runAction(CCSequence::create(CCEaseOut::create(CCMoveTo::create(1.5, ccp(pot->getContentSize().width/1.1, pot->getContentSize().height/1.7)), 1.0),
                                            action1,
                                            NULL));
        pot->addChild(spoon);
    }

//    spoon->setRotation(20);
}

void MakeSauce::showSpoon1(){
//    rotation = 20;
    CCSprite* pot = (CCSprite*)this->getChildByTag(kPot);
    if (pot!=NULL) {
        CCSprite* spoon =CCSprite::create("pizza/element/spoon1.png");
        CCPoint pos = pot->getPosition();
        spoon->setPosition(ccp(pot->getContentSize().width/1.1, pot->getContentSize().height/1.7));
        spoon->setTag(kSpoon);
        spoon->setScale(0.6);
        pot->addChild(spoon);
        pot->setAnchorPoint(ccp(0.5,0.5));
        spoon->setRotation(90);
        originRotation =90;
        CCActionInterval *forwardBy = CCJumpBy::create(0.4, ccp(0,0), 10, 1);
        CCActionInterval *backBy = forwardBy->reverse();
        
        CCFiniteTimeAction *action = CCSpawn::create(CCCallFunc::create(this, callfunc_selector(MakeSauce::removeNewsprite)),
                                                     CCCallFunc::create(this, callfunc_selector(MakeSauce::showSauce)),
                                                     NULL);
        
        spoon->runAction(CCSequence::create(
                                            forwardBy,
                                            backBy,
                                            action,
                                            CCCallFunc::create(this, callfunc_selector(MakeSauce::canTouchedSpoon)),
                                            NULL));
    }

//    canTouchSpoon = true;
}

void MakeSauce::canTouchedSpoon(){
    canTouchSpoon = true;
}

void MakeSauce::removeNewsprite(){
    CCSprite* pot = (CCSprite*)this->getChildByTag(kPot);
    if (pot!=NULL) {
        for (int i=0; i<newSpriteIndex; i++) {
            CCSprite* newSprite = (CCSprite*)pot->getChildByTag(kNewSprite+i);
            if (newSprite != NULL) {
                newSprite->removeFromParentAndCleanup(true);
            }
            
        }
        CCSprite* milk = (CCSprite*)pot->getChildByTag(kMilkPot);
        if (milk) {
            milk->removeFromParentAndCleanup(true);
        }
    }

   
//    this->removeChildByTag(kMilk);
}


void MakeSauce::showSauce(){
    
    if (strcmp(fileName, "") != 0) {
        
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(CCString::createWithFormat("pizza/animate/%s/sauce_%s.plist",fileName,fileName)->getCString());
        
        CCSprite* pot = (CCSprite*)this->getChildByTag(kPot);
        if (pot!=NULL) {
            CCSprite* sauce = CCSprite::createWithSpriteFrameName(CCString::createWithFormat("sauce%s_1.png",fileName)->getCString());
            sauce->setTag(kSauce);
            sauce->setPosition(ccp(pot->getContentSize().width/2, pot->getContentSize().height/2));
            pot->addChild(sauce,2);
        }

    }
    
}

void MakeSauce::sauceAction(int index){
    if (index >=4) {
        index =4;
    }
    CCSprite* pot = (CCSprite*)this->getChildByTag(kPot);
    if (pot!=NULL) {
        CCSprite* sauce = (CCSprite*)pot->getChildByTag(kSauce);
        if (sauce!=NULL) {
            CCString *name =CCString::createWithFormat("sauce%s_%d.png",fileName,index+2);
        //    CCString *name = CCString::createWithFormat("sauce_%d.png",index+2);
            CCSpriteFrame* sauceAction= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString());
            sauce->setDisplayFrame(sauceAction);
            if (sauceIndex%2==0) {
                stirMp3();
            }
        }
    }

}

void MakeSauce::clickBack(){
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, CutMaterial::scene(), ccBLACK));
}

void MakeSauce::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent){
    CCTouch *pTouch = (CCTouch*)(pTouches->anyObject());
    CCPoint location=CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
//    if (touchOther) {
        this->unschedule(schedule_selector(MakeSauce::showFinger));
    CCSprite* milk = (CCSprite*)this->getChildByTag(kMilk);
    if (pTouches->count() == 1) {                       
        if (milk && milk->boundingBox().containsPoint(location) && !touchedMilk) {
            touchedMilk=true;
            touchOther = false;
            touchSprite = milk;
            touchMilk = true;
            touchIndex=44;
            originPos = touchSprite->getPosition();
            SimpleAudioEngine::sharedEngine()->playEffect("mp3/pin.mp3");
        }
        if (touchOther == true) {
            if (whichMaterial==2) {
                for (int i=0; i<4; i++) {
                    CCSprite* candy = (CCSprite*)this->getChildByTag(kCandy+i);
                    if (candy && candy->boundingBox().containsPoint(location)) {
                        touchSprite = candy;
                        touchIndex=i+1;
                        originPos = touchSprite->getPosition();
                    }
                }
            }else if (whichMaterial==3) {
                for (int i=0; i<2; i++) {
                    CCSprite* halloween = (CCSprite*)this->getChildByTag(kHalloweenn+i);
                    if (halloween && halloween->boundingBox().containsPoint(location)) {
                        touchSprite = halloween;
                        touchIndex=i+1;
                        originPos = touchSprite->getPosition();
                    }
                }
            }else if (whichMaterial==4) {
                for (int i=0; i<4; i++) {
                    CCSprite* christmas = (CCSprite*)this->getChildByTag(kChristmas+i);
                    if (christmas && christmas->boundingBox().containsPoint(location)) {
                        touchSprite = christmas;
                        touchIndex=i+1;
                        originPos = touchSprite->getPosition();
                    }
                }
            }
        }

    //    }
        

        
        if (canTouchSpoon) {
            
            CCSprite* pot = (CCSprite*)this->getChildByTag(kPot);
            if (pot!=NULL) {
                CCSprite* spoon = (CCSprite*)pot->getChildByTag(kSpoon);
                CCPoint pos = pot->convertToNodeSpace(location);
                if (spoon && spoon->boundingBox().containsPoint(pos)) {
                    touchSpoon = spoon;
                    beginPos = location.x;
                }
            }
        }
        
        
        
        CCSprite* back = (CCSprite*)this->getChildByTag(kBack);
        CCSprite* next = (CCSprite*)this->getChildByTag(kNextTag);
        if (back!=NULL && back->boundingBox().containsPoint(location) && backClick==false) {
            backClick = true;
            fileName = "";
            touchSprite = NULL;
            touchSpoon = NULL;
            touchMilk = false;
            SimpleAudioEngine::sharedEngine()->stopAllEffects();
    //        SimpleAudioEngine::sharedEngine()->playEffect("mp3/done.mp3");
    //        if (PizzaManager::sharedManager()->whichPizza != 8) {
    //            CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, MakePizza::scene(), ccBLACK));
    //        }else{
            CCScaleBy* scaleBy = CCScaleBy::create(0.1, 1.2);
            //            homeBtn->setScale(1.2);
            //            touchSprite = homeBtn;
            SimpleAudioEngine::sharedEngine()->playEffect("mp3/touchItem.mp3");
            back->runAction(CCSequence::createWithTwoActions(CCSequence::createWithTwoActions(scaleBy, scaleBy->reverse()), CCCallFunc::create(this, callfunc_selector(MakeSauce::clickBack))));
    //        }
    //        PizzaManager::sharedManager()->cleanAllSprite();
        }else if (next !=NULL && next->boundingBox().containsPoint(location) && clickNext==false) {
            clickNext = true;
            CCScaleBy* scaleBy = CCScaleBy::create(0.1, 1.2);
            SimpleAudioEngine::sharedEngine()->playEffect("mp3/touchItem.mp3");
            next->runAction(CCSequence::createWithTwoActions(CCSequence::createWithTwoActions(scaleBy, scaleBy->reverse()), CCCallFunc::create(this, callfunc_selector(MakeSauce::goNext))));
        }
    }

}


void MakeSauce::cannotStir(){
    sauceIndex = 0;
    canStri = true;
    canTouchSpoon = false;
    this->stopAllActions();
}


void MakeSauce::stirMp3(){
    SimpleAudioEngine::sharedEngine()->playEffect("mp3/stir.mp3");
}

void MakeSauce::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent){
    CCTouch *pTouch = (CCTouch*)(pTouches->anyObject());
    CCPoint location = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
    
    if (touchSprite && !canTouchSpoon) {
        touchSprite->setPosition(location);
    }else if(touchSpoon && canTouchSpoon){
        CCSprite* pot = (CCSprite*)this->getChildByTag(kPot);
        CCPoint pos = pot->convertToNodeSpace(location);
        if (rotation<=110  && rotation!=70 && rotation>70 && !subStir) {
            rotation = rotation-2;
//                    }
        }else if(rotation<=70){
            subStir=true;
            addStir=true;
            rotation=70;
        }
        if (rotation>=70 && rotation!=110 && rotation<110 &&  addStir) {
            rotation = rotation+2;
//                    }
        }else if(rotation>=110){
            addStir=false;
            subStir = false;
            rotation=110;
        }
//

    if (pos.y <= pot->getContentSize().height/1.4 && pos.y >= pot->getContentSize().height/1.8 && !stirNum) {
//        stirTimes++;
        stirNum =true;
        this->sauceAction(sauceIndex);
        sauceIndex++;
    }else if((pos.y >= pot->getContentSize().height/1.4 || pos.x <= pot->getContentSize().height/1.8) && !canStri){
        stirNum=false;
    }
//    if(pos.y<=pot->getContentSize().height/1.4 && pos.x >=pot->getContentSize().height/2){
//        touchSpoon->setPositionY(pos.y);
//    }
        
//        if (abs(endPos-beginPos)>40) {
//        ////
//            originRotation +=15;
//            beginPos = endPos;
//            sauceIndex++;
//        }
////
////
        touchSpoon->setRotation(rotation);
        if (sauceIndex ==4) {
                this->runAction(CCSequence::create(
                                                   CCDelayTime::create(1.0),
                                                   CCCallFunc::create(this, callfunc_selector(MakeSauce::cannotStir)),
                                                   CCCallFunc::create(this, callfunc_selector(MakeSauce::goNext)),
                                                     NULL));
//                this->scheduleOnce(schedule_selector(MakeDough::cannotStirFlour), 0.3);
        }
//
////
//        this->sauceAction(sauceIndex);
    }
}

void MakeSauce::goNext(){
    SimpleAudioEngine::sharedEngine()->stopAllEffects();
    PizzaManager::sharedManager()->noughComplate = true;
    fileName = "";
    CCUserDefault::sharedUserDefault()->setBoolForKey("isFirstSauce", false);
    GameManager::sharedManager()->firstPizzaSauce=false;
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.0, MakePizza::scene(), ccBLACK));
}

void MakeSauce::oliMp3(){
    SimpleAudioEngine::sharedEngine()->playEffect("mp3/water1.mp3");
}

void MakeSauce::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent){
    CCTouch *pTouch = (CCTouch*)(pTouches->anyObject());
    CCPoint location = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
    CCSprite* pot = (CCSprite*)this->getChildByTag(kPot);
    if (touchSprite !=NULL) {
        float rectWidth = 55;
        float rectHeight = 55;
        float rectWidth1 = touchSprite->getContentSize().width;
        float rectHeight1 = touchSprite->getContentSize().height;
        CCPoint potPos = ccp(pot->getPosition().x, pot->getPosition().y+35);
        CCRect rect1 = this->createRectByPoint(potPos, rectWidth, rectHeight);
        CCRect rect2 = this->createRectByPoint(touchSprite->getPosition(), rectWidth1, rectHeight1);
        if (rect1.intersectsRect(rect2)) {
            
            if (touchMilk==true) {
                touchSprite->runAction(CCCallFunc::create(this, callfunc_selector(MakeSauce::milkAction)));
            }
            
            if(touchOther == true){
                SimpleAudioEngine::sharedEngine()->playEffect("mp3/pinIn.mp3");
                touchSprite->removeFromParentAndCleanup(true);
                CCSprite* newSprite = CCSprite::create(CCString::createWithFormat("pizza/element/sauce/%s/%s%d.png",fileName,fileName,touchIndex)->getCString());
                newSprite->setTag(kNewSprite+newSpriteTag);
                newSpriteTag++;
                newSprite->setPosition(ccp(pot->getContentSize().width/2, pot->getContentSize().height/1.7));
                pot->addChild(newSprite,5+touchIndex);
                if (fireOn == false) {
//                    this->potActoion();
                    this->scheduleOnce(schedule_selector(MakeSauce::potActoion), 0.1);
                }
            }
            MaterialIndex++;
            if ((whichMaterial==2 && MaterialIndex==4) || (whichMaterial==3 && MaterialIndex==3) || (whichMaterial==4 && MaterialIndex==4) ) {
                
                CCSprite* vegBoard = (CCSprite*)this->getChildByTag(kVegBoardTag);
                if (vegBoard) {
                    vegBoard->runAction(CCMoveTo::create(0.35, ccp(center.x, -vegBoard->getContentSize().height)));
                }
                
                CCFiniteTimeAction *action = CCSpawn::create(CCMoveTo::create(0.35, center),
                                                             CCScaleTo::create(0.35, 1.2),
                                                             NULL);
                pot->runAction(CCSequence::create(CCDelayTime::create(1.2),
                                                  action,
                                                  CCCallFunc::create(this,callfunc_selector(MakeSauce::showSpoon)),
                                                  NULL));
                MaterialIndex=0;
                touchOther = false;
//                newSpriteTag=0;
            }
        }else{
            touchOther = true;
            touchedMilk=false;
            touchMilk = false;
            SimpleAudioEngine::sharedEngine()->playEffect("mp3/movein.wav");
            touchSprite->runAction(CCMoveTo::create(0.5, originPos));
        }
        touchSprite = NULL;
        touchSpoon = NULL;
    }
    SimpleAudioEngine::sharedEngine()->stopAllEffects();
}

CCRect MakeSauce::createRectByPoint(CCPoint point, float width, float height){
    return CCRectMake(point.x-width/2,point.y-height/2,width,height);       //CCRectMake(x,y,width,height)；x,矩形左下角x坐标；y，矩形左下角y坐标；width，矩形宽度；height，矩形高度
}
