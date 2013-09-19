//
//  GCHelper.h
//  BubbleBreaker
//
//  Created by zlmcd on 13-9-15.
//
//

#import <Foundation/Foundation.h>

#if 0
@interface HSpriteOC


+(void) testLog;
+(void) hMessageBox:(NSString*)pszMsg title:(NSString*)pszTitle;
@end
#endif


//#import<Foundation/Foundation.h>
#import<GameKit/GameKit.h>

@protocol GameKitHelperProtocol<NSObject>
-(void) onScoresSubmitted:(bool)success;
@end

@interface GameKitHelper : NSObject

@property (nonatomic, assign)
id<GameKitHelperProtocol> delegate;

// This property holds the last known error
// that occured while using the Game Center API's
@property (nonatomic, readonly) NSError* lastError;

+ (id) sharedGameKitHelper;

// Player authentication, info
-(void) authenticateLocalPlayer;
// Scores
-(void) submitScore:(int64_t)score
           category:(NSString*)category;
-(void)globalRecordWithBlock;
-(void)loadPlayerData: (NSArray *)identifiers;
@end



@interface GCHelper : NSObject {
    BOOL gameCenterAvailable;
    BOOL userAuthenticated;
}

@property (assign, readonly) BOOL gameCenterAvailable;
@property (nonatomic, assign) id<GameKitHelperProtocol> delegate;

+ (GCHelper *)sharedInstance;
- (void)authenticateLocalUser;
// Scores
-(void) submitScore:(int64_t)score
           category:(NSString*)category;

-(void) onScoresSubmitted:(bool)success;



@end