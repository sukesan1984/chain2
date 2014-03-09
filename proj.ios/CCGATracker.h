//
//  CCGATracker.h
//  chain
//
//  Created by Kosuke Takami on 2014/03/09.
//
//

//#import <Foundation/Foundation.h>

//@interface CCGATracker : NSObject


class CCGATracker{
public:
    static void sendView(const char *screen);
    static void sendEvent(const char *category, const char *action, const char *label, int value);
};

//@end
