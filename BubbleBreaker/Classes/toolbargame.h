//
//  toolbargame.h
//  BubbleBreaker
//
//  Created by zlmcd on 13-9-3.
//
//

#ifndef __BubbleBreaker__toolbargame__
#define __BubbleBreaker__toolbargame__

#include <iostream>
#include "cocos2d.h"
using namespace cocos2d;

class toolbar : public CCLayerColor
{
public:
    CREATE_FUNC(toolbar);
    virtual bool init();
    virtual bool ccTouchBegan(CCTouch *touch, CCEvent * pEvent);
    virtual void ccTouchEnded(CCTouch *touch, CCEvent * pEvent);


public:
    void setTitle(const char *);

};


#endif /* defined(__BubbleBreaker__toolbargame__) */
