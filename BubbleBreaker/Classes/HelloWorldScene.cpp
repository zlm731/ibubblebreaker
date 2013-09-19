#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "pad.h"
#include "layout.h"
#include "mainmenu.h"
#include "toolbargame.h"
#include "tops.h"
#include "option.h"
#include "about.h"
#include "locate.h"
#include "title.h"
#include "misc.h"

using namespace cocos2d;
using namespace CocosDenshion;









CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);
    layer->setTag(TAG_ROOT);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayerColor::init() )
    {
        return false;
    }
    
    LOCATE::init();
    
    m_scene = SCENE_OPEN;
    
    // set myself with color
    CCSize WinSize = CCDirector::sharedDirector()->getWinSize();
    initWithColor(ccc4(255, 255, 255, 255), WinSize.width, WinSize.height);
    setPosition(ccp(0,0));
    
    //++++++++++++++++   create title sprite
    title *pTitle = title::create();
    //CCSprite *pTitle = CCSprite::create("title.png");
    //CCSize titlesize = pTitle->getContentSize();
    pTitle->setAnchorPoint(ccp(0.5,0.5));
    pTitle->setTag(TAG_TITLE);
    addChild(pTitle);
    pTitle->setPosition(titlepos(POS_OUT));
    
    //+++++++++++++++++   create mainmenu
    
    MainMenu *pMainmenu = MainMenu::create();
    pMainmenu->setAnchorPoint(ccp(0.5,0.5));
    pMainmenu->setTag(TAG_MAINMENU);
    addChild(pMainmenu);
    pMainmenu->setPosition(mainmenupos(POS_OUT));
    
    //++++++++++++++++++   create gamelayer
    
    GAMELAYER *pgame = GAMELAYER::create();
    pgame->setAnchorPoint(ccp(0,0));
    pgame->setTag(TAG_GAMELAYER);
    addChild(pgame);
    pgame->setPosition(gamelayerpos(POS_OUT));
    

    
    //+++++++++++++++++++   create toolbar

    ccColor4B c4b = getrandomcolor();
    toolbar *pToolbar = toolbar::create();
    CCAssert(pToolbar, "toolbar new fail");
    pToolbar->setColor(ccc3(c4b.r, c4b.g, c4b.b));
    pToolbar->setOpacity(128);
    pToolbar->setContentSize(CCSize(WinSize.width, LO_TOOLBAR_H));

    //pToolbar->setAnchorPoint(ccp(0,));
    pToolbar->setTag(TAG_TOOLBAR);
    addChild(pToolbar);
    pToolbar->setPosition(toolbarpos(POS_OUT));
    pToolbar->setAnchorPoint(ccp(0,0));
    


    
    // +++++++++++++++++   create tops
    
    tops *pTops = tops::create();
    addChild(pTops);
    pTops->setTag(TAG_TOPS);
    pTops->setPosition(topspos(POS_OUT));
    
    // ++++++++++++++++   create option
    option *pOption = option::create();
    addChild(pOption);
    pOption->setTag(TAG_OPTION);
    pOption->setPosition(optionpos(POS_OUT));
    
    // +++++++++++++++++  create about
    about *pAbout = about::create();
    addChild(pAbout);
    pAbout->setTag(TAG_ABOUT);
    pAbout->setPosition(aboutpos(POS_OUT));
    
    
    return true;
}

void HelloWorld::onEnter()
{
    CCLayerColor::onEnter();
    EnterOpen();
}

void HelloWorld::onExit()
{
    CCLayerColor::onExit();
}


void HelloWorld::newround()
{

    
    // set pad new round
    GAMELAYER *pgame = (GAMELAYER *)getChildByTag(TAG_GAMELAYER);
    CCAssert(pgame != NULL, "");
    pgame->newround();
}

void HelloWorld::EnterOpen()
{
    float fduration = 0.5;
    // title in
    CCNode *pTitle = (CCNode *)getChildByTag(TAG_TITLE);
    CCActionInterval*  actiontitle = CCMoveTo::create(fduration, titlepos(POS_IN));
    pTitle->runAction(actiontitle);
    
    // mainmenu in
    CCNode *pMainmenu = (CCNode *)getChildByTag(TAG_MAINMENU);
    CCActionInterval*  actionmainmenu = CCMoveTo::create(fduration, mainmenupos(POS_IN));
    pMainmenu->runAction(actionmainmenu);
    
    // game out
    CCNode *pgame = (CCNode *)getChildByTag(TAG_GAMELAYER);
    CCActionInterval*  actiongamelayer = CCMoveTo::create(fduration, gamelayerpos(POS_OUT));
    pgame->runAction(actiongamelayer);
    
    // toolbar out
    CCNode *pToolbar = (CCNode *)getChildByTag(TAG_TOOLBAR);
    CCActionInterval*  actiontoolbar = CCMoveTo::create(fduration, toolbarpos(POS_OUT));
    pToolbar->runAction(actiontoolbar);
    
    // tops out
    CCNode *ptops = (CCNode *)getChildByTag(TAG_TOPS);
    CCActionInterval*  actiontops = CCMoveTo::create(fduration, topspos(POS_OUT));
    ptops->runAction(actiontops);
    // option out
    CCNode *poption = (CCNode *)getChildByTag(TAG_OPTION);
    CCActionInterval*  actionoption = CCMoveTo::create(fduration, optionpos(POS_OUT));
    poption->runAction(actionoption);
}

void HelloWorld::EnterGame()
{
    float fduration = 0.2;
    // title out
    CCNode *pTitle = (CCNode *)getChildByTag(TAG_TITLE);
    CCActionInterval*  actiontitle = CCMoveTo::create(fduration, titlepos(POS_OUT));
    pTitle->runAction(actiontitle);
    // mainmenu out
    CCNode *pMainmenu = (CCNode *)getChildByTag(TAG_MAINMENU);
    CCActionInterval*  actionmainmenu = CCMoveTo::create(fduration, mainmenupos(POS_OUT));
    pMainmenu->runAction(actionmainmenu);
    // game in
    CCNode *pgame = (CCNode *)getChildByTag(TAG_GAMELAYER);
    CCActionInterval*  actiongamelayer = CCMoveTo::create(fduration, gamelayerpos(POS_IN));
    pgame->runAction(actiongamelayer);
    // toolbar in
    toolbar *pToolbar = (toolbar *)getChildByTag(TAG_TOOLBAR);
    CCActionInterval*  actiontoolbar = CCMoveTo::create(fduration, toolbarpos(POS_IN));
    pToolbar->runAction(actiontoolbar);
    pToolbar->setTitle("GAME");
    
    // tops out
    CCNode *ptops = (CCNode *)getChildByTag(TAG_TOPS);
    CCActionInterval*  actiontops = CCMoveTo::create(fduration, topspos(POS_OUT));
    ptops->runAction(actiontops);
    // option out
    CCNode *poption = (CCNode *)getChildByTag(TAG_OPTION);
    CCActionInterval*  actionoption = CCMoveTo::create(fduration, optionpos(POS_OUT));
    poption->runAction(actionoption);
    
    newround();
    
}

void HelloWorld::EnterTops()
{
    float fduration = 0.5;
    // title out
    CCNode *pTitle = (CCNode *)getChildByTag(TAG_TITLE);
    CCActionInterval*  actiontitle = CCMoveTo::create(fduration, titlepos(POS_OUT));
    pTitle->runAction(actiontitle);
    // mainmenu out
    CCNode *pMainmenu = (CCNode *)getChildByTag(TAG_MAINMENU);
    CCActionInterval*  actionmainmenu = CCMoveTo::create(fduration, mainmenupos(POS_OUT));
    pMainmenu->runAction(actionmainmenu);
    // game out
    CCNode *pgame = (CCNode *)getChildByTag(TAG_GAMELAYER);
    CCActionInterval*  actiongame = CCMoveTo::create(fduration, gamelayerpos(POS_OUT));
    pgame->runAction(actiongame);
    // toolbar in
    toolbar *pToolbar = (toolbar *)getChildByTag(TAG_TOOLBAR);
    CCActionInterval*  actiontoolbar = CCMoveTo::create(fduration, toolbarpos(POS_IN));
    pToolbar->runAction(actiontoolbar);
    pToolbar->setTitle(LOCATE::GetString(STR_MENU_TOP));
    
    // tops in
    CCNode *ptops = (CCNode *)getChildByTag(TAG_TOPS);
    CCActionInterval*  actiontops = CCMoveTo::create(fduration, topspos(POS_IN));
    ptops->runAction(actiontops);
    // option out
    CCNode *poption = (CCNode *)getChildByTag(TAG_OPTION);
    CCActionInterval*  actionoption = CCMoveTo::create(fduration, optionpos(POS_OUT));
    poption->runAction(actionoption);
}

void HelloWorld::EnterOption()
{
    float fduration = 0.5;
    // title out
    CCNode *pTitle = (CCNode *)getChildByTag(TAG_TITLE);
    CCActionInterval*  actiontitle = CCMoveTo::create(fduration, titlepos(POS_OUT));
    pTitle->runAction(actiontitle);
    // mainmenu out
    CCNode *pMainmenu = (CCNode *)getChildByTag(TAG_MAINMENU);
    CCActionInterval*  actionmainmenu = CCMoveTo::create(fduration, mainmenupos(POS_OUT));
    pMainmenu->runAction(actionmainmenu);
    // game out
    CCNode *pgame = (CCNode *)getChildByTag(TAG_GAMELAYER);
    CCActionInterval*  actiongame = CCMoveTo::create(fduration, gamelayerpos(POS_OUT));
    pgame->runAction(actiongame);
    // toolbar in
    toolbar *pToolbar = (toolbar *)getChildByTag(TAG_TOOLBAR);
    CCActionInterval*  actiontoolbar = CCMoveTo::create(fduration, toolbarpos(POS_IN));
    pToolbar->runAction(actiontoolbar);
    pToolbar->setTitle(LOCATE::GetString(STR_MENU_OPTION));

    // tops out
    CCNode *ptops = (CCNode *)getChildByTag(TAG_TOPS);
    CCActionInterval*  actiontops = CCMoveTo::create(fduration, topspos(POS_OUT));
    ptops->runAction(actiontops);
    // option out
    CCNode *poption = (CCNode *)getChildByTag(TAG_OPTION);
    CCActionInterval*  actionoption = CCMoveTo::create(fduration, optionpos(POS_IN));
    poption->runAction(actionoption);
}

void HelloWorld::ShowAbout(bool bEnable)
{
    float fduration = 0.1;
    CCNode *pNode = (CCNode *)getChildByTag(TAG_ABOUT);
    CCActionInterval*  action = NULL;
    if (bEnable)
    {
        action = CCMoveTo::create(fduration, aboutpos(POS_IN));
    }
    else
    {
        action = CCMoveTo::create(fduration, aboutpos(POS_OUT));
    }
    pNode->runAction(action);
}

CCPoint HelloWorld::titlepos(int pos)
{
    CCSize WinSize = CCDirector::sharedDirector()->getWinSize();
    CCNode *pNode = (CCNode *)getChildByTag(TAG_TITLE);
    CCSize nodesize = pNode->getContentSize();
    
    if (pos == POS_IN)
    {
        return ccp(WinSize.width/2, WinSize.height/2+nodesize.height);
    
    }
    else
    {
        return ccp(-nodesize.width/2, WinSize.height/2+nodesize.height);
    
    }
}

CCPoint HelloWorld::mainmenupos(int pos)
{
    CCSize WinSize = CCDirector::sharedDirector()->getWinSize();
    CCNode *pNode = (CCNode *)getChildByTag(TAG_MAINMENU);
    CCSize nodesize = pNode->getContentSize();
    if (pos == POS_IN)
    {
        return ccp(WinSize.width/2, WinSize.height/2-100);
    }
    else
    {
        return ccp(WinSize.width+nodesize.width/2, WinSize.height/2-100);
    }
}

CCPoint HelloWorld::toolbarpos(int pos)
{
    CCSize WinSize = CCDirector::sharedDirector()->getWinSize();
    CCNode *pNode = (CCNode *)getChildByTag(TAG_TOOLBAR);
    CCSize nodesize = pNode->getContentSize();
    if (pos == POS_IN)
    {
        return ccp(0, WinSize.height-nodesize.height);
        
    }
    else
    {
        return ccp(0, WinSize.height);
    }
}

CCPoint HelloWorld::gamelayerpos(int pos)
{
    CCSize WinSize = CCDirector::sharedDirector()->getWinSize();
    if (pos == POS_IN)
    {
        return ccp(0,0);
        
    }
    else
    {
        return ccp(WinSize.width, 0);
    }
}

CCPoint HelloWorld::topspos(int pos)
{
    CCSize WinSize = CCDirector::sharedDirector()->getWinSize();
    CCNode *pNode = (CCNode *)getChildByTag(TAG_TOPS);
    CCSize nodesize = pNode->getContentSize();
    if (pos == POS_IN)
    {
        return ccp((WinSize.width-nodesize.width)/2,
                   (WinSize.height-nodesize.height)/2);
        
    }
    else
    {
        return ccp(WinSize.width, (WinSize.height-nodesize.height)/2);
    }
}

CCPoint HelloWorld::optionpos(int pos)
{
    CCSize WinSize = CCDirector::sharedDirector()->getWinSize();
    CCNode *pNode = (CCNode *)getChildByTag(TAG_OPTION);
    CCSize nodesize = pNode->getContentSize();
    if (pos == POS_IN)
    {
        return ccp((WinSize.width-nodesize.width)/2,
                   (WinSize.height-nodesize.height)/2);
        
    }
    else
    {
        return ccp(WinSize.width, (WinSize.height-nodesize.height)/2);
    }
}

CCPoint HelloWorld::aboutpos(int pos)
{
    CCSize WinSize = CCDirector::sharedDirector()->getWinSize();
    CCNode *pNode = (CCNode *)getChildByTag(TAG_ABOUT);
    CCSize nodesize = pNode->getContentSize();
    if (pos == POS_IN)
    {
        return ccp((WinSize.width-nodesize.width)/2,
                   (WinSize.height-nodesize.height)/2);
        
    }
    else
    {
        return ccp(WinSize.width, (WinSize.height-nodesize.height)/2);
    }
}


