//
//  CCGATrackerJni.h
//  chain
//
//  Created by Kosuke Takami on 2014/03/19.
//
//

#ifndef __chain__CCGATrackerJni__
#define __chain__CCGATrackerJni__

#include <iostream>
#include <jni.h>

extern "C"
{
    extern void trackViewJNI(char const *view);
    extern void trackEventJNI(char const *category, char const *action, char const *label, int value);
}

#endif /* defined(__chain__CCGATrackerJni__) */
