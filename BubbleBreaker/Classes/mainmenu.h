//
//  mainmenu.h
//  BubbleBreaker
//
//  Created by zlmcd on 13-9-2.
//
//

#ifndef __BubbleBreaker__mainmenu__
#define __BubbleBreaker__mainmenu__
#include "cocos2d.h"
using namespace cocos2d;


class MainMenu : public CCLayer
{
public:
    CREATE_FUNC(MainMenu);
public:
    virtual bool init();
    virtual bool ccTouchBegan(CCTouch *touch, CCEvent * pEvent);
    virtual void ccTouchEnded(CCTouch *touch, CCEvent * pEvent);

    
    void menuCallback(CCObject* pSender);
    
    //CREATE_NODE(MenuLayer1);
};

#endif /* defined(__BubbleBreaker__mainmenu__) */
