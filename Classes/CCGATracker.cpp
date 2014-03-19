//
//  CCGATracker.cpp
//  chain
//
//  Created by Kosuke Takami on 2014/03/17.
//
//

#include "CCGATracker.h"
#include "CCGATrackerJni.h"

void CCGATracker::sendView(const char *screen){
    trackViewJNI(screen);
}

void CCGATracker::sendEvent(const char *category, const char *action, const char *label, int value){
    trackEventJNI(category, action, label, value);
}
