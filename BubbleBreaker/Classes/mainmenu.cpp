//
//  mainmenu.cpp
//  BubbleBreaker
//
//  Created by zlmcd on 13-9-2.
//
//

#include "mainmenu.h"
#include "layout.h"
#include "HelloWorldScene.h"
#include "locate.h"

typedef struct _menuitem
{
    int strid;
    int tag;
}MENUITEM;


MENUITEM g_menuarry[] =
{
    {STR_MENU_STANDARD, MENU_TAG_PLAY_STD},
    //{STR_MENU_INFINITE,MENU_TAG_PLAY_INFINIT},
    {STR_MENU_TOP,MENU_TAG_SCORE},
    //{STR_MENU_OPTION,MENU_TAG_OPTION},
    //{STR_MENU_ABOUT,MENU_TAG_ABOUT},
};


bool MainMenu::init()
{

    if (!CCLayer::init())
        return false;
    
    setTouchEnabled(true);
    setTouchPriority(kCCMenuHandlerPriority + 1);
    setTouchMode(kCCTouchesOneByOne);
    
    CCMenuItemFont::setFontName(FONT_TYPE_DEFAULT);
    CCArray menuitemarry;
    for (int i = 0; i < sizeof(g_menuarry)/sizeof(MENUITEM); i++)
    {
        CCMenuItemFont *item = CCMenuItemFont::create(LOCATE::GetString(g_menuarry[i].strid), this, menu_selector(MainMenu::menuCallback) );
        //item->setFontName(FONT_TYPE_DEFAULT);
        item->setColor(ccc3(0, 0, 0));
        item->setTag(g_menuarry[i].tag);
        
        menuitemarry.addObject(item);
    
    }
    
    CCMenu* menu = CCMenu::createWithArray(&menuitemarry);
    //menu->alignItemsVertically();
    menu->alignItemsVerticallyWithPadding(50.0f);
    addChild(menu);
    
    CCSize mysize = getContentSize();
    menu->setPosition(ccp(0,0));
    
    return true;
}

bool MainMenu::ccTouchBegan(CCTouch *touch, CCEvent * pEvent)
{
    CCSize s = getContentSize();
    CCRect rect = CCRectMake(0, 0, s.width, s.height);
    if (rect.containsPoint(convertTouchToNodeSpaceAR(touch)))
    {
        return true;
    }
    return false;
}

void MainMenu::ccTouchEnded(CCTouch *touch, CCEvent * pEvent)
{

}


void MainMenu::menuCallback(CCObject* pSender)
{
    CCMenuItemFont *pMenuItem = (CCMenuItemFont *)pSender;
    //CCLabelTTF *pLabel = (CCLabelTTF *)pMenuItem->getLabel();
    
    HelloWorld *pHello = (HelloWorld *)getParent();
    
    switch (pMenuItem->getTag()) {
        case MENU_TAG_PLAY_STD:
            pHello->EnterGame();
            break;
        case MENU_TAG_PLAY_INFINIT:
            pHello->EnterGame();
            break;
        case MENU_TAG_SCORE:
            pHello->EnterTops();
            break;
        case MENU_TAG_OPTION:
            pHello->EnterOption();
            break;
        case MENU_TAG_ABOUT:
            pHello->ShowAbout(true);
            break;
        default:
            break;
    }
    
}