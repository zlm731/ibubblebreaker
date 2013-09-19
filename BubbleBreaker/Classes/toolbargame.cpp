//
//  toolbargame.cpp
//  BubbleBreaker
//
//  Created by zlmcd on 13-9-3.
//
//

#include "toolbargame.h"
#include "cocos2d.h"
#include "layout.h"
#include "HelloWorldScene.h"
using namespace cocos2d;


bool toolbar::init()
{
    if (!CCLayerColor::init())
        return false;
    
    setTouchEnabled(true);
    setTouchPriority(kCCMenuHandlerPriority + 1);
    setTouchMode(kCCTouchesOneByOne);
    

    
    CCSize WinSize = CCDirector::sharedDirector()->getWinSize();
    setContentSize(CCSize(WinSize.width, LO_TOOLBAR_H));
    CCSize mysize = getContentSize();
    
    //create <-
    CCSprite *pReturn = CCSprite::create("left.png");
    CCAssert(pReturn != NULL, "");
    addChild(pReturn);
    pReturn->setTag(TAG_TOOLBAR_RETURN);
    CCSize returnsize = pReturn->getContentSize();
    pReturn->setPosition(ccp(returnsize.width/2, mysize.height/2));
    
    // create label
    CCLabelTTF *pLabel = CCLabelTTF::create("", FONT_TYPE_DEFAULT, 32);
    CCAssert(pLabel != NULL, "");
    addChild(pLabel);
    pLabel->setTag(TAG_TOOLBAR_TITLE);
    pLabel->setPosition(ccp(mysize.width/2, mysize.height/2));
    
    return true;
}

bool toolbar::ccTouchBegan(CCTouch *touch, CCEvent *pEvent)
{
    CCNode *pReturn = getChildByTag(TAG_TOOLBAR_RETURN);
    CCAssert(pReturn != NULL, "");
    
    CCSize s = pReturn->getContentSize();
    CCPoint p = pReturn->getPosition();
    CCRect rect = CCRectMake(p.x-s.width/2, p.y-s.height/2, p.x+s.width/2, p.y+s.height/2);

    
    
    if (rect.containsPoint(convertTouchToNodeSpaceAR(touch)))
    {
        return true;
    }
    return false;
}

void toolbar::ccTouchEnded(CCTouch *touch, CCEvent *pEvent)
{
    CCNode *pReturn = getChildByTag(TAG_TOOLBAR_RETURN);
    CCAssert(pReturn != NULL, "");
    
    CCSize s = pReturn->getContentSize();
    CCPoint p = pReturn->getPosition();
    CCRect rect = CCRectMake(p.x-s.width/2, p.y-s.height/2, p.x+s.width/2, p.y+s.height/2);
    
    
    
    if (rect.containsPoint(convertTouchToNodeSpaceAR(touch)))
    {
        HelloWorld *pHello = (HelloWorld *)getParent();
        CCAssert(pHello != NULL, "");
        pHello->EnterOpen();
    }
}

void toolbar::setTitle(const char *p)
{
    CCLabelTTF *pTitle = (CCLabelTTF *)getChildByTag(TAG_TOOLBAR_TITLE);
    CCAssert(pTitle != NULL, "");
    pTitle->setString(p);
}
