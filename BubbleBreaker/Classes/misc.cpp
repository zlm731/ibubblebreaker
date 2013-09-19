//
//  misc.cpp
//  BubbleBreaker
//
//  Created by zlmcd on 13-9-17.
//
//

#include "misc.h"
#include "cocos2d.h"
#include "layout.h"
using namespace cocos2d;


int randomBetweenInt(int max, int min)
{
    static int seek = 0;
    if (seek == 0)
    {
        time_t t;
        seek = (unsigned int)time(&t);
    }
    std::srand(seek);//随机数种子
    seek = std::rand();
    return seek % (max - min) + min;
}

ccColor4B colors[] = {
    {235,42,115,128},
    {61,129,252,128},
    {179,249,130,128},
    {128,29,128,128},
    {242,126,34,128},
};

ccColor4B getrandomcolor()
{
    int idx = randomBetweenInt(BALL_TYPES, 0);
    return colors[idx];
}