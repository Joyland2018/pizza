//
// Created by LiXiaofei on 5/28/22.
//

#include "FirstScene.h"
#include "GameManager.h"
#include "MakeDough.h"
#include "SimpleAudioEngine.h"
#include "PizzaManager.h"
//#include "DeviceManager.h"
//#include "DinoTownScene.h"
#include "BuyPage.h"
#include "MakeSauce.h"
#include "MakePizza.h"
#include "AddTopping.h"
#include "SelectPizza.h"

using namespace cocos2d;
using namespace CocosDenshion;

enum{
    kBackground = 0,
    kStart = 1,
    kFire=5,
    kSteam=10,
    kBuylayerTag = 900,
};

CCScene* FirstScene::scene(){
    CCScene* scene = CCScene::create();
    FirstScene* layer = FirstScene::create();
    scene->addChild(layer);
    return  scene;
}

void FirstScene::onEnter(){
    CCLayer::onEnter();
    touchStart = false;
    CCPoint center = GameManager::sharedManager()->getCenter();
    CCPoint leftTop = GameManager::sharedManager()->getLeftTopPos();
    CCPoint rightTop = GameManager::sharedManager()->getRightTopPos();
    CCPoint leftBottom = GameManager::sharedManager()->getLeftBottomPos();

    //返回按钮
    CCSprite* back=CCSprite::create("background/bg.png");
    back->setPosition(ccp(center.x,center.y));
    this->addChild(back,1);

    if(GameManager::sharedManager()->isIphoneX()){
        back->setScale(1.3);
    }

    CCSprite* start=CCSprite::create("background/start.png");
    start->setPosition(ccp(center.x-170,center.y-50));
    start->setTag(kStart);
    this->addChild(start,1);

    CCRepeatForever* repeatplay = CCRepeatForever::create(CCSequence::create(CCScaleTo::create(0.5, 1.3),
                                                                             CCScaleTo::create(0.5, 1),
                                                                             NULL));

    start->runAction(repeatplay);

    bt_firstword = NULL;
    bt_wordbreak = NULL;
    bt_wordblock = NULL;
    bt_shapepuzzle = NULL;
    bt_Jorland = NULL;
    bt_Match = NULL;

    if (CCUserDefault::sharedUserDefault()->getBoolForKey("purchased") == false){
        //导量
        bt_firstword = CCSprite::create("otherGame_FirstWords.png");
        bt_shapepuzzle = CCSprite::create("otherGame_ShapePuzzle.png");
        bt_wordblock = CCSprite::create("otherGame_WordBlock.png");
        bt_wordbreak = CCSprite::create("otherGame_WordBreak.png");
        bt_Jorland = CCSprite::create("otherGame_Joyland.png");
        bt_Match = CCSprite::create("otherGame_Match.png");
        bt_ad = CCSprite::create("ad.png");
        bt_background = CCSprite::create("background.png");

        bt_firstword->setPosition(ccp(leftTop.x+bt_firstword->getContentSize().width/2.0+5,leftTop.y-bt_firstword->getContentSize().height/2.0+5));
        bt_firstword->setScale(0.65);
        bt_shapepuzzle->setPosition(ccp(leftTop.x+bt_shapepuzzle->getContentSize().width/2.0+5,leftTop.y-bt_shapepuzzle->getContentSize().height/2.0-95));
        bt_shapepuzzle->setScale(0.65);
        bt_wordblock->setPosition(ccp(leftTop.x+bt_wordblock->getContentSize().width/2.0+5,leftTop.y-bt_wordblock->getContentSize().height/2.0-195));
        bt_wordblock->setScale(0.65);
        bt_wordbreak->setPosition(ccp(leftTop.x+bt_wordbreak->getContentSize().width/2.0+5,leftTop.y-bt_wordbreak->getContentSize().height/2.0-295));
        bt_wordbreak->setScale(0.65);
        bt_Jorland->setPosition(ccp(leftTop.x+bt_Jorland->getContentSize().width/2.0+5,leftTop.y-bt_Jorland->getContentSize().height/2.0-395));
        bt_Jorland->setScale(0.65);
        bt_Match->setPosition(ccp(leftTop.x+bt_Match->getContentSize().width/2.0+5,leftTop.y-bt_Match->getContentSize().height/2.0-495));
        bt_Match->setScale(0.65);
        bt_ad->setPosition(ccp(leftBottom.x+bt_ad->getContentSize().width/2.0,leftBottom.y+bt_ad->getContentSize().height/2.0+12));
        bt_background->setPosition(ccp(leftTop.x+bt_background->getContentSize().width/2.0,leftTop.y-bt_background->getContentSize().height/2.0-240));
        bt_background->setScaleY(4);

        this->addChild(bt_background,10);
        this->addChild(bt_firstword,10);
        this->addChild(bt_shapepuzzle,10);
        this->addChild(bt_wordblock,10);
        this->addChild(bt_wordbreak,10);
        this->addChild(bt_Jorland,10);
        this->addChild(bt_Match,10);
        this->addChild(bt_ad,10);

    }
    if (!CCUserDefault::sharedUserDefault()->getBoolForKey("purchased")){
        GameManager::sharedManager()->showBanner();
    }

    SimpleAudioEngine::sharedEngine()->playBackgroundMusic("mp3/beginBg.mp3",true);
    this->scheduleOnce(schedule_selector(FirstScene::fireAction), 0.1f);
    this->scheduleOnce(schedule_selector(FirstScene::steamAction), 0.1f);
    this->setTouchEnabled(true);
}


void FirstScene::fireAction() {
    CCPoint center = GameManager::sharedManager()->getCenter();
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("background/logofire.plist");
    CCSprite* fire = CCSprite::createWithSpriteFrameName("fire_1.png");
    fire->setPosition(ccp(center.x-400,center.y-20));
    fire->setTag(kFire);
    fire->runAction(CCFadeIn::create(0.3));
    this->addChild(fire,6);
    this->schedule(schedule_selector(FirstScene::fireActions), 0.5f);
}

void FirstScene::fireActions() {
    CCSprite* fire=(CCSprite*)this->getChildByTag(kFire);
    CCArray* frame = CCArray::create();
    for (int m =1; m<3; m++) {
        CCString *name = CCString::createWithFormat("fire_%d.png",m);
        frame->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString()));
    }
    CCAnimation *animation = CCAnimation::createWithSpriteFrames(frame);
    animation->setDelayPerUnit(0.3f);
    CCAnimate *animate = CCAnimate::create(animation);
    fire->runAction(animate);
}

void FirstScene::steamAction() {
        CCPoint center = GameManager::sharedManager()->getCenter();
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("background/steam.plist");
        CCSprite* steam = CCSprite::createWithSpriteFrameName("steam1.png");
        steam->setPosition(ccp(center.x+30,center.y-50));
        //    iphone->setScale(1.2);
        steam->setTag(kSteam);
        steam->runAction(CCFadeIn::create(0.3));
        this->addChild(steam,6);
        this->schedule(schedule_selector(FirstScene::steamActions), 0.5f);

}

void FirstScene::steamActions() {
    CCSprite* steam=(CCSprite*)this->getChildByTag(kSteam);
    CCArray* frame = CCArray::create();
    for (int m =1; m<4; m++) {
        CCString *name = CCString::createWithFormat("steam%d.png",m);
        frame->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString()));
    }
    CCAnimation *animation = CCAnimation::createWithSpriteFrames(frame);
    animation->setDelayPerUnit(0.2f);
    CCAnimate *animate = CCAnimate::create(animation);
    steam->runAction(animate);
}

void FirstScene::onExit(){
    CCLayer::onExit();
}

FirstScene::FirstScene(){

}

FirstScene::~FirstScene(){
}


bool FirstScene::init(){
    if (!CCLayer::init()) {
        return false;
    }



    return true;
}





void FirstScene::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent){
    CCTouch *pTouch = (CCTouch*)(pTouches->anyObject());
    CCPoint location = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
    CCSprite* start = (CCSprite*)this->getChildByTag(kStart);
    if (start && start->boundingBox().containsPoint(location) && touchStart==false){
        SimpleAudioEngine::sharedEngine()->playEffect("universal/pressBt.mp3");
        touchStart=true;
        this->goToNext();
    }

    if (CCUserDefault::sharedUserDefault()->getBoolForKey("purchased") == false){
        if (bt_firstword != NULL && bt_firstword->boundingBox().containsPoint(location)){

            SimpleAudioEngine::sharedEngine()->playEffect("universal/pressBt.mp3");

            GameManager::sharedManager()->otherGame(3);
        }
        if (bt_shapepuzzle != NULL && bt_shapepuzzle->boundingBox().containsPoint(location)){
            SimpleAudioEngine::sharedEngine()->playEffect("universal/pressBt.mp3");

            GameManager::sharedManager()->otherGame(2);
        }
        if (bt_wordblock != NULL && bt_wordblock->boundingBox().containsPoint(location)){

            SimpleAudioEngine::sharedEngine()->playEffect("universal/pressBt.mp3");

            GameManager::sharedManager()->otherGame(1);
        }
        if (bt_wordbreak != NULL && bt_wordbreak->boundingBox().containsPoint(location)){

            SimpleAudioEngine::sharedEngine()->playEffect("universal/pressBt.mp3");

            GameManager::sharedManager()->otherGame(0);
        }
        if (bt_Jorland != NULL && bt_Jorland->boundingBox().containsPoint(location)){

            SimpleAudioEngine::sharedEngine()->playEffect("universal/pressBt.mp3");

            GameManager::sharedManager()->otherGame(4);
        }
        if (bt_Match != NULL && bt_Match->boundingBox().containsPoint(location)){

            SimpleAudioEngine::sharedEngine()->playEffect("universal/pressBt.mp3");

            GameManager::sharedManager()->otherGame(5);
        }

    }
}

void FirstScene::goToNext(){
    if (!CCUserDefault::sharedUserDefault()->getBoolForKey("purchased")){
            GameManager::sharedManager()->showInterstitial();
    }
    SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    this->unschedule(schedule_selector(FirstScene::fireAction));
    this->unschedule(schedule_selector(FirstScene::steamAction));
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.0, SelectPizza::scene(), ccBLACK));
//    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.0, AddTopping::scene(), ccBLACK));
}

void FirstScene::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent){

}

void FirstScene::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent){}
