//
//  locate.cpp
//  BubbleBreaker
//
//  Created by zlmcd on 13-9-8.
//
//

#include "locate.h"
#include "cocos2d.h"
#include <string>
using namespace cocos2d;
using namespace std;

void LOCATE::init()
{
    ccLanguageType currentLanguageType = CCApplication::sharedApplication()->getCurrentLanguage();
    CCLog("lang=%d",currentLanguageType);
    switch (currentLanguageType)
    {
        case kLanguageChinese:
            CCFileUtils::sharedFileUtils()->addSearchPath("CHN");
            break;
        case kLanguageFrench:
            CCFileUtils::sharedFileUtils()->addSearchPath("FRE");
            break;
        case kLanguageGerman:
            CCFileUtils::sharedFileUtils()->addSearchPath("GER");
            break;
        case kLanguageItalian:
            CCFileUtils::sharedFileUtils()->addSearchPath("ITA");
            break;
        case kLanguageRussian:
            CCFileUtils::sharedFileUtils()->addSearchPath("RUS");
            break;
        case kLanguageSpanish:
            CCFileUtils::sharedFileUtils()->addSearchPath("SPN");
            break;
        case kLanguageKorean:
            CCFileUtils::sharedFileUtils()->addSearchPath("KOR");
            break;
        case kLanguageJapanese:
            CCFileUtils::sharedFileUtils()->addSearchPath("JAP");
            break;
        case kLanguageHungarian:
            CCFileUtils::sharedFileUtils()->addSearchPath("HUN");
            break;
        case kLanguagePortuguese:
            CCFileUtils::sharedFileUtils()->addSearchPath("POR");
            break;
        case kLanguageArabic:
            CCFileUtils::sharedFileUtils()->addSearchPath("ARB");
            break;
        default:
        //kLanguageEnglish:
            CCFileUtils::sharedFileUtils()->addSearchPath("EN");
            break;
    }

}

char *LOCATE::GetString(int i)
{
    const char *xmlName = "str.plist"; //文件名
    CCDictionary* pDict = CCDictionary::createWithContentsOfFile(xmlName);
    CCAssert(pDict != NULL, "");
    
    CCString ckey;
    ckey.initWithFormat("%d",i);
    const CCString *pstr = pDict->valueForKey(ckey.getCString());
    
    return (char *)pstr->getCString();
}