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
    
    CCSize winsize = GameManager::sharedManager()->getViewVisibleSize();
    xDispostion=-950;
    halloXDis = -590;
    for (int i = 0; i < 10; ++i) {
        topping[i] = 99;
    }
    for (int i = 0; i < 100; ++i) {
        addTop[i] = 55;
    }

    for (int i = 0; i < 100; ++i) {
        for (int j = 0; j < 100; ++j) {
            addToppingPos[i][j] = 0;
        }
    }
}

void PizzaManager::selectPizzaTopping(int topIndex){
//    int i=0;
    topping[selectedNum] = topIndex;
}


void PizzaManager::addPizzaTopping(int index){
    addTop[selectedTop] = index ;
}


void PizzaManager::addTopPos(int index,int indexs){
    addToppingPos[selectedTopPos][0] = index;
    addToppingPos[selectedTopPos][1] = indexs;
}


void PizzaManager::cleanAllSprite(){
    selectedNum=0;
    selectedTop=0;
    selectedTopPos=0;
//    selectNum = 0;
    for (int i=0; i<10; i++) {
        topping[i]=99;
    }
    
    for (int i=0; i<100; i++) {
        addTop[i]=55;
    }
    
    for (int i=0; i<100; i++) {
        addToppingPos[i][0]=0;
        addToppingPos[i][1]=0;
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
