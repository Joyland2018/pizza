//
//  CutMaterial.cpp
//  DrDino
//
//  Created by LiXiaofei on 8/31/21.
//

#include "CutMaterial.h"
//
//  CutMaterial.cpp
//  Pizza
//
//  Created by LiXiaofei on 4/8/21.
//
//
//  CutMaterial.cpp
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
#include "MakeSauce.h"


using namespace CocosDenshion;

enum{
    kBack=0,
    kTopping=10,
    kDone=1,
    kStrawberry = 2,
    kBanana = 3,
    kBeet = 4,
    kPotato = 5,
    kPumpkin = 6,
    kOnion = 7,
    kGarlic = 8,
    kNextTag = 199,
};

CCScene* CutMaterial::scene(){
    CCScene* scene = CCScene::create();
    CutMaterial* layer = CutMaterial::create();
    scene->addChild(layer);
    return scene;
}

void CutMaterial::onEnter(){
    CCLayer::onEnter();
}

void CutMaterial::onExit(){
    CCLayer::onExit();
}

CutMaterial::CutMaterial(){}
CutMaterial::~CutMaterial(){}

bool CutMaterial::init(){
    if (!CCLayer::init()) {
        return false;
    }
    backClick =false;
    clickNext = false;
    
    CCPoint visibleOrigin=CCDirector::sharedDirector()->getVisibleOrigin();
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    center = GameManager::sharedManager()->getCenter();
    CCPoint leftTop = GameManager::sharedManager()->getLeftTopPos();
    CCPoint rightTop = GameManager::sharedManager()->getRightTopPos();
    
    
    for (int i=1; i<4; i++) {
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(CCString::createWithFormat("pizza/animate/candy/candy%d.plist",i)->getCString());
    }
    for (int i=1; i<3; i++) {
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(CCString::createWithFormat("pizza/animate/halloween/halloween%d.plist",i)->getCString());
    }
    for (int i=1; i<3; i++) {
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(CCString::createWithFormat("pizza/animate/christmas/christmas%d.plist",i)->getCString());
    }
    
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
        this->schedule(schedule_selector(CutMaterial::showFinger),1.5f);
    }
    
    this->showTopping();
    return true;
}

//手指提示
void CutMaterial::showFinger(){
    
    CCSize winSize = GameManager::sharedManager()->getViewVisibleSize();
    CCSprite* fingerTouch = CCSprite::create("background/touch0.png");
    fingerTouch->setPosition(ccp(center.x, center.y+100));
    fingerTouch->setScale(0.6);
    this->addChild(fingerTouch,11);
    fingerTouch->setOpacity(0);
    fingerTouch->runAction(CCSequence::create(CCFadeIn::create(0.3),
                                              CCEaseOut::create(CCMoveTo::create(0.8, ccp(center.x, center.y-100)), 1.0f),
                                                                CCFadeOut::create(0.4),
                                                                CCCallFuncN::create(this, callfuncN_selector(CutMaterial::removeSprite)),
                                              NULL));
}

void CutMaterial::removeSprite(CCObject *pSender){
    CCSprite* sprite = (CCSprite*)pSender;
    if(sprite!=NULL){
        sprite->removeAllChildrenWithCleanup(true);
        sprite->stopAllActions();
        sprite->removeFromParentAndCleanup(true);
        sprite=NULL;
    }
}


void CutMaterial::showTopping(){
    
    if (PizzaManager::sharedManager()->whichPizza == 2) {
        this->candyMaterial1();
    }else if (PizzaManager::sharedManager()->whichPizza == 4) {
        this->halloween1();
    }else if (PizzaManager::sharedManager()->whichPizza == 6) {
        this->christmas1();
    }
}

//void CutMaterial::cheeseTopping(){
//
//}


void CutMaterial::candyMaterial1(){
    CCSprite* strawberry = CCSprite::createWithSpriteFrameName("candy1_1.png");
    strawberry->setPosition(ccp(center.x-1000, center.y));
    strawberry->runAction(CCSequence::create(CCEaseIn::create(CCMoveTo::create(1.0, ccp(center.x, center.y)), 0.2f),
                                            CCCallFunc::create(this, callfunc_selector(CutMaterial::isCancut)),
                                            NULL));
    strawberry->setTag(kStrawberry);
    this->addChild(strawberry,2);
    strawberrys = true;
}


void CutMaterial::candyMaterial2(){
    CCSprite* banana = CCSprite::createWithSpriteFrameName("candy2_1.png");
    banana->setPosition(ccp(center.x-1000, center.y));
    banana->runAction(CCSequence::create(CCEaseIn::create(CCMoveTo::create(1.0, ccp(center.x, center.y)), 0.2f),
                                            CCCallFunc::create(this, callfunc_selector(CutMaterial::isCancut)),
                                            NULL));
    banana->setTag(kBanana);
    this->addChild(banana,2);
    bananas = true;
}

void CutMaterial::candyMaterial3(){
    CCSprite* beet = CCSprite::createWithSpriteFrameName("candy3_1.png");
    beet->setPosition(ccp(center.x-1000, center.y));
    beet->runAction(CCSequence::create(CCEaseIn::create(CCMoveTo::create(1.0, ccp(center.x, center.y)), 0.2f),
                                            CCCallFunc::create(this, callfunc_selector(CutMaterial::isCancut)),
                                            NULL));
    beet->setTag(kBeet);
    this->addChild(beet,2);
    beets = true;
}

void CutMaterial::halloween1(){
    CCSprite* potato = CCSprite::createWithSpriteFrameName("halloween1_1.png");
    potato->setPosition(ccp(center.x-1000, center.y));
    potato->runAction(CCSequence::create(CCEaseIn::create(CCMoveTo::create(1.0, ccp(center.x, center.y)), 0.2f),
                                            CCCallFunc::create(this, callfunc_selector(CutMaterial::isCancut)),
                                            NULL));
    potato->setTag(kPotato);
    this->addChild(potato,2);
    potatos = true;
}
void CutMaterial::halloween2(){
    CCSprite* pumpkin = CCSprite::createWithSpriteFrameName("halloween2_1.png");
    pumpkin->setPosition(ccp(center.x-1000, center.y));
    pumpkin->runAction(CCSequence::create(CCEaseIn::create(CCMoveTo::create(1.0, ccp(center.x, center.y)), 0.2f),
                                            CCCallFunc::create(this, callfunc_selector(CutMaterial::isCancut)),
                                            NULL));
    pumpkin->setTag(kPumpkin);
    this->addChild(pumpkin,2);
    pumpkins = true;
}

void CutMaterial::christmas1(){
    CCSprite* onion = CCSprite::createWithSpriteFrameName("christmas1_1.png");
    onion->setPosition(ccp(center.x-1000, center.y));
    onion->runAction(CCSequence::create(CCEaseIn::create(CCMoveTo::create(1.0, ccp(center.x, center.y)), 0.2f),
                                            CCCallFunc::create(this, callfunc_selector(CutMaterial::isCancut)),
                                            NULL));
    onion->setTag(kOnion);
    this->addChild(onion,2);
    onions = true;
}

void CutMaterial::christmas2(){
    CCSprite* garlic = CCSprite::createWithSpriteFrameName("christmas2_1.png");
    garlic->setPosition(ccp(center.x-1000, center.y));
    garlic->runAction(CCSequence::create(CCEaseIn::create(CCMoveTo::create(1.0, ccp(center.x, center.y)), 0.2f),
                                            CCCallFunc::create(this, callfunc_selector(CutMaterial::isCancut)),
                                            NULL));
    garlic->setTag(kGarlic);
    this->addChild(garlic,2);
    garlics = true;
}



void CutMaterial::goNext(){
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.0, MakeSauce::scene(), ccBLACK));
}

void CutMaterial::isCancut(){
    canCuttop=true;
}

void CutMaterial::CannotCut(){
    canCuttop=false;
}

void CutMaterial::noStrawberry(){
    strawberrys = false;
}

void CutMaterial::noBanana(){
    bananas = false;
}
void CutMaterial::noBeet(){
    beets = false;
}

void CutMaterial::noPotato(){
    potatos = false;
}

void CutMaterial::noPumpkins(){
    pumpkins = false;
}
void CutMaterial::noOnion(){
    onions = false;
}

void CutMaterial::noGarlic(){
    garlics = false;
}



void CutMaterial::setComplate(){
    isMoveComplate=false;
}

void CutMaterial::resetCutNum(){
    cutNum=1;
}



void CutMaterial::strawberryAction(int index){
    CCSprite* strawberry=(CCSprite*)this->getChildByTag(kStrawberry);
//    if(sausage!=NULL && sausage->boundingBox().containsPoint(newPoint) && canCuttop && !isMoveComplate){
    if (strawberry!=NULL) {
        isMoveComplate = true;
    //        index++;
    //        cutNum++;
            CCString *name = CCString::createWithFormat("candy1_%d.png",index);
            CCSpriteFrame*  sausageAction= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString());
        if (sausageAction) {
            strawberry->setDisplayFrame(sausageAction);
        }
            if (index==4) {
    //            isMoveComplate=true;
    //            cutNum=1;
                strawberry->runAction(CCSequence::create(CCCallFunc::create(this, callfunc_selector(CutMaterial::CannotCut)),
                                                      CCCallFunc::create(this, callfunc_selector(CutMaterial::noStrawberry)),
                                                      CCCallFunc::create(this, callfunc_selector(CutMaterial::setComplate)),
                                                      CCCallFunc::create(this, callfunc_selector(CutMaterial::resetCutNum)),
                                                      CCEaseOut::create(CCMoveTo::create(1.0, ccp(center.x-1000, center.y)), 0.2f),
                                                     CCCallFunc::create(this, callfunc_selector(CutMaterial::candyMaterial2)),
                                                     
                                                      NULL));
            }
    }

}

void CutMaterial::bananaAction(int index){
    CCSprite* banana=(CCSprite*)this->getChildByTag(kBanana);
//    if(sausage!=NULL && sausage->boundingBox().containsPoint(newPoint) && canCuttop && !isMoveComplate){
    if (banana!=NULL) {
        isMoveComplate = true;
    //        index++;
    //        cutNum++;
            CCString *name = CCString::createWithFormat("candy2_%d.png",index);
            CCSpriteFrame*  sausageAction= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString());
        if (sausageAction) {
            banana->setDisplayFrame(sausageAction);
        }
            if (index==4) {
    //            isMoveComplate=true;
    //            cutNum=1;
                banana->runAction(CCSequence::create(CCCallFunc::create(this, callfunc_selector(CutMaterial::CannotCut)),
                                                      CCCallFunc::create(this, callfunc_selector(CutMaterial::noBanana)),
                                                      CCCallFunc::create(this, callfunc_selector(CutMaterial::setComplate)),
                                                      CCCallFunc::create(this, callfunc_selector(CutMaterial::resetCutNum)),
                                                      CCEaseOut::create(CCMoveTo::create(1.0, ccp(center.x-1000, center.y)), 0.2f),
                                                     CCCallFunc::create(this, callfunc_selector(CutMaterial::candyMaterial3)),
                                                     
                                                      NULL));
            }
    }

}

void CutMaterial::beetAction(int index){
    CCSprite* beet=(CCSprite*)this->getChildByTag(kBeet);
//    if(sausage!=NULL && sausage->boundingBox().containsPoint(newPoint) && canCuttop && !isMoveComplate){
    if (beet!=NULL) {
        isMoveComplate = true;
    //        index++;
    //        cutNum++;
            CCString *name = CCString::createWithFormat("candy3_%d.png",index);
            CCSpriteFrame*  sausageAction= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString());
        if (sausageAction) {
            beet->setDisplayFrame(sausageAction);
        }
            if (index==4) {
    //            isMoveComplate=true;
    //            cutNum=1;
                beet->runAction(CCSequence::create(CCCallFunc::create(this, callfunc_selector(CutMaterial::CannotCut)),
                                                      CCCallFunc::create(this, callfunc_selector(CutMaterial::noBeet)),
                                                      CCCallFunc::create(this, callfunc_selector(CutMaterial::setComplate)),
                                                      CCCallFunc::create(this, callfunc_selector(CutMaterial::resetCutNum)),
                                                      CCEaseOut::create(CCMoveTo::create(1.0, ccp(center.x-1000, center.y)), 0.2f),
                                                     CCCallFunc::create(this, callfunc_selector(CutMaterial::goNext)),
                                                     
                                                      NULL));
            }
    }

}

void CutMaterial::potatoAction(int index){
    CCSprite* potato=(CCSprite*)this->getChildByTag(kPotato);
//    if(sausage!=NULL && sausage->boundingBox().containsPoint(newPoint) && canCuttop && !isMoveComplate){
    if(potato!=NULL){
        isMoveComplate = true;
    //        index++;
    //        cutNum++;
            CCString *name = CCString::createWithFormat("halloween1_%d.png",index);
            CCSpriteFrame*  sausageAction= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString());
        if (sausageAction) {
            potato->setDisplayFrame(sausageAction);
        }
            if (index==4) {
    //            isMoveComplate=true;
    //            cutNum=1;
                potato->runAction(CCSequence::create(CCCallFunc::create(this, callfunc_selector(CutMaterial::CannotCut)),
                                                      CCCallFunc::create(this, callfunc_selector(CutMaterial::noPotato)),
                                                      CCCallFunc::create(this, callfunc_selector(CutMaterial::setComplate)),
                                                      CCCallFunc::create(this, callfunc_selector(CutMaterial::resetCutNum)),
                                                      CCEaseOut::create(CCMoveTo::create(1.0, ccp(center.x-1000, center.y)), 0.2f),
                                                     CCCallFunc::create(this, callfunc_selector(CutMaterial::halloween2)),
                                                     
                                                      NULL));
            }
    }

}

void CutMaterial::pumpkinAction(int index){
    CCSprite* pumpkin=(CCSprite*)this->getChildByTag(kPumpkin);
//    if(sausage!=NULL && sausage->boundingBox().containsPoint(newPoint) && canCuttop && !isMoveComplate){
    if (pumpkin!=NULL) {
        isMoveComplate = true;
    //        index++;
    //        cutNum++;
            CCString *name = CCString::createWithFormat("halloween2_%d.png",index);
            CCSpriteFrame*  sausageAction= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString());
        if (sausageAction) {
            pumpkin->setDisplayFrame(sausageAction);
        }
            if (index==4) {
    //            isMoveComplate=true;
    //            cutNum=1;
                pumpkin->runAction(CCSequence::create(CCCallFunc::create(this, callfunc_selector(CutMaterial::CannotCut)),
                                                      CCCallFunc::create(this, callfunc_selector(CutMaterial::noPumpkins)),
                                                      CCCallFunc::create(this, callfunc_selector(CutMaterial::setComplate)),
                                                      CCCallFunc::create(this, callfunc_selector(CutMaterial::resetCutNum)),
                                                      CCEaseOut::create(CCMoveTo::create(1.0, ccp(center.x-1000, center.y)), 0.2f),
                                                     CCCallFunc::create(this, callfunc_selector(CutMaterial::goNext)),
                                                     
                                                      NULL));
            }
    }

}

void CutMaterial::onionAction(int index){
    CCSprite* onion=(CCSprite*)this->getChildByTag(kOnion);
//    if(sausage!=NULL && sausage->boundingBox().containsPoint(newPoint) && canCuttop && !isMoveComplate){
    if (onion!=NULL) {
        isMoveComplate = true;
    //        index++;
    //        cutNum++;
            CCString *name = CCString::createWithFormat("christmas1_%d.png",index);
            CCSpriteFrame*  sausageAction= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString());
        if (sausageAction) {
            onion->setDisplayFrame(sausageAction);
        }
            if (index==4) {
    //            isMoveComplate=true;
    //            cutNum=1;
                onion->runAction(CCSequence::create(CCCallFunc::create(this, callfunc_selector(CutMaterial::CannotCut)),
                                                      CCCallFunc::create(this, callfunc_selector(CutMaterial::noOnion)),
                                                      CCCallFunc::create(this, callfunc_selector(CutMaterial::setComplate)),
                                                      CCCallFunc::create(this, callfunc_selector(CutMaterial::resetCutNum)),
                                                      CCEaseOut::create(CCMoveTo::create(1.0, ccp(center.x-1000, center.y)), 0.2f),
                                                     CCCallFunc::create(this, callfunc_selector(CutMaterial::christmas2)),
                                                      NULL));
            }
    }

}

void CutMaterial::garlicAction(int index){
    CCSprite* garlic=(CCSprite*)this->getChildByTag(kGarlic);
//    if(sausage!=NULL && sausage->boundingBox().containsPoint(newPoint) && canCuttop && !isMoveComplate){
    if (garlic!=NULL) {
        isMoveComplate = true;
    //        index++;
    //        cutNum++;
            CCString *name = CCString::createWithFormat("christmas2_%d.png",index);
            CCSpriteFrame*  sausageAction= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString());
        if (sausageAction) {
            garlic->setDisplayFrame(sausageAction);
        }
            if (index==3) {
    //            isMoveComplate=true;
    //            cutNum=1;
                garlic->runAction(CCSequence::create(CCCallFunc::create(this, callfunc_selector(CutMaterial::CannotCut)),
                                                      CCCallFunc::create(this, callfunc_selector(CutMaterial::noGarlic)),
                                                      CCCallFunc::create(this, callfunc_selector(CutMaterial::setComplate)),
                                                      CCCallFunc::create(this, callfunc_selector(CutMaterial::resetCutNum)),
                                                      CCEaseOut::create(CCMoveTo::create(1.0, ccp(center.x-1000, center.y)), 0.2f),
                                                     CCCallFunc::create(this, callfunc_selector(CutMaterial::goNext)),
                                                      NULL));
            }
    }

}



void CutMaterial::clickBack(){
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, MakePizza::scene(), ccBLACK));
}

void CutMaterial::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent){
    CCTouch *pTouch = (CCTouch*)(pTouches->anyObject());
    CCPoint location=CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
    
    CCSetIterator it = pTouches->begin();
    CCTouch* touch = (CCTouch*)*it;
    CCPoint beginPoint = touch->getLocationInView();
    beginPoint = CCDirector::sharedDirector()->convertToGL(beginPoint);
    pizzaLineSprite->pointList.push_back(beginPoint);
    
    beginTouchX = beginPoint.x;
    
    CCSprite* next = (CCSprite*)this->getChildByTag(kNextTag);
    
    CCSprite* back = (CCSprite*)this->getChildByTag(kBack);
    if (back!=NULL && back->boundingBox().containsPoint(location) && backClick ==false) {
        backClick = true;
        //        SimpleAudioEngine::sharedEngine()->playEffect("mp3/done.mp3");
//        if (PizzaManager::sharedManager()->whichPizza != 8) {
        CCScaleBy* scaleBy = CCScaleBy::create(0.1, 1.2);
        //            homeBtn->setScale(1.2);
        //            touchSprite = homeBtn;
        SimpleAudioEngine::sharedEngine()->playEffect("mp3/touchItem.mp3");
        back->runAction(CCSequence::createWithTwoActions(CCSequence::createWithTwoActions(scaleBy, scaleBy->reverse()), CCCallFunc::create(this, callfunc_selector(CutMaterial::clickBack))));
//        }else{
//        PizzaManager::sharedManager()->cleanAllSprite();
    }else if (next !=NULL && next->boundingBox().containsPoint(location) && clickNext==false) {
        clickNext=true;
        CCScaleBy* scaleBy = CCScaleBy::create(0.1, 1.2);
        SimpleAudioEngine::sharedEngine()->playEffect("mp3/touchItem.mp3");
        next->runAction(CCSequence::createWithTwoActions(CCSequence::createWithTwoActions(scaleBy, scaleBy->reverse()), CCCallFunc::create(this, callfunc_selector(CutMaterial::goNext))));
    }
}

void CutMaterial::cutActionMp3(){
    SimpleAudioEngine::sharedEngine()->playEffect("mp3/cut.m4a");
}

void CutMaterial::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent){
    CCSprite* potato=(CCSprite*)this->getChildByTag(kPotato);
    CCSprite* strawberry=(CCSprite*)this->getChildByTag(kStrawberry);
    CCSprite* banana=(CCSprite*)this->getChildByTag(kBanana);
    CCSprite* beet=(CCSprite*)this->getChildByTag(kBeet);
    CCSprite* pumpkin=(CCSprite*)this->getChildByTag(kPumpkin);
    CCSprite* onion=(CCSprite*)this->getChildByTag(kOnion);
    CCSprite* garlic=(CCSprite*)this->getChildByTag(kGarlic);
    CCTouch *pTouch = (CCTouch*)(pTouches->anyObject());
    CCPoint location=CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
    this->unschedule(schedule_selector(CutMaterial::showFinger));
    
    
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
                if(strawberrys){
                    if (strawberry!=NULL && CCRect(center.x-90, center.y, 180, 90).containsPoint(newPoint) && !isMoveComplate && canCuttop) {
                        cutNum++;
                        this->cutActionMp3();
                        this->strawberryAction(cutNum);
                    }
                }else if(bananas){
                    if (banana!=NULL && CCRect(center.x-90, center.y, 180, 90).containsPoint(newPoint) && !isMoveComplate && canCuttop) {
                        cutNum++;
                        this->cutActionMp3();
                        this->bananaAction(cutNum);
                    }
                }else if(beets){
                    if (beet!=NULL && CCRect(center.x-90, center.y, 180, 90).containsPoint(newPoint) && !isMoveComplate && canCuttop) {
                        cutNum++;
                        this->cutActionMp3();
                        this->beetAction(cutNum);
                    }
                }
                else if(potatos){
                    if (potato!=NULL && CCRect(center.x-90, center.y, 180, 90).containsPoint(newPoint) && !isMoveComplate && canCuttop) {
                        cutNum++;
                        this->cutActionMp3();
                        this->potatoAction(cutNum);
                    }
                }else if(pumpkins){
                    if (pumpkin!=NULL && CCRect(center.x-90, center.y, 180, 90).containsPoint(newPoint) && !isMoveComplate && canCuttop) {
                        cutNum++;
                        this->cutActionMp3();
                        this->pumpkinAction(cutNum);
                    }
                }else if(onions){
                    if (onion!=NULL && CCRect(center.x-90, center.y, 180, 90).containsPoint(newPoint) && !isMoveComplate && canCuttop) {
                        cutNum++;
                        this->cutActionMp3();
                        this->onionAction(cutNum);
                    }
                }else if(garlics){
                    if (garlic!=NULL && CCRect(center.x-90, center.y, 180, 90).containsPoint(newPoint) && !isMoveComplate && canCuttop) {
                        cutNum++;
                        this->cutActionMp3();
                        this->garlicAction(cutNum);
                    }
                }
            }
        }
    }
}

void CutMaterial::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent){
    CCTouch *pTouch = (CCTouch*)(pTouches->anyObject());
    CCPoint location = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
    pizzaLineSprite->pointList.clear();
    if(isMoveComplate){
        this->setComplate();
    }
    

}

//CCRect CutMaterial::createRectByPoint(CCPoint point, float width, float height){
//    return CCRectMake(point.x-width/2,point.y-height/2,width,height);       //CCRectMake(x,y,width,height)；x,矩形左下角x坐标；y，矩形左下角y坐标；width，矩形宽度；height，矩形高度
//}
