//
//  Header.h
//  BubbleBreaker
//
//  Created by zlmcd on 13-8-25.
//
//

#ifndef BubbleBreaker_Header_h
#define BubbleBreaker_Header_h
///////////////LAYOUT/////////////
//#define LO_FRAME_W 640
//#define LO_FRAME_H 960
#if 0
#define LO_PAD_BALL_X 12
#define LO_PAD_BALL_Y 12
#define LO_PAD_BALL_W 52
#define LO_PAD_BALL_H 52
#endif
#define LO_PAD_BALL_X 10
#define LO_PAD_BALL_Y 10
#define LO_PAD_BALL_W 64
#define LO_PAD_BALL_H 64

#define LO_TOOLBAR_H 80
#define LO_SCORE_Y  (LO_TOOLBAR_H-100)


#define LO_TOP_RECORD_H  64
#define LO_GAMELAYER_WINBAR 160

////////////TAG///////////////
#define TAG_ROOT 1
#define TAG_TITLE  300
#define TAG_MAINMENU 301
#define TAG_BATCHNODE_ID 302
#define TAG_GAMELAYER 303
#define TAG_GAMELAYER_SCORE 304
#define TAG_TOOLBAR 305
#define TAG_TOPS 306
#define TAG_OPTION 307
#define TAG_ABOUT 308
#define TAG_GAMELAYER_PAD 309
#define TAG_GAMELAYER_HIGHEST 310
#define TAG_GAMELAYER_WINBAR 311

//
#define TAG_TOOLBAR_RETURN 306
#define TAG_TOOLBAR_TITLE 307

// font
#define FONT_TYPE_DEFAULT "Helvetica-Bold"

//menu tag
#define MENU_TAG_PLAY_STD     1
#define MENU_TAG_PLAY_INFINIT 2
#define MENU_TAG_SCORE  3
#define MENU_TAG_OPTION 4
#define MENU_TAG_ABOUT 5


// game config
#define BALL_TYPES 5

#define TOP_RANK_NUM 10



//////  strings////////

#define STR_MENU_STANDARD  1
#define STR_MENU_INFINITE  2
#define STR_MENU_TOP       3
#define STR_MENU_OPTION    4
#define STR_MENU_ABOUT     5

#define STR_SCORE_FMT      6
#define STR_HIGHEST_FMT      7
#define STR_MYNAME          8

// fileutil
#define FU_HIESTSCORE "FU_highest_score"
#define FU_CREDIT   "FU_credit"


#define kHighScoreLeaderboardCategory @"com.zlmcd.bubblebreaker.top"

#define SND_CLICKBALL "clickball1.wav"

#endif
