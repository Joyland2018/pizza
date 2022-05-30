//
//  CutPizza.cpp
//  Pizza
//
//  Created by LiXiaofei on 4/8/21.
//

#include "CutPizza.h"
#include "GameManager.h"
#include "PizzaManager.h"
#include "SimpleAudioEngine.h"
#include "BakedPizza.h"
#include "SelectPizza.h"
//#include "DeviceManager.h"

using namespace CocosDenshion;

enum{
    kBack = 0,
    kPizzaShape=1,
    kDino = 2,
    kMoney = 3,
};

CCScene* CutPizza::scene(){
    CCScene* scene = CCScene::create();
    CutPizza* layer = CutPizza::create();
    scene->addChild(layer);
    return scene;
}


CutPizza::CutPizza(){}
CutPizza::~CutPizza(){};


void CutPizza::onEnter(){
    CCLayer::onEnter();
}

void CutPizza::onExit(){
    CCLayer::onExit();
}

bool CutPizza::init(){
    if (!CCLayer::init()) {
        return false;
    }
    
    backClick = false;
    visibleOrigin = CCDirector::sharedDirector()->getVisibleOrigin();
    visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("pizza/animate/eatpizza.plist");
    center = GameManager::sharedManager()->getCenter();
    CCPoint leftTop = GameManager::sharedManager()->getLeftTopPos();
    //背景
    CCSprite* bg = CCSprite::create("background/bg2.png");
    bg->setPosition(center);
    this->addChild(bg);
    
    if (GameManager::sharedManager()->isIphoneX()) {
        bg->setScale(1.3);
        x_x=-100;
    }else if (GameManager::sharedManager()->isAndroidPad()){
        x_x=52;
    }
//    else if(DeviceManager::sharedManager()->getIsPad()){
//        x_x=0;
////        x_y=300;
//    }
    
    
    CCSprite* back = CCSprite::create("background/back.png");
    back->setPosition(ccp(leftTop.x+50,leftTop.y-50));
    back->setTag(kBack);
    this->addChild(back,1111);
    CCSprite* money = CCSprite::create("background/money.png");
    money->setPosition(ccp(visibleOrigin.x+visibleSize.width-100, visibleSize.height-50));
    money->setTag(kMoney);
    this->addChild(money,10);
    
    CCString* curscore = CCString::createWithFormat("%d",GameManager::sharedManager()->getCurrentCoin());
    const char* curscores = curscore->getCString();
    curallscores = CCLabelTTF::create(curscores, "Arial", 28);
    curallscores->setColor(ccWHITE);
    curallscores->setTag(100);
    curallscores->setPosition(ccp(visibleOrigin.x+visibleSize.width-70, visibleSize.height-50));
    this->addChild(curallscores,11);


    if (!CCUserDefault::sharedUserDefault()->getBoolForKey("purchased")){
        GameManager::sharedManager()->showBanner();
    }

    this->scheduleOnce(schedule_selector(CutPizza::showPizza), 1.0);
//    this->showPizza();
    this->setTouchEnabled(true);
    return true;
}

void CutPizza::eatMp3(){
    SimpleAudioEngine::sharedEngine()->playEffect("mp3/food1_effect.mp3");
}

void CutPizza::showDino(){
    CCSprite* dino =CCSprite::createWithSpriteFrameName("eatpizza_0.png");
    dino->setPosition(ccp(center.x,center.y-800));
//        sugar->runAction(CCEaseIn::create(CCMoveTo::create(1.0, ccp(center.x-115,center.y+80)), 0.3f));
    dino->runAction(CCSequence::create(CCEaseIn::create(CCMoveTo::create(1.0, ccp(center.x,center.y-200)), 0.3f),
                                        CCCallFunc::create(this, callfunc_selector(CutPizza::dinoEatAction)),
                                        NULL));
    dino->setTag(kDino);
    this->addChild(dino,9);
}

void CutPizza::dinoEatAction(){
    CCSprite* dino = (CCSprite*)this->getChildByTag(kDino);
    if (dino!=NULL) {
            CCArray* frame = CCArray::create();
            for (int i =0; i<7; i++) {
                CCString *name = CCString::createWithFormat("eatpizza_%d.png",i);
                frame->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString()));
            }
            CCAnimation *animation = CCAnimation::createWithSpriteFrames(frame);
            animation->setDelayPerUnit(0.09);
            CCAnimate *animate = CCAnimate::create(animation);
        
            CCArray* frame1 = CCArray::create();
            for (int i =7; i<26; i++) {
                CCString *name = CCString::createWithFormat("eatpizza_%d.png",i);
                frame1->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString()));
            }
            CCAnimation *animation1 = CCAnimation::createWithSpriteFrames(frame1);
            animation1->setDelayPerUnit(0.09);
            CCAnimate *animate1 = CCAnimate::create(animation1);
            CCFiniteTimeAction *action1=CCSpawn::create(animate1,
                                                    CCCallFunc::create(this, callfunc_selector(CutPizza::eatMp3)),
                                                    NULL);
            dino->runAction(CCSequence::create(animate,
                                               action1,
                                               CCCallFunc::create(this, callfunc_selector(CutPizza::showFlower)),
                                               CCCallFunc::create(this, callfunc_selector(CutPizza::eatFinish)),
                                               NULL));
        }
}

void CutPizza::showPizza(){
    
    board = CCSprite::create("background/plate.png");
    board->setPosition(ccp(center.x, center.y-500));
    board->setScale(0.78);
    this->addChild(board);
//    PizzaManager::sharedManager()->whichShape = 3;
    CCLOG("---%d---",PizzaManager::sharedManager()->whichShape);
    CCSprite* pizzaShape = CCSprite::create();
    const char* file = "";
    if (PizzaManager::sharedManager()->whichPizza!=1) {
        if (PizzaManager::sharedManager()->whichShape==1) {
            if (PizzaManager::sharedManager()->whichPizza==2) {
                file ="heartcandy";
            }else if (PizzaManager::sharedManager()->whichPizza==4) {
                file ="hearthalloween";
            }else if (PizzaManager::sharedManager()->whichPizza==6) {
                file ="heartchristmas";
            }else{
                file ="heartbakecheese";
            }
            pizzaShape = CCSprite::create(CCString::createWithFormat("pizza/element/bake/%s.png",file)->getCString());
//            pizzaShape = CCSprite::create("pizza/element/heartbakecheese.png");
            pizzaShape->setScale(2.8);
            topXdis=0;
        }else if(PizzaManager::sharedManager()->whichShape==3){
            if (PizzaManager::sharedManager()->whichPizza==2) {
                file ="equalcandy";
            }else if (PizzaManager::sharedManager()->whichPizza==4) {
                file ="equalhalloween";
            }else if (PizzaManager::sharedManager()->whichPizza==6) {
                file ="equalchristmas";
            }else{
                file ="bakeCheese";
            }
            pizzaShape = CCSprite::create(CCString::createWithFormat("pizza/element/bake/%s.png",file)->getCString());
//            pizzaShape = CCSprite::create("pizza/element/bakeCheese.png");
            pizzaShape->setScale(2.5);
            topXdis=30;
        }else if(PizzaManager::sharedManager()->whichShape==2){
            rect_x = 50;
            if (PizzaManager::sharedManager()->whichPizza==2) {
                file ="rectcandy";
            }else if (PizzaManager::sharedManager()->whichPizza==4) {
                file ="recthalloween";
            }else if (PizzaManager::sharedManager()->whichPizza==6) {
                file ="rectchristmas";
            }else{
                file ="rectcheese";
            }
            pizzaShape = CCSprite::create(CCString::createWithFormat("pizza/element/bake/%s.png",file)->getCString());
//            pizzaShape = CCSprite::create("pizza/element/rectcheese.png");
            pizzaShape->setScale(2.5);
            topXdis=30;
        }
        
    }else if (PizzaManager::sharedManager()->whichPizza==1) {
        if (PizzaManager::sharedManager()->whichShape==1) {
            pizzaShape = CCSprite::create("pizza/element/bake/heartbakecheeses.png");
            pizzaShape->setScale(2.8);
        }else if(PizzaManager::sharedManager()->whichShape==3){
            pizzaShape = CCSprite::create("pizza/element/bake/bakeCheeses.png");
            pizzaShape->setScale(2.5);
        }else if(PizzaManager::sharedManager()->whichShape==2){
            rect_x = 50;
            pizzaShape = CCSprite::create("pizza/element/bake/rectcheeses.png");
            pizzaShape->setScale(2.5);
        }
    }
    pizzaShape->setPosition(ccp(center.x-pizzaShape->getContentSize().width*1.28+x_x, center.y+pizzaShape->getContentSize().height*1.15));
//    pizzaShape->setScale(2.5);
    pizzaShape->setTag(kPizzaShape);
    board->addChild(pizzaShape);
//    board->runAction(CCEaseIn::create(CCMoveTo::create(0.3, ccp(center.x, center.y-100)), 0.2));
    if (PizzaManager::sharedManager()->whichPizza!=1 && PizzaManager::sharedManager()->whichPizza!=3) {
        CCFiniteTimeAction *action1=CCSpawn::create(CCEaseIn::create(CCMoveTo::create(0.3, ccp(center.x, center.y-100)), 0.2),
                                            CCCallFunc::create(this, callfunc_selector(CutPizza::showTopping)),
                                            NULL);
        board->runAction(CCSequence::create(action1,
                                            CCCallFunc::create(this, callfunc_selector(CutPizza::showSlide)),
                                            NULL));
    }else{
        board->runAction(CCSequence::create(CCEaseIn::create(CCMoveTo::create(0.3, ccp(center.x, center.y-100)), 0.2),
                                            CCCallFunc::create(this, callfunc_selector(CutPizza::showSlide)),
                                            NULL));
    }
    
}

void CutPizza::showTopping(){
    if (pizzaTop !=NULL) {
        pizzaTop = NULL;
    }
    int topPosArrLen = sizeof(PizzaManager::sharedManager()->addToppingPos)/sizeof(PizzaManager::sharedManager()->addToppingPos[0]);
    if (board!=NULL) {
        //    CCLOG("---%d---",PizzaManager::sharedManager()->selectedTop);
            if (PizzaManager::sharedManager()->whichPizza==0) {
                if (PizzaManager::sharedManager()->selectedTop>0) {
                    for (int i = 0; i<PizzaManager::sharedManager()->selectedTop; i++) {
                        pizzaTop = CCSprite::create("pizza/element/topping_9.png");
            //            pizzaTop->setPosition(ccp(PizzaManager::sharedManager()->addToppingPos[i][0], PizzaManager::sharedManager()->addToppingPos[i][1]-400));
                        if (i<topPosArrLen) {
                            pizzaTop->setPosition(ccp(PizzaManager::sharedManager()->addToppingPos[i][0]+topXdis, PizzaManager::sharedManager()->addToppingPos[i][1]+287+rect_x));
                        }

            //            pizzaTop->runAction(CCMoveTo::create(0.3, ccp(PizzaManager::sharedManager()->addToppingPos[i][0], PizzaManager::sharedManager()->addToppingPos[i][1]-100)));
                        board->addChild(pizzaTop,2);
                    }
                }

            }else if (PizzaManager::sharedManager()->whichPizza==5) {
                if (PizzaManager::sharedManager()->selectedTop>0) {
                    for (int i = 0; i<PizzaManager::sharedManager()->selectedTop; i++) {
                        pizzaTop = CCSprite::create("pizza/element/topping_5.png");
            //            pizzaTop->setPosition(ccp(PizzaManager::sharedManager()->addToppingPos[i][0], PizzaManager::sharedManager()->addToppingPos[i][1]-400));
                        if (i<topPosArrLen) {
                            pizzaTop->setPosition(ccp(PizzaManager::sharedManager()->addToppingPos[i][0]+topXdis, PizzaManager::sharedManager()->addToppingPos[i][1]+287+rect_x));
                        }

            //            pizzaTop->runAction(CCMoveTo::create(0.3, ccp(PizzaManager::sharedManager()->addToppingPos[i][0], PizzaManager::sharedManager()->addToppingPos[i][1]-100)));
                        board->addChild(pizzaTop,2);
                    }
                }

            }else if (PizzaManager::sharedManager()->whichPizza==7 || PizzaManager::sharedManager()->whichPizza==8) {
                if (PizzaManager::sharedManager()->selectedTop>0) {
                    for (int i = 0; i<PizzaManager::sharedManager()->selectedTop; i++) {
                        char nmName[100] = {0};
                        sprintf(nmName, "pizza/element/topping_%d.png",PizzaManager::sharedManager()->addTop[i]);     //随机加载数字
//                        for (int i =0; i<PizzaManager::sharedManager()->selectedTop; i++) {
//                            CCLog("----%d----",PizzaManager::sharedManager()->addTop[i]);
//                        }
//                        CCLog("----%s----",nmName);                 //
                        pizzaTop = CCSprite::create(nmName);
                        if (i<topPosArrLen) {
                            pizzaTop->setPosition(ccp(PizzaManager::sharedManager()->addToppingPos[i][0]+topXdis, PizzaManager::sharedManager()->addToppingPos[i][1]+287+rect_x));
                        }

            //            pizzaTop->setPosition(ccp(center.x-PizzaM anager::sharedManager()->addToppingPos[i][0]+x_x+x_y, center.y+PizzaManager::sharedManager()->addToppingPos[i][1]-x_y*0.5));
            //            pizzaTop->runAction(CCMoveTo::create(0.3, ccp(PizzaManager::sharedManager()->addToppingPos[i][0]+x_y*0.08, PizzaManager::sharedManager()->addToppingPos[i][1]+x_y)));
                        board->addChild(pizzaTop,2);
                    }
                }

            }else {
                const char* file = "";
        //        int topNum=0;
                if (PizzaManager::sharedManager()->whichPizza==2) {
                    file = "candy";
        //            topNum = 8;
                }else if (PizzaManager::sharedManager()->whichPizza==4) {
                    file = "halloween";
        //            topNum = 5;
                }else if (PizzaManager::sharedManager()->whichPizza==6) {
                    file = "christmas";
        //            topNum = 8;
                }
                if (PizzaManager::sharedManager()->selectedTop>0) {
                    for (int i = 0; i<PizzaManager::sharedManager()->selectedTop; i++) {
                        char nmName[100] = {0};
                        sprintf(nmName, "pizza/element/topping/%s/%s_top%d.png",file,file,PizzaManager::sharedManager()->addTop[i]);     //随机加载数字
//                        for (int i =0; i<PizzaManager::sharedManager()->selectedTop; i++) {
//                            CCLog("----%d----",PizzaManager::sharedManager()->addTop[i]);
//                        }
//                        CCLog("----%s----",nmName);                 //
                        pizzaTop = CCSprite::create(nmName);
                        if (i<topPosArrLen) {
                            pizzaTop->setPosition(ccp(PizzaManager::sharedManager()->addToppingPos[i][0]+topXdis, PizzaManager::sharedManager()->addToppingPos[i][1]+287+rect_x));
                        }
 
            //            pizzaTop->setPosition(ccp(center.x-PizzaM anager::sharedManager()->addToppingPos[i][0]+x_x+x_y, center.y+PizzaManager::sharedManager()->addToppingPos[i][1]-x_y*0.5));
            //            pizzaTop->runAction(CCMoveTo::create(0.3, ccp(PizzaManager::sharedManager()->addToppingPos[i][0]+x_y*0.08, PizzaManager::sharedManager()->addToppingPos[i][1]+x_y)));
                        board->addChild(pizzaTop,2);
                    }
                }

            }
    }

    
}

void CutPizza::playSildeMp3(){
    SimpleAudioEngine::sharedEngine()->playEffect("mp3/pin.mp3");
}


void CutPizza::showSlide(){
    CCSprite* slide = CCSprite::create("pizza/element/slice.png");
//    this->playSildeMp3();
    slide->setVisible(false);
    this->addChild(slide,9);
    if (PizzaManager::sharedManager()->whichShape==1) {
        slide->setScale(1.5);
        slide->setScaleX(1.8);
        slide->setPosition(ccp(center.x+5, center.y-43));
    }else if(PizzaManager::sharedManager()->whichShape==2){
        slide->setScale(1.45);
        slide->setScaleX(1.7);
        slide->setPosition(ccp(center.x, center.y));
    }else if(PizzaManager::sharedManager()->whichShape==3){
        slide->setScale(2);
        slide->setPosition(ccp(center.x, center.y));
    }
    
    slide->runAction(CCSequence::create(
//                                        CCCallFunc::create(this, callfunc_selector(CutPizza::playSildeMp3)),
                                        CCFadeIn::create(0.5),
                                        CCCallFuncN::create(this, callfuncN_selector(CutPizza::visiSlide)),
                                        CCCallFunc::create(this, callfunc_selector(CutPizza::showSlide1)),
                                     NULL));
//    PizzaManager::sharedManager()->cleanAllSprite();
}

void CutPizza::showSlide1(){
    CCSprite* slide = CCSprite::create("pizza/element/slice.png");
//    this->playSildeMp3();
    slide->setVisible(false);
    slide->setRotation(90);
    this->addChild(slide,9);
    if (PizzaManager::sharedManager()->whichShape==1) {
        slide->setScale(1.9);
        slide->setScaleX(1.8);
        slide->setPosition(ccp(center.x, center.y-20));
    }else if(PizzaManager::sharedManager()->whichShape==2){
        slide->setScale(1.85);
        slide->setPosition(ccp(center.x, center.y));
    }else if(PizzaManager::sharedManager()->whichShape==3){
        slide->setScale(2);
        slide->setPosition(ccp(center.x, center.y));
    }
//    slide->setScale(1.75);
    slide->runAction(CCSequence::create(
//                                        CCCallFunc::create(this, callfunc_selector(CutPizza::playSildeMp3)),
                                        CCFadeIn::create(0.5),
                                        CCCallFuncN::create(this, callfuncN_selector(CutPizza::visiSlide)),
                                        CCCallFunc::create(this, callfunc_selector(CutPizza::showSlide2)),
                                     NULL));
}

void CutPizza::showSlide2(){
//    this->playSildeMp3();
    CCSprite* slide = CCSprite::create("pizza/element/slice.png");
    slide->setVisible(false);
    this->addChild(slide,9);
    
//    slide->setScale(1.75);
    if (PizzaManager::sharedManager()->whichShape==1) {
        slide->setRotation(130);
        slide->setScale(1.95);
        slide->setScaleX(1.8);
        slide->setPosition(ccp(center.x-25, center.y));
    }else if(PizzaManager::sharedManager()->whichShape==2){
        slide->setRotation(125);
        slide->setScale(2);
        slide->setPosition(ccp(center.x, center.y));
    }else if(PizzaManager::sharedManager()->whichShape==3){
        slide->setRotation(135);
        slide->setScale(2);
        slide->setPosition(ccp(center.x, center.y));
    }
    slide->runAction(CCSequence::create(
//                                        CCCallFunc::create(this, callfunc_selector(CutPizza::playSildeMp3)),
                                        CCFadeIn::create(0.5),
                                        CCCallFuncN::create(this, callfuncN_selector(CutPizza::visiSlide)),
                                        CCCallFunc::create(this, callfunc_selector(CutPizza::showSlide3)),
                                     NULL));
}
void CutPizza::showSlide3(){
//    this->playSildeMp3();
    CCSprite* slide = CCSprite::create("pizza/element/slice.png");
    
    slide->setVisible(false);
    this->addChild(slide,9);
//    slide->setRotation(50);
//    slide->setScale(1.75);
    if (PizzaManager::sharedManager()->whichShape==1) {
        slide->setRotation(50);
        slide->setScale(1.95);
        slide->setScaleX(1.8);
        slide->setPosition(ccp(center.x+35, center.y));
    }else if(PizzaManager::sharedManager()->whichShape==2){
        slide->setRotation(55);
        slide->setScale(1.95);
        slide->setPosition(ccp(center.x, center.y));
    }else if(PizzaManager::sharedManager()->whichShape==3){
        slide->setRotation(45);
        slide->setScale(2);
        slide->setPosition(ccp(center.x, center.y));
    }
    slide->runAction(CCSequence::create(
//                                        CCCallFunc::create(this, callfunc_selector(CutPizza::playSildeMp3)),
                                        CCFadeIn::create(0.5),
                                        CCCallFuncN::create(this, callfuncN_selector(CutPizza::visiSlide)),
                                        CCDelayTime::create(1),
                                        CCCallFunc::create(this, callfunc_selector(CutPizza::showDino)),
                                     NULL));
}

void CutPizza::showFlower(){
//    this->playSildeMp3();
   CCParticleSystemQuad* flower1;
    CCParticleSystemQuad* flower2;
    CCParticleSystemQuad* flower3;
    CCParticleSystemQuad* flower4;
    
    flower1 = CCParticleSystemQuad::create("pizza/element/flower_shower0_Hd.plist");
    flower2 = CCParticleSystemQuad::create("pizza/element/flower_shower1_Hd.plist");
    flower3 = CCParticleSystemQuad::create("pizza/element/flower_shower2_Hd.plist");
    flower4 = CCParticleSystemQuad::create("pizza/element/flower_shower3_Hd.plist");
    
    flower1->setSpeed(flower1->getSpeed()*1.5);
    flower2->setSpeed(flower2->getSpeed()*1.5);
    flower3->setSpeed(flower3->getSpeed()*1.5);
    flower4->setSpeed(flower4->getSpeed()*1.5);
    
    flower1->setDuration(flower1->getDuration()-1.5);
    flower2->setDuration(flower2->getDuration()-1.5);
    flower3->setDuration(flower3->getDuration()-1.5);
    flower4->setDuration(flower4->getDuration()-1.5);
    
    flower1->setAutoRemoveOnFinish(true);
    flower2->setAutoRemoveOnFinish(true);
    flower3->setAutoRemoveOnFinish(true);
    flower4->setAutoRemoveOnFinish(true);
    
    this->addChild(flower1, 100);
    this->addChild(flower2, 100);
    this->addChild(flower3, 100);
    this->addChild(flower4, 100);

    if (!CCUserDefault::sharedUserDefault()->getBoolForKey("purchased")){
        GameManager::sharedManager()->showInterstitial();
    }
    
    SimpleAudioEngine::sharedEngine()->playEffect("mp3/kidsCheering.mp3");
//    PizzaManager::sharedManager()->cleanAllSprite();
}

void CutPizza::visiSlide(CCObject *pSender){
    CCSprite* sprite = (CCSprite*)pSender;
    if (sprite) {
        sprite->setVisible(true);
        this->scheduleOnce(schedule_selector(CutPizza::playSildeMp3), 0.3);
    }
}

void CutPizza::eatFinish(){
    CCLog("UpdateTarget------GameWin");
//    SimpleAudioEngine::sharedEngine()->playEffect("mp3/yeah.mp3");
    CCPoint rightTopPos = GameManager::sharedManager()->getRightTopPos();

    auto layer = CCLayerColor::create(ccc4(50, 50, 50, 100));
       // 锚点默认是左下角
    layer->setPosition(0,0);
    layer->setTag(5555);
    this->addChild(layer, 999);

    CCLabelTTF* earnCoinLabel1 = CCLabelTTF::create("Congratulation", "Helvetica-Bold",80);
    earnCoinLabel1->CCNode::setPosition(layer->getContentSize().width/2,layer->getContentSize().height/2+150);
    earnCoinLabel1->setColor(ccc3(255, 255, 255));
    layer->addChild(earnCoinLabel1);

//    layer->addChild(you_earn);
    CCLabelTTF* earnCoinLabel = CCLabelTTF::create("You Earned: ", "Helvetica-Bold", 50);
    earnCoinLabel->CCNode::setPosition(layer->getContentSize().width/2-120,layer->getContentSize().height/2);
    earnCoinLabel->setColor(ccc3(255, 255, 255));
    layer->addChild(earnCoinLabel);

    GameManager::sharedManager()->setEarnCoinCount(20);
    GameManager::sharedManager()->saveCurrentCoin();

    CCSprite* coinSpr = CCSprite::create("background/coin.png");
    coinSpr->setPosition(ccp(layer->getContentSize().width/2+80,layer->getContentSize().height/2));
//    coinSpr->setScale(2);
    layer->addChild(coinSpr);

    CCLabelTTF*  Score = CCLabelTTF::create(CCString::createWithFormat(" + %d", 20)->getCString(),"Helvetica-Bold", 50);
    Score->setPosition(ccp(coinSpr->getPosition().x+coinSpr->getContentSize().width+30, coinSpr->getPosition().y));
//    Score->setPosition(ccp(center.x,center.y));
    layer->addChild(Score);

    CCSprite* coinBg = (CCSprite*)this->getChildByTag(kMoney);

    if (coinBg != NULL) {

        curallscores->setString(CCString::createWithFormat("%d",GameManager::sharedManager()->getCurrentCoin())->getCString());

        CCPoint flyTargetPos = layer->convertToNodeSpace(ccp(coinBg->getPosition().x-40, coinBg->getPosition().y));

        for (int i = 0; i < 4; i++) {
            CCSprite* flyCoin = CCSprite::create("background/coin.png");
            flyCoin->setPosition(ccp(earnCoinLabel->getPosition().x+earnCoinLabel->getContentSize().width/2+flyCoin->getContentSize().width*0.7-10, earnCoinLabel->getPosition().y));
            flyCoin->setScale(0.7);
            layer->addChild(flyCoin);

            flyCoin->runAction(CCSequence::create(CCDelayTime::create(0.1+0.1*i),CCEaseIn::create(CCMoveTo::create(1.0, ccp(flyTargetPos.x, flyTargetPos.y)), 0.5),CCCallFunc::create(this, callfunc_selector(CutPizza::collectCoinMusic)),CCCallFuncN::create(this, callfuncN_selector(CutPizza::removeNormalSprite)),NULL));
        }

        CCLabelTTF* plusScore = CCLabelTTF::create(CCString::createWithFormat("+%d",20)->getCString(), "Arial", 30);
        plusScore->setColor(ccc3(200, 200, 200));
        plusScore->setAnchorPoint(ccp(1.0, 0.5));
        plusScore->setPosition(ccp(rightTopPos.x-50, coinBg->getPosition().y-50));
        this->addChild(plusScore,1001);

        plusScore->runAction(CCSequence::create(CCEaseIn::create(CCMoveBy::create(1.5, ccp(0, 30)), 0.5),CCCallFuncN::create(this, callfuncN_selector(CutPizza::removeNormalSprite)),NULL));
    }

    CCSprite* lightBg = CCSprite::create("background/light.png");
    lightBg->setPosition(ccp(coinSpr->getContentSize().width/2, coinSpr->getContentSize().height/2));
//    coinSpr->addChild(lightBg,-1);
//    lightBg->runAction(CCRepeatForever::create(CCRotateBy::create(1.5f, 180.0f)));
    const char* btnPathStr = "background/refresh.png";
    auto item1= CCMenuItemImage::create(btnPathStr, btnPathStr, this,menu_selector(CutPizza::gameComplate));
    auto menu = CCMenu::create(item1, NULL);

    menu->setPosition(ccp(layer->getContentSize().width / 2, layer->getContentSize().height / 2-150));

    layer->addChild(menu);

//    this->setTouchEnabled(false);
    PizzaManager::sharedManager()->noughComplate=false;
}


void CutPizza::gameComplate(){
    if (!CCUserDefault::sharedUserDefault()->getBoolForKey("purchased")){
        if (GameManager::sharedManager()->num == 3){
            GameManager::sharedManager()->showInterstitial();
            GameManager::sharedManager()->num = 0;
        }else{
            GameManager::sharedManager()->num++;
        }
    }
    SimpleAudioEngine::sharedEngine()->playEffect("mp3/button_click.mp3");
    CCUserDefault::sharedUserDefault()->setBoolForKey("isHavePlayPizza", false);
    PizzaManager::sharedManager()->havePlay = false;
    PizzaManager::sharedManager()->cleanAllSprite();
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.0, SelectPizza::scene(), ccWHITE));
}

void CutPizza::collectCoinMusic(){
    SimpleAudioEngine::sharedEngine()->playEffect("mp3/get_prop.mp3");
}
void CutPizza::removeNormalSprite(CCObject *pSender){
    CCSprite* _sprite = (CCSprite*)pSender;
    if (_sprite != NULL) {
        _sprite->stopAllActions();
        _sprite->removeFromParentAndCleanup(true);
        _sprite = NULL;
    }
}

void CutPizza::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent){
    CCTouch *pTouch = (CCTouch*)(pTouches->anyObject());
    CCPoint location = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
    CCSprite* back = (CCSprite*)this->getChildByTag(kBack);
    if (back!=NULL && back->boundingBox().containsPoint(location) && backClick == false) {
        backClick = true;
        CCUserDefault::sharedUserDefault()->setBoolForKey("isHavePlayPizza", false);
        PizzaManager::sharedManager()->havePlay = false;
//        SimpleAudioEngine::sharedEngine()->playEffect("mp3/done.mp3");
        PizzaManager::sharedManager()->cleanAllSprite();
        CCScaleBy* scaleBy = CCScaleBy::create(0.1, 1.2);
        //            homeBtn->setScale(1.2);
        //            touchSprite = homeBtn;
        SimpleAudioEngine::sharedEngine()->playEffect("mp3/touchItem.mp3");
        back->runAction(CCSequence::createWithTwoActions(CCSequence::createWithTwoActions(scaleBy, scaleBy->reverse()), CCCallFunc::create(this, callfunc_selector(CutPizza::clickBack))));
        
        
    }
}

void CutPizza::clickBack(){
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, SelectPizza::scene(), ccBLACK));
}

void CutPizza::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent){
    
}

void CutPizza::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent){
    
}
