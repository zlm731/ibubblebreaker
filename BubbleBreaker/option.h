//
//  option.h
//  BubbleBreaker
//
//  Created by zlmcd on 13-9-5.
//
//

#ifndef __BubbleBreaker__option__
#define __BubbleBreaker__option__

#include <iostream>
#include "cocos2d.h"
using namespace cocos2d;
class option : public CCLayerColor
{
public:
    CREATE_FUNC(option);
    virtual bool init();
    virtual bool ccTouchBegan(CCTouch *touch, CCEvent * pEvent);
    virtual void ccTouchEnded(CCTouch *touch, CCEvent * pEvent);
    
bool bLeft;
bool bsfxOn;

};
#endif /* defined(__BubbleBreaker__option__) */
