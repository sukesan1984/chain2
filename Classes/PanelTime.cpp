//
//  PanelTime.cpp
//  chain
//
//  Created by Kosuke Takami on 2014/03/09.
//
//

#include "PanelTime.h"

PanelTime& PanelTime::instance(){
    static PanelTime instance;
    return instance;
}

PanelTime::PanelTime(){
    panelRemoveTime = PANEL_REMOVE_TIME;
}

void PanelTime::speedUp(){
    panelRemoveTime /= SPEED_UP_RATE;
}

float PanelTime::getPanelRemoveTime(){
    float removeTime = (float) this->panelRemoveTime / 10000;
    return removeTime;
}

