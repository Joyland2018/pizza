//
//  PizzaManager.hpp
//  Pizza
//
//  Created by LiXiaofei on 4/5/21.
//

#ifndef PizzaManager_h
#define PizzaManager_h

#include <stdio.h>
#include "cocos2d.h"

using namespace cocos2d;

class PizzaManager{
public:
    static PizzaManager* sharedManager();
    
    //初始化数据
    void initPizzaManager();
    
    //获取已选择的pizza
    void selectPizzaTopping(int topIndex);
    
    void addPizzaTopping(int index);
    
    void addTopPos(int index,int indexs);
    //选择的配菜
    int topping[10];
    int addTop[100];
    int addToppingPos[100][100];
    //pizza口味
    int whichPizza=0;
    
    //面饼形状
    int whichShape=0;;
    int xDispostion=0;
    int halloXDis = 0;
    int topXDis = 0;
    int selectedNum=0;
    
    bool tomatoSelected=false;
    bool xilanhuaSelected= false;
    bool ganlanyeSelected = false;
    bool pepperSelected = false;
    bool boluoSelected = false;
    bool moguSelected = false;
    bool changSelected = false;
    bool meatSelected = false;
    bool baconsSelected =  false;
    bool bocaiSelected = false;
    
//    bool haveMovedScroll =false;
    int selectedTop=0;
    int selectedTopPos=0;
//    int selectNum=0;
    
    bool havePlay = false;
    bool noughComplate=false;
    
    void cleanAllSprite();
    
};

#endif /* PizzaManager_hpp */
