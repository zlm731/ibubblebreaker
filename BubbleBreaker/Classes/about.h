//
//  about.h
//  BubbleBreaker
//
//  Created by zlmcd on 13-9-5.
//
//

#ifndef __BubbleBreaker__about__
#define __BubbleBreaker__about__

#include <iostream>
#include "cocos2d.h"
using namespace cocos2d;
class about : public CCLayerColor
{
public:
    CREATE_FUNC(about);
    virtual bool init();
    virtual bool ccTouchBegan(CCTouch *touch, CCEvent * pEvent);
    virtual void ccTouchEnded(CCTouch *touch, CCEvent * pEvent);
    
};
#endif /* defined(__BubbleBreaker__about__) */
