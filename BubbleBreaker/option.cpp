//
//  option.cpp
//  BubbleBreaker
//
//  Created by zlmcd on 13-9-5.
//
//

#include "option.h"
#include "cocos2d.h"
#include "layout.h"
#include "HelloWorldScene.h"
using namespace cocos2d;


bool option::init()
{
    if (!CCLayerColor::init())
        return false;
    
    bLeft= false;
    bsfxOn = true;
    
    setTouchEnabled(true);
    setTouchPriority(kCCMenuHandlerPriority + 1);
    setTouchMode(kCCTouchesOneByOne);
    
    //setColor(ccc3(128, 0, 0));
    //setOpacity(128);
    
    
    CCSize WinSize = CCDirector::sharedDirector()->getWinSize();
    
    setContentSize(WinSize);
    CCSize mysize = getContentSize();
    
    // first line
    CCPoint firstpoint(mysize.width/2, 800);
    const int space_long = 10;
    const int FONT_SIZE = 40;
    // create left right hands
    CCLabelTTF *pHandsA = CCLabelTTF::create("hand", FONT_TYPE_DEFAULT, FONT_SIZE);
    addChild(pHandsA);
    pHandsA->setColor(ccc3(0, 0, 0));
    pHandsA->setAnchorPoint(ccp(1,0));
    CCPoint handapos = firstpoint;
    handapos.x -= space_long;
    pHandsA->setPosition(handapos);
    
    char *pleft = NULL;
    if (bLeft){
        pleft = "<left>";
    }
    else{
        pleft = "<right>";
    }
    CCLabelTTF *pHandsB = CCLabelTTF::create(pleft, FONT_TYPE_DEFAULT, FONT_SIZE);
    addChild(pHandsB);
    pHandsB->setColor(ccc3(0, 0, 0));
    pHandsB->setAnchorPoint(ccp(0,0));
    CCPoint handbpos = firstpoint;
    handbpos.x += space_long;
    pHandsB->setPosition(handbpos);
    
    // second line
    CCPoint secondpoint = firstpoint;
    secondpoint.y -= 2*pHandsA->getContentSize().height;
    // create sfx on/off
    CCLabelTTF *psfxA = CCLabelTTF::create("sfx", FONT_TYPE_DEFAULT, FONT_SIZE);
    addChild(psfxA);
    psfxA->setColor(ccc3(0, 0, 0));
    psfxA->setAnchorPoint(ccp(1,0));
    CCPoint sfxapos = secondpoint;
    sfxapos.x -= space_long;
    psfxA->setPosition(sfxapos);
    
    char *psfxon = NULL;
    if (bsfxOn){
        psfxon = "<on>";
    }
    else{
        psfxon = "<off>";
    }
    CCLabelTTF *psfxB = CCLabelTTF::create(psfxon, FONT_TYPE_DEFAULT, FONT_SIZE);
    addChild(psfxB);
    psfxB->setColor(ccc3(0, 0, 0));
    psfxB->setAnchorPoint(ccp(0,0));
    CCPoint sfxbpos = secondpoint;
    sfxbpos.x += space_long;
    psfxB->setPosition(sfxbpos);
    
    return true;
}

bool option::ccTouchBegan(CCTouch *touch, CCEvent *pEvent)
{
    CCSize s = getContentSize();
    CCRect rect = CCRectMake(0, 0, s.width, s.height);
    if (rect.containsPoint(convertTouchToNodeSpaceAR(touch)))
    {
        return true;
    }
    return false;
}

void option::ccTouchEnded(CCTouch *touch, CCEvent *pEvent)
{
    CCSize s = getContentSize();
    CCRect rect = CCRectMake(0, 0, s.width, s.height);
    if (rect.containsPoint(convertTouchToNodeSpaceAR(touch)))
    {
        HelloWorld *pHello = (HelloWorld *)getParent();
        pHello->ShowAbout(false);
    }
}