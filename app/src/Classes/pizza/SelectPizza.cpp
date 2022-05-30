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
#include "BuyPage.h"
#include "MakeSauce.h"
#include "MakePizza.h"
#include "AddTopping.h"
#include "FirstScene.h"


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
    CCPoint center = GameManager::sharedManager()->getCenter();
    CCPoint leftTop = GameManager::sharedManager()->getLeftTopPos();
    CCPoint rightTop = GameManager::sharedManager()->getRightTopPos();
    CCPoint leftBottom = GameManager::sharedManager()->getLeftBottomPos();

    CCPoint rightBottom = GameManager::sharedManager()->getRightBottomPos();
    
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
        x_x = 0;
        x_y = 100;
    }

    if (!CCUserDefault::sharedUserDefault()->getBoolForKey("purchased")){
        GameManager::sharedManager()->showBanner();
    }

    //导量
    if (CCUserDefault::sharedUserDefault()->getBoolForKey("purchased") == false){

        bt_firstword = NULL;
        bt_wordbreak = NULL;
        bt_wordblock = NULL;
        bt_shapepuzzle = NULL;
        bt_Jorland = NULL;
        bt_Match = NULL;

        bt_ad = CCSprite::create("ad.png");
        bt_background = CCSprite::create("background.png");
        this->addChild(bt_background,1);
        bt_background->setPosition(ccp(leftBottom.x+bt_background->getContentSize().width/2.0-22,leftBottom.y+bt_background->getContentSize().height/2.0-22));
        bt_ad->setPosition(ccp(leftBottom.x+bt_ad->getContentSize().width/2.0-2,leftBottom.y+bt_ad->getContentSize().height/2.0-2));
        bt_background->setScale(0.7);
        bt_ad->setScale(0.7);
        select = arc4random()%8;
        switch (select){
            case 0:{
                bt_firstword = CCSprite::create("firstword.png");
                this->addChild(bt_firstword,1);
                bt_firstword->setPosition(ccp(leftBottom.x+bt_firstword->getContentSize().width/2.0-50,leftBottom.y+bt_firstword->getContentSize().height/2.0-40));
                bt_firstword->setScale(0.7);
            }
                break;
            case 1:{
                bt_shapepuzzle = CCSprite::create("shapepuzzle.png");
                this->addChild(bt_shapepuzzle,1);
                bt_shapepuzzle->setPosition(ccp(leftBottom.x+bt_shapepuzzle->getContentSize().width/2.0-50,leftBottom.y+bt_shapepuzzle->getContentSize().height/2.0-40));
                bt_shapepuzzle->setScale(0.7);
            }
                break;
            case 2:{
                bt_wordblock = CCSprite::create("otherGame_WordBlock.png");
                this->addChild(bt_wordblock,1);
                bt_wordblock->setPosition(ccp(leftBottom.x+bt_wordblock->getContentSize().width/2.0-14,leftBottom.y+bt_wordblock->getContentSize().height/2.0-12));
                bt_wordblock->setScale(0.6);
            }
                break;
            case 3:{
                bt_wordbreak = CCSprite::create("otherGame_WordBreak.png");
                this->addChild(bt_wordbreak,1);
                bt_wordbreak->setPosition(ccp(leftBottom.x+bt_wordbreak->getContentSize().width/2.0-14,leftBottom.y+bt_wordbreak->getContentSize().height/2.0-12));
                bt_wordbreak->setScale(0.6);
            }
                break;
            case 4:{
                bt_firstword = CCSprite::create("otherGame_FirstWords.png");
                this->addChild(bt_firstword,1);
                bt_firstword->setPosition(ccp(leftBottom.x+bt_firstword->getContentSize().width/2.0-17,leftBottom.y+bt_firstword->getContentSize().height/2.0-12));
                bt_firstword->setScale(0.6);
            }
                break;
            case 5:{
                bt_shapepuzzle = CCSprite::create("otherGame_ShapePuzzle.png");
                this->addChild(bt_shapepuzzle,1);
                bt_shapepuzzle->setPosition(ccp(leftBottom.x+bt_shapepuzzle->getContentSize().width/2.0-17,leftBottom.y+bt_shapepuzzle->getContentSize().height/2.0-12));
                bt_shapepuzzle->setScale(0.6);
            }
                break;
            case 6:{
                bt_Jorland = CCSprite::create("otherGame_Joyland.png");
                this->addChild(bt_Jorland,1);
                bt_Jorland->setPosition(ccp(leftBottom.x+bt_Jorland->getContentSize().width/2.0-17,leftBottom.y+bt_Jorland->getContentSize().height/2.0-12));
                bt_Jorland->setScale(0.6);
            }
                break;
            case 7:{
                bt_Match = CCSprite::create("otherGame_Match.png");
                this->addChild(bt_Match,1);
                bt_Match->setPosition(ccp(leftBottom.x+bt_Match->getContentSize().width/2.0-17,leftBottom.y+bt_Match->getContentSize().height/2.0-12));
                bt_Match->setScale(0.6);
            }
                break;
            default:
                break;
        }
        this->addChild(bt_ad,1);


        CCMenuItemImage* noadsItem = CCMenuItemImage::create("noAds.png", "noAds.png", this, menu_selector(SelectPizza::clickBuy));
//        noadsItem->setScale(1.2);
        CCMenu* noadsMenu = CCMenu::create(noadsItem,NULL);
//    reviewMenu->setPosition(ccp(homeMenu->getPosition().x+homeItem->getContentSize().width/2+reviewItem->getContentSize().width/2, homeMenu->getPosition().y));
        noadsMenu->setPosition(ccp(rightBottom.x-noadsItem->getContentSize().width/2,leftBottom.y+noadsItem->getContentSize().height-40));
        this->addChild(noadsMenu, 110);

    }

    this->setTouchEnabled(true);
    this->showPizzaTaste();
    return true;
}

void SelectPizza::clickBuy(){
    SimpleAudioEngine::sharedEngine()->playEffect("universal/pressBt.mp3");
    GameManager::sharedManager()->goToBuyIAP(0);
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
//        if (i<3) {
        //圣诞节
//        if (i==6) {
//            index=0;
//        }else if(i>6){
//            index=i;
//        }else{
//            index=i+1;
//        }

        taste->setPosition(ccp(300-x_y+(i%3)*(305-x_x), 510-(i/3)*190));
//        }else if(i>=3){
//            taste->setPosition(ccp(280+(i-3)*(320-x_x), 190));
//        }
        if (GameManager::sharedManager()->isAndroidPad()) {
            taste->setScale(0.7);
        }
        taste->setTag(kTaste+i);
        this->addChild(taste);
        CCLog("---%d---",PizzaManager::sharedManager()->havePlay);
        if (!CCUserDefault::sharedUserDefault()->getBoolForKey("purchased")){
//            if (PizzaManager::sharedManager()->havePlay) {
                if (i>1) {
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
        if (!CCUserDefault::sharedUserDefault()->getBoolForKey("purchased")){
            if (GameManager::sharedManager()->num == 3){
                GameManager::sharedManager()->showInterstitial();
                GameManager::sharedManager()->num = 0;
            }else{
                GameManager::sharedManager()->num++;
            }
        }
        CCScaleBy* scaleBy = CCScaleBy::create(0.1, 1.2);
        //            homeBtn->setScale(1.2);
        //            touchSprite = homeBtn;
        SimpleAudioEngine::sharedEngine()->playEffect("mp3/touchItem.mp3");
        back->runAction(CCSequence::createWithTwoActions(CCSequence::createWithTwoActions(scaleBy, scaleBy->reverse()), CCCallFunc::create(this, callfunc_selector(SelectPizza::clickBack))));
    }else{
        for (int i = 0; i<9; i++) {
            CCSprite* pizzaTaste = (CCSprite*)this->getChildByTag(kTaste+i);
            if (pizzaTaste!=NULL && pizzaTaste->boundingBox().containsPoint(location)) {
                if ((i<=1) || (CCUserDefault::sharedUserDefault()->getBoolForKey("purchased"))) {
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
                }else{
                    this->openIAPPage();
                }
                
            }
        }
    }


    
}

void SelectPizza::goToNext(){
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.0, MakeDough::scene(), ccBLACK));
//    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.0, AddTopping::scene(), ccBLACK));
}

void SelectPizza::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent){
    
}

void SelectPizza::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent){
    CCTouch *pTouch = (CCTouch*)(pTouches->anyObject());
    CCPoint location = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());

    if (CCUserDefault::sharedUserDefault()->getBoolForKey("purchased") == false && backClick==false){
        //导量
        if (bt_firstword != NULL && bt_firstword->boundingBox().containsPoint(location)){

            SimpleAudioEngine::sharedEngine()->playEffect("universal/pressBt.mp3");

            GameManager::sharedManager()->otherGame(3);
        }
        else if (bt_shapepuzzle != NULL && bt_shapepuzzle->boundingBox().containsPoint(location)){
            SimpleAudioEngine::sharedEngine()->playEffect("universal/pressBt.mp3");

            GameManager::sharedManager()->otherGame(2);
        }
        else if (bt_wordblock != NULL && bt_wordblock->boundingBox().containsPoint(location)){

            SimpleAudioEngine::sharedEngine()->playEffect("universal/pressBt.mp3");

            GameManager::sharedManager()->otherGame(1);
        }
        else if (bt_wordbreak != NULL && bt_wordbreak->boundingBox().containsPoint(location)){

            SimpleAudioEngine::sharedEngine()->playEffect("universal/pressBt.mp3");

            GameManager::sharedManager()->otherGame(0);
        }
        else if (bt_Jorland != NULL && bt_Jorland->boundingBox().containsPoint(location)){

            SimpleAudioEngine::sharedEngine()->playEffect("universal/pressBt.mp3");

            GameManager::sharedManager()->otherGame(4);
        }
        else if (bt_Match != NULL && bt_Match->boundingBox().containsPoint(location)){

            SimpleAudioEngine::sharedEngine()->playEffect("universal/pressBt.mp3");

            GameManager::sharedManager()->otherGame(5);
        }
    }

}
