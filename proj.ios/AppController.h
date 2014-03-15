#import <UIKit/UIKit.h>


@class RootViewController;
@class GADBannerView;

@interface AppController : NSObject <UIApplicationDelegate> {
    UIWindow *window;
    RootViewController    *viewController;
    GADBannerView *bannerView_;
    UIView* obi;
}

@property(nonatomic, assign) RootViewController *viewController;

@end

