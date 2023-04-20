//
//  PizzaManager.cpp
//  Pizza
//
//  Created by LiXiaofei on 4/5/21.
//

#include "PizzaManager.h"
#include "GameManager.h"
static PizzaManager* pizzamanager = NULL;

PizzaManager* PizzaManager::sharedManager(){
    if (!pizzamanager) {
        pizzamanager = new PizzaManager();
    }
    
    return pizzamanager;
}


void PizzaManager::initPizzaManager(){
    whichPizza = 0;
    whichShape = 0;
//    selectedTopPos = 0;
//    selectedTop=0;
//    selectedNum=0;
    this->cleanAllSprite();
    
    CCSize winsize = GameManager::sharedManager()->getViewVisibleSize();
    xDispostion=-950;
    halloXDis = -590;
//    for (int i=0; i<100; i++) {
//        addToppingPos[i][0]=0;
//        addToppingPos[i][1]=0;
//    }
    addToppingPosX = CCArray::create();
    CC_SAFE_RETAIN(addToppingPosX);
    addToppingPosY = CCArray::create();
    CC_SAFE_RETAIN(addToppingPosY);
    addTop = CCArray::create();
    CC_SAFE_RETAIN(addTop);
}

void PizzaManager::selectPizzaTopping(int topIndex){
//    int i=0;
    topping[selectedNum] = topIndex;
}


void PizzaManager::addPizzaTopping(int index){
//    addTop[selectedTop] = index ;
    addTop->addObject(CCInteger::create(index));
}


void PizzaManager::addTopPos(float index,float indexs){
//    addToppingPos[selectedTopPos][0] = index;
//    addToppingPos[selectedTopPos][1] = indexs;
    addToppingPosX->addObject(CCFloat::create(index));
    addToppingPosY->addObject(CCFloat::create(indexs));
}


void PizzaManager::cleanAllSprite(){
    selectedNum=0;
    selectedTop=0;
    selectedTopPos=0;
//    selectNum = 0;
    for (int i=0; i<10; i++) {
        topping[i]=99;
    }
    if (addTop!=NULL) {
        addTop->removeAllObjects();
    }
    if (addToppingPosX!=NULL) {
        addToppingPosX->removeAllObjects();
    }
    if (addToppingPosY!=NULL) {
        addToppingPosY->removeAllObjects();
    }
    
    
    tomatoSelected = false;
    xilanhuaSelected =false;
    ganlanyeSelected =false;
    pepperSelected = false;
    boluoSelected = false;
    moguSelected = false;
    changSelected = false;
    meatSelected = false;
    baconsSelected = false;
    bocaiSelected = false;
}


void PizzaManager::cleanTopping(){
    selectedTopPos=0;
    selectedTop=0;
    if (addTop!=NULL) {
        addTop->removeAllObjects();
    }
    if (addToppingPosX!=NULL) {
        addToppingPosX->removeAllObjects();
    }
    if (addToppingPosY!=NULL) {
        addToppingPosY->removeAllObjects();
    }
}
