#import <UIKit/UIKit.h>


@class RootViewController;
@class GADBannerView;

@interface AppController : NSObject <UIApplicationDelegate> {
    UIWindow *window;
    RootViewController    *viewController;
    GADBannerView *bannerView_;
    UIView* obitop;
    UIView* obibottom;
    BOOL isIphone5;
    Rect getTopObi;
    Rect getBottomObi;
}

@property(nonatomic, assign) RootViewController *viewController;

@end

