//
//  pad.cpp
//  BubbleBreaker
//
//  Created by zlmcd on 13-8-25.
//
//

#include "pad.h"
#include "cocos2d.h"
#include "layout.h"
#include "HelloWorldScene.h"
#include "locate.h"
#include "GCHelper.h"
#include "tops.h"
#include "SimpleAudioEngine.h"
#include "misc.h"

using namespace cocos2d;
using namespace CocosDenshion;

#define PARENT_CLASS CCLayerColor



void ball::setenable(bool flag)
{
    m_enable = flag;
    setVisible(m_enable);
}

bool ball::getenable()
{
    return m_enable;
}


PAD::PAD()
{
    m_x = LO_PAD_BALL_X;
    m_y = LO_PAD_BALL_Y;
    m_ballw = LO_PAD_BALL_W;
    m_ballh = LO_PAD_BALL_H;
    m_balltypes = BALL_TYPES;
    m_bSelectFlag = false;
    m_bLeftHand = false;
    
    m_vSelectedBalls.clear();
    m_pGameLayer = NULL;
}

PAD::~PAD()
{
    m_pGameLayer = NULL;
}

bool PAD::init()
{
    bool bc = initWithColor(ccc4(255,255, 255, 255), m_x*m_ballw, m_y*m_ballh);
    //bool bc = initWithColor(ccc4(0, 0, 0, 128), 640, 640);
    CCSpriteBatchNode* batchNode = CCSpriteBatchNode::create("balls5.png", m_x*m_y);
    batchNode->setPosition(ccp(0,0));
    addChild(batchNode,1,TAG_BATCHNODE_ID);
    
    for (int y = 0; y < m_y; y++)
    {
        for (int x = 0; x< m_x; x++)
        {
            CCRect rect(0, 0, m_ballw, m_ballh);
            ball *pball = ball::create();
            pball->initWithTexture(batchNode->getTexture(), rect);
            CCPoint position = xy2point(ccp(x,y));
            pball->setPosition(position);
            pball->setAnchorPoint(ccp(0.5,0.5));
            batchNode->addChild(pball);
            pball->setTag(xy2idx(ccp(x,y)));
            pball->setBatchNode(batchNode);
        }
    }

    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(SND_CLICKBALL);
    
    return bc;
}

void PAD::onEnter()
{
    
    setTouchMode(kCCTouchesOneByOne);
    setTouchEnabled(true);
    CCLayerColor::onEnter();
}

void PAD::onExit()
{
    setTouchEnabled(false);
    CCLayerColor::onExit();
}

bool PAD::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    CCSize s = getContentSize();
    //CCPoint p = getPosition();
    CCRect rect = CCRectMake(0, 0, s.width, s.height);
    if (rect.containsPoint(convertTouchToNodeSpaceAR(pTouch)))
    {
        return true;
    }
    return false;
}

void PAD::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    CCSize s = getContentSize();
    CCRect rect = CCRectMake(0, 0, s.width, s.height);
    CCPoint ptouch = convertTouchToNodeSpaceAR(pTouch);
    if (rect.containsPoint(ptouch))
    {
        CCPoint pxy = point2xy(ptouch);
        CCLog("touch on %i-%i",(char)pxy.x,(char)pxy.y);
        
        onPress(pxy);
        
        return;
    }
}

void PAD::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
    cancelSelect();
    setSelectFlag(false);
}


void PAD::cleanall()
{
    for (int y = 0; y < m_y; y++)
    {
        for (int x = 0; x< m_x; x++)
        {
            ball *pball = getball(x, y);
            CCAssert(pball != NULL, "pball == NULL");
            pball->setenable(false);
        }
    }
}

void PAD::newround()
{
    //CCSpriteBatchNode* batchNode = (CCSpriteBatchNode *)getChildByTag(TAG_BATCHNODE_ID);
    // init all balls with a random type
    for (int y = 0; y < m_y; y++)
    {
        for (int x = 0; x< m_x; x++)
        {
            int type = randomBetweenInt(m_balltypes+1, 1);
            setballtype(ccp(x,y), type);
        }
    }

    // clear the selection flag and list
    cancelSelect();
    setTouchEnabled(true);
}

void PAD::onPress(CCPoint p)
{
    SimpleAudioEngine::sharedEngine()->playEffect(SND_CLICKBALL);
    // already selected
    if (getSelectFlag())
    {
        // press on the selections
        if (isPressOnSelect(p))
        {
            Select();
            calcscore(p);
            falldown();
            cancelSelect();
            if (checkisover())
            {
                onGameOver();
            }
        }
        else //press out of the selections
        {
            // cancel the old selections
            cancelSelect();
            // to check if select the other balls
            if (preSelect(p))
            {
                
            }
        }
    
    }
    else
    {
        // to check if selected something
        if (preSelect(p))
        {
            
        }
    }
}

bool PAD::isPressOnSelect(CCPoint p)
{
    //return false;//test
    
    CCAssert(getSelectFlag() == true, "select flag invalid");
    
    for (int i = 0; i < m_vSelectedBalls.size(); i++)
    {
        CCSprite *psp = m_vSelectedBalls[i];
        int selectidx = xy2idx(p);
        if (psp->getTag() == selectidx)
        {
            return true;
        }
    }
    return false;
}

bool PAD::preSelect(CCPoint p)
{
    CCAssert(m_vSelectedBalls.size() == 0, "m_vSelectedBalls.size() != 0");
    vector<ball *> vlist;
    Collect(p.x, p.y, vlist);
    dbgout(vlist);
    if (vlist.size() <2)
    {
        return false;
    }
    else
    {
        m_vSelectedBalls = vlist;
        setSelectFlag(true);
        return true;
    }
}

void PAD::cancelSelect()
{
    m_vSelectedBalls.clear();
    setSelectFlag(false);
}

void PAD::Select()
{
    CCAssert(getSelectFlag() == true, "select flag invalid");
    CCAssert(m_vSelectedBalls.size() != 0, "m_vSelectedBalls.size() == 0");

    
    for (int i = 0; i < m_vSelectedBalls.size(); i++)
    {
        ball *pball = m_vSelectedBalls[i];
        pball->setenable(false);
    }
}

void PAD::setSelectFlag(bool flag)
{
    m_bSelectFlag = flag;
}

bool PAD::getSelectFlag()
{
    return m_bSelectFlag;
}

void PAD::falldown()
{
    vector<vector<int> > vtypes;
    for (int x = 0; x< m_x; x++)
    {
        vector<int> vtmptypes;
        for (int y = m_y-1; y >= 0; y--)
        {
            ball *pball = getball(x, y);
            if (pball->getenable())
            {
                vtmptypes.push_back(pball->gettype());
                pball->setenable(false);
            }
        
        }
        if (vtmptypes.size()>0)
        {
            vtypes.push_back(vtmptypes);
        }
    }
    
    if (isLeftHand())
    {
        int x =0;
        vector<vector<int> >::iterator itr1 = vtypes.begin();
        for (;itr1 != vtypes.end(); itr1++,x++)
        {
            int y = m_y-1;
            vector<int>::iterator itr2 = itr1->begin();
            for (;itr2 != itr1->end(); itr2++,y--)
            {
                setballtype(ccp(x,y), *itr2);
            }
        }
    }
    else
    {
        int x = m_x - vtypes.size();
        vector<vector<int> >::iterator itr1 = vtypes.begin();
        for (;itr1 != vtypes.end(); itr1++,x++)
        {
            int y = m_y-1;
            vector<int>::iterator itr2 = itr1->begin();
            for (;itr2 != itr1->end(); itr2++,y--)
            {
                setballtype(ccp(x,y), *itr2);
            }
        }
    }

}

bool PAD::checkisover()
{
    for (int y = 0; y < m_y; y++)
    {
        for (int x = 0; x< m_x; x++)
        {
            ball *pball = getball(x, y);
            CCAssert(pball != NULL, "pball == NULL");
            if (pball->getenable())
            {
                vector<ball *> vlist;
                Collect(x, y, vlist);
                if (vlist.size() > 1)
                {
                    return false;
                }
            }
        }
    }
    return true;
}

void PAD::Collect(int x, int y, vector<ball *> &vlist)
{
    ball *pball = getball(x, y);
    CCAssert(pball != NULL, "");
    if (pball->getenable() == false)
        return;
    
    int type = pball->gettype();
    
    vlist.push_back(pball);
    // 递归找左边
    if (x>=1)
    {
        ball *pballleft = getball(x-1, y);
        if (pballleft != NULL && pballleft->gettype() == type)
        {
            if (vlist.end() == find(vlist.begin(), vlist.end(), pballleft))
            {
                Collect(x-1, y, vlist);
            }
        }
    }
    // 递归找右边
    if (x<m_x-1)
    {
        ball *pballleft = getball(x+1, y);
        if (pballleft != NULL && pballleft->gettype() == type)
        {
            if (vlist.end() == find(vlist.begin(), vlist.end(), pballleft))
            {
                Collect(x+1, y, vlist);
            }
        }
    }
    // 递归找shang边
    if (y>=1)
    {
        ball *pballleft = getball(x, y-1);
        if (pballleft != NULL && pballleft->gettype() == type)
        {
            if (vlist.end() == find(vlist.begin(), vlist.end(), pballleft))
            {
                Collect(x, y-1, vlist);
            }
        }
    }
    // 递归找xia边
    if (y<m_y-1)
    {
        ball *pballleft = getball(x, y+1);
        if (pballleft != NULL && pballleft->gettype() == type)
        {
            if (vlist.end() == find(vlist.begin(), vlist.end(), pballleft))
            {
                Collect(x, y+1, vlist);
            }
        }
    }
}
void PAD::dbgout(vector<ball *> &vlist)
{
    string output;
    CCString str;
    for (int i = 0; i < vlist.size(); i++)
    {
        ball *pball = vlist[i];
        CCPoint xy = idx2xy(pball->getTag());
        str.initWithFormat("[%i,%i] ",(char)xy.x, (char)xy.y);
        output += str.getCString();
    }
    //CCLog("list = %s", output.c_str());
}

void PAD::setballtype(CCPoint p, int type)
{
    ball *psp = getball((int)p.x, (int)p.y);
    psp->settype(type);
    CCRect rect = type2texturerect(type);
    psp->setTextureRect(rect);
    psp->setenable(true);
}

void PAD::calcscore(cocos2d::CCPoint xy)
{
    int num = m_vSelectedBalls.size();
    int score = num*(num+1)/2;
    
    m_pGameLayer->addscore(score);
}

void PAD::getcolors(vector<ccColor4B> &vcolors)
{
    CCSpriteBatchNode* batchNode = (CCSpriteBatchNode *)getChildByTag(TAG_BATCHNODE_ID);
    for (int i = 0; i< m_balltypes; i++)
    {
        /*
        CCRect rect = type2texturerect(i+1);
        CCTexture2D *pTexture = batchNode->getTexture();
        CCImage *pimg = CCImage::ini
        cctexture2dmutable;
         */
    }
}

void PAD::onGameOver()
{
    setTouchEnabled(false);
    m_pGameLayer->onGameOver();
}

ball *PAD::getball(int x, int y)
{
    CCSpriteBatchNode* batchNode = (CCSpriteBatchNode *)getChildByTag(TAG_BATCHNODE_ID);
    
    return (ball *)batchNode->getChildByTag(xy2idx(ccp(x,y)));
}

CCPoint PAD::xy2point(CCPoint xy)
{
    CCPoint p;
    p.x = xy.x*m_ballw+m_ballw/2;
    p.y = (m_ballh*m_y)-xy.y*m_ballh-m_ballh/2;
    return p;
}

CCPoint PAD::point2xy(CCPoint point)
{
    CCPoint p;
    p.x = (int)(point.x/m_ballw);
    p.y = (int)((m_ballh*m_y - point.y)/m_ballh);
    return p;
}

int PAD::xy2idx(CCPoint xy)
{
    return xy.y*m_x+xy.x+1;
}

CCPoint PAD::idx2xy(int idx)
{
    CCPoint xy;
    xy.x = (int)((idx%m_x)-1);        //eg idx=12,x=11,y=0   idx = 25,x=0,y=2
    xy.y = (int)(idx/m_x);
    return xy;
}

CCRect PAD::type2texturerect(int type)
{
    switch (type)
    {
        case 1:
            return CCRect(11, 0, LO_PAD_BALL_W, LO_PAD_BALL_H);
            break;
        case 2:
            return CCRect(77, 0, LO_PAD_BALL_W, LO_PAD_BALL_H);
            break;
        case 3:
            return CCRect(143, 0, LO_PAD_BALL_W, LO_PAD_BALL_H);
            break;
        case 4:
            return CCRect(209, 0, LO_PAD_BALL_W, LO_PAD_BALL_H);
            break;
        case 5:
            return CCRect(275, 0, LO_PAD_BALL_W, LO_PAD_BALL_H);
            break;
        default:
            break;
    }
    return CCRect(2, 2, LO_PAD_BALL_W, LO_PAD_BALL_H);
}


bool WINBAR::init()
{
    if (!CCLayerColor::init())
        return false;
    CCSize winsize = CCDirector::sharedDirector()->getWinSize();
    CCSize mysize;
    mysize.height = LO_GAMELAYER_WINBAR;
    mysize.width = winsize.width;
    setContentSize(mysize);
    
    ccColor4B c4b = getrandomcolor();
    setColor(ccc3(c4b.r, c4b.g, c4b.b));
    setOpacity(255);
    return  true;
}







GAMELAYER::GAMELAYER()
{
    m_pad = NULL;
    m_score = 0;
    m_labelscore = NULL;
    m_lableHighest = NULL;
    m_highest = 0;
}

GAMELAYER::~GAMELAYER()
{
    m_pad = NULL;
    m_labelscore = NULL;
    m_lableHighest = NULL;
}

bool GAMELAYER::init()
{
    if (!CCLayerColor::init())
        return false;
    CCSize mysize = getContentSize();
    
    
    // ++++++++++++++++++ create pad
    PAD *ppad = PAD::create();
    addChild(ppad);
    ppad->setTag(TAG_GAMELAYER_PAD);
    ppad->setAnchorPoint(ccp(0,0));
    
    m_pad = ppad;
    ppad->m_pGameLayer = this;
    
    CCSize padsize = ppad->getContentSize();
    CCPoint padpos = ccp((mysize.width-padsize.width)/2,
                         (mysize.height-padsize.height)/2);
    ppad->setPosition(padpos);
    
    //+++++++++++++++++++   create score lable
    
    CCLabelTTF *pScore = CCLabelTTF::create("score", FONT_TYPE_DEFAULT, 40);
    pScore->setColor(ccc3(0, 0, 0));
    pScore->setAnchorPoint(ccp(0.5,0.5));
    pScore->setTag(TAG_GAMELAYER_SCORE);
    addChild(pScore);
    
    m_labelscore = pScore;
    CCSize scoresize = pScore->getContentSize();
    CCPoint scorepos = ccp(mysize.width/2 - scoresize.width - 20,
                           padpos.y+padsize.height+scoresize.height);
    pScore->setPosition(scorepos);
    
    // create highest
    CCLabelTTF *pHighest = CCLabelTTF::create("highest", FONT_TYPE_DEFAULT, 40);
    pHighest->setColor(ccc3(0, 0, 0));
    pHighest->setAnchorPoint(ccp(0.5,0.5));
    pHighest->setTag(TAG_GAMELAYER_HIGHEST);
    addChild(pHighest);
    
    m_lableHighest = pHighest;
    CCSize highestsize = pHighest->getContentSize();
    CCPoint highestpos = ccp(mysize.width/2+ highestsize.width,
                           padpos.y+padsize.height+highestsize.height);
    pHighest->setPosition(highestpos);
    // load highest
    int i = CCUserDefault::sharedUserDefault()->getIntegerForKey(FU_HIESTSCORE);
    sethighest(i, false);
    
    // create winbar
    WINBAR *pWinbar =  WINBAR::create();
    addChild(pWinbar);
    pWinbar->setTag(TAG_GAMELAYER_WINBAR);
    CCSize winbarsize = pWinbar->getContentSize();
    pWinbar->setPosition(ccp(0, mysize.height/2));
    showWinbar(false);
    
    return true;
}

void GAMELAYER::newround()
{
    // set score to zero
    m_score = 0;
    CCString str;
    str.initWithFormat(LOCATE::GetString(STR_SCORE_FMT), m_score);
    m_labelscore->setString(str.getCString());
    
    m_pad->newround();
    showWinbar(false);
}

void GAMELAYER::addscore(int i)
{
    m_score += i;
    CCString str;
    str.initWithFormat(LOCATE::GetString(STR_SCORE_FMT), m_score);
    m_labelscore->setString(str.getCString());
}

void GAMELAYER::onGameOver()
{
    if (m_score > m_highest)
    {
        sethighest(m_score, true);
    }
    
    showWinbar(true);
    
    addlocaltop(m_score);
    
    [[GameKitHelper sharedGameKitHelper] submitScore:(int64_t)m_score category:kHighScoreLeaderboardCategory];
}

void GAMELAYER::sethighest(int i, bool bsave)
{
    m_highest = i;
    CCString str;
    str.initWithFormat(LOCATE::GetString(STR_HIGHEST_FMT), m_highest);
    m_lableHighest->setString(str.getCString());
    // save to file
    if (bsave)
    {
        CCUserDefault::sharedUserDefault()->setIntegerForKey(FU_HIESTSCORE, m_highest);
    }
}

void GAMELAYER::showWinbar(bool benable)
{
    WINBAR *pWinbar = (WINBAR *)getChildByTag(TAG_GAMELAYER_WINBAR);
    pWinbar->setVisible(benable);
}
