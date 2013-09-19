//
//  title.cpp
//  BubbleBreaker
//
//  Created by zlmcd on 13-9-14.
//
//

#include "title.h"

bool title::init()
{
    if (!CCLayerColor::init())
        return false;
    
    CCSprite *pTitle = CCSprite::create("title.png");
    addChild(pTitle);
    pTitle->setAnchorPoint(ccp(0.5,0.5));
    pTitle->setPosition(ccp(0,0));
    
    CCSize titlesize = pTitle->getContentSize();
    setContentSize(titlesize);
    
    
    return true;
}