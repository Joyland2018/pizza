//
//  CutTopping.cpp
//  Pizza
//
//  Created by LiXiaofei on 4/2/21.
//

#include "CutTopping.h"
#include "SimpleAudioEngine.h"
#include "GameManager.h"
#include "SelectTopping.h"
#include "MakePizza.h"
#include "PizzaManager.h"
#include "AddTopping.h"


using namespace CocosDenshion;

enum{
    kBack=0,
    kTopping=10,
    kDone=1,
    kPepporoni = 2,
    kBoluo=3,
    kMogu=4,
    kBocai=5,
    kRouwan=6,
    kLajiao=7,
    kXiLanHua=8,
    kPotato=9,
    kPengen=11,
};

CCScene* CutTopping::scene(){
    CCScene* scene = CCScene::create();
    CutTopping* layer = CutTopping::create();
    scene->addChild(layer);
    return scene;
}

void CutTopping::onEnter(){
    CCLayer::onEnter();
}

void CutTopping::onExit(){
    CCLayer::onExit();
}

CutTopping::CutTopping(){}
CutTopping::~CutTopping(){}

bool CutTopping::init(){
    if (!CCLayer::init()) {
        return false;
    }
    
    backClick = false;
    CCPoint visibleOrigin=CCDirector::sharedDirector()->getVisibleOrigin();
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    center = GameManager::sharedManager()->getCenter();
    CCPoint leftTop = GameManager::sharedManager()->getLeftTopPos();
    CCPoint rightTop = GameManager::sharedManager()->getRightTopPos();
    
    
    CCSprite* bg = CCSprite::create("background/tablecloth.png");
    bg->setPosition(center);
    this->addChild(bg);
    
    CCSprite* board = CCSprite::create("background/board.png");
    board->setPosition(center);
    this->addChild(board);
    
    CCSprite* back = CCSprite::create("background/back.png");
    back->setPosition(ccp(leftTop.x+50,leftTop.y-50));
    back->setTag(kBack);
    this->addChild(back);
    
    this->setTouchEnabled(true);
    
    pizzaLineSprite = PizzaLineSprite::create();
    this->addChild(pizzaLineSprite,10);
    
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
    
    if(GameManager::sharedManager()->firstPlayPizza){
        this->schedule(schedule_selector(CutTopping::showFinger),1.5f);
    }
    if (PizzaManager::sharedManager()->whichPizza == 7 || PizzaManager::sharedManager()->whichPizza == 8) {
        this->scheduleOnce(schedule_selector(CutTopping::showTopping), 0.5);
    }else if(PizzaManager::sharedManager()->whichPizza == 0){
        this->pepperoniTopping();
    }else if(PizzaManager::sharedManager()->whichPizza == 5){
        this->showBoluo();
    }

    if (!CCUserDefault::sharedUserDefault()->getBoolForKey("purchased")){
        GameManager::sharedManager()->showBanner();
    }
//    this->showTopping();
    return true;
}

//手指提示
void CutTopping::showFinger(){
    
    CCSize winSize = GameManager::sharedManager()->getViewVisibleSize();
    CCSprite* fingerTouch = CCSprite::create("background/touch0.png");
    fingerTouch->setPosition(ccp(center.x, center.y+100));
    fingerTouch->setScale(0.6);
    this->addChild(fingerTouch,11);
    fingerTouch->setOpacity(0);
    fingerTouch->runAction(CCSequence::create(CCFadeIn::create(0.4),
                                              CCEaseOut::create(CCMoveTo::create(0.8, ccp(center.x, center.y-100)), 1.0f),
                                                                CCFadeOut::create(0.4),
                                                                CCCallFuncN::create(this, callfuncN_selector(CutTopping::removeSprite)),
                                              NULL));
}

void CutTopping::removeSprite(CCObject *pSender){
    CCSprite* sprite = (CCSprite*)pSender;
    if(sprite!=NULL){
        sprite->removeAllChildrenWithCleanup(true);
        sprite->stopAllActions();
        sprite->removeFromParentAndCleanup(true);
        sprite=NULL;
    }
}


void CutTopping::showTopping(){
    
    if (PizzaManager::sharedManager()->tomatoSelected) {
        this->showTomato();
    }else if(PizzaManager::sharedManager()->xilanhuaSelected){
        this->showXiLanHua();
    }else if(PizzaManager::sharedManager()->moguSelected){
        this->showMogu();
    }else if(PizzaManager::sharedManager()->pepperSelected){
        this->showLajiao();
    }else if(PizzaManager::sharedManager()->boluoSelected){
        this->showBoluo();
    }else if(PizzaManager::sharedManager()->bocaiSelected){
        this->showBocai();
    }else if(PizzaManager::sharedManager()->baconsSelected){
        this->showPeigen();
    }else if(PizzaManager::sharedManager()->meatSelected){
        this->showRouwan();
    }else if(PizzaManager::sharedManager()->changSelected){
        this->pepperoniTopping();
    }else{
        this->goNext();
    }
}

//void CutTopping::cheeseTopping(){
//    
//}


void CutTopping::pepperoniTopping(){
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("pizza/animate/sausage.plist");
    CCSprite* pepperoni = CCSprite::createWithSpriteFrameName("sausage1.png");
    pepperoni->setPosition(ccp(center.x-1000, center.y));
    pepperoni->runAction(CCSequence::create(CCEaseIn::create(CCMoveTo::create(1.0, ccp(center.x, center.y)), 0.2f),
                                            CCCallFunc::create(this, callfunc_selector(CutTopping::isCancut)),
                                            NULL));
    pepperoni->setTag(kPepporoni);
    this->addChild(pepperoni,2);
    chang = true;
    PizzaManager::sharedManager()->changSelected=false;
}

void CutTopping::showBoluo(){
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("pizza/animate/pineapple.plist");
    CCSprite* boluo = CCSprite::createWithSpriteFrameName("pineapple1.png");
    boluo->setPosition(ccp(center.x-1000, center.y));
    boluo->runAction(CCSequence::create(CCEaseIn::create(CCMoveTo::create(1.0, ccp(center.x, center.y)), 0.2f),
                                        CCCallFunc::create(this, callfunc_selector(CutTopping::isCancut)),
                                        NULL));
    boluo->setTag(kBoluo);
    this->addChild(boluo,2);
    pineapple = true;
    PizzaManager::sharedManager()->boluoSelected=false;
}

void CutTopping::showMogu(){
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("pizza/animate/mushroom.plist");
    CCSprite* mogu = CCSprite::createWithSpriteFrameName("mushroom1.png");
    mogu->setPosition(ccp(center.x-1000, center.y));
    mogu->runAction(CCSequence::create(CCEaseIn::create(CCMoveTo::create(1.0, ccp(center.x, center.y)), 0.2f),
                                       CCCallFunc::create(this, callfunc_selector(CutTopping::isCancut)),
                                       NULL));
    mogu->setTag(kMogu);
    this->addChild(mogu,2);
    mushroom = true;
    PizzaManager::sharedManager()->moguSelected=false;
}

void CutTopping::showBocai(){
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("pizza/animate/spinach.plist");
    CCSprite* bocai = CCSprite::createWithSpriteFrameName("spinach1.png");
    bocai->setPosition(ccp(center.x-1000, center.y));
    bocai->runAction(CCSequence::create(CCEaseIn::create(CCMoveTo::create(1.0, ccp(center.x, center.y)), 0.2f),
                                        CCCallFunc::create(this, callfunc_selector(CutTopping::isCancut)),
                                        NULL));
    bocai->setTag(kBocai);
    this->addChild(bocai,2);
    spinach = true;
    PizzaManager::sharedManager()->bocaiSelected=false;
}

void CutTopping::showXiLanHua(){
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("pizza/animate/xilanhua.plist");
    CCSprite* bocai = CCSprite::createWithSpriteFrameName("xilanhua1.png");
    bocai->setPosition(ccp(center.x-1000, center.y));
    bocai->runAction(CCSequence::create(CCEaseIn::create(CCMoveTo::create(1.0, ccp(center.x, center.y)), 0.2f),
                                        CCCallFunc::create(this, callfunc_selector(CutTopping::isCancut)),
                                        NULL));
    bocai->setTag(kXiLanHua);
    this->addChild(bocai,2);
    xilanhuas=true;
    PizzaManager::sharedManager()->xilanhuaSelected =  false;
}

void CutTopping::showLajiao(){
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("pizza/animate/pepper.plist");
    CCSprite* lajiao = CCSprite::createWithSpriteFrameName("pepper1.png");
    lajiao->setPosition(ccp(center.x-1000, center.y));
    lajiao->runAction(CCSequence::create(CCEaseIn::create(CCMoveTo::create(1.0, ccp(center.x, center.y)), 0.2f),
                                        CCCallFunc::create(this, callfunc_selector(CutTopping::isCancut)),
                                        NULL));
    lajiao->setTag(kLajiao);
    this->addChild(lajiao,2);
    pepper=true;
    PizzaManager::sharedManager()->pepperSelected=false;
}

void CutTopping::showTomato(){
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("pizza/animate/tomato.plist");
    CCSprite* potato = CCSprite::createWithSpriteFrameName("tomato1.png");
    potato->setPosition(ccp(center.x-1000, center.y));
    potato->runAction(CCSequence::create(CCEaseIn::create(CCMoveTo::create(1.0, ccp(center.x, center.y)), 0.2f),
                                        CCCallFunc::create(this, callfunc_selector(CutTopping::isCancut)),
                                        NULL));
    potato->setTag(kPotato);
//    potato->setScale(1.5);
    this->addChild(potato,2);
    potatos = true;
    PizzaManager::sharedManager()->tomatoSelected=false;
}

void CutTopping::showRouwan(){
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("pizza/animate/meatball.plist");
    CCSprite* rouwan = CCSprite::createWithSpriteFrameName("meatball1.png");
    rouwan->setPosition(ccp(center.x-1000, center.y));
    rouwan->runAction(CCSequence::create(CCEaseIn::create(CCMoveTo::create(1.0, ccp(center.x, center.y)), 0.2f),
                                        CCCallFunc::create(this, callfunc_selector(CutTopping::isCancut)),
                                        NULL));
    rouwan->setTag(kRouwan);
    this->addChild(rouwan,2);
    rouwans = true;
    PizzaManager::sharedManager()->meatSelected=false;
}


void CutTopping::showPeigen(){
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("pizza/animate/bacons.plist");
    CCSprite* peigen = CCSprite::createWithSpriteFrameName("bacons1.png");
    peigen->setPosition(ccp(center.x-1000, center.y));
    peigen->runAction(CCSequence::create(CCEaseIn::create(CCMoveTo::create(1.0, ccp(center.x, center.y)), 0.2f),
                                        CCCallFunc::create(this, callfunc_selector(CutTopping::isCancut)),
                                        NULL));
    peigen->setTag(kPengen);
    this->addChild(peigen,2);
    pengens =true;
    PizzaManager::sharedManager()->baconsSelected=false;
}


void CutTopping::goNext(){
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.0, AddTopping::scene(), ccBLACK));
}

void CutTopping::isCancut(){
    canCuttop=true;
}

void CutTopping::CannotCut(){
    canCuttop=false;
}

void CutTopping::noPotato(){
    potatos=false;
}

void CutTopping::noXilanhua(){
    xilanhuas=false;
}
void CutTopping::noMogu(){
    mushroom=false;
}
void CutTopping::noPepper(){
    pepper=false;
}
void CutTopping::noBoluo(){
    pineapple=false;
}
void CutTopping::noBocai(){
    spinach=false;
}
void CutTopping::noChang(){
    chang=false;
}
void CutTopping::noRouwan(){
    rouwans=false;
}
void CutTopping::noPengen(){
    pengens=false;
}

void CutTopping::setComplate(){
    isMoveComplate=false;
}

void CutTopping::resetCutNum(){
    cutNum=1;
}

void CutTopping::tomatoAction(int index){
    CCSprite* potato=(CCSprite*)this->getChildByTag(kPotato);
//    CCString *name = CCString::createWithFormat("spoon%d.png",sausageIndex);
//    CCSpriteFrame*  spoonAction= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString());
//    sausage->setDisplayFrame(spoonAction);
//    if(potato!=NULL && potato->boundingBox().containsPoint(newPoint) && canCuttop && !isMoveComplate){
//        index++;
        isMoveComplate=true;
        
        CCString *name = CCString::createWithFormat("tomato%d.png",index);
        CCSpriteFrame*  tomatoAction= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString());
        potato->setDisplayFrame(tomatoAction);
        if (index == 4) {
//            isMoveComplate=true;
//            cutNum=1;
            potato->runAction(CCSequence::create(CCCallFunc::create(this, callfunc_selector(CutTopping::CannotCut)),
                                                 CCCallFunc::create(this, callfunc_selector(CutTopping::noPotato)),
                                                 CCCallFunc::create(this, callfunc_selector(CutTopping::setComplate)),
                                                 CCCallFunc::create(this, callfunc_selector(CutTopping::resetCutNum)),
                                                 CCEaseOut::create(CCMoveTo::create(1.0, ccp(center.x-1000, center.y)), 0.2f),
                                                 CCCallFunc::create(this, callfunc_selector(CutTopping::showTopping)),
            //                                              scheduleOnce(schedule_selector(CutTopping::showTopping), 0.3),
                                                 
                                                 NULL));
        }
//    }
//        potato->setSpriteFrame();
//        CCArray* frame = CCArray::create();
//               for (int m =1; m<6; m++) {
//                   CCString *name = CCString::createWithFormat("tomato%d.png",m);
//                   frame->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString()));
//               }
//        CCAnimation *animation = CCAnimation::createWithSpriteFrames(frame);
//        animation->setDelayPerUnit(0.2f);
//        CCAnimate *animate = CCAnimate::create(animation);
////        CCFiniteTimeAction *action1=CCSpawn::create(animate,
//////                                                                                      CCCallFunc::create(this, callfunc_selector(CutTopping::cutLemonMusic)),
////                                                    NULL);
//        potato->runAction(CCSequence::create(animate,
//                                              CCDelayTime::create(0.3),
//                                              CCEaseOut::create(CCMoveTo::create(1.0, ccp(center.x-1000, center.y)), 0.2f),
//                                              CCCallFunc::create(this, callfunc_selector(CutTopping::showTopping)),
////                                              scheduleOnce(schedule_selector(CutTopping::showTopping), 0.3),
//                                              CCCallFunc::create(this, callfunc_selector(CutTopping::CannotCut)),
//                                             CCCallFunc::create(this, callfunc_selector(CutTopping::noPotato)),
//                                             CCCallFunc::create(this, callfunc_selector(CutTopping::setComplate)),
//                                              NULL));
////        break;
//    }
}


//至尊

void CutTopping::rouwanAction(int index){
    CCSprite* rouwan=(CCSprite*)this->getChildByTag(kRouwan);
//    CCString *name = CCString::createWithFormat("spoon%d.png",sausageIndex);
//    CCSpriteFrame*  spoonAction= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString());
//    sausage->setDisplayFrame(spoonAction);
//    if(rouwan!=NULL && rouwan->boundingBox().containsPoint(newPoint) && canCuttop && !isMoveComplate){
//        index++;
        isMoveComplate = true;
//        cutNum++;
        CCString *name = CCString::createWithFormat("meatball%d.png",index);
        CCSpriteFrame*  rouwanAction= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString());
        rouwan->setDisplayFrame(rouwanAction);
        if (index==4) {
//            isMoveComplate=true;
//            cutNum=1;
            rouwan->runAction(CCSequence::create(CCCallFunc::create(this, callfunc_selector(CutTopping::CannotCut)),
                                                 CCCallFunc::create(this, callfunc_selector(CutTopping::noRouwan)),
                                                 CCCallFunc::create(this, callfunc_selector(CutTopping::setComplate)),
                                                 CCCallFunc::create(this, callfunc_selector(CutTopping::resetCutNum)),
                                                 CCEaseOut::create(CCMoveTo::create(1.0, ccp(center.x-1000, center.y)), 0.2f),
                                                 CCCallFunc::create(this, callfunc_selector(CutTopping::showTopping)),
                                                 
                                                  NULL));
        }
        
//        CCArray* frame = CCArray::create();
//               for (int m =1; m<5; m++) {
//                   CCString *name = CCString::createWithFormat("meatball%d.png",m);
//                   frame->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString()));
//               }
//        CCAnimation *animation = CCAnimation::createWithSpriteFrames(frame);
//        animation->setDelayPerUnit(0.2f);
//        CCAnimate *animate = CCAnimate::create(animation);
////        CCFiniteTimeAction *action1=CCSpawn::create(animate,
//////                                                                                      CCCallFunc::create(this, callfunc_selector(CutTopping::cutLemonMusic)),
////                                                    NULL);
//        rouwan->runAction(CCSequence::create(animate,
//                                              CCDelayTime::create(0.3),
//                                              CCEaseOut::create(CCMoveTo::create(1.0, ccp(center.x-1000, center.y)), 0.2f),
//                                              CCCallFunc::create(this, callfunc_selector(CutTopping::showTopping)),
//                                             CCCallFunc::create(this, callfunc_selector(CutTopping::CannotCut)),
//                                             CCCallFunc::create(this, callfunc_selector(CutTopping::noRouwan)),
//                                             CCCallFunc::create(this, callfunc_selector(CutTopping::setComplate)),
//                                              NULL));
//        break;
//    }
}


void CutTopping::peigenAction(int index){
    CCSprite* peigen=(CCSprite*)this->getChildByTag(kPengen);
//    CCString *name = CCString::createWithFormat("spoon%d.png",sausageIndex);
//    CCSpriteFrame*  spoonAction= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString());
//    sausage->setDisplayFrame(spoonAction);
//    if(peigen!=NULL && peigen->boundingBox().containsPoint(newPoint) && canCuttop && !isMoveComplate){
        isMoveComplate =true;
//        index++;
//        cutNum++;
        CCString *name = CCString::createWithFormat("bacons%d.png",index);
        CCSpriteFrame*  peigenAction= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString());
        peigen->setDisplayFrame(peigenAction);
        if (index==4) {
//            isMoveComplate=true;
//            cutNum=1;
            peigen->runAction(CCSequence::create(CCCallFunc::create(this, callfunc_selector(CutTopping::CannotCut)),
                                                 CCCallFunc::create(this, callfunc_selector(CutTopping::noPengen)),
                                                 CCCallFunc::create(this, callfunc_selector(CutTopping::setComplate)),
                                                 CCCallFunc::create(this, callfunc_selector(CutTopping::resetCutNum)),
                                                 CCEaseOut::create(CCMoveTo::create(1.0, ccp(center.x-1000, center.y)), 0.2f),
                                                 CCCallFunc::create(this, callfunc_selector(CutTopping::showTopping)),
                                                 
                                                  NULL));
        }
        
        
//        CCArray* frame = CCArray::create();
//               for (int m =1; m<5; m++) {
//                   CCString *name = CCString::createWithFormat("bacons%d.png",m);
//                   frame->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString()));
//               }
//        CCAnimation *animation = CCAnimation::createWithSpriteFrames(frame);
//        animation->setDelayPerUnit(0.2f);
//        CCAnimate *animate = CCAnimate::create(animation);
////        CCFiniteTimeAction *action1=CCSpawn::create(animate,
//////                                                                                      CCCallFunc::create(this, callfunc_selector(CutTopping::cutLemonMusic)),
////                                                    NULL);
//        peigen->runAction(CCSequence::create(animate,
//                                              CCDelayTime::create(0.3),
//                                              CCEaseOut::create(CCMoveTo::create(1.0, ccp(center.x-1000, center.y)), 0.2f),
//                                              CCCallFunc::create(this, callfunc_selector(CutTopping::showTopping)),
//                                             CCCallFunc::create(this, callfunc_selector(CutTopping::CannotCut)),
//                                             CCCallFunc::create(this, callfunc_selector(CutTopping::noPengen)),
//                                             CCCallFunc::create(this, callfunc_selector(CutTopping::setComplate)),
//                                              NULL));
//        break;
//    }
}

void CutTopping::lajiaoAction(int index){
    CCSprite* lajiao=(CCSprite*)this->getChildByTag(kLajiao);
//    CCString *name = CCString::createWithFormat("spoon%d.png",sausageIndex);
//    CCSpriteFrame*  spoonAction= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString());
//    sausage->setDisplayFrame(spoonAction);
//    if(lajiao!=NULL && lajiao->boundingBox().containsPoint(newPoint) && canCuttop && !isMoveComplate){
        isMoveComplate=true;
//        index++;
//        cutNum++;
        CCString *name = CCString::createWithFormat("pepper%d.png",index);
        CCSpriteFrame*  lajiaoAction= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString());
        lajiao->setDisplayFrame(lajiaoAction);
        if (index==4) {
//            isMoveComplate=true;
//            cutNum=1;
            lajiao->runAction(CCSequence::create(CCCallFunc::create(this, callfunc_selector(CutTopping::CannotCut)),
                                                 CCCallFunc::create(this, callfunc_selector(CutTopping::noPepper)),
                                                 CCCallFunc::create(this, callfunc_selector(CutTopping::setComplate)),
                                                 CCCallFunc::create(this, callfunc_selector(CutTopping::resetCutNum)),
                                                 CCEaseOut::create(CCMoveTo::create(1.0, ccp(center.x-1000, center.y)), 0.2f),
                                                 CCCallFunc::create(this, callfunc_selector(CutTopping::showTopping)),
                                                 
                                                  NULL));
        }
        
        
        
//        CCArray* frame = CCArray::create();
//               for (int m =1; m<7; m++) {
//                   CCString *name = CCString::createWithFormat("pepper%d.png",m);
//                   frame->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString()));
//               }
//        CCAnimation *animation = CCAnimation::createWithSpriteFrames(frame);
//        animation->setDelayPerUnit(0.2f);
//        CCAnimate *animate = CCAnimate::create(animation);
////        CCFiniteTimeAction *action1=CCSpawn::create(animate,
//////                                                                                      CCCallFunc::create(this, callfunc_selector(CutTopping::cutLemonMusic)),
////                                                    NULL);
//        lajiao->runAction(CCSequence::create(animate,
//                                              CCDelayTime::create(0.3),
//                                              CCEaseOut::create(CCMoveTo::create(1.0, ccp(center.x-1000, center.y)), 0.2f),
//                                              CCCallFunc::create(this, callfunc_selector(CutTopping::showTopping)),
//                                             CCCallFunc::create(this, callfunc_selector(CutTopping::CannotCut)),
//                                             CCCallFunc::create(this, callfunc_selector(CutTopping::noPepper)),
//                                             CCCallFunc::create(this, callfunc_selector(CutTopping::setComplate)),
//                                              NULL));
//        break;
//    }
}


//蔬菜

void CutTopping::moguAction(int index){
    CCSprite* mogu=(CCSprite*)this->getChildByTag(kMogu);
//    CCString *name = CCString::createWithFormat("spoon%d.png",sausageIndex);
//    CCSpriteFrame*  spoonAction= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString());
//    sausage->setDisplayFrame(spoonAction);
//    if(mogu!=NULL && mogu->boundingBox().containsPoint(newPoint) && canCuttop && !isMoveComplate){
        isMoveComplate=true;
//        index++;
//        cutNum++;
        CCString *name = CCString::createWithFormat("mushroom%d.png",index);
        CCSpriteFrame*  moguAction= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString());
        mogu->setDisplayFrame(moguAction);
        if (index==4) {
//            isMoveComplate=true;
//            cutNum=1;
            mogu->runAction(CCSequence::create(CCCallFunc::create(this, callfunc_selector(CutTopping::CannotCut)),
                                               CCCallFunc::create(this, callfunc_selector(CutTopping::noMogu)),
                                               CCCallFunc::create(this, callfunc_selector(CutTopping::setComplate)),
                                               CCCallFunc::create(this, callfunc_selector(CutTopping::resetCutNum)),
                                               CCEaseOut::create(CCMoveTo::create(1.0, ccp(center.x-1000, center.y)), 0.2f),
                                                 CCCallFunc::create(this, callfunc_selector(CutTopping::showTopping)),
                                                 
                                                  NULL));
        }
//        CCArray* frame = CCArray::create();
//               for (int m =1; m<7; m++) {
//                   CCString *name = CCString::createWithFormat("mushroom%d.png",m);
//                   frame->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString()));
//               }
//        CCAnimation *animation = CCAnimation::createWithSpriteFrames(frame);
//        animation->setDelayPerUnit(0.2f);
//        CCAnimate *animate = CCAnimate::create(animation);
////        CCFiniteTimeAction *action1=CCSpawn::create(animate,
//////                                                                                      CCCallFunc::create(this, callfunc_selector(CutTopping::cutLemonMusic)),
////                                                    NULL);
//        mogu->runAction(CCSequence::create(animate,
//                                              CCDelayTime::create(0.3),
//                                              CCEaseOut::create(CCMoveTo::create(1.0, ccp(center.x-1000, center.y)), 0.2f),
//                                              CCCallFunc::create(this, callfunc_selector(CutTopping::showTopping)),
//                                               CCCallFunc::create(this, callfunc_selector(CutTopping::CannotCut)),
//                                               CCCallFunc::create(this, callfunc_selector(CutTopping::noMogu)),
//                                               CCCallFunc::create(this, callfunc_selector(CutTopping::setComplate)),
//                                              NULL));
//        break;
//    }
}

void CutTopping::bocaiAction(int index){
    CCSprite* bocai=(CCSprite*)this->getChildByTag(kBocai);
//    CCString *name = CCString::createWithFormat("spoon%d.png",sausageIndex);
//    CCSpriteFrame*  spoonAction= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString());
//    sausage->setDisplayFrame(spoonAction);
//    if(bocai!=NULL && bocai->boundingBox().containsPoint(newPoint) && canCuttop && !isMoveComplate){
        isMoveComplate = true;
//        index++;
//        cutNum++;
        CCString *name = CCString::createWithFormat("spinach%d.png",index);
        CCSpriteFrame*  bocaiAction= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString());
        bocai->setDisplayFrame(bocaiAction);
        if (index==4) {
//            isMoveComplate=true;
//            cutNum=1;
            bocai->runAction(CCSequence::create(CCCallFunc::create(this, callfunc_selector(CutTopping::CannotCut)),
                                                CCCallFunc::create(this, callfunc_selector(CutTopping::noBocai)),
                                                CCCallFunc::create(this, callfunc_selector(CutTopping::setComplate)),
                                                CCCallFunc::create(this, callfunc_selector(CutTopping::resetCutNum)),
                                                CCEaseOut::create(CCMoveTo::create(1.0, ccp(center.x-1000, center.y)), 0.2f),
                                                 CCCallFunc::create(this, callfunc_selector(CutTopping::showTopping)),
                                                 
                                                  NULL));
        }
        
//        CCArray* frame = CCArray::create();
//               for (int m =1; m<7; m++) {
//                   CCString *name = CCString::createWithFormat("spinach%d.png",m);
//                   frame->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString()));
//               }
//        CCAnimation *animation = CCAnimation::createWithSpriteFrames(frame);
//        animation->setDelayPerUnit(0.2f);
//        CCAnimate *animate = CCAnimate::create(animation);
////        CCFiniteTimeAction *action1=CCSpawn::create(animate,
//////                                                                                      CCCallFunc::create(this, callfunc_selector(CutTopping::cutLemonMusic)),
////                                                    NULL);
//        bocai->runAction(CCSequence::create(animate,
//                                              CCDelayTime::create(0.3),
//                                              CCEaseOut::create(CCMoveTo::create(1.0, ccp(center.x-1000, center.y)), 0.2f),
//                                              CCCallFunc::create(this, callfunc_selector(CutTopping::showTopping)),
//                                            CCCallFunc::create(this, callfunc_selector(CutTopping::CannotCut)),
//                                            CCCallFunc::create(this, callfunc_selector(CutTopping::noBocai)),
//                                            CCCallFunc::create(this, callfunc_selector(CutTopping::setComplate)),
//                                              NULL));
//        break;
//    }
}

void CutTopping::xilanhuaAction(int index){
    CCSprite* xilanhua=(CCSprite*)this->getChildByTag(kXiLanHua);
//    CCString *name = CCString::createWithFormat("spoon%d.png",sausageIndex);
//    CCSpriteFrame*  spoonAction= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString());
//    sausage->setDisplayFrame(spoonAction);
//    if(xilanhua!=NULL && xilanhua->boundingBox().containsPoint(newPoint) && canCuttop && !isMoveComplate){
        isMoveComplate = true;
//        index++;
//        cutNum++;
        CCString *name = CCString::createWithFormat("xilanhua%d.png",index);
        CCSpriteFrame*  xilanhuaAction= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString());
        xilanhua->setDisplayFrame(xilanhuaAction);
        if (index==4) {
//            isMoveComplate=true;
//            cutNum=1;
            xilanhua->runAction(CCSequence::create(
                                                   CCCallFunc::create(this, callfunc_selector(CutTopping::CannotCut)),
                                                   CCCallFunc::create(this, callfunc_selector(CutTopping::noXilanhua)),
                                                   CCCallFunc::create(this, callfunc_selector(CutTopping::setComplate)),
                                                   CCCallFunc::create(this, callfunc_selector(CutTopping::resetCutNum)),
                                                   CCEaseOut::create(CCMoveTo::create(1.0, ccp(center.x-1000, center.y)), 0.2f),
                                                 CCCallFunc::create(this, callfunc_selector(CutTopping::showTopping)),
                                                 
                                                  NULL));
        }
        
//        CCArray* frame = CCArray::create();
//               for (int m =1; m<7; m++) {
//                   CCString *name = CCString::createWithFormat("xilanhua%d.png",m);
//                   frame->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString()));
//               }
//        CCAnimation *animation = CCAnimation::createWithSpriteFrames(frame);
//        animation->setDelayPerUnit(0.2f);
//        CCAnimate *animate = CCAnimate::create(animation);
////        CCFiniteTimeAction *action1=CCSpawn::create(animate,
//////                                                                                      CCCallFunc::create(this, callfunc_selector(CutTopping::cutLemonMusic)),
////                                                    NULL);
//        xilanhua->runAction(CCSequence::create(animate,
//                                              CCDelayTime::create(0.3),
//                                              CCEaseOut::create(CCMoveTo::create(1.0, ccp(center.x-1000, center.y)), 0.2f),
//                                              CCCallFunc::create(this, callfunc_selector(CutTopping::showTopping)),
//                                               CCCallFunc::create(this, callfunc_selector(CutTopping::CannotCut)),
//                                               CCCallFunc::create(this, callfunc_selector(CutTopping::noXilanhua)),
//                                               CCCallFunc::create(this, callfunc_selector(CutTopping::setComplate)),
//                                              NULL));
//        break;
//    }
}


void CutTopping::sausageAction(int index){
    CCSprite* sausage=(CCSprite*)this->getChildByTag(kPepporoni);
//    if(sausage!=NULL && sausage->boundingBox().containsPoint(newPoint) && canCuttop && !isMoveComplate){
        isMoveComplate = true;
//        index++;
//        cutNum++;
    if (index > 0 && index < 5) {
        CCString *name = CCString::createWithFormat("sausage%d.png",index);
        CCSpriteFrame*  sausageActionFrame= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString());
        sausage->setDisplayFrame(sausageActionFrame);
        if (index==4) {
//            isMoveComplate=true;
//            cutNum=1;
            sausage->runAction(CCSequence::create(CCCallFunc::create(this, callfunc_selector(CutTopping::CannotCut)),
                                                  CCCallFunc::create(this, callfunc_selector(CutTopping::noChang)),
                                                  CCCallFunc::create(this, callfunc_selector(CutTopping::setComplate)),
                                                  CCCallFunc::create(this, callfunc_selector(CutTopping::resetCutNum)),
                                                  CCEaseOut::create(CCMoveTo::create(1.0, ccp(center.x-1000, center.y)), 0.2f),
                                                 CCCallFunc::create(this, callfunc_selector(CutTopping::showTopping)),
                                                  NULL));
        }
    }
        
//        CCArray* frame = CCArray::create();
//               for (int m =1; m<6; m++) {
//                   CCString *name = CCString::createWithFormat("sausage%d.png",m);
//                   frame->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString()));
//               }
//        CCAnimation *animation = CCAnimation::createWithSpriteFrames(frame);
//        animation->setDelayPerUnit(0.2f);
//        CCAnimate *animate = CCAnimate::create(animation);
////        CCFiniteTimeAction *action1=CCSpawn::create(animate,
//////                                                                                      CCCallFunc::create(this, callfunc_selector(CutTopping::cutLemonMusic)),
////                                                    NULL);
//        sausage->runAction(CCSequence::create(animate,
//                                              CCDelayTime::create(0.3),
//                                              CCEaseOut::create(CCMoveTo::create(1.0, ccp(center.x-1000, center.y)), 0.2f),
////                                              CCCallFunc::create(this, callfunc_selector(CutTopping::goNext)),
//                                              CCCallFunc::create(this, callfunc_selector(CutTopping::goNext)),
//                                              CCCallFunc::create(this, callfunc_selector(CutTopping::CannotCut)),
//                                              CCCallFunc::create(this, callfunc_selector(CutTopping::noChang)),
//                                              CCCallFunc::create(this, callfunc_selector(CutTopping::setComplate)),
//                                              NULL));
//        break;
//    }
}

void CutTopping::boluoAction(int index){
    CCSprite* boluo=(CCSprite*)this->getChildByTag(kBoluo);
//    CCString *name = CCString::createWithFormat("spoon%d.png",sausageIndex);
//    CCSpriteFrame*  spoonAction= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString());
//    sausage->setDisplayFrame(spoonAction);
//    if(boluo!=NULL && boluo->boundingBox().containsPoint(newPoint)  && canCuttop && !isMoveComplate){
        isMoveComplate  = true;
//        index++;
//        cutNum++;
        CCString *name = CCString::createWithFormat("pineapple%d.png",index);
        CCSpriteFrame*  boluoAction= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString());
        boluo->setDisplayFrame(boluoAction);
        if (index==4) {
//            isMoveComplate=true;
//            cutNum=1;
            boluo->runAction(CCSequence::create(
                                                CCCallFunc::create(this, callfunc_selector(CutTopping::CannotCut)),
                                                CCCallFunc::create(this, callfunc_selector(CutTopping::noBoluo)),
                                                CCCallFunc::create(this, callfunc_selector(CutTopping::setComplate)),
                                                CCCallFunc::create(this, callfunc_selector(CutTopping::resetCutNum)),
                                                CCEaseOut::create(CCMoveTo::create(1.0, ccp(center.x-1000, center.y)), 0.2f),
                                                 CCCallFunc::create(this, callfunc_selector(CutTopping::showTopping)),
                                                
                                                  NULL));
        }
        
//        CCArray* frame = CCArray::create();
//               for (int m =1; m<7; m++) {
//                   CCString *name = CCString::createWithFormat("pineapple%d.png",m);
//                   frame->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString()));
//               }
//        CCAnimation *animation = CCAnimation::createWithSpriteFrames(frame);
//        animation->setDelayPerUnit(0.2f);
//        CCAnimate *animate = CCAnimate::create(animation);
////        CCFiniteTimeAction *action1=CCSpawn::create(animate,
//////                                                                                      CCCallFunc::create(this, callfunc_selector(CutTopping::cutLemonMusic)),
////                                                    NULL);
//        boluo->runAction(CCSequence::create(animate,
//                                              CCDelayTime::create(0.3),
//                                              CCEaseOut::create(CCMoveTo::create(1.0, ccp(center.x-1000, center.y)), 0.2f),
//                                              CCCallFunc::create(this, callfunc_selector(CutTopping::showTopping)),
//                                              CCCallFunc::create(this, callfunc_selector(CutTopping::CannotCut)),
//                                              CCCallFunc::create(this, callfunc_selector(CutTopping::noBoluo)),
//                                              CCCallFunc::create(this, callfunc_selector(CutTopping::setComplate)),
//                                              NULL));
//        break;
//    }
}

void CutTopping::clickBack(){
    if (PizzaManager::sharedManager()->whichPizza != 8) {
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, MakePizza::scene(), ccBLACK));
    }else{
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, SelectTopping::scene(), ccBLACK));
    }
}

void CutTopping::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent){
    CCTouch *pTouch = (CCTouch*)(pTouches->anyObject());
    CCPoint location=CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
    
    CCSetIterator it = pTouches->begin();
    CCTouch* touch = (CCTouch*)*it;
    CCPoint beginPoint = touch->getLocationInView();
    beginPoint = CCDirector::sharedDirector()->convertToGL(beginPoint);
    pizzaLineSprite->pointList.push_back(beginPoint);
    
    beginTouchX = beginPoint.x;
    
    CCSprite* back = (CCSprite*)this->getChildByTag(kBack);
    if (back!=NULL && back->boundingBox().containsPoint(location) && backClick==false) {
        backClick = true;
//        SimpleAudioEngine::sharedEngine()->playEffect("mp3/done.mp3");
        CCScaleBy* scaleBy = CCScaleBy::create(0.1, 1.2);
        //            homeBtn->setScale(1.2);
        //            touchSprite = homeBtn;
        SimpleAudioEngine::sharedEngine()->playEffect("mp3/touchItem.mp3");
        back->runAction(CCSequence::createWithTwoActions(CCSequence::createWithTwoActions(scaleBy, scaleBy->reverse()), CCCallFunc::create(this, callfunc_selector(CutTopping::clickBack))));
        PizzaManager::sharedManager()->cleanAllSprite();
    }
}

void CutTopping::cutActionMp3(){
    SimpleAudioEngine::sharedEngine()->playEffect("mp3/cut.m4a");
}

void CutTopping::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent){
    CCSprite* potato=(CCSprite*)this->getChildByTag(kPotato);
    CCSprite* rouwan=(CCSprite*)this->getChildByTag(kRouwan);
    CCSprite* peigen=(CCSprite*)this->getChildByTag(kPengen);
    CCSprite* lajiao=(CCSprite*)this->getChildByTag(kLajiao);
    CCSprite* mogu=(CCSprite*)this->getChildByTag(kMogu);
    CCSprite* bocai=(CCSprite*)this->getChildByTag(kBocai);
    CCSprite* xilanhua=(CCSprite*)this->getChildByTag(kXiLanHua);
    CCSprite* sausage=(CCSprite*)this->getChildByTag(kPepporoni);
    CCSprite* boluo=(CCSprite*)this->getChildByTag(kBoluo);
    CCTouch *pTouch = (CCTouch*)(pTouches->anyObject());
    CCPoint location=CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
    this->unschedule(schedule_selector(CutTopping::showFinger));
    
    
    //刀痕
    CCSetIterator it = pTouches->begin();
    CCTouch* touch = (CCTouch*)*it;
//    CCPoint newPoint;
    CCPoint nextPoint = touch->getLocationInView( );
    nextPoint = CCDirector::sharedDirector()->convertToGL(nextPoint);
    CCPoint preMovePoint = touch->getPreviousLocationInView();
    preMovePoint = CCDirector::sharedDirector()->convertToGL(preMovePoint);
    float distance = ccpDistance(nextPoint, preMovePoint);
    if (distance > 1 && canCuttop){
        int d = (int)distance;
        for (int i =0; i < d; i++ ){
            float distanceX = nextPoint.x - preMovePoint.x;
            float distanceY = nextPoint.y - preMovePoint.y;
            float percent = i / distance;
//            CCPoint newPoint;
            newPoint.x = preMovePoint.x + (distanceX * percent);
            newPoint.y = preMovePoint.y + (distanceY * percent);
//            newPoint.x =center.x;
//            newPoint.y = center.y;
            pizzaLineSprite->pointList.push_back(newPoint);
            endTouchX=newPoint.x;
            int xDis = endTouchX-beginTouchX;
            if (abs(xDis)>=10) {                                                        //保证用户划过一段距离
//                CCUserDefault::sharedUserDefault()->setBoolForKey("isFirstPizza", false);
//                GameManager::sharedManager()->firstPlayPizza=false;
                if (potatos) {
                    if (potato!=NULL && CCRect(center.x-90, center.y, 180, 90).containsPoint(newPoint) && !isMoveComplate && canCuttop) {
                        cutNum++;
                        this->cutActionMp3();
                        this->tomatoAction(cutNum);
                    }
                }else if(xilanhuas){
                    if (xilanhua!=NULL && CCRect(center.x-90, center.y, 180, 90).containsPoint(newPoint) && !isMoveComplate && canCuttop) {
                        cutNum++;
                        this->cutActionMp3();
                        this->xilanhuaAction(cutNum);
                    }
                    
                }else if(mushroom){
                    if (mogu!=NULL && CCRect(center.x-90, center.y, 120, 90).containsPoint(newPoint) && !isMoveComplate && canCuttop) {
                        cutNum++;
                        this->cutActionMp3();
                        this->moguAction(cutNum);
                    }
                    
                }else if(pepper){
                    if (lajiao!=NULL && CCRect(center.x-90, center.y, 180, 90).containsPoint(newPoint) && !isMoveComplate && canCuttop) {
                        cutNum++;
                        this->cutActionMp3();
                        this->lajiaoAction(cutNum);
                    }
                }else if(pineapple){
                    if (boluo!=NULL && CCRect(center.x-90, center.y, 180, 90).containsPoint(newPoint) && !isMoveComplate && canCuttop) {
                        cutNum++;
                        this->cutActionMp3();
                        this->boluoAction(cutNum);
                    }
                }else if(spinach){
                    if (bocai!=NULL && CCRect(center.x-90, center.y, 180, 90).containsPoint(newPoint) && !isMoveComplate && canCuttop) {
                        cutNum++;
                        this->cutActionMp3();
                        this->bocaiAction(cutNum);
                    }
                    
                }else if(pengens){
                    if (peigen!=NULL && CCRect(center.x-90, center.y, 180, 90).containsPoint(newPoint) && !isMoveComplate && canCuttop) {
                        cutNum++;
                        this->cutActionMp3();
                        this->peigenAction(cutNum);
                    }
                    
                }else if(rouwans){
                    if (rouwan!=NULL && CCRect(center.x-90, center.y, 180, 90).containsPoint(newPoint) && !isMoveComplate && canCuttop) {
                        cutNum++;
                        this->cutActionMp3();
                        this->rouwanAction(cutNum);
                    }
                    
                }else if(chang){
                    if (sausage!=NULL && CCRect(center.x-90, center.y, 180, 90).containsPoint(newPoint) && !isMoveComplate && canCuttop) {
                        cutNum++;
                        this->cutActionMp3();
                        this->sausageAction(cutNum);
                    }
                    
                }
            }
//            int xDis = endTouchX-beginTouchX;
//            if (abs(xDis)>=10) {                                                        //保证用户划过一段距离
////                cutNum++;
//                if (potatos) {
//                    this->potatoAction(cutNum);
//                }else if(xilanhuas){
//                    this->xilanhuaAction(cutNum);
//                }else if(mushroom){
//                    this->moguAction(cutNum);
//                }else if(pepper){
//                    this->lajiaoAction(cutNum);
//                }else if(pineapple){
//                    this->boluoAction(cutNum);
//                }else if(spinach){
//                    this->bocaiAction(cutNum);
//                }else if(pengens){
//                    this->peigenAction(cutNum);
//                }else if(rouwans){
//                    this->rouwanAction(cutNum);
//                }else if(chang){
//                    this->sausageAction(cutNum);
//                }
//                for(int j=0;j<6;j++){
//                if(PizzaManager::sharedManager()->topping[0] == 1){
//
//                }else if(PizzaManager::sharedManager()->whichPizza == 2){
////                    if (sausageIndex<5) {
////                        sausageIndex++;
////                    }else if (sausageIndex==5){
////
////                    }
////                    this->sausageAction();
//                }else if(PizzaManager::sharedManager()->whichPizza == 3){
//
//                }else if(PizzaManager::sharedManager()->whichPizza == 4){
//
//                }else if(PizzaManager::sharedManager()->whichPizza == 5){
//
//                }
//                this->sausageAction();
                                      
//                }
                
//            }
        }
    }
}

void CutTopping::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent){
    CCTouch *pTouch = (CCTouch*)(pTouches->anyObject());
    CCPoint location = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
    pizzaLineSprite->pointList.clear();
    if(isMoveComplate){
        this->setComplate();
    }
    
//    CCSprite* potato=(CCSprite*)this->getChildByTag(kPotato);
//    CCSprite* rouwan=(CCSprite*)this->getChildByTag(kRouwan);
//    CCSprite* peigen=(CCSprite*)this->getChildByTag(kPengen);
//    CCSprite* lajiao=(CCSprite*)this->getChildByTag(kLajiao);
//    CCSprite* mogu=(CCSprite*)this->getChildByTag(kMogu);
//    CCSprite* bocai=(CCSprite*)this->getChildByTag(kBocai);
//    CCSprite* xilanhua=(CCSprite*)this->getChildByTag(kXiLanHua);
//    CCSprite* sausage=(CCSprite*)this->getChildByTag(kPepporoni);
//    CCSprite* boluo=(CCSprite*)this->getChildByTag(kBoluo);
//    int xDis = endTouchX-beginTouchX;
//    if (abs(xDis)>=10) {                                                        //保证用户划过一段距离
////        if (cutNum<4) {
////            cutNum++;
////        }
////            CCPoint pos = ccp(center.x, center.y+50);
//
//        if (potatos) {
//            this->potatoAction(cutNum);
//        }else if(xilanhuas){
//            this->xilanhuaAction(cutNum);
//        }else if(mushroom){
//            this->moguAction(cutNum);
//        }else if(pepper){
//            this->lajiaoAction(cutNum);
//        }else if(pineapple){
//            this->boluoAction(cutNum);
//        }else if(spinach){
//            this->bocaiAction(cutNum);
//        }else if(pengens){
//            this->peigenAction(cutNum);
//        }else if(rouwans){
//            this->rouwanAction(cutNum);
//        }else if(chang){
//            this->sausageAction(cutNum);
//        }
//    }
    
}

//CCRect CutTopping::createRectByPoint(CCPoint point, float width, float height){
//    return CCRectMake(point.x-width/2,point.y-height/2,width,height);       //CCRectMake(x,y,width,height)；x,矩形左下角x坐标；y，矩形左下角y坐标；width，矩形宽度；height，矩形高度
//}
