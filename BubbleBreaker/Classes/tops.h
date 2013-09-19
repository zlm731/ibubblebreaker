//
//  tops.h
//  BubbleBreaker
//
//  Created by zlmcd on 13-9-5.
//
//

#ifndef __BubbleBreaker__tops__
#define __BubbleBreaker__tops__

#include <iostream>
#include "cocos2d.h"
#include <vector>


using namespace cocos2d;
using namespace std;



class tops : public CCLayerColor
{
public:
    CREATE_FUNC(tops);
    virtual bool init();

    void insertscore(int);
vector<int> m_vlocalscore;
};

typedef struct _userinfo
{
    char *pimage;
    char *pname;
    int score;
}USERINFO;


class record: public CCLayerColor
{
public:
    CREATE_FUNC(record);
    virtual bool init();
    void setinfo(USERINFO&);
    
};

#include <vector>
using namespace std;



void loadtop(vector<USERINFO>);
void addlocaltop(int);

#endif /* defined(__BubbleBreaker__tops__) */
