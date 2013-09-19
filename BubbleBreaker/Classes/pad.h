//
//  pad.h
//  BubbleBreaker
//
//  Created by zlmcd on 13-8-25.
//
//

#ifndef __BubbleBreaker__pad__
#define __BubbleBreaker__pad__

#include <iostream>
#include "cocos2d.h"
#include "layout.h"
#include <vector>
using namespace cocos2d;
using namespace std;

class ball : public CCSprite
{
public:
    ball()
    {
        m_enable = true;
        m_type = 0;
    };
    CREATE_FUNC(ball);
    
    void setenable(bool flag);
    bool getenable();
    void settype(int type){m_type = type;};
    int gettype(){return m_type;};
    
private:
    bool m_enable;
    int m_type;

};

class GAMELAYER;
class PAD : public cocos2d::CCLayerColor, public CCTargetedTouchDelegate
{
public:
    CREATE_FUNC(PAD);
    PAD();
    ~PAD();
    
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    
    // default implements are used to call script callback if exist
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

    
public:
    void cleanall();
    void newround();
    
    void onPress(CCPoint p);
    bool isPressOnSelect(CCPoint p);
    
    bool preSelect(CCPoint p);
    void cancelSelect();
    void Select();
    
    void setSelectFlag(bool flag);
    bool getSelectFlag();
    
    void falldown();
    
    bool checkisover();
    
    void Collect(int x, int y, vector<ball *> &vlist);
    void dbgout(vector<ball *> &vlist);
    
    void setballtype(CCPoint p, int type);
    
    bool isLeftHand(){return m_bLeftHand;};
    void setLeftHand(bool flag){m_bLeftHand = flag;};
    
    void calcscore(CCPoint xy);
    
    void getcolors(vector<ccColor4B> &vcolors);
    void onGameOver();
    
    
public:
    ball *getball(int x, int y);
    CCPoint xy2point(CCPoint xy);
    CCPoint point2xy(CCPoint point);
    int xy2idx(CCPoint xy);
    CCPoint idx2xy(int idx);
    CCRect type2texturerect(int type);
    
private:
    int m_x;
    int m_y;
    float m_ballw;
    float m_ballh;
    int m_balltypes;
    bool m_bSelectFlag;
    
    bool m_bLeftHand;

    vector<ball *> m_vSelectedBalls;
    
public:
    GAMELAYER *m_pGameLayer;
};


class WINBAR : public CCLayerColor
{
public:
    CREATE_FUNC(WINBAR);
    virtual bool init();
};



class GAMELAYER : public cocos2d::CCLayerColor
{
public:
    CREATE_FUNC(GAMELAYER);
    GAMELAYER();
    ~GAMELAYER();
    
    virtual bool init();
public:
    void newround();
    void addscore(int);
    void onGameOver();
    void sethighest(int,bool);
    void showWinbar(bool );
    
    
public:
    PAD *m_pad;
    CCLabelTTF *m_labelscore;
    CCLabelTTF *m_lableHighest;
    int m_score;
    int m_highest;
};


#endif /* defined(__BubbleBreaker__pad__) */
