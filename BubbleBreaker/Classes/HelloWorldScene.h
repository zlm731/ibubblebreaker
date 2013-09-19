#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
using namespace cocos2d;
using namespace std;

const int SCENE_OPEN = 1;
const int SCENE_GAME = 2;
const int SCENE_SCORE = 3;

const int POS_OUT = 1;
const int POS_IN = 2;



class HelloWorld : public cocos2d::CCLayerColor
{
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();

    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();

    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(HelloWorld);
    virtual void onEnter();
    virtual void onExit();
public:
    void newround();
    void EnterOpen();
    void EnterGame();
    void EnterTops();
    void EnterOption();
    void ShowAbout(bool bEnable);
    
    CCPoint titlepos(int);
    CCPoint mainmenupos(int);
    CCPoint toolbarpos(int);
    CCPoint gamelayerpos(int);
    CCPoint topspos(int);
    CCPoint optionpos(int);
    CCPoint aboutpos(int);
    
private:
    int m_scene;
};

#endif // __HELLOWORLD_SCENE_H__
