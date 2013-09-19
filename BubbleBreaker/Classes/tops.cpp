//
//  tops.cpp
//  BubbleBreaker
//
//  Created by zlmcd on 13-9-5.
//
//

#include "tops.h"
#include "layout.h"
#include "locate.h"
using namespace cocos2d;


bool tops::init()
{
    if (!CCLayerColor::init())
        return false;
    
    //bool bc = initWithColor(ccc4(0,255, 255, 255), 50, 50);
    setColor(ccc3(0, 255, 255));
    CCSize mysize = getContentSize();
    
    // create label
    ///CCLabelTTF::setColor(ccc3(0, 0, 0));
    CCLabelTTF *pLabel = CCLabelTTF::create("tops...", FONT_TYPE_DEFAULT, 32);
    pLabel->setColor(ccc3(0, 0, 0));
    CCAssert(pLabel != NULL, "");
    addChild(pLabel);

    pLabel->setPosition(ccp(mysize.width/2, mysize.height/2));
    //pLabel->setPosition(ccp(0, 0));
    
    // create records
    for (int i = 0; i < TOP_RANK_NUM; i++)
    {
        record *precord = record::create();
        precord->setTag(i+1);
        addChild(precord);
        precord->setPosition(ccp(0, mysize.height-LO_TOOLBAR_H-(i+1)*LO_TOP_RECORD_H));
        
        CCString rank;
        rank.initWithFormat("%d",i+1);
        int score = CCUserDefault::sharedUserDefault()->getIntegerForKey(rank.getCString());
        USERINFO info;
        info.pname = LOCATE::GetString(STR_MYNAME);
        info.score = score;
        precord->setinfo(info);
        
        m_vlocalscore.push_back(score);
    }
    
    return true;
}

void tops::insertscore(int score)
{
    if (score <= m_vlocalscore[m_vlocalscore.size()-1])
        return;
    
    vector<int>::iterator itr = m_vlocalscore.begin();
    for (; itr != m_vlocalscore.end(); itr++)
    {
        if (*itr < score)
        {
            m_vlocalscore.insert(itr, score);
            m_vlocalscore.pop_back();
            break;
        }
        else
        {

        }
    }

    
    for (int i = 0; i < m_vlocalscore.size(); i++)
    {
        record *precord = (record *)getChildByTag(i+1);
        USERINFO info;
        info.pname = LOCATE::GetString(STR_MYNAME);
        info.score = m_vlocalscore[i];
        precord->setinfo(info);
        CCString rank;
        rank.initWithFormat("%d", i+1);
        CCUserDefault::sharedUserDefault()->setIntegerForKey(rank.getCString(), info.score);
    }

}


#define TAG_TOP_RECORD_NAME 1
#define TAG_TOP_RECORD_SCORE 2

bool record::init()
{
    if (!CCLayerColor::init())
        return false;
    
    CCSize WinSize = CCDirector::sharedDirector()->getWinSize();
    
    bool bc = initWithColor(ccc4(0,255, 255, 255), WinSize.width, LO_TOP_RECORD_H);
    CCSize mysize = getContentSize();
    
    CCLabelTTF *pName = CCLabelTTF::create("", FONT_TYPE_DEFAULT, 32);
    pName->setColor(ccc3(0, 0, 0));
    CCAssert(pName != NULL, "");
    addChild(pName);
    pName->setTag(TAG_TOP_RECORD_NAME);
    pName->setPosition(ccp(0, mysize.height/2));

    CCLabelTTF *pScore = CCLabelTTF::create("", FONT_TYPE_DEFAULT, 32);
    pScore->setColor(ccc3(0, 0, 0));
    CCAssert(pScore != NULL, "");
    addChild(pScore);
    pScore->setTag(TAG_TOP_RECORD_SCORE);
    
    
    pScore->setPosition(ccp(0, mysize.height/2));
    
    return true;
}

void record::setinfo(USERINFO &userinfo)
{
    CCLabelTTF *pName = (CCLabelTTF *)getChildByTag(TAG_TOP_RECORD_NAME);
    CCLabelTTF *pScore = (CCLabelTTF *)getChildByTag(TAG_TOP_RECORD_SCORE);
    CCSize mysize = getContentSize();
    
    
    pName->setString(userinfo.pname);
    CCSize namesize = pName->getContentSize();
    
    pName->setPosition(ccp(namesize.width/2, mysize.height/2));
    
    
    CCString strscore;
    strscore.initWithFormat("%d", userinfo.score);
    pScore->setString(strscore.getCString());
    CCSize scoresize = pScore->getContentSize();

    
    pScore->setPosition(ccp(mysize.width-scoresize.width, mysize.height/2));
}

void loadtop(vector<USERINFO> userinfo)
{
    CCScene *pScene = CCDirector::sharedDirector()->getRunningScene();
    CCNode *pRoot = pScene->getChildByTag(TAG_ROOT);
    CCNode *pTop = pRoot->getChildByTag(TAG_TOPS);
    for (int i = 0; i < userinfo.size();i++)
    {
        record *pRecord = (record *)pTop->getChildByTag(i+1);
        pRecord->setinfo(userinfo[i]);
    }
}

void addlocaltop(int score)
{
    CCScene *pScene = CCDirector::sharedDirector()->getRunningScene();
    CCNode *pRoot = pScene->getChildByTag(TAG_ROOT);
    tops *pTop = (tops *)pRoot->getChildByTag(TAG_TOPS);
    pTop->insertscore(score);
}
