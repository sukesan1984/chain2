//
//  PanelTime.h
//  chain
//
//  Created by Kosuke Takami on 2014/03/09.
//
//

#ifndef __chain__PanelTime__
#define __chain__PanelTime__

#include <iostream>
#include "Const.h"
class PanelTime{
    int panelRemoveTime;
    PanelTime();
    PanelTime(const PanelTime&);
public:
    static PanelTime& instance();
    void speedUp();
    float getPanelRemoveTime();
    void reset();
    
};

#endif /* defined(__chain__PanelTime__) */
