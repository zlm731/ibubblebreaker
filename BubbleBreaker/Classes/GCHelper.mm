//
//  GCHelper.m
//  BubbleBreaker
//
//  Created by zlmcd on 13-9-15.
//
//

#import "GCHelper.h"
#include "cocos2d.h"
#include "layout.h"
#include "tops.h"
using namespace cocos2d;


@implementation GameKitHelperProtocol
-(void) onScoresSubmitted:(bool)success
{
    NSLog(@"submit %d", success);
}
@end


@implementation GCHelper

@synthesize gameCenterAvailable;

#pragma mark Initialization

static GCHelper *sharedHelper = nil;
+ (GCHelper *) sharedInstance {
    if (!sharedHelper) {
        sharedHelper = [[GCHelper alloc] init];
    }
    return sharedHelper;
}

- (BOOL)isGameCenterAvailable {
    // check for presence of GKLocalPlayer API
    Class gcClass = (NSClassFromString(@"GKLocalPlayer"));
    
    // check if the device is running iOS 4.1 or later
    NSString *reqSysVer =@"4.1";
    NSString *currSysVer = [[UIDevice currentDevice] systemVersion];
    BOOL osVersionSupported = ([currSysVer compare:reqSysVer
                                           options:NSNumericSearch] != NSOrderedAscending);
    
    return (gcClass && osVersionSupported);
}

- (id)init {
    if ((self = [super init])) {
        gameCenterAvailable = [self isGameCenterAvailable];
        if (gameCenterAvailable) {
            NSNotificationCenter *nc =
            [NSNotificationCenter defaultCenter];
            [nc addObserver:self
                   selector:@selector(authenticationChanged)
                       name:GKPlayerAuthenticationDidChangeNotificationName
                     object:nil];
        }
    }
    return self;
}

- (void)authenticationChanged {
    
    if ([GKLocalPlayer localPlayer].isAuthenticated &&!userAuthenticated) {
        NSLog(@"Authentication changed: player authenticated.");
        userAuthenticated = TRUE;
    } else if (![GKLocalPlayer localPlayer].isAuthenticated && userAuthenticated) {
        NSLog(@"Authentication changed: player not authenticated");
        userAuthenticated = FALSE;
    }
}

    
#pragma mark User functions
    
- (void)authenticateLocalUser {
        
        if (!gameCenterAvailable) return;
        
        NSLog(@"Authenticating local user...");
        if ([GKLocalPlayer localPlayer].authenticated == NO) {
            [[GKLocalPlayer localPlayer] authenticateWithCompletionHandler:nil];
        } else {
            NSLog(@"Already authenticated!");
        }
    }

-(void) submitScore:(int64_t)score
           category:(NSString*)category {
    //1: Check if Game Center
    //   features are enabled
    if (!userAuthenticated) {
        NSLog(@"Player not authenticated");
        return;
    }
    
    //2: Create a GKScore object
    GKScore* gkScore =
    [[GKScore alloc]
     initWithCategory:category];
    
    //3: Set the score value
    gkScore.value = score;
    
    //4: Send the score to Game Center
    [gkScore reportScoreWithCompletionHandler:
     ^(NSError* error) {
         
         [self setLastError:error];
         
         BOOL success = (error == nil);
         
         if ([_delegate
              respondsToSelector:
              @selector(onScoresSubmitted:)]) {
             
             [_delegate onScoresSubmitted:success];
         }
     }];
}

@end








@interface GameKitHelper ()
<GKGameCenterControllerDelegate> {
    BOOL _gameCenterFeaturesEnabled;
}
@end


@implementation GameKitHelper

#pragma mark Singleton stuff

+(id) sharedGameKitHelper {
    static GameKitHelper *sharedGameKitHelper;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        sharedGameKitHelper =
        [[GameKitHelper alloc] init];
    });
    return sharedGameKitHelper;
}

#pragma mark Player Authentication

-(void) authenticateLocalPlayer {
    
    GKLocalPlayer* localPlayer =
    [GKLocalPlayer localPlayer];
    
    localPlayer.authenticateHandler =
    ^(UIViewController *viewController,
      NSError *error) {
        
        [self setLastError:error];
        
        //if ([CCDirector sharedDirector].isPaused)
        //    [[CCDirector sharedDirector] resume];
        if (CCDirector::sharedDirector()->isPaused())
        {
            CCDirector::sharedDirector()->resume();
        }
        
        if (localPlayer.authenticated) {
            _gameCenterFeaturesEnabled = YES;
        } else if(viewController) {
            //[[CCDirector sharedDirector] pause];
            CCDirector::sharedDirector()->pause();
            [self presentViewController:viewController];
        } else {
            _gameCenterFeaturesEnabled = NO;
        }
    };
}

#pragma mark Property setters

-(void) setLastError:(NSError*)error {
    _lastError = [error copy];
    if (_lastError) {
        NSLog(@"GameKitHelper ERROR: %@", [[_lastError userInfo]
                                           description]);
    }
}

#pragma mark UIViewController stuff

-(UIViewController*) getRootViewController {
    return [UIApplication
            sharedApplication].keyWindow.rootViewController;
}

-(void)presentViewController:(UIViewController*)vc {
    UIViewController* rootVC = [self getRootViewController];
    [rootVC presentViewController:vc animated:YES
                       completion:nil];
}

-(void) submitScore:(int64_t)score
           category:(NSString*)category {
    //1: Check if Game Center
    //   features are enabled
    if (!_gameCenterFeaturesEnabled) {
        NSLog(@"Player not authenticated");
        return;
    }
    
    //2: Create a GKScore object
    GKScore* gkScore =
    [[GKScore alloc]
     initWithCategory:category];
    
    //3: Set the score value
    gkScore.value = score;
    
    //4: Send the score to Game Center
    [gkScore reportScoreWithCompletionHandler:
     ^(NSError* error) {
         
         [self setLastError:error];
         
         BOOL success = (error == nil);
         
         if ([_delegate
              respondsToSelector:
              @selector(onScoresSubmitted:)]) {
             
             [_delegate onScoresSubmitted:success];
         }
     }];
}


-(void)globalRecordWithBlock
{
    __block NSInteger globalRecord = 0;
    
    [GKLeaderboard loadLeaderboardsWithCompletionHandler:^(NSArray *leaderboards, NSError *error) {
        GKLeaderboard *globalTaps = nil;
        for (GKLeaderboard *lb in leaderboards) if ([lb.category isEqualToString:kHighScoreLeaderboardCategory]) globalTaps = lb;
        
        [globalTaps loadScoresWithCompletionHandler:^(NSArray *scores, NSError *error) {
            if ([scores count] != 0)
            {
                vector<USERINFO> vuserinfo;
                NSMutableArray *userdetail = [[NSMutableArray alloc] init];
                
                GKScore *topScore = nil;
                for (int i = 0; i < [scores count]; i++)
                {
                    topScore = [scores objectAtIndex:i];
                    //CCLog("%lld",topScore.value);
                    //USERINFO info;
                    //info.pname = (char *)topScore.playerID.UTF8String;
                    //info.score = topScore.value;
                    //vuserinfo.push_back(info);
                    [userdetail insertObject:topScore.playerID atIndex:i];
                }
                //[self loadPlayerData:userdetail];
                loadtop(vuserinfo);
                
            }
        }];
    }];
    
}
/*    Whether you received player identifiers by loading the identifiers for the local player’s   friends, or from another Game Center class, you must retrieve the details about that player   from Game Center.    */
- (void) loadPlayerData: (NSArray *) identifiers
{
    [GKPlayer loadPlayersForIdentifiers:identifiers withCompletionHandler:^(NSArray *players, NSError *error) {
        if (error != nil)
        {
            // Handle the error.
        }
        if (players != nil)
        {
            NSLog(@"得到好友的alias成功");
            GKPlayer *friend1 = [players objectAtIndex:0];
            NSLog(@"friedns---alias---%@",friend1.alias);
            NSLog(@"friedns---isFriend---%d",friend1.isFriend);
            NSLog(@"friedns---playerID---%@",friend1.playerID);
        }
    }];
}
@end
