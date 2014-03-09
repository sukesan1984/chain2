#import <UIKit/UIKit.h>


@class RootViewController;
@class GADBannerView;

@interface AppController : NSObject <UIApplicationDelegate> {
    UIWindow *window;
    RootViewController    *viewController;
    GADBannerView *bannerView_;
}

@property(nonatomic, assign) RootViewController *viewController;

@end

