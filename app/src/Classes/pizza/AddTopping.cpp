//
//  AddTopping.cpp
//  Pizza
//
//  Created by LiXiaofei on 4/5/21.
//

#include "AddTopping.h"
#include "GameManager.h"
#include "PizzaManager.h"
#include "CutTopping.h"
#include "SelectTopping.h"
#include "SimpleAudioEngine.h"
#include "BakedPizza.h"
#include "MakePizza.h"
//#include "DeviceManager.h"



using namespace CocosDenshion;

enum{
    kBack=0,
    kScrollViewTag=1,
    kNextTag = 2,
    kTopping = 10,
    kNewTop =100,
    kVegTop = 200,
    kPizzaTag = 220,
    kPepperTag = 110,
    kHawaiiTag = 111,
    kMoreCheeseTag = 112,
    kGuard=3,
};

CCScene* AddTopping::scene(){
    CCScene* scene = CCScene::create();
    AddTopping* layer = AddTopping::create();
    scene->addChild(layer);
    return scene;
}

void AddTopping::onEnter(){
    CCLayer::onEnter();
}

void AddTopping::onExit(){
    CCLayer::onExit();
}

AddTopping::AddTopping(){}
AddTopping::~AddTopping(){}

bool AddTopping::init(){
    if (!CCLayer::init()) {
        return false;
    }
    newTop = NULL;
    addTopping = false;
    
    clickNext = false;
    backClick=false;
    selectTop=false;
    board=NULL;
    pizzaShape=NULL;
    
    iphoneXoffsetX = 0.0f;
    
//    curPizza = PizzaManager::sharedManager()->whichPizza;
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("pizza/animate/pick.plist");
    center = GameManager::sharedManager()->getCenter();
    CCPoint leftTop = GameManager::sharedManager()->getLeftTopPos();
    CCPoint rightTop = GameManager::sharedManager()->getRightTopPos();
    
    CCSprite* bg = CCSprite::create("background/bg2.png");
    bg->setPosition(center);
    this->addChild(bg);
    if(GameManager::sharedManager()->isIphoneX()){
        bg->setScale(1.3);
        iphoneXoffsetX = 100.0f;
    }
    
    

   if (GameManager::sharedManager()->isAndroidPad()) {
       ipadX=-50;
   }
    
    CCSprite* back = CCSprite::create("background/back.png");
    back->setPosition(ccp(leftTop.x+50,leftTop.y-50));
    back->setTag(kBack);
    this->addChild(back);
    
    CCSprite* next = CCSprite::create("background/next.png");
    next->setPosition(ccp(rightTop.x-50,rightTop.y-50));
    next->setTag(kNextTag);
    this->addChild(next,99);
    
    board = CCScale9Sprite::create("background/toppings-board.png");
//    board->setPosition(ccp(center.x, center.y-210));
    board->setPosition(ccp(center.x+300+ipadX, center.y-30));
    board->setRotation(90);
//    board->setScaleY(1.2);
    this->addChild(board,10);
   
    if (PizzaManager::sharedManager()->whichPizza ==7 || PizzaManager::sharedManager()->whichPizza ==8) {
        this->showTopping();
    }else if (PizzaManager::sharedManager()->whichPizza ==0) {
        this->showPepperTopping();
    }else if (PizzaManager::sharedManager()->whichPizza ==5) {
        this->showHawaiiTopping();
    }else if (PizzaManager::sharedManager()->whichPizza ==3) {
        this->showMoreCheeseTopping();
    }else if (PizzaManager::sharedManager()->whichPizza ==2){
        this->candyTopping();
    }else if (PizzaManager::sharedManager()->whichPizza ==4){
        this->halloweenTopping();
    }else if (PizzaManager::sharedManager()->whichPizza ==6){
        this->christmasTopping();
    }
    
//    if (DeviceManager::sharedManager()->getIsPad()) {
//        x_x = 80;
//    }
    
//    if(GameManager::sharedManager()->firstPlayPizza){
//        this->playGuaid();
//    }
//    this->showPizza();
    this->scheduleOnce(schedule_selector(AddTopping::showPizza), 0.4);
    this->setTouchEnabled(true);
    return true;
}

void AddTopping::playGuaid(){
    //手势
    CCSprite* bakeMachine = (CCSprite*)this->getChildByTag(kNextTag);
    if (bakeMachine!=NULL) {
        CCSprite* finger = CCSprite::createWithSpriteFrameName("touch0.png");
        finger->setPosition(ccp(bakeMachine->getPosition().x+bakeMachine->getContentSize().width/2, bakeMachine->getPosition().y-bakeMachine->getContentSize().height/2));
        finger->setTag(kGuard);
        finger->setScale(0.5);
        finger->runAction(CCFadeIn::create(0.3));
        this->addChild(finger,10);
        this->schedule(schedule_selector(BakedPizza::guardAction),1.0f);
    }

}

void AddTopping::guardAction(){
    CCSprite* finger=(CCSprite*)this->getChildByTag(kGuard);
    if (finger!=NULL) {
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
    }

//    }
        
}

void AddTopping::showPizza(){
     CCLog("---%d---",PizzaManager::sharedManager()->whichShape);
    if (pizzaShape==NULL) {
        const char* file = "";
    //    PizzaManager::sharedManager()->whichShape=1;
        if (PizzaManager::sharedManager()->whichShape==1) {
            if (PizzaManager::sharedManager()->whichPizza==2) {
                file ="candy_heart";
            }else if (PizzaManager::sharedManager()->whichPizza==4) {
                file ="halloween_heart";
            }else if (PizzaManager::sharedManager()->whichPizza==6) {
                file ="christmas_heart";
            }else{
                file ="heartPizza";
            }
            
    //        pizzaShape = CCSprite::create("pizza/element/heartPizza.png");
        }else if (PizzaManager::sharedManager()->whichShape==3) {
            if (PizzaManager::sharedManager()->whichPizza==2) {
                file ="candy_equal";
            }else if (PizzaManager::sharedManager()->whichPizza==4) {
                file ="halloween_equal";
            }else if (PizzaManager::sharedManager()->whichPizza==6) {
                file ="christmas_equal";
            }else{
                file ="equalPizza";
            }
    //        pizzaShape = CCSprite::create("pizza/element/equalPizza.png");
        }else if (PizzaManager::sharedManager()->whichShape==2) {
            if (PizzaManager::sharedManager()->whichPizza==2) {
                file ="candy_rect";
            }else if (PizzaManager::sharedManager()->whichPizza==4) {
                file ="halloween_rect";
            }else if (PizzaManager::sharedManager()->whichPizza==6) {
                file ="christmas_rect";
            }else{
                file ="rectPizza";
            }
    //        pizzaShape = CCSprite::create("pizza/element/rectPizza.png");
        }

        pizzaShape = CCSprite::create(CCString::createWithFormat("pizza/element/%s.png",file)->getCString());
    //    pizzaShape->setScale(0.7);
        pizzaShape->setTag(kPizzaTag);
    //    pizzaShape->setPosition(ccp(center.x, center.y+800));
        pizzaShape->setPosition(ccp(center.x-150, center.y-30));
    //    pizzaShape->setScale(1.2);
        
    //    pizzaShape->runAction(CCEaseIn::create(CCMoveTo::create(0.33, ccp(center.x, center.y+50)), 0.3));
        this->addChild(pizzaShape,9);
        SimpleAudioEngine::sharedEngine()->playEffect("mp3/movein.wav");
    }

}

void AddTopping::candyTopping(){
    whichTopping=1;
    
//    containerLayer=CCLayer::create();
//    scrollView = extension::CCScrollView::create();
//    scrollView->setPosition(ccp(15, 0));                        //位置
//    scrollView->setViewSize(CCSizeMake(board->getContentSize().width/1.04, board->getContentSize().height));
//    containerLayer->setContentSize(CCSizeMake(board->getContentSize().width+1000, center.y-140));
//
//
//    scrollView->setContainer(containerLayer);
//    scrollView->setContentOffset(ccp(PizzaManager::sharedManager()->xDispostion, 0));
//
//    scrollView->setTouchEnabled(true);
//    scrollView->setDirection(cocos2d::extension::kCCScrollViewDirectionHorizontal);                 //只能横向拖动
//    scrollView->setDelegate(this);
//    scrollView->setTag(kScrollViewTag);
//    scrollView->setBounceable(true);                //是否具有弹性
//    board->addChild(scrollView);
//    containerLayer->setTouchEnabled(true);
//
    for (int i =0; i<PizzaManager::sharedManager()->selectedNum; i++) {
        CCLog("----%d----",PizzaManager::sharedManager()->topping[i]);
    }

    CCLog("----%d----",PizzaManager::sharedManager()->selectedNum);
    int row = 0;
    int column = 0;
    
    for (int i =0; i<8; i++) {
        char nmName[100] = {0};
        sprintf(nmName, "pizza/element/topping/candy/candy_top_%d.png",i+1);     //随机加载数字
        CCLog("----%s----",nmName);                 //
        CCSprite* top = CCSprite::create(nmName);
//        if (PizzaManager::sharedManager()->selectedNum==1) {
//            top->setPosition(ccp(350, center.y-255));
//        }else if (PizzaManager::sharedManager()->selectedNum==2){
//            top->setPosition(ccp(250+i*200, center.y-255));
//        }else{
//            top->setPosition(ccp(200+i*200, center.y-255));
//        }
        
        top->setPosition(ccp(center.x+230+column*150+ipadX, center.y+155-row*120));
        top->setTag(kTopping+i);
        if (GameManager::sharedManager()->isIphoneX()) {
            top->setScale(1.0);
        }
       else if(GameManager::sharedManager()->isAndroidPad()){
            top->setScale(1.1);
        }
        else{
            top->setScale(1.0);
        }
//        containerLayer->addChild(top);
        this->addChild(top,10);
        
        if (column < 1) {
            column++;
        }else {
            column = 0;
            row++;
        }
    }
    if (board!=NULL) {
        board->setContentSize(CCSize(500,320));
    }
    
//    board->setScaleY(2.2);
//    if(!haveMovedScroll){
//        CCPoint beginPos=containerLayer->getPosition();
//        containerLayer->runAction(CCSequence::create(CCDelayTime::create(0.5),
//                                                     CCEaseOut::create(CCMoveTo::create(1.0,ccp(beginPos.x+850, beginPos.y)), 1),
//    //                                                 CCMoveTo::create(1.5,ccp(GameManager::sharedManager()->xDispostion, beginPos.y)),
//                                                     NULL));
//        PizzaManager::sharedManager()->xDispostion = -100;
//        haveMovedScroll = true;
//    }
    
    
}

void AddTopping::halloweenTopping(){
    whichTopping = 2;
//    containerLayer=CCLayer::create();
//    scrollView = extension::CCScrollView::create();
//    scrollView->setPosition(ccp(15, 0));                        //位置
//    scrollView->setViewSize(CCSizeMake(board->getContentSize().width/1.04, board->getContentSize().height));
//    containerLayer->setContentSize(CCSizeMake(board->getContentSize().width+400, center.y-140));
//
//
//    scrollView->setContainer(containerLayer);
//    scrollView->setContentOffset(ccp(PizzaManager::sharedManager()->halloXDis, 0));
//
//    scrollView->setTouchEnabled(true);
//    scrollView->setDirection(cocos2d::extension::kCCScrollViewDirectionHorizontal);                 //只能横向拖动
//    scrollView->setDelegate(this);
//    scrollView->setTag(kScrollViewTag);
//    scrollView->setBounceable(true);                //是否具有弹性
//    board->addChild(scrollView);
//
//    containerLayer->setTouchEnabled(true);
    
    for (int i =0; i<PizzaManager::sharedManager()->selectedNum; i++) {
        CCLog("----%d----",PizzaManager::sharedManager()->topping[i]);
    }
    int row = 0;
    int column = 0;
    CCLog("----%d----",PizzaManager::sharedManager()->selectedNum);
    for (int i =0; i<5; i++) {
        char nmName[100] = {0};
        sprintf(nmName, "pizza/element/topping/halloween/halloween_top_%d.png",i+1);     //随机加载数字
        CCLog("----%s----",nmName);                 //
        CCSprite* top = CCSprite::create(nmName);
//        if (PizzaManager::sharedManager()->selectedNum==1) {
//            top->setPosition(ccp(350, center.y-255));
//        }else if (PizzaManager::sharedManager()->selectedNum==2){
//            top->setPosition(ccp(250+i*200, center.y-255));
//        }else{
            top->setPosition(ccp(center.x+230+column*150+ipadX, center.y+105-row*120));
//        }
        top->setTag(kTopping+i);
        if (GameManager::sharedManager()->isIphoneX()) {
            top->setScale(1.0);
        }
        else if(GameManager::sharedManager()->isAndroidPad()){
            top->setScale(1.1);
        }
        else{
            top->setScale(1.0);
        }
//        containerLayer->addChild(top);
        this->addChild(top,10);
        if (column < 1) {
            column++;
        }else {
            column = 0;
            row++;
        }
    }
    if (board!=NULL) {
        board->setContentSize(CCSize(400,320));
    }
    
//    if(!haveMovedScroll){
//        CCPoint beginPos=containerLayer->getPosition();
//        containerLayer->runAction(CCSequence::create(CCDelayTime::create(0.5),
//                                                     CCEaseOut::create(CCMoveTo::create(0.8,ccp(beginPos.x+490, beginPos.y)), 1),
//    //                                                 CCMoveTo::create(1.5,ccp(GameManager::sharedManager()->xDispostion, beginPos.y)),
//                                                     NULL));
//        PizzaManager::sharedManager()->halloXDis = -100;
//        haveMovedScroll = true;
//    }
}

void AddTopping::christmasTopping(){
    whichTopping = 3;
//    containerLayer=CCLayer::create();
//    scrollView = extension::CCScrollView::create();
//    scrollView->setPosition(ccp(15, 0));                        //位置
//    scrollView->setViewSize(CCSizeMake(board->getContentSize().width/1.04, board->getContentSize().height));
//    containerLayer->setContentSize(CCSizeMake(board->getContentSize().width+1000, center.y-140));
//
//
//    scrollView->setContainer(containerLayer);
//    scrollView->setContentOffset(ccp(PizzaManager::sharedManager()->xDispostion, 0));
//
//    scrollView->setTouchEnabled(true);
//    scrollView->setDirection(cocos2d::extension::kCCScrollViewDirectionHorizontal);                 //只能横向拖动
//    scrollView->setDelegate(this);
//    scrollView->setTag(kScrollViewTag);
//    scrollView->setBounceable(true);                //是否具有弹性
//    board->addChild(scrollView);
////    containerLayer->setPosition(ccp(<#__X__#>, 0));
//    containerLayer->setTouchEnabled(true);
    
    for (int i =0; i<PizzaManager::sharedManager()->selectedNum; i++) {
        CCLog("----%d----",PizzaManager::sharedManager()->topping[i]);
    }
    int row = 0;
    int column = 0;
    CCLog("----%d----",PizzaManager::sharedManager()->selectedNum);
    for (int i =0; i<8; i++) {
        char nmName[100] = {0};
        sprintf(nmName, "pizza/element/topping/christmas/christmas_top_%d.png",i+1);     //随机加载数字
        CCLog("----%s----",nmName);                 //
        CCSprite* top = CCSprite::create(nmName);
//        if (PizzaManager::sharedManager()->selectedNum==1) {
//            top->setPosition(ccp(350, center.y-255));
//        }else if (PizzaManager::sharedManager()->selectedNum==2){
//            top->setPosition(ccp(250+i*200, center.y-255));
//        }else{
            top->setPosition(ccp(center.x+230+column*150+ipadX, center.y+155-row*120));
//        }
        top->setTag(kTopping+i);
        if (GameManager::sharedManager()->isIphoneX()) {
            top->setScale(1.0);
        }else if(GameManager::sharedManager()->isAndroidPad()){
            top->setScale(1.1);
        }else{
            top->setScale(1.0);
        }
//        containerLayer->addChild(top);
        this->addChild(top,10);
        if (column < 1) {
            column++;
        }else {
            column = 0;
            row++;
        }
    }
    if (board!=NULL) {
        board->setContentSize(CCSize(500,320));
    }
    
//    if(!haveMovedScroll){
//        CCPoint beginPos=containerLayer->getPosition();
//        containerLayer->runAction(CCSequence::create(CCDelayTime::create(0.5),
//                                                     CCEaseOut::create(CCMoveTo::create(1.0,ccp(beginPos.x+850, beginPos.y)), 1),
//    //                                                 CCMoveTo::create(1.5,ccp(GameManager::sharedManager()->xDispostion, beginPos.y)),
//                                                     NULL));
//        PizzaManager::sharedManager()->xDispostion = -100;
//        haveMovedScroll = true;
//    }
}



void AddTopping::showTopping(){
    CCPoint leftTop = GameManager::sharedManager()->getLeftTopPos();
    CCPoint rightTop = GameManager::sharedManager()->getRightTopPos();
    CCPoint rightBottom=GameManager::sharedManager()->getLeftBottomPos();
    CCSize winsize = CCEGLView::sharedOpenGLView()->getVisibleSize();
//    PizzaManager::sharedManager()->topXDis = -(PizzaManager::sharedManager()->selectedNum*118);
////    CCSprite* board = CCSprite::create("background/toppings-board.png");
////    board->setPosition(ccp(center.x, center.y-150));
//////    board->setScaleY(1.2);
////    this->addChild(board);
////    CCSprite* board = CCSprite::create("background/toparea.png");
////    board->setPosition(ccp(center.x, center.y-150));
////    this->addChild(board);
//    containerLayer=CCLayer::create();
//    scrollView = extension::CCScrollView::create();
//    scrollView->setPosition(ccp(15, 0));                        //位置
//    scrollView->setViewSize(CCSizeMake(board->getContentSize().width/1.04, board->getContentSize().height));
////    scrollView->setContentOffset(ccp(board->getPosition().x-x_x, center.y-150));
//
////    scrollView->setContentSize(CCSizeMake(3000, center.y-150));
//    containerLayer->setContentSize(CCSizeMake(board->getContentSize().width+((PizzaManager::sharedManager()->selectedNum-3)*200), center.y-150));
//
////    containerLayer->setPosition(ccp(-x_x, 0));
//    scrollView->setContainer(containerLayer);
//    scrollView->setContentOffset(ccp(PizzaManager::sharedManager()->topXDis, 0));
//
//    scrollView->setTouchEnabled(true);
//    scrollView->setDirection(cocos2d::extension::kCCScrollViewDirectionHorizontal);                 //只能横向拖动
//    scrollView->setDelegate(this);
//    scrollView->setTag(kScrollViewTag);
//    scrollView->setBounceable(true);                //是否具有弹性
//    board->addChild(scrollView);
//
//    containerLayer->setTouchEnabled(true);
    
    if(PizzaManager::sharedManager()->selectedNum==1){
            topDis=100;
        }else if(PizzaManager::sharedManager()->selectedNum==2){
            topDis=100;
        }else if(PizzaManager::sharedManager()->selectedNum==3){
            topDis=50;
        }else{
            topDis=0;
        }
    
    for (int i =0; i<PizzaManager::sharedManager()->selectedNum; i++) {
        CCLog("----%d----",PizzaManager::sharedManager()->topping[i]);
    }
    
    int row = 0;
    int column = 0;
    int topX=0;
    if (PizzaManager::sharedManager()->selectedNum>=9) {
        topX=10;
    }
    float offsetYModule = 0.0f;
    offsetYModule = PizzaManager::sharedManager()->selectedNum/2.0;
    if (PizzaManager::sharedManager()->selectedNum > 4) {
        offsetYModule = ((PizzaManager::sharedManager()->selectedNum-1)/2)/2.0;
    }
    
    CCLog("----%d----",PizzaManager::sharedManager()->selectedNum);
    for (int i =0; i<PizzaManager::sharedManager()->selectedNum; i++) {
//        CCSprite* top = CCSprite::create(CCString::createWithFormat("topping/topping_1.png"));
//        CCSprite* top = CCSprite::create("topping/topping_1.png");
        
        char nmName[100] = {0};
        sprintf(nmName, "pizza/element/topping/topping_%d.png",PizzaManager::sharedManager()->topping[i]);     //随机加载数字
//        sprintf(nmName, "pizza/element/topping/topping_%d.png",i);
        CCLog("----%s----",nmName);                 //
        CCSprite* top = CCSprite::create(nmName);
//        if(i<=5){
//            top->setPosition(ccp(210+(i-1)*180, center.y+150));
//        }else if(i>4){
//            top->setPosition(ccp(210+(i-6)*180, center.y));
//        }
        
        if (PizzaManager::sharedManager()->selectedNum==1) {
            top->setPosition(ccp(center.x+300+ipadX, center.y-25));
        }else if (PizzaManager::sharedManager()->selectedNum <= 4){
            top->setPosition(ccp(center.x+300+ipadX, center.y+60+80*(offsetYModule-1)-i*120));
        }else{
            top->setPosition(ccp(center.x+230+column*150+ipadX, center.y+100+100*(offsetYModule-1)-row*(120-topX)));
        }
        top->setTag(kTopping+i);
//        if (GameManager::sharedManager()->isIphoneX()) {
//            top->setScale(1.0);
//        }else if(DeviceManager::sharedManager()->getIsPad()){
//            top->setScale(1.1);
//        }else{
//            top->setScale(1.0);
//        }
//        top->setScale(0.8);
//        containerLayer->addChild(top);
        this->addChild(top,10);
        if (column < 1) {
            column++;
        }else {
            column = 0;
            row++;
        }
    }
    
    if (board!=NULL) {
        if (PizzaManager::sharedManager()->selectedNum < 5) {
            board->setContentSize(CCSize(500,160));
        }else if (PizzaManager::sharedManager()->selectedNum < 7) {
            board->setContentSize(CCSize(400,320));
        }else if (PizzaManager::sharedManager()->selectedNum < 9) {
            board->setContentSize(CCSize(500,320));
        }else if (PizzaManager::sharedManager()->selectedNum<=10) {
            board->setContentSize(CCSize(580,320));
    //        board->setScale(0.9);
        }
    }

    
//    if(!haveMovedScroll){
//        CCPoint beginPos=containerLayer->getPosition();
//        containerLayer->runAction(CCSequence::create(CCDelayTime::create(0.5),
//                                                     CCEaseOut::create(CCMoveTo::create(0.1*PizzaManager::sharedManager()->selectedNum,ccp(beginPos.x+PizzaManager::sharedManager()->selectedNum*118-100+topDis, beginPos.y)), 1),
//    //                                                 CCMoveTo::create(1.5,ccp(GameManager::sharedManager()->xDispostion, beginPos.y)),
//                                                     NULL));
//        PizzaManager::sharedManager()->topXDis = -100;
//        haveMovedScroll = true;
//    }
//    for (int i = 0; i<5; i++) {
//        CCSprite* topping = CCSprite::create("element/cheese.png");
//        topping->setPosition(ccp(100+i*200, center.y-200));
//        topping->setTag(kTopping+i);
////        topping->setScale(1.5);
//        containerLayer->addChild(topping,2);
//    }
}

void AddTopping::showPepperTopping(){
    CCSprite* top = CCSprite::create("pizza/element/topping/topping_9.png");
    top->setPosition(ccp(center.x+300+ipadX, center.y-25));
    top->setTag(kPepperTag);
//    if (GameManager::sharedManager()->isIphoneX()) {
//        top->setScale(1.0);
//    }else if(DeviceManager::sharedManager()->getIsPad()){
////        top->setScale(1.3);
//    }else{
//        top->setScale(1.0);
//    }
//    top->setScale(0.8);
    this->addChild(top,11);
    if (board!=NULL) {
        board->setContentSize(CCSize(500,160));
    }
    
}


void AddTopping::showHawaiiTopping(){
    CCSprite* top = CCSprite::create("pizza/element/topping/topping_5.png");
    top->setPosition(ccp(center.x+300+ipadX, center.y-25));
    top->setTag(kHawaiiTag);
//    top->setScale(0.8);
    if (GameManager::sharedManager()->isIphoneX()) {
        top->setScale(1.0);
    }else if(GameManager::sharedManager()->isAndroidPad()){
        top->setScale(1.3);
    }else{
        top->setScale(1.0);
    }
    this->addChild(top,11);
    if (board!=NULL) {
        board->setContentSize(CCSize(500,160));
    }
    
}

void AddTopping::showVegTopping(){
//    for (int i=0; i<7; i++) {
//        char nmName[100] = {0};
//        sprintf(nmName, "element/topping%d.png",PizzaManager::sharedManager()->topping[i]);     //随机加载数字
//        CCSprite* top = CCSprite::create(nmName);
//        top->setPosition(ccp(200+i*200, center.y-245));
//        top->setTag(kVegTop+i);
//        top->setScale(0.8);
//        this->addChild(top,9);
//    }
    
}

void AddTopping::showMoreCheeseTopping(){
    CCSprite* top = CCSprite::create("pizza/element/cheese.png");
    top->setPosition(ccp(center.x+300+ipadX, center.y-25));
    top->setTag(kMoreCheeseTag);
    top->setScale(0.7);
    this->addChild(top,11);
    if (board!=NULL) {
        board->setContentSize(CCSize(500,160));
    }
    
}

void AddTopping::scrollViewDidScroll(extension::CCScrollView *view){
    PizzaManager::sharedManager()->xDispostion = containerLayer->getPosition().x;
    PizzaManager::sharedManager()->halloXDis =containerLayer->getPosition().x;
    PizzaManager::sharedManager()->topXDis = containerLayer->getPosition().x;
    return;
}

void AddTopping::scrollViewDidZoom(extension::CCScrollView *view){
    return;
}

void AddTopping::goNext(){
    haveMovedScroll = false;
    PizzaManager::sharedManager()->xDispostion =-950;
    PizzaManager::sharedManager()->halloXDis =-590;
    PizzaManager::sharedManager()->topXDis = -(PizzaManager::sharedManager()->selectedNum*118);
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, BakedPizza::scene(), ccBLACK));
}

void AddTopping::clickBack(){
    if (PizzaManager::sharedManager()->whichPizza ==0 || PizzaManager::sharedManager()->whichPizza ==5) {
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, CutTopping::scene(), ccBLACK));
    }else if(PizzaManager::sharedManager()->whichPizza ==7 || PizzaManager::sharedManager()->whichPizza ==8){
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, SelectTopping::scene(), ccBLACK));
    }else if(PizzaManager::sharedManager()->whichPizza ==2 || PizzaManager::sharedManager()->whichPizza ==4 || PizzaManager::sharedManager()->whichPizza ==6 || PizzaManager::sharedManager()->whichPizza ==1 || PizzaManager::sharedManager()->whichPizza ==3){
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, MakePizza::scene(), ccBLACK));
    }
}

bool AddTopping::ccTouchBegan(cocos2d::CCTouch *touch, cocos2d::CCEvent *event){
//    showTop=false;
//    CCTouch *pTouch = (CCTouch*)(touch->anyObject());  //一个触摸的对象
    CCPoint location = touch->getLocationInView();
    location = CCDirector::sharedDirector()->convertToGL(location);//触摸点在这个场景的位置
    beginTouchX = PizzaManager::sharedManager()->xDispostion;
    beginPosY =location.y;
    beginPosX = location.x;
    CCSprite* back = (CCSprite*)this->getChildByTag(kBack);
    CCSprite* next = (CCSprite*)this->getChildByTag(kNextTag);
//    this->unschedule(schedule_selector(BakedPizza::guardAction));
//    this->removeChildByTag(kGuard);
    if (next !=NULL && next->boundingBox().containsPoint(location) && clickNext==false) {
        clickNext = true;
        SimpleAudioEngine::sharedEngine()->playEffect("mp3/touchItem.mp3");
        goNext();
//        CCUserDefault::sharedUserDefault()->setBoolForKey("isFirstPizza", false);
//        GameManager::sharedManager()->firstPlayPizza=false;
    }
    if (back!=NULL && back->boundingBox().containsPoint(location) && backClick==false) {
        backClick = true;
        haveMovedScroll = false;
        PizzaManager::sharedManager()->xDispostion =-950;
        PizzaManager::sharedManager()->halloXDis =-590;
        PizzaManager::sharedManager()->topXDis = -(PizzaManager::sharedManager()->selectedNum*118);
//        SimpleAudioEngine::sharedEngine()->playEffect("mp3/done.mp3");
        CCScaleBy* scaleBy = CCScaleBy::create(0.1, 1.2);
        //            homeBtn->setScale(1.2);
        //            touchSprite = homeBtn;
        SimpleAudioEngine::sharedEngine()->playEffect("mp3/touchItem.mp3");
        back->runAction(CCSequence::createWithTwoActions(CCSequence::createWithTwoActions(scaleBy, scaleBy->reverse()), CCCallFunc::create(this, callfunc_selector(AddTopping::clickBack))));
        PizzaManager::sharedManager()->cleanAllSprite();
        
    }
   
//    if (abs(xDis)<20 && abs(xDis)!=0) {
//
//    }
//    if (PizzaManager::sharedManager()->whichPizza>9 || PizzaManager::sharedManager()->whichPizza<0) {
//        PizzaManager::sharedManager()->whichPizza = curPizza;
//    }
    
    CCLog("----点击%d----",PizzaManager::sharedManager()->whichPizza);
    if (newTop==NULL) {
        if(PizzaManager::sharedManager()->whichPizza == 3){
            CCSprite* cheese = (CCSprite*)this->getChildByTag(kMoreCheeseTag);
            if (cheese != NULL && cheese->boundingBox().containsPoint(location) && selectTop==false) {
//                scrollView->setTouchEnabled(false);
                SimpleAudioEngine::sharedEngine()->playEffect("mp3/touchItem.mp3");
                newTop = CCSprite::create("pizza/element/cheese.png");
                newTop->setPosition(cheese->getPosition());
                originalPosition = newTop->getPosition();
                this->addChild(newTop,15);
    //            CC_SAFE_RETAIN(newTop);
                selectTop=true;
                showTop=false;
            }
        }else if(PizzaManager::sharedManager()->whichPizza == 5){
            CCSprite* Hawaii = (CCSprite*)this->getChildByTag(kHawaiiTag);
            if (Hawaii != NULL && Hawaii->boundingBox().containsPoint(location) && selectTop==false) {
//                scrollView->setTouchEnabled(false);
                
                SimpleAudioEngine::sharedEngine()->playEffect("mp3/touchItem.mp3");
                newTop = CCSprite::create("pizza/element/topping_5.png");
                newTop->setPosition(Hawaii->getPosition());
                originalPosition = newTop->getPosition();
                this->addChild(newTop,15);
    //            CC_SAFE_RETAIN(newTop);
                selectTop=true;
                showTop=false;
            }
        }else if (PizzaManager::sharedManager()->whichPizza == 0) {
            CCSprite* Pepper = (CCSprite*)this->getChildByTag(kPepperTag);
            if (Pepper != NULL && Pepper->boundingBox().containsPoint(location) && selectTop==false) {
                SimpleAudioEngine::sharedEngine()->playEffect("mp3/touchItem.mp3");
                newTop = CCSprite::create("pizza/element/topping_9.png");
                newTop->setPosition(Pepper->getPosition());
                originalPosition = newTop->getPosition();
                this->addChild(newTop,15);
                selectTop=true;
                showTop=false;
//                CCLog("----选上了----");
    //            CC_SAFE_RETAIN(newTop);
            }
        }else if (PizzaManager::sharedManager()->whichPizza == 7 || PizzaManager::sharedManager()->whichPizza == 8) {
            for (int i =0; i<PizzaManager::sharedManager()->selectedNum; i++) {
//                CCSprite* topping = (CCSprite*)containerLayer->getChildByTag(kTopping+i);
//                CCPoint topPos = containerLayer->convertToNodeSpace(location);
                CCSprite* topping = (CCSprite*)this->getChildByTag(kTopping+i);
    //            CCPoint touchTopPos = containerLayer->convertToWorldSpace(location);
                if (topping != NULL && topping->boundingBox().containsPoint(location) && selectTop==false) {
//                    scrollView->setTouchEnabled(false);
                    SimpleAudioEngine::sharedEngine()->playEffect("mp3/touchItem.mp3");
        //            selected=true;
        //            selectedTop = i;
                    touchTopping=i;
                    char nmName[100] = {0};
                    sprintf(nmName, "pizza/element/topping_%d.png",PizzaManager::sharedManager()->topping[i]);     //随机加载数字
                    CCLog("----%s----",nmName);                 //
                    newTop = CCSprite::create(nmName);
        //                if (newTop != NULL) {
                    newTop->setPosition(location);
                    originalPosition = newTop->getPosition();
    //                newTop->setTag(kNewTop);
                    this->addChild(newTop,15);
    //                CC_SAFE_RETAIN(newTop);
        //            if (PizzaManager::sharedManager()->addTop[i] != i) {
        //                PizzaManager::sharedManager()->addPizzaTopping(i);
        //            }
                    selectTop=true;
                    showTop=false;
                }else{
//                    scrollView->setTouchEnabled(true);
                }
            }
        }else{
            const char* file="";
            int topNum=0;
            if (whichTopping==1) {
                file = "candy";
                topNum=8;
            }else if (whichTopping==2){
                file = "halloween";
                topNum=5;
            }else if (whichTopping==3){
                file = "christmas";
                topNum=8;
            }
            
            for (int i =0; i<topNum; i++) {
//                CCSprite* topping = (CCSprite*)containerLayer->getChildByTag(kTopping+i);
                CCSprite* topping = (CCSprite*)this->getChildByTag(kTopping+i);
//                CCPoint topPos = containerLayer->convertToNodeSpace(location);
    //            CCPoint touchTopPos = containerLayer->convertToWorldSpace(location);
                if (topping != NULL && topping->boundingBox().containsPoint(location) && selectTop==false) {
//                    scrollView->setTouchEnabled(false);
                    SimpleAudioEngine::sharedEngine()->playEffect("mp3/touchItem.mp3");
        //            selected=true;
        //            selectedTop = i;
//                    touchTopping=i+1;
                    char nmName[100] = {0};
                    if (i==1 && strcmp(file, "christmas")==0) {
                        int j=arc4random()%2;
                        if (j==0) {
                            touchTopping=i+1;
                            sprintf(nmName, "pizza/element/topping/%s/%s_top%d.png",file,file,i+1);
                        }else{
                            touchTopping=i+8;
                            sprintf(nmName, "pizza/element/topping/%s/%s_top%d.png",file,file,i+8);
                        }
//                        sprintf(nmName, "pizza/element/topping/%s/%s_top%d.png",file,file,i+1);
                    }else{
                        touchTopping=i+1;
                        sprintf(nmName, "pizza/element/topping/%s/%s_top%d.png",file,file,i+1);
                    }
//                    sprintf(nmName, "pizza/element/topping/%s/%s_top%d.png",file,file,i+1);     //随机加载数字
                    CCLog("----%s----",nmName);                 //
                    newTop = CCSprite::create(nmName);
        //                if (newTop != NULL) {
                    newTop->setPosition(location);
                    originalPosition = newTop->getPosition();
    //                newTop->setTag(kNewTop);
                    this->addChild(newTop,15);
    //                CC_SAFE_RETAIN(newTop);
        //            if (PizzaManager::sharedManager()->addTop[i] != i) {
        //                PizzaManager::sharedManager()->addPizzaTopping(i);
        //            }
                    selectTop=true;
                    showTop=false;
                }else{
//                    scrollView->setTouchEnabled(true);
                }
            }
        }
    }
    return true;
    
}

void AddTopping::ccTouchMoved(cocos2d::CCTouch* touch, cocos2d::CCEvent* event){
    CCPoint location = touch->getLocationInView();
    location = CCDirector::sharedDirector()->convertToGL(location);//触摸点在这个场景的位置
    CCPoint lastPoint = touch->getPreviousLocationInView();
    lastPoint = CCDirector::sharedDirector()->convertToGL(lastPoint);
    endPosY = location.y;
    endPosX = location.x;
    int yDis = endPosY - beginPosY;
    int xDisp = endPosX - beginPosX;
    int xmoveDisp = endPosX - lastPoint.x;
//    if (abs(yDis)>=10) {
//        showTop=true;
//    }
    if (abs(xDisp)>=20 &&  selectTop) {
//        showTop=true;
        if(newTop!=NULL){
            CCLOG("---横坐标%f---",location.x);
            CCLOG("---纵坐标%f---",location.y);
//            CCLog("----移动了----");
            newTop->setPosition(location);
        }
    }
}

void AddTopping::ccTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent* event){
    CCPoint location = touch->getLocationInView();
    location = CCDirector::sharedDirector()->convertToGL(location);//触摸点在这个场景的位置
    CCSprite* pizza = (CCSprite*)this->getChildByTag(kPizzaTag);
    CCPoint topPos = pizza->convertToNodeSpace(location);
    endTouchX = PizzaManager::sharedManager()->xDispostion;
    xDis = endTouchX-beginTouchX;
    endPosX = location.x;
    int xDisp = endPosX - beginPosX;
    if (abs(xDis)<10 && selectTop) {
        if (newTop != NULL) {
//            CCLog("----停止触摸----");
            int xDis=0;
            int yDis=0;
            int yDist1=0;
            int yDist2=0;
            float rectWidth = 40;
            float rectHeight = 40;
            if (PizzaManager::sharedManager()->whichShape==1) {
                storeWidth = 260;
                storeHeight = 150;
                storeWidth1 =100;
                storeHeight1 = 70;
                storeWidth2 =100;
                storeHeight2 = 40;
                storeWidth3 =50;
                storeHeight3 = 20;
                xDis = 130;
                yDis = 150;
                yDist1=40;
                yDist2=80;
            }else if(PizzaManager::sharedManager()->whichShape==2){
                if (GameManager::sharedManager()->isIphoneX()) {
                    storeWidth = 320;
                }else{
                    storeWidth = 320;
                }
                storeHeight = 201;
            }else if(PizzaManager::sharedManager()->whichShape==3){
                storeWidth = 240;
                storeHeight = 240;
                storeWidth1 = 40;
                storeHeight1 = 120;
                storeWidth2 =100;
                storeHeight2 = 40;
                storeWidth3 =100;
                storeHeight3 = 40;
                xDis=140;
                yDis=55;
                yDist1=-200;
                yDist2=75;
            }
//            float storeWidth = 400;
            CCPoint pos = ccp(center.x-150, center.y+55-70);
            CCPoint pos1 = ccp(center.x-xDis-150, center.y+yDis-70);
            CCPoint pos2 = ccp(center.x+xDis-150, center.y+yDis-70);
            CCPoint pos3 = ccp(center.x-150, center.y-yDist1-70);
            CCPoint pos4 = ccp(center.x-150, center.y-yDist2-70);
            CCRect rect1 = this->createRectByPoint(newTop->getPosition(), rectWidth, rectHeight);
//            if (PizzaManager::sharedManager()->whichShape==1) {
//                rect2 = this->createRectByPoint(pos, pizza->getContentSize().width/4, pizza->getContentSize().height/4.5);
//            }else{
//                rect2 = this->createRectByPoint(pos, pizza->getContentSize().width/3.5, pizza->getContentSize().height/4);
//            }
//
            CCRect rect2 = this->createRectByPoint(pos, storeWidth, storeHeight);
            CCRect rect3 = this->createRectByPoint(pos1, storeWidth1, storeHeight1);
            CCRect rect4 = this->createRectByPoint(pos2, storeWidth1, storeHeight1);
            CCRect rect5 = this->createRectByPoint(pos3, storeWidth2, storeHeight2);
            CCRect rect6 = this->createRectByPoint(pos4, storeWidth3, storeHeight3);
            if (PizzaManager::sharedManager()->whichShape==1) {
                CCLog("----圆形pizza----");
                if (rect1.intersectsRect(rect2) || rect1.intersectsRect(rect3) || rect1.intersectsRect(rect4) || rect1.intersectsRect(rect5) || rect1.intersectsRect(rect6)) {

                    
                    if(location.x>(220+iphoneXoffsetX) && location.x<(640+iphoneXoffsetX) && location.y>130 && location.y<430){
                        
                        if (PizzaManager::sharedManager()->whichPizza == 0) {
                            PizzaManager::sharedManager()->addPizzaTopping(9);
                            PizzaManager::sharedManager()->selectedTop++;
                        }else if(PizzaManager::sharedManager()->whichPizza == 5){
                            PizzaManager::sharedManager()->addPizzaTopping(5);
                            PizzaManager::sharedManager()->selectedTop++;
                        }else if(PizzaManager::sharedManager()->whichPizza == 7 || PizzaManager::sharedManager()->whichPizza == 8){
                            PizzaManager::sharedManager()->addPizzaTopping(PizzaManager::sharedManager()->topping[touchTopping]);
                            PizzaManager::sharedManager()->selectedTop++;
                        }else {
                            PizzaManager::sharedManager()->addPizzaTopping(touchTopping);
                            PizzaManager::sharedManager()->selectedTop++;
                        }
                        newTop->setPosition(location);
                        CCLOG("---心形移动距离%f---",abs(location.x-originalPosition.x));
                        addTopping = true;
                        PizzaManager::sharedManager()->addTopPos(topPos.x, topPos.y);
                        PizzaManager::sharedManager()->selectedTopPos++;
                        selectTop=false;
                    }else{
                        CCLog("----又点错了----");
                        newTop->removeFromParentAndCleanup(true);
                        addTopping = false;
                        newTop=NULL;
                        selectTop=false;
                    }


    //                newTop=NULL;
    //                if (PizzaManager::sharedManager()->addTop[0] == 0) {
                        CCLog("----点错了----");
    //                }
    //                return;
                }else{
                    //                newTop->runAction(CCMoveTo::create(0.2, originalPosition));
//                                    newTop->runAction(CCSequence::create(CCMoveTo::create(0.2, originalPosition),
//                                                                         CCRemoveSelf::create(),
//                                                                         NULL));
                                    newTop->removeFromParentAndCleanup(true);
//                                    CCLog("----%f----",originalPosition.x);
                    CCLog("----移出了----");
                    addTopping = false;
                                    newTop=NULL;
                                    selectTop=false;
                    //                return;
                                }
            }else if(PizzaManager::sharedManager()->whichShape==3){
                if (rect1.intersectsRect(rect2) || rect1.intersectsRect(rect3) || rect1.intersectsRect(rect4) || rect1.intersectsRect(rect5) || rect1.intersectsRect(rect6)) {

//                    CCLOG("---移动距离%f---",abs(location.x-originalPosition.x));
//                    CCLOG("---横坐标%f---",location.x);
//                    CCLOG("---纵坐标%f---",location.y);
                    if(location.x>(230+iphoneXoffsetX) && location.x<(610+iphoneXoffsetX) && location.y>115 && location.y<480){
                        if (PizzaManager::sharedManager()->whichPizza == 0) {
                            PizzaManager::sharedManager()->addPizzaTopping(9);
                            PizzaManager::sharedManager()->selectedTop++;
                        }else if(PizzaManager::sharedManager()->whichPizza == 5){
                            PizzaManager::sharedManager()->addPizzaTopping(5);
                            PizzaManager::sharedManager()->selectedTop++;
                        }else if(PizzaManager::sharedManager()->whichPizza ==7 || PizzaManager::sharedManager()->whichPizza ==8){
                            PizzaManager::sharedManager()->addPizzaTopping(PizzaManager::sharedManager()->topping[touchTopping]);
                            PizzaManager::sharedManager()->selectedTop++;
                        }else {
                            PizzaManager::sharedManager()->addPizzaTopping(touchTopping);
                            PizzaManager::sharedManager()->selectedTop++;
                        }
                        newTop->setPosition(location);
                        CCLOG("---圆形移动距离%f---",abs(location.x-originalPosition.x));
                        addTopping = true;
                        PizzaManager::sharedManager()->addTopPos(topPos.x, topPos.y);
                        PizzaManager::sharedManager()->selectedTopPos++;
                        selectTop=false;
                    }else{
                        newTop->removeFromParentAndCleanup(true);
                        addTopping = false;
                        newTop=NULL;
                        selectTop=false;
                    }
                    
                }else{
                    //                newTop->runAction(CCMoveTo::create(0.2, originalPosition));
//                                    newTop->runAction(CCSequence::create(CCMoveTo::create(0.2, originalPosition),
//                                                                         CCRemoveSelf::create(),
//                                                                         NULL));
                    newTop->removeFromParentAndCleanup(true);
                    CCLog("----%f----",originalPosition.x);
                                    newTop=NULL;
                    addTopping = false;
                    selectTop=false;
                    //                return;
                                }
            }else{
                if (rect1.intersectsRect(rect2)) {

                    if(location.x>(220+iphoneXoffsetX) && location.x<(620+iphoneXoffsetX) && location.y>160 && location.y<460){
                        if (PizzaManager::sharedManager()->whichPizza == 0) {
                            PizzaManager::sharedManager()->addPizzaTopping(9);
                            PizzaManager::sharedManager()->selectedTop++;
                        }else if(PizzaManager::sharedManager()->whichPizza == 5){
                            PizzaManager::sharedManager()->addPizzaTopping(5);
                            PizzaManager::sharedManager()->selectedTop++;
                        }else if(PizzaManager::sharedManager()->whichPizza ==7 || PizzaManager::sharedManager()->whichPizza ==8){
                            PizzaManager::sharedManager()->addPizzaTopping(PizzaManager::sharedManager()->topping[touchTopping]);
                            PizzaManager::sharedManager()->selectedTop++;
                        }else {
                            PizzaManager::sharedManager()->addPizzaTopping(touchTopping);
                            PizzaManager::sharedManager()->selectedTop++;
                        }
                        newTop->setPosition(location);
                        CCLOG("---方形移动距离%f---",abs(location.x-originalPosition.x));
                        PizzaManager::sharedManager()->addTopPos(topPos.x, topPos.y);
                        PizzaManager::sharedManager()->selectedTopPos++;
                        selectTop=false;
                        addTopping = true;
                    }else{
                        newTop->removeFromParentAndCleanup(true);
                        addTopping = false;
                        newTop=NULL;
                        selectTop=false;
                    }
    //                newTop=NULL;
    //                if (PizzaManager::sharedManager()->addTop[0] == 0) {
    //                    CCLog("----xuan----");
    //                }
    //                return;
                }else{
    //                newTop->runAction(CCMoveTo::create(0.2, originalPosition));
//                    newTop->runAction(CCSequence::create(CCMoveTo::create(0.2, originalPosition),
//                                                         CCRemoveSelf::create(),
//                                                         NULL));
                    newTop->removeFromParentAndCleanup(true);
                    CCLog("----%f----",originalPosition.x);
                    newTop=NULL;
                    addTopping = false;
                    selectTop=false;
    //                return;
                }
            }

//            if (newTop!=NULL) {
//                newTop->removeFromParentAndCleanup(true);
//                newTop=NULL;
//            }
            
        }

//    }else if (newTop!=NULL) {
//        newTop=NULL;
    }
//    if (PizzaManager::sharedManager()->whichPizza == 7 || PizzaManager::sharedManager()->whichPizza == 8){
////        scrollView->setTouchEnabled(true);
//    }
    if (newTop!=NULL) {
        if(addTopping==false){
            newTop->removeFromParentAndCleanup(true);
        }
        newTop=NULL;
    }
    
    showTop=false;
}
void AddTopping::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
}

CCRect AddTopping::createRectByPoint(CCPoint point, float width, float height){
    return CCRectMake(point.x-width/2,point.y-height/2,width,height);       //CCRectMake(x,y,width,height)；x,矩形左下角x坐标；y，矩形左下角y坐标；width，矩形宽度；height，矩形高度
}


void AddTopping::registerWithTouchDispatcher(){
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, false);
}
