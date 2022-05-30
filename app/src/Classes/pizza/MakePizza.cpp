//
//  MakePizza.cpp
//  Pizza
//
//  Created by LiXiaofei on 3/30/21.
//

#include "MakePizza.h"
#include "MakeDough.h"
#include "SimpleAudioEngine.h"
#include "GameManager.h"
#include "SelectTopping.h"
#include "CutTopping.h"
#include "PizzaManager.h"
#include "BakedPizza.h"
#include "AddTopping.h"
#include "CutMaterial.h"
//#include "DeviceManager.h"
#include "MakeSauce.h"

using namespace CocosDenshion;

enum{
    kBack = 0,
    kNough=5,
    kNougher=10,
    kRollingpin=11,
    kRollspoon = 999,
    kCheeserub = 998,
    kSauce=20,
    kCheese=100,
};

CCScene* MakePizza::scene(){
    CCScene* scene = CCScene::create();
    MakePizza* layer = MakePizza::create();
    scene->addChild(layer);
    return  scene;
}

void MakePizza::onEnter(){
    CCLayer::onEnter();
}

void MakePizza::onExit(){
    CCLayer::onExit();
}

MakePizza::MakePizza(){
}

MakePizza::~MakePizza(){}

bool MakePizza::init(){
    if (!CCLayer::init()) {
        return false;
    }
    
    backClick = false;
    CCPoint visibleOrigin=CCDirector::sharedDirector()->getVisibleOrigin();
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    center = GameManager::sharedManager()->getCenter();
    CCPoint leftTop = GameManager::sharedManager()->getLeftTopPos();
    CCPoint rightTop = GameManager::sharedManager()->getRightTopPos();
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("pizza/animate/grater.plist");
    CCSprite* bg = CCSprite::create("background/tablecloth.png");
    bg->setPosition(center);
    this->addChild(bg);
    
//    CCSprite* board = CCSprite::create("background/board.png");
//    board->setPosition(center);
//    this->addChild(board);
    
    CCSprite* back = CCSprite::create("background/back.png");
    back->setPosition(ccp(leftTop.x+50,leftTop.y-50));
    back->setTag(kBack);
    this->addChild(back);
    if (GameManager::sharedManager()->isAndroidPad()) {
        x_x=100;
        y_x=-5;
        sauce_x=-50;
    }else if(GameManager::sharedManager()->isIphoneX()){
        y_x=100;
        sauce_x=100;
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

    if (!selectedNough && !PizzaManager::sharedManager()->noughComplate) {
        this->selectNough();
    }else{
        showNough();
    }
    
    
    
    this->setTouchEnabled(true);
    return true;
}

void MakePizza::showNough(){
//    CCLog("");
    CCSprite* nougher = CCSprite::create(CCString::createWithFormat("pizza/element/shape_%d.png", PizzaManager::sharedManager()->whichShape)->getCString());;
    nougher->setScale(1.1);
    nougher->setPosition(ccp(center.x, center.y));
    this->addChild(nougher);
    noughComplate=true;
    this->runAction(CCSequence::create(CCDelayTime::create(1.0),
                                       CCCallFunc::create(this, callfunc_selector(MakePizza::moJiang)),
                                       NULL));
//    moJiang();
}


//选择面饼形状
void MakePizza::selectNough(){
        for (int i = 1; i<4; i++) {
            CCSprite* nough = CCSprite::create(CCString::createWithFormat("pizza/element/shape_%d.png", i)->getCString());
            nough->setPosition(ccp(250+x_x*0.8+(i-1)*(350-x_x)+y_x, center.y+800));
//            nough->runAction(CCMoveTo::create(0.5,ccp(250+x_x*0.8+(i-1)*(350-x_x), center.y)));
//            nough->runAction(CCSpawn::create(CCMoveTo::create(0.5,ccp(250+x_x*0.8+(i-1)*(350-x_x), center.y)),
//                                             CCCallFunc::create(this, callfunc_selector(MakePizza::noughActionMp3)),
//                                             NULL));
            nough->runAction(CCSequence::create(CCDelayTime::create(1.0),
                                                CCMoveTo::create(0.5,ccp(250+x_x*0.8+(i-1)*(350-x_x)+y_x, center.y)),
                                             CCCallFunc::create(this, callfunc_selector(MakePizza::noughActionMp3)),
                                             NULL));
            nough->setTag(kNough+i);
            if (GameManager::sharedManager()->isAndroidPad()) {
                nough->setScale(0.4);
            }else{
                nough->setScale(0.5);
            }
//            nough->setScale(0.5);
            this->addChild(nough);
        }
//    }
}


void MakePizza::removeNough(){
    for (int i = 1; i<4; i++) {
        CCSprite* nough = (CCSprite*)this->getChildByTag(kNough+i);
//        nough->runAction(CCMoveTo::create(0.5,ccp(250+(i-1)*350, center.y+800)));
        CCFiniteTimeAction *action = CCSpawn::create(CCMoveTo::create(0.5,ccp(250+(i-1)*350+y_x, center.y+800)),
                                                     CCCallFunc::create(this, callfunc_selector(MakePizza::noughActionMp3)),
                                                     NULL);
        nough->runAction(CCSequence::create(action,
                                            CCRemoveSelf::create(),
                                            NULL));
    }
}

//显示
void MakePizza::rollNough(){
    CCSprite* nougher = CCSprite::create(CCString::createWithFormat("pizza/element/shape_%d.png", PizzaManager::sharedManager()->whichShape)->getCString());;
    nougher->setScale(0.8);
    nougher->setPosition(ccp(center.x, center.y));
    CCFiniteTimeAction *action = CCSpawn::create(CCEaseIn::create(CCMoveTo::create(0.5, ccp(center.x,center.y)), 0.3f),
                                                 CCScaleTo::create(0.5, 0.3),
                                                 NULL);
    nougher->runAction(CCSequence::create(action,
                                          CCScaleTo::create(0.3, 0.4),
                                          CCCallFunc::create(this, callfunc_selector(MakePizza::noughSteam)),
                                          CCCallFunc::create(this, callfunc_selector(MakePizza::noughDropMusic)),
                                          CCScaleTo::create(0.3, 0.3),
//                                          CCCallFunc::create(this, callfunc_selector(MakePizza::noughSteam)),
                                          CCCallFunc::create(this, callfunc_selector(MakePizza::showRollingPin)),
                                          NULL));
    nougher->setTag(kNougher);
    this->addChild(nougher,2);
}

void MakePizza::noughActionMp3(){
    SimpleAudioEngine::sharedEngine()->playEffect("mp3/movein.wav");
}

void MakePizza::noughSteam(){
    CCSprite* noughSteam = (CCSprite*)this->getChildByTag(kNougher);
    CCSprite* steam = CCSprite::create("pizza/element/steam.png");
    steam->setPosition(ccp(noughSteam->getPosition().x-250-y_x, noughSteam->getPosition().y));
//    steam->setScale(0.7);
    steam->runAction(CCSequence::create(CCScaleTo::create(0.5, 3),
                                        CCRemoveSelf::create(),
                                        NULL));
    noughSteam->addChild(steam,-2);
//    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("animate/smoke.plist");
//    CCSprite* steam = CCSprite::createWithSpriteFrameName("smoke_1.png");
//    steam->setScale(10);
//    steam->setPosition(ccp(noughSteam->getPosition().x-100, noughSteam->getPosition().y));
////    steam->setOpacity(0.9);
////    steam->runAction(CCSequence::create(CCEaseIn::create(CCFadeIn::create(0.5), 0.1),
//////                                        CCDelayTime::create(0.1),
////                                        CCEaseOut::create(CCFadeOut::create(0), 0.1),
////                                        NULL));
//
//    CCArray* frame = CCArray::create();
//    for (int i =1; i<7; i++) {
//        CCString *name = CCString::createWithFormat("smoke_%d.png",i);
//        frame->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString()));
//    }
//    CCAnimation *animation = CCAnimation::createWithSpriteFrames(frame);
//    animation->setDelayPerUnit(0.01f);
//    CCAnimate *animate = CCAnimate::create(animation);
//    steam->runAction(CCSequence::create(animate,
////                                        CCDelayTime::create(0.3),
////                                        CCRemoveSelf::create(),
//                                        CCEaseIn::create(CCFadeIn::create(0.5), 0.05),
////                                        CCDelayTime::create(0.1),
//                                        CCEaseOut::create(CCFadeOut::create(0), 0.05),
//                                        NULL));
////    steam->runAction(animate);
//    noughSteam->addChild(steam,-2);
////    CCSprite* steam = CCSprite::create("element/steam.png");
   
}

void MakePizza::noughDropMusic(){
    SimpleAudioEngine::sharedEngine()->playEffect("mp3/pin.mp3");
}

void MakePizza::sauce(){
    const char* file="";
    if (PizzaManager::sharedManager()->whichPizza==2) {
        file = "candy_sauce";
    }else if(PizzaManager::sharedManager()->whichPizza==4){
        file = "halloween_sauce";
    }else if(PizzaManager::sharedManager()->whichPizza==6){
        file = "christmas_sauce";
    }else {
        file = "sauce";
    }
    
    if(PizzaManager::sharedManager()->whichShape==1){
        //心形
        for (int i = 0; i<6; i++) {
            saucer = CCSprite::create(CCString::createWithFormat("pizza/element/%s.png",file)->getCString());
//            saucer = CCSprite::create("pizza/element/sauce.png");
            saucer->setPosition(ccp(390+i*70+sauce_x, center.y));
            this->addChild(saucer,10);
            saucer->setOpacity(0);
            saucer->setTag(kSauce+i);
        }
        for (int j = 0; j<4; j++) {
            saucer = CCSprite::create(CCString::createWithFormat("pizza/element/%s.png",file)->getCString());
//            saucer = CCSprite::create("pizza/element/sauce.png");
            saucer->setPosition(ccp(center.x, 160+j*55));
            this->addChild(saucer,10);
            saucer->setOpacity(0);
            saucer->setTag(kSauce+j+6);
        }
        for (int i =0; i<6; i++) {
            saucer = CCSprite::create(CCString::createWithFormat("pizza/element/%s.png",file)->getCString());
//            saucer = CCSprite::create("pizza/element/sauce.png");
            saucer->setPosition(ccp(405+i*55+sauce_x, 460-i*45));
            this->addChild(saucer,10);
            saucer->setOpacity(0);
            saucer->setTag(kSauce+i+10);
        }
        for (int i =0; i<6; i++) {
            saucer = CCSprite::create(CCString::createWithFormat("pizza/element/%s.png",file)->getCString());
//            saucer = CCSprite::create("pizza/element/sauce.png");
            saucer->setPosition(ccp(470+i*55+sauce_x, 220+i*45));
            this->addChild(saucer,10);
            saucer->setOpacity(0);
            saucer->setTag(kSauce+i+16);
        }
        
        CCSprite* saucer1 = CCSprite::create(CCString::createWithFormat("pizza/element/%s.png",file)->getCString());
        saucer1->setPosition(ccp(380+sauce_x, center.y+70));
        this->addChild(saucer1,10);
        saucer1->setOpacity(0);
        saucer1->setTag(kSauce+22);
        
        CCSprite* saucer2 = CCSprite::create(CCString::createWithFormat("pizza/element/%s.png",file)->getCString());
        saucer2->setPosition(ccp(420+sauce_x, center.y-60));
        this->addChild(saucer2,10);
        saucer2->setOpacity(0);
        saucer2->setTag(kSauce+23);
        
        CCSprite* saucer3 = CCSprite::create(CCString::createWithFormat("pizza/element/%s.png",file)->getCString());
        saucer3->setPosition(ccp(center.x-50, 180));
        this->addChild(saucer3,10);
        saucer3->setOpacity(0);
        saucer3->setTag(kSauce+24);
        
        CCSprite* saucer4 = CCSprite::create(CCString::createWithFormat("pizza/element/%s.png",file)->getCString());
        saucer4->setPosition(ccp(center.x+50, 180));
        this->addChild(saucer4,10);
        saucer4->setOpacity(0);
        saucer4->setTag(kSauce+25);
        
        CCSprite* saucer5 = CCSprite::create(CCString::createWithFormat("pizza/element/%s.png",file)->getCString());
        saucer5->setPosition(ccp(720+sauce_x, center.y-60));
        this->addChild(saucer5,10);
        saucer5->setOpacity(0);
        saucer5->setTag(kSauce+26);
        
        CCSprite* saucer6 = CCSprite::create(CCString::createWithFormat("pizza/element/%s.png",file)->getCString());
        saucer6->setPosition(ccp(750+sauce_x, center.y+70));
        this->addChild(saucer6,10);
        saucer6->setOpacity(0);
        saucer6->setTag(kSauce+27);
        
        CCSprite* saucer7 = CCSprite::create(CCString::createWithFormat("pizza/element/%s.png",file)->getCString());
        saucer7->setPosition(ccp(center.x, 380));
        this->addChild(saucer7,10);
        saucer7->setOpacity(0);
        saucer7->setTag(kSauce+28);
    }
    else if (PizzaManager::sharedManager()->whichShape == 2) {
        //圆角方形
        for (int i = 0; i<4; i++) {
            for(int j=0;j<5;j++){
                saucer = CCSprite::create(CCString::createWithFormat("pizza/element/%s.png",file)->getCString());
//                saucer = CCSprite::create("pizza/element/sauce.png");
                saucer->setPosition(ccp(400+j*80+sauce_x, 200+i*80));
                this->addChild(saucer,10);
                saucer->setOpacity(0);
                saucer->setTag(kSauce+j+i*5);
            }
        }
//        saucePoint = CCPointArray::create(36);
    }
    
    else if(PizzaManager::sharedManager()->whichShape == 3){
        //圆形
        for (int i = 0; i<5; i++) {
            saucer = CCSprite::create(CCString::createWithFormat("pizza/element/%s.png",file)->getCString());
//            saucer = CCSprite::create("pizza/element/sauce.png");
            saucer->setPosition(ccp(410+i*80+sauce_x, center.y));
            this->addChild(saucer,10);
            saucer->setOpacity(0);
            saucer->setTag(kSauce+i);
        }
        for (int j = 0; j<5; j++) {
            saucer = CCSprite::create(CCString::createWithFormat("pizza/element/%s.png",file)->getCString());
//            saucer = CCSprite::create("pizza/element/sauce.png");
            saucer->setPosition(ccp(center.x, 160+j*80));
            this->addChild(saucer,10);
            saucer->setOpacity(0);
            saucer->setTag(kSauce+j+5);
        }
        for (int i =0; i<5; i++) {
            saucer = CCSprite::create(CCString::createWithFormat("pizza/element/%s.png",file)->getCString());
//            saucer = CCSprite::create("pizza/element/sauce.png");
            saucer->setPosition(ccp(455+i*55+sauce_x, 445-i*55));
            this->addChild(saucer,10);
            saucer->setOpacity(0);
            saucer->setTag(kSauce+i+10);
        }
        for (int i =0; i<5; i++) {
            saucer = CCSprite::create(CCString::createWithFormat("pizza/element/%s.png",file)->getCString());
//            saucer = CCSprite::create("pizza/element/sauce.png");
            saucer->setPosition(ccp(455+i*55+sauce_x, 205+i*55));
            this->addChild(saucer,10);
            saucer->setOpacity(0);
            saucer->setTag(kSauce+i+15);
        }
        
        CCSprite* saucer1 = CCSprite::create(CCString::createWithFormat("pizza/element/%s.png",file)->getCString());
        saucer1->setPosition(ccp(495+sauce_x, 180));
        this->addChild(saucer1,10);
        saucer1->setOpacity(0);
        saucer1->setTag(kSauce+20);
        
        CCSprite* saucer2 = CCSprite::create(CCString::createWithFormat("pizza/element/%s.png",file)->getCString());
        saucer2->setPosition(ccp(630+sauce_x, 180));
        this->addChild(saucer2,10);
        saucer2->setOpacity(0);
        saucer2->setTag(kSauce+21);
        
        CCSprite* saucer3 = CCSprite::create(CCString::createWithFormat("pizza/element/%s.png",file)->getCString());
        saucer3->setPosition(ccp(710+sauce_x, center.y-60));
        this->addChild(saucer3,10);
        saucer3->setOpacity(0);
        saucer3->setTag(kSauce+22);
        
        
        CCSprite* saucer4 = CCSprite::create(CCString::createWithFormat("pizza/element/%s.png",file)->getCString());
        saucer4->setPosition(ccp(410+sauce_x, center.y-60));
        this->addChild(saucer4,10);
        saucer4->setOpacity(0);
        saucer4->setTag(kSauce+23);
        
        CCSprite* saucer5 = CCSprite::create(CCString::createWithFormat("pizza/element/%s.png",file)->getCString());
        saucer5->setPosition(ccp(410+sauce_x, center.y+60));
        this->addChild(saucer5,10);
        saucer5->setOpacity(0);
        saucer5->setTag(kSauce+24);
        
        CCSprite* saucer6 = CCSprite::create(CCString::createWithFormat("pizza/element/%s.png",file)->getCString());
        saucer6->setPosition(ccp(710+sauce_x, center.y+60));
        this->addChild(saucer6,10);
        saucer6->setOpacity(0);
        saucer6->setTag(kSauce+25);
        
        CCSprite* saucer7 = CCSprite::create(CCString::createWithFormat("pizza/element/%s.png",file)->getCString());
        saucer7->setPosition(ccp(495+sauce_x, 455));
        this->addChild(saucer7,10);
        saucer7->setOpacity(0);
        saucer7->setTag(kSauce+26);
        
        CCSprite* saucer8 = CCSprite::create(CCString::createWithFormat("pizza/element/%s.png",file)->getCString());
        saucer8->setPosition(ccp(630+sauce_x, 455));
        this->addChild(saucer8,10);
        saucer8->setOpacity(0);
        saucer8->setTag(kSauce+27);
//
//        saucer = CCSprite::create("element/sauce.png");
//        saucer->setPosition(ccp(center.x-20, 205));
//        this->addChild(saucer,10);
//        saucer->setOpacity(0);
//        saucer->setTag(kSauce+21);
        
//        for (int i =0; i<28; i++) {
//            saucer->setTag(kSauce+i);
//        }
        
//        saucePoint = CCPointArray::create(28);
    }
}

void MakePizza::sprinkleCheese(){
    if(PizzaManager::sharedManager()->whichShape==1){
        //心形
        for (int i = 0; i<6; i++) {
            cheeser = CCSprite::create("pizza/element/cheese.png");
            cheeser->setPosition(ccp(390+i*80+sauce_x, center.y));
            this->addChild(cheeser,10);
            cheeser->setOpacity(0);
            cheeser->setTag(kCheese+i);
        }
        for (int j = 0; j<4; j++) {
            cheeser = CCSprite::create("pizza/element/cheese.png");
            cheeser->setPosition(ccp(center.x, 160+j*50));
            this->addChild(cheeser,10);
            cheeser->setOpacity(0);
            cheeser->setTag(kCheese+j+6);
        }
        for (int i =0; i<6; i++) {
            cheeser = CCSprite::create("pizza/element/cheese.png");
            cheeser->setPosition(ccp(400+i*55+sauce_x, 485-i*55));
            this->addChild(cheeser,10);
            cheeser->setOpacity(0);
            cheeser->setTag(kCheese+i+10);
        }
        for (int i =0; i<6; i++) {
            cheeser = CCSprite::create("pizza/element/cheese.png");
            cheeser->setPosition(ccp(460+i*55+sauce_x, 210+i*55));
            this->addChild(cheeser,10);
            cheeser->setOpacity(0);
            cheeser->setTag(kCheese+i+16);
        }
    }
    else if (PizzaManager::sharedManager()->whichShape == 2) {
        //圆角方形
        for (int i = 0; i<4; i++) {
            for(int j=0;j<5;j++){
                cheeser = CCSprite::create("pizza/element/cheese.png");
                cheeser->setPosition(ccp(400+j*80+sauce_x, 200+i*80));
                this->addChild(cheeser,10);
                cheeser->setOpacity(0);
                cheeser->setTag(kCheese+j+i*5);
            }
        }
    }
    
    else if(PizzaManager::sharedManager()->whichShape == 3){
        //圆形
        for (int i = 0; i<5; i++) {
            cheeser = CCSprite::create("pizza/element/cheese.png");
            cheeser->setPosition(ccp(410+i*80+sauce_x, center.y));
            this->addChild(cheeser,10);
            cheeser->setOpacity(0);
            cheeser->setTag(kCheese+i);
        }
        for (int j = 0; j<5; j++) {
            cheeser = CCSprite::create("pizza/element/cheese.png");
            cheeser->setPosition(ccp(center.x, 160+j*80));
            this->addChild(cheeser,10);
            cheeser->setOpacity(0);
            cheeser->setTag(kCheese+j+5);
        }
        for (int i =0; i<5; i++) {
            cheeser = CCSprite::create("pizza/element/cheese.png");
            cheeser->setPosition(ccp(455+i*55+sauce_x, 445-i*55));
            this->addChild(cheeser,10);
            cheeser->setOpacity(0);
            cheeser->setTag(kCheese+i+10);
        }
        for (int i =0; i<5; i++) {
            cheeser = CCSprite::create("pizza/element/cheese.png");
            cheeser->setPosition(ccp(455+i*55+sauce_x, 205+i*55));
            this->addChild(cheeser,10);
            cheeser->setOpacity(0);
            cheeser->setTag(kCheese+i+15);
        }
    }
}

//面团变成面饼动画
void MakePizza::noughAction(){
//    CCSprite* nougher = (CCSprite*)this->getChildByTag(kNougher);
//    nougher->setScale(1.3);
//    noughComplate=true;
//    PizzaManager::sharedManager()->noughComplate=false;
    if (PizzaManager::sharedManager()->whichPizza ==2 || PizzaManager::sharedManager()->whichPizza ==4 || PizzaManager::sharedManager()->whichPizza ==6) {
        this->runAction(CCSequence::create(CCCallFunc::create(this, callfunc_selector(MakePizza::removePin)),
                                           CCDelayTime::create(0.7),
                                           CCCallFunc::create(this, callfunc_selector(MakePizza::goMaterial)),
                                           NULL));
    }else{
        this->runAction(CCSequence::create(CCCallFunc::create(this, callfunc_selector(MakePizza::removePin)),
                                           CCDelayTime::create(0.7),
                                           CCCallFunc::create(this, callfunc_selector(MakePizza::moJiang)),
                                           NULL));
    }
    
}

void MakePizza::goMaterial(){
//    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::cre);
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, CutMaterial::scene(), ccBLACK));
}


//显示擀面仗
void MakePizza::showRollingPin(){
//    CCSprite* rollingPin = CCSprite::create("element/roll.png");
//    rollingPin->setPosition(center);
//    rollingPin->setTag(kRollingpin);
//    this->addChild(rollingPin);
//
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("pizza/animate/rolling_pin.plist");
    CCSprite* rollingPin =CCSprite::createWithSpriteFrameName("rolling_pin1.png");
    rollingPin->setPosition(ccp(center.x,center.y+800));
    rollingPin->runAction(CCSequence::create(CCEaseIn::create(CCMoveTo::create(1.0, ccp(center.x,center.y)), 0.3f),
                                        NULL));
//    sugar->setTag(kSugar);
    rollingPin->setScale(0.6);
    rollingPin->setTag(kRollingpin);
    this->addChild(rollingPin,9);
}

void MakePizza::rollingAction(int index){
    CCSprite* rollingPins = (CCSprite*)this->getChildByTag(kRollingpin);
    if (rollingPins!=NULL) {
        CCString *name = CCString::createWithFormat("rolling_pin%d.png",index);
        CCSpriteFrame*  pinAction= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString());
        rollingPins->setDisplayFrame(pinAction);
        if (index == 4) {
            rollPinIndex=1;
        }
//        CCArray* frame = CCArray::create();
//        for (int i =1; i<5; i++) {
//            CCString *name = CCString::createWithFormat("rolling_pin%d.png",i);
//            frame->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString()));
//        }
//            CCAnimation *animation = CCAnimation::createWithSpriteFrames(frame);
//            animation->setDelayPerUnit(0.5f);
//            CCAnimate *animate = CCAnimate::create(animation);
//            rollingPins->runAction(animate);
    }
}

void MakePizza::removePin(){
    this->removeChildByTag(kRollingpin);
}

void MakePizza::removeSpoon(){
    this->removeChildByTag(kRollspoon);
}

void MakePizza::removeCheeserub(){
    this->removeChildByTag(kCheeserub);
}

//显示抹酱勺
void MakePizza::moJiang(){
    SimpleAudioEngine::sharedEngine()->playEffect("mp3/movein.wav");
    const char* file="";
    if (PizzaManager::sharedManager()->whichPizza==2) {
        file = "candy_rollspoon";
    }else if(PizzaManager::sharedManager()->whichPizza==4){
        file = "halloween_rollspoon";
    }else if(PizzaManager::sharedManager()->whichPizza==6){
        file = "christmas_rollspoon";
    }else {
        file = "rollspoon";
    }
    CCSprite* rollspoon = CCSprite::create(CCString::createWithFormat("pizza/element/%s.png",file)->getCString());
//    CCSprite* rollspoon = CCSprite::create("pizza/element/rollspoon.png");
//    rollspoon->runAction(CCEaseIn::create(CCMoveTo::create(0.2, center), 0.2));
    rollspoon->setPosition(ccp(center.x-800, center.y));
    rollspoon->setScale(0.8);
    rollspoon->setTag(kRollspoon);
    rollspoon->runAction(CCEaseIn::create(CCMoveTo::create(0.3, ccp(center.x, center.y)), 0.3));
    this->addChild(rollspoon,11);
    this->sauce();
}


//芝士
void MakePizza::cheese(){
//    CCSprite* cheeserub = CCSprite::create("element/cheeserub.png");
//    cheeserub->setPosition(center);
//    cheeserub->setTag(kCheeserub);
//    this->addChild(cheeserub,12);
//
    
    SimpleAudioEngine::sharedEngine()->playEffect("mp3/movein.wav");
    CCSprite* cheeserub = CCSprite::createWithSpriteFrameName("grater1.png");
    cheeserub->setPosition(ccp(center.x-800, center.y));
    cheeserub->setScale(0.7);
    cheeserub->setTag(kCheeserub);
    cheeserub->runAction(CCEaseIn::create(CCMoveTo::create(0.3, ccp(center.x, center.y)), 0.3));
//    cheeserub->runAction(CCFadeIn::create(0.5));
    this->addChild(cheeserub,12);
    this->sprinkleCheese();
}

void MakePizza::cheeseAction(CCObject *pSender,int index){
    CCSprite* cheeserubs = (CCSprite*)pSender;
    if (cheeserubs!=NULL) {
        CCString *name = CCString::createWithFormat("grater%d.png",index);
        CCSpriteFrame*  cheeseAction= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString());
        cheeserubs->setDisplayFrame(cheeseAction);
//        if (index == 4) {
//            cheeseRubNum=1;
//        }
//        CCArray* frame = CCArray::create();
//        for (int i =1; i<5; i++) {
//            CCString *name = CCString::createWithFormat("grater%d.png",i);
//            frame->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString()));
//        }
//        CCAnimation *animation = CCAnimation::createWithSpriteFrames(frame);
//        animation->setDelayPerUnit(1.0f);
//        CCAnimate *animate = CCAnimate::create(animation);
//        cheeserubs->runAction(animate);
    }
}

void MakePizza::sauceNum(){
    showSauce=showSauce+1;
}

void MakePizza::cheeseNum(){
    showCheese=showCheese+1;
}

void MakePizza::goNext(){
//    PizzaManager::sharedManager()->noughComplate=false;
    if(PizzaManager::sharedManager()->whichPizza == 1){
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, BakedPizza::scene(), ccBLACK));
    }else if(PizzaManager::sharedManager()->whichPizza ==3){
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, AddTopping::scene(), ccBLACK));
    }else if(PizzaManager::sharedManager()->whichPizza ==0 || PizzaManager::sharedManager()->whichPizza ==5 ){
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, CutTopping::scene(), ccBLACK));
    }else if(PizzaManager::sharedManager()->whichPizza <9 && PizzaManager::sharedManager()->whichPizza >6 ){
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, SelectTopping::scene(), ccBLACK));
    }else if(PizzaManager::sharedManager()->whichPizza ==2 || PizzaManager::sharedManager()->whichPizza ==4 || PizzaManager::sharedManager()->whichPizza ==6){
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, AddTopping::scene(), ccBLACK));
    }
//    else{
//        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, SelectTopping::scene(), ccBLACK));
//    }
}

void MakePizza::cannotRoll(){
    noughComplate=true;
}

void MakePizza::clickBack(){
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, MakeDough::scene(), ccBLACK));
}

void MakePizza::clickToBack(){
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, MakeSauce::scene(), ccBLACK));
}

void MakePizza::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent){
    CCTouch *pTouch = (CCTouch*)(pTouches->anyObject());
    CCPoint location=CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
    CCSprite* back = (CCSprite*)this->getChildByTag(kBack);
    CCSprite* rollpin = (CCSprite*)this->getChildByTag(kRollingpin);
    CCSprite* rollspoon = (CCSprite*)this->getChildByTag(kRollspoon);
    CCSprite* cheesesrub = (CCSprite*)this->getChildByTag(kCheeserub);
    beginY=location.y;
    if (back!=NULL && back->boundingBox().containsPoint(location) && !PizzaManager::sharedManager()->noughComplate && backClick == false) {
        backClick = true;
        CCScaleBy* scaleBy = CCScaleBy::create(0.1, 1.2);
        //            homeBtn->setScale(1.2);
        //            touchSprite = homeBtn;
        SimpleAudioEngine::sharedEngine()->playEffect("mp3/touchItem.mp3");
        back->runAction(CCSequence::createWithTwoActions(CCSequence::createWithTwoActions(scaleBy, scaleBy->reverse()), CCCallFunc::create(this, callfunc_selector(MakePizza::clickBack))));
    }else if(back!=NULL && back->boundingBox().containsPoint(location) && PizzaManager::sharedManager()->noughComplate){
        PizzaManager::sharedManager()->noughComplate=false;
        CCScaleBy* scaleBy = CCScaleBy::create(0.1, 1.2);
        //            homeBtn->setScale(1.2);
        //            touchSprite = homeBtn;
        SimpleAudioEngine::sharedEngine()->playEffect("mp3/touchItem.mp3");
        back->runAction(CCSequence::createWithTwoActions(CCSequence::createWithTwoActions(scaleBy, scaleBy->reverse()), CCCallFunc::create(this, callfunc_selector(MakePizza::clickToBack))));
    }
    
    if (rollpin!=NULL &&  rollpin->boundingBox().containsPoint(location)) {
        touchSprite = rollpin;
    }
    if (rollspoon!=NULL && rollspoon->boundingBox().containsPoint(location) && !canSpoonPizza){
        touchSpoonSprite = rollspoon;
        
    }
    if (cheesesrub!=NULL && cheesesrub->boundingBox().containsPoint(location) && !canRubPizza){
        touchCheeseSprite = cheesesrub;
        
    }
    
    //选择面饼形状
    if (!selectedNough) {
        for (int i = 1; i<4; i++) {
            CCSprite* nough = (CCSprite*)this->getChildByTag(kNough+i);
            if (nough != NULL && nough->boundingBox().containsPoint(location)) {
                if (!CCUserDefault::sharedUserDefault()->getBoolForKey("purchased")){
                    GameManager::sharedManager()->showInterstitial();
                }
                selectedNough=true;
                SimpleAudioEngine::sharedEngine()->playEffect("mp3/touchItem.mp3");
                this->runAction(CCSequence::create(CCDelayTime::create(0.2),
                                                   CCCallFunc::create(this, callfunc_selector(MakePizza::removeNough)),
                                                   CCDelayTime::create(0.5),
                                                   CCCallFunc::create(this, callfunc_selector(MakePizza::rollNough)),
                                                   NULL));
                PizzaManager::sharedManager()->whichShape=i;
            }
        }
    }
}



void MakePizza::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent){
    CCTouch *pTouch = (CCTouch*)(pTouches->anyObject());
    CCPoint location=CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
//    CCSprite* rollpin = (CCSprite*)this->getChildByTag(kRollingpin);
//    CCSprite* rollspoon = (CCSprite*)this->getChildByTag(kRollspoon);
//    CCSprite* cheesesrub = (CCSprite*)this->getChildByTag(kCheeserub);
    endY = location.y;
    //用擀面杖擀面
    if (touchSprite && !noughComplate) {
        touchSprite->setPositionY(location.y);
        if (abs(beginY-endY)>=50) {
            rollPinIndex++;
            this->rollingAction(rollPinIndex);
        }
        CCLog("---%d---",(int)location.y);
        if ((int)location.y<= 320 && (int)location.y>= 305 && !canRolling && !cannotSpoon) {
            rollingIndex++;
            isRolled = true;
        }else if ((int)location.y>= 320 || (int)location.y<= 305){
            canRolling = false;
            isRolled=false;
        }
       
        CCSprite* nougher = (CCSprite*)this->getChildByTag(kNougher);
        if (rollingIndex ==1 && isRolled) {
            nougher->runAction(CCScaleTo::create(0.2, 0.5));
            SimpleAudioEngine::sharedEngine()->playBackgroundMusic("mp3/poursugar.mp3");
            canRolling = true;
        }else if (rollingIndex ==2 && isRolled) {
            nougher->runAction(CCScaleTo::create(0.2, 0.7));
            SimpleAudioEngine::sharedEngine()->playBackgroundMusic("mp3/poursugar.mp3");
            canRolling = true;
        }else if (rollingIndex ==3 && isRolled) {
            nougher->runAction(CCScaleTo::create(0.2, 0.9));
            SimpleAudioEngine::sharedEngine()->playBackgroundMusic("mp3/poursugar.mp3");
            canRolling = true;
        }else if (rollingIndex ==4 && isRolled) {
            SimpleAudioEngine::sharedEngine()->playBackgroundMusic("mp3/poursugar.mp3");
//            canRolling = false;
            isRolled=false;
            canRolling = true;
            cannotSpoon = true;
            nougher->runAction(CCSequence::create(CCScaleTo::create(0.2, 1.1),
                                                  CCCallFunc::create(this, callfunc_selector(MakePizza::cannotRoll)),
                                                  CCDelayTime::create(0.5),
                                                  CCCallFunc::create(this, callfunc_selector(MakePizza::noughAction)),
                                                  NULL));
            rollingIndex=0;
//            this->noughAction();
        }
        
//        if (rollingIndex ==4) {
//
//        }
//        time++;
//
    }
    
//    if (time >=3) {
//        this->noughAction();
//    }
    
    if (noughComplate && touchSpoonSprite &&  !canSpoonPizza) {
        touchSpoonSprite->setPosition(location);
        float rectWidth = 75;
        float rectHeight = 75;
        float spoonWidth = 70;
        float spoonHeight = 70;
        CCRect rect1 = this->createRectByPoint(ccp(touchSpoonSprite->getPosition().x-160, touchSpoonSprite->getPosition().y), spoonWidth/2, spoonHeight/2);            //勺子区域
        if (PizzaManager::sharedManager()->whichShape == 1) {
            sauceCount=29;
        }else if(PizzaManager::sharedManager()->whichShape==2){
            sauceCount=20;
        }else if(PizzaManager::sharedManager()->whichShape==3){
            sauceCount=28;
        }
        
        for (int i =0; i<sauceCount; i++) {
            CCSprite* sauce = (CCSprite*)this->getChildByTag(kSauce+i);
            CCRect rect2 = this->createRectByPoint(sauce->getPosition(), rectWidth, rectHeight);
            if ((rect1.intersectsRect(rect2)) && sauceArray[i]==0) {
                SimpleAudioEngine::sharedEngine()->playEffect("mp3/pinIn.mp3");
                sauceArray[i]=1;
                sauce->runAction(CCSequence::create(CCFadeTo::create(0.1, 255),
                                                    CCCallFunc::create(this, callfunc_selector(MakePizza::sauceNum)),
                                                    NULL));
            }
        }
        if (showSauce == sauceCount) {
            canSpoonPizza = true;
//            touchSpoonSprite->runAction(CCEaseOut::create(CCMoveTo::create(0.3, ccp(center.x-800, center.y)), 0.3)),
            touchSpoonSprite->runAction(CCSequence::create(CCEaseOut::create(CCMoveTo::create(0.3, ccp(center.x-800, center.y)), 0.3),
                                                           CCDelayTime::create(0.5),
                                                           CCCallFunc::create(this, callfunc_selector(MakePizza::cheese)),
                                                           CCCallFunc::create(this, callfunc_selector(MakePizza::removeSpoon)),
                                                           NULL));
        }
    }
    if(noughComplate && touchCheeseSprite && !canRubPizza){
        touchCheeseSprite->setPosition(location);
        float rectWidth = 65;
        float rectHeight = 65;
        float rubWidth = 40;
        float rubHeight = 40;
        CCRect rect1 = this->createRectByPoint(touchCheeseSprite->getPosition(), rubWidth/2, rubHeight);            //芝士区域
        
        if (PizzaManager::sharedManager()->whichShape == 1) {
            sauceCount=22;
        }else if(PizzaManager::sharedManager()->whichShape==2){
            sauceCount=20;
        }else if(PizzaManager::sharedManager()->whichShape==3){
            sauceCount=20 ;
        }
        
        for (int i =0; i<sauceCount; i++) {
            CCSprite* cheese = (CCSprite*)this->getChildByTag(kCheese+i);
            CCRect rect2 = this->createRectByPoint(cheese->getPosition(), rectWidth, rectHeight);
            if ((rect1.intersectsRect(rect2)) && cheeseArray[i]==0) {
                SimpleAudioEngine::sharedEngine()->playEffect("mp3/pinIn.mp3");
                cheeseArray[i]=1;
                cheese->runAction(CCSequence::create(CCFadeTo::create(0.1, 255),
                                                    CCCallFunc::create(this, callfunc_selector(MakePizza::cheeseNum)),
//                                                     CCCallFunc::create(this, callfunc_selector(MakePizza::cheeseAction)),
//                                                     CCCallFuncND::create(this, callfuncND_selector(MakePizza::cheeseAction),(int*)(intptr_t)cheeseRubNum),
                                                    NULL));
                cheeseRubNum++;
                if (cheeseRubNum == 5) {
                    cheeseRubNum=1;
                }
                touchCheeseSprite->runAction(CCCallFuncND::create(this, callfuncND_selector(MakePizza::cheeseAction),(int*)(intptr_t)cheeseRubNum));
            }
        }
        if (showCheese == sauceCount) {
            canRubPizza = true;
//            touchCheeseSprite->runAction(CCEaseOut::create(CCMoveTo::create(0.3, ccp(center.x-800, center.y)), 0.3)),
            touchCheeseSprite->runAction(CCSequence::create(CCEaseOut::create(CCMoveTo::create(0.3, ccp(center.x-800, center.y)), 0.3),
                                                            CCDelayTime::create(1.0),
                                                           CCCallFunc::create(this, callfunc_selector(MakePizza::goNext)),
                                                            CCCallFunc::create(this, callfunc_selector(MakePizza::removeCheeserub)),
                                                           NULL));
        }
    }
}

void MakePizza::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent){
    CCTouch *pTouch = (CCTouch*)pTouches->anyObject();
    CCPoint location = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
    if (touchSprite) {
        touchSprite = NULL;
    }
    if (touchSpoonSprite) {
        touchSpoonSprite = NULL;
    }
    if (touchCheeseSprite) {
        touchCheeseSprite = NULL;
    }
}


CCRect MakePizza::createRectByPoint(CCPoint point, float width, float height){
    return CCRectMake(point.x-width/2,point.y-height/2,width,height);       //CCRectMake(x,y,width,height)；x,矩形左下角x坐标；y，矩形左下角y坐标；width，矩形宽度；height，矩形高度
}
