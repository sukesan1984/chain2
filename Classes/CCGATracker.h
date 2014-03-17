//
//  CCGATracker.h
//  chain
//
//  Created by Kosuke Takami on 2014/03/17.
//
//

#ifndef __chain__CCGATracker__
#define __chain__CCGATracker__

#include <iostream>

class CCGATracker{
public:
    static void sendView(const char *screen);
    static void sendEvent(const char *category, const char *action, const char *label, int value);
};

#endif /* defined(__chain__CCGATracker__) */
