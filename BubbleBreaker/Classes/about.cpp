//
//  about.cpp
//  BubbleBreaker
//
//  Created by zlmcd on 13-9-5.
//
//

#include "about.h"
#include "cocos2d.h"
#include "layout.h"
#include "HelloWorldScene.h"
using namespace cocos2d;


bool about::init()
{
    if (!CCLayerColor::init())
        return false;
    
    setTouchEnabled(true);
    setTouchPriority(kCCMenuHandlerPriority + 1);
    setTouchMode(kCCTouchesOneByOne);
    
    setContentSize(CCSize(300, 300));
    CCSize mysize = getContentSize();
    
    //create <-
    CCSprite *pMyPhoto = CCSprite::create("zlm.jpg");
    CCAssert(pMyPhoto != NULL, "");
    addChild(pMyPhoto);
    pMyPhoto->setAnchorPoint(ccp(0.5,0.5));

    pMyPhoto->setPosition(ccp(mysize.width/2, mysize.height/2));
    
    return true;
}

bool about::ccTouchBegan(CCTouch *touch, CCEvent *pEvent)
{
    CCSize s = getContentSize();
    CCRect rect = CCRectMake(0, 0, s.width, s.height);
    if (rect.containsPoint(convertTouchToNodeSpaceAR(touch)))
    {
        return true;
    }
    return false;
}

void about::ccTouchEnded(CCTouch *touch, CCEvent *pEvent)
{
    CCSize s = getContentSize();
    CCRect rect = CCRectMake(0, 0, s.width, s.height);
    if (rect.containsPoint(convertTouchToNodeSpaceAR(touch)))
    {
        HelloWorld *pHello = (HelloWorld *)getParent();
        pHello->ShowAbout(false);
    }
}