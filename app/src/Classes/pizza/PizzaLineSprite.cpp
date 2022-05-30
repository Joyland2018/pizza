//
//  PizzaLineSprite.cpp
//  Pizza
//
//  Created by LiXiaofei on 4/5/21.
//

#include "PizzaLineSprite.h"


void PizzaLineSprite::draw(){
   
    drawLine();
}

void PizzaLineSprite::drawLine(){
    int tickSubCount=10;
    int pointListKeepCount=500;
    for (int i =0; i<tickSubCount; i++) {
        if (pointList.size()>0) {
            pointList.pop_front();
        }else{
            break;
        }
    }
    while(pointList.size()>pointListKeepCount){                             //防止线段过长
        pointList.pop_front();
    }

    float max_lineWidth=4;
    float min_lineWidth=1;
    int alpha_min=10;
    int alpha_max=200;
   
//    int R = 255;
//    int G = 68;
//    int B = 68;
//    LemonLineSprite = LemonLineSprite::create();
//    double pointListCount = pointList.size();
    size_t pointListCount = pointList.size();
    std::list<CCPoint>::iterator it=pointList.begin();
    float pointIndex=0;
    for (; it!=pointList.end(); it++) {
       
//        int distanceToMiddle = fabs(pointIndex-pointListCount/2);
//
//        float percent =(float)distanceToMiddle/(float)(pointListCount/2.0);
//
//        float lintWidth = min_lineWidth + max_lineWidth*percent;
//
//        int alpha = alpha_min +alpha_max*percent;
        int distanceToMiddle =fabs(pointIndex-pointListCount/2);

                float percent = 1.0-(float)distanceToMiddle/(float)(pointListCount/2.0);

                float lintWidth = min_lineWidth + max_lineWidth*percent;

                int alpha = alpha_min +alpha_max*percent;
//        ccDrawColor4B(R, G, B, alpha);
        ccc4(R,G,B,alpha);
//        ccc3(R,G,B);
        ccPointSize(lintWidth*3);
//        glLineWidth(lintWidth*3);
        ccDrawPoint( *it );

        pointIndex++;
//        if (pointIndex==pointListCount/2) {
//            pointIndex=0;
//        }
    }
}
